#include "headers/ph.hpp"

#include "headers/types_mapping.hpp"

#include <boost/foreach.hpp>

namespace Semantics
{
        
TypesMappingInfo::TypesMappingInfo()
    : m_typeMappingPredicate( 0 )
{
}
   
TypesMappingInfo::TypesMappingInfo(
    TypesMappingPolicy::TypeMappingPredicate _typeMappingPredicate,
    boost::shared_ptr< TypeLazyExpression > _typeLazyExpression
)
    : m_typeMappingPredicate( _typeMappingPredicate )
    , m_typeLazyExpression( _typeLazyExpression )
{
}

TypesMappingPolicy::TypeMappingPredicate
TypesMappingInfo::getTypeMappingPredicate() const
{
    return m_typeMappingPredicate;
}
    
boost::shared_ptr< TypeLazyExpression >
TypesMappingInfo::getTypeLazyExpression() const
{
    return m_typeLazyExpression;
}

void TypesMapping::addMappingRule(
    boost::shared_ptr< Type > _type,
    boost::shared_ptr< TypeLazyExpression > _typeLazyExpression,
    TypesMappingPolicy::TypeMappingPredicate _typeMappingPredicate
)
{
    addMappingRule( _type, AnyType::create(), _typeLazyExpression, _typeMappingPredicate );
}

// for unary operators
void TypesMapping::addMappingRule(
    boost::shared_ptr< Type > _lhs,
    boost::shared_ptr< Type > _rhs,
    boost::shared_ptr< TypeLazyExpression > _typeLazyExpression,
    TypesMappingPolicy::TypeMappingPredicate _typeMappingPredicate
)
{
    m_typesMappingRules[ std::make_pair( _lhs, _rhs ) ]
        = TypesMappingInfo( _typeMappingPredicate, _typeLazyExpression );
}

boost::optional< TypesMappingInfo > TypesMapping::isMappable(
    boost::shared_ptr< Type > _type
) const
{
    return isMappable( _type, AnyType::create() );
}

boost::optional< TypesMappingInfo > TypesMapping::isMappable(
    boost::shared_ptr< Type > _lhs,
    boost::shared_ptr< Type > _rhs
) const
{
    PRECONDITION2( _lhs, _rhs );
    
    typedef
        std::pair<
            std::pair< TypesMapping::TypeSPtr, TypesMapping::TypeSPtr >,
            TypesMappingInfo
        >
    IteratedObjectType;
    
    BOOST_FOREACH( IteratedObjectType current, m_typesMappingRules )
    {
        if( ( TypesMappingPolicy() .* current.second.getTypeMappingPredicate() )
                ( _lhs, current.first.first, _rhs, current.first.second )
        )
            return boost::optional< TypesMappingInfo >( current.second );
    }
    
    return boost::optional< TypesMappingInfo >();
}
    
}
