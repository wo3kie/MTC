#ifndef __TYPES_MAPPING_HPP__
#define	__TYPES_MAPPING_HPP__

#include "headers/equal_types_multimethod.hpp"
#include "headers/precondition.hpp"
#include "headers/type.hpp"

#include <boost/optional.hpp>

namespace Semantics
{

struct TypesMappingPolicy
{
    typedef
        bool ( TypesMappingPolicy ::* TypeMappingPredicate )(
            boost::shared_ptr< Type >,
            boost::shared_ptr< Type >,
            boost::shared_ptr< Type >,
            boost::shared_ptr< Type >
        ) const;
    
    bool areEqual(
        boost::shared_ptr< Type > _lhs,
        boost::shared_ptr< Type > _lhsPattern,
        boost::shared_ptr< Type > _rhs,
        boost::shared_ptr< Type > _rhsPattern    
    ) const
    {
        return equal( * _lhs, * _lhsPattern ) && equal( * _rhs, * _rhsPattern );
    }
    
    bool areCorresponding(
        boost::shared_ptr< Type > _lhs,
        boost::shared_ptr< Type > ,
        boost::shared_ptr< Type > _rhs,
        boost::shared_ptr< Type > 
    ) const
    {
        return equal( * _lhs, * _rhs );
    }
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class TypePlaceholder;

class TypeLazyExpression
{
public:
    virtual ~TypeLazyExpression(){}
    
    static boost::shared_ptr< TypeLazyExpression > create(
        boost::shared_ptr< TypeLazyExpression > _typeLazyExpression
    )
    {
        PRECONDITION1( _typeLazyExpression );
        return boost::shared_ptr< TypeLazyExpression >( _typeLazyExpression );
    }

    boost::shared_ptr< TypeLazyExpression > getType() const
    {
        return m_typeLazyExpression;
    }
    
    virtual boost::shared_ptr< Type > evaluate(
        boost::shared_ptr< Type > _left,
        boost::shared_ptr< Type > _right
    ) const = 0;
    
protected:
    TypeLazyExpression()
    {
    }
    
    TypeLazyExpression( boost::shared_ptr< TypeLazyExpression > _typeLazyExpression )
        : m_typeLazyExpression( _typeLazyExpression )
    {
        PRECONDITION1( _typeLazyExpression );
    }
    
private:
    boost::shared_ptr< TypeLazyExpression > m_typeLazyExpression;
};

struct LazyType : public TypeLazyExpression
{
    static boost::shared_ptr< LazyType > create( boost::shared_ptr< Type > _type )
    {
        return boost::shared_ptr< LazyType >( new LazyType( _type ) );
    }
        
    boost::shared_ptr< Type > evaluate(
        boost::shared_ptr< Type >,
        boost::shared_ptr< Type >
    ) const
    {
        return m_type;
    }
    
private:
    LazyType( boost::shared_ptr< Type > _type )
        : m_type( _type )
    {
        PRECONDITION1( _type );
    }    
    
private:
    boost::shared_ptr< Type > m_type;
};

struct TypePlaceholder : public TypeLazyExpression
{
    TypePlaceholder()
    {
    }
};
    
struct _1 : public TypePlaceholder
{
    static boost::shared_ptr< TypePlaceholder > create()
    {
        return boost::shared_ptr< TypePlaceholder >( new _1 );
    }
    
    boost::shared_ptr< Type > evaluate(
        boost::shared_ptr< Type > _first,
        boost::shared_ptr< Type > _second
    ) const
    {
        return _first;
    }
};

struct _2 : public TypePlaceholder
{
    static boost::shared_ptr< TypePlaceholder > create()
    {
        return boost::shared_ptr< TypePlaceholder >( new _2 );
    }
        
