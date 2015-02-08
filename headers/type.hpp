#ifndef __TYPE_HPP__
#define	__TYPE_HPP__

//#include "headers/syntax_tree_node.hpp"

namespace Semantics
{

struct Type
//	: public ISyntaxTreeNode
{
    virtual ~Type();
    
    virtual boost::shared_ptr< Type > getSelf() = 0;
    
    virtual boost::shared_ptr< Type > getBasicType();
    virtual boost::shared_ptr< Type > getPointedType();
    virtual boost::shared_ptr< Type > removePointerType();
    
    virtual std::string getTypeName() const{ return "";};
};

struct AnyType : public Type {
    static boost::shared_ptr< Type > create();
    
    virtual boost::shared_ptr< Type > getSelf();
};

struct BasicType : public Type
{
};

struct NullType : public BasicType
{
    static boost::shared_ptr< Type > create();
    
    virtual boost::shared_ptr< Type > getSelf();
};

class BuildInType : public BasicType
{
public:
    static boost::shared_ptr< Type > create( std::string const & _typeName );

    virtual boost::shared_ptr< Type > getSelf();
    
    std::string getTypeName() const;
    
    //void setHandler( Semantics::TypesController::Handler _handler );
    
    //Semantics::TypesController::Handler getTypeHandler() const;
    
private:
    BuildInType( std::string const & _typeName );
    
private:
    std::string m_typeName;
    //Semantics::TypesController::Handler m_handler;
};

struct CompoundType : public Type
{  
};

struct PointerType : public CompoundType
{
public:
    static boost::shared_ptr< Type > create( boost::shared_ptr< Type > _type );
    
    virtual boost::shared_ptr< Type > getSelf();
    
    virtual boost::shared_ptr< Type > getBasicType();
    
    virtual boost::shared_ptr< Type > getPointedType();
    
    virtual boost::shared_ptr< Type > removePointerType();
    
    virtual std::string getTypeName()const
    {
        return m_pointedType->getTypeName() + std::string( " ^" );
    }
    
private:
    PointerType( boost::shared_ptr< Type > _type );
    
private:
    boost::shared_ptr< Type > m_pointedType;
};

}

#endif