    boost::shared_ptr< Type > evaluate(
        boost::shared_ptr< Type > _first,
        boost::shared_ptr< Type > _second
    ) const
    {
        PRECONDITION2( _first, _second );
        return _second;
    }
};  
    
struct AddPointer : public TypeLazyExpression
{
public:
    static boost::shared_ptr< TypeLazyExpression > create(
        boost::shared_ptr< TypeLazyExpression > _typeLazyExpression
    )
    {
        PRECONDITION1( _typeLazyExpression );
        return boost::shared_ptr< TypeLazyExpression >( new AddPointer( _typeLazyExpression ) );
    }
    
    boost::shared_ptr< Type > evaluate(
        boost::shared_ptr< Type > _left,
        boost::shared_ptr< Type > _right
    ) const
    {
        return PointerType::create( getType()->evaluate( _left, _right ) );
    }
    
private:
    AddPointer( boost::shared_ptr<TypeLazyExpression > _typeLazyExpression )
        : TypeLazyExpression( _typeLazyExpression )
    {
    }
};

struct RemovePointer : public TypeLazyExpression
{
public:
    static boost::shared_ptr< TypeLazyExpression > create(
        boost::shared_ptr< TypeLazyExpression > _typeLazyExpression
    )
    {
        return boost::shared_ptr< TypeLazyExpression >( new RemovePointer( _typeLazyExpression ) );
    }
    
    boost::shared_ptr< Type > evaluate(
        boost::shared_ptr< Type > _left,
        boost::shared_ptr< Type > _right
    ) const
    {
        return getType()->evaluate( _left, _right )->removePointerType();
    }
    
private:
    RemovePointer( boost::shared_ptr<TypeLazyExpression > _typeLazyExpression )
        : TypeLazyExpression( _typeLazyExpression )
    {
    }
};

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
class TypesMappingInfo
{
public:
    TypesMappingInfo();
    
    TypesMappingInfo(
        TypesMappingPolicy::TypeMappingPredicate _typeMappingPredicate,
        boost::shared_ptr< TypeLazyExpression > _resultType
    );
    
    TypesMappingPolicy::TypeMappingPredicate getTypeMappingPredicate() const;
    boost::shared_ptr< TypeLazyExpression > getTypeLazyExpression() const;
    
private:
    TypesMappingPolicy::TypeMappingPredicate m_typeMappingPredicate;
    boost::shared_ptr< TypeLazyExpression > m_typeLazyExpression;
};
    
class TypesMapping
{
    typedef boost::shared_ptr< Type > TypeSPtr;
    typedef std::map< std::pair< TypeSPtr, TypeSPtr >, TypesMappingInfo > TypesMappingImpl;

public:
    TypesMapping()
    {
    }
    
    // for unary operators
    void addMappingRule(
        boost::shared_ptr< Type > _type,
        boost::shared_ptr< TypeLazyExpression > _typeLazyExpression,
        TypesMappingPolicy::TypeMappingPredicate _typeMappingPredicate = & TypesMappingPolicy::areEqual
    );
    
    // for unary operators
    void addMappingRule(
        boost::shared_ptr< Type > _lhs,
        boost::shared_ptr< Type > _rhs,
        boost::shared_ptr< TypeLazyExpression > _typeLazyExpression,
        TypesMappingPolicy::TypeMappingPredicate _typeMappingPredicate = & TypesMappingPolicy::areCorresponding
    );
    
    // for unary operators
    boost::optional< TypesMappingInfo > isMappable(
        boost::shared_ptr< Type > _type
    ) const;
    
    // for binary operators
    boost::optional< TypesMappingInfo > isMappable(
        boost::shared_ptr< Type > _lhs,
        boost::shared_ptr< Type > _rhs
    ) const;
    
    TypesMappingImpl m_typesMappingRules;
};

template< typename _T >    
struct TypeMappingImpl
{
    static Semantics::TypesMapping m_typeMapping;
};
    
template< typename _T >
Semantics::TypesMapping TypeMappingImpl< _T >::m_typeMapping;

}

#endif
