#include "headers/ph.hpp"

#include "headers/type.hpp"
#include "headers/syntax_tree_node.hpp"

namespace Semantics
{

Type::~Type()
{
}

boost::shared_ptr< Type > Type::getBasicType()
{
    return getSelf();
}

boost::shared_ptr< Type >
Type::getPointedType()
{
    return getSelf();
}

boost::shared_ptr< Type >
Type::removePointerType()
{
    return getSelf(); 
}

boost::shared_ptr< Type > AnyType::create()
{
    return boost::shared_ptr< Type >( new AnyType );
}

boost::shared_ptr< Type >
AnyType::getSelf()
{
    return boost::shared_ptr< Type >( new AnyType );
}

boost::shared_ptr< Type >
NullType::create()
{
    return boost::shared_ptr< Type >();
}

boost::shared_ptr< Type >
NullType::getSelf()
{
    return boost::shared_ptr< Type >();
}

boost::shared_ptr< Type >
BuildInType::create( std::string const & _typeName )
{
    return boost::shared_ptr< Type >( new BuildInType( _typeName ) );
}

boost::shared_ptr< Type > 
BuildInType::getSelf()
{
    return boost::shared_ptr< Type >( new BuildInType( m_typeName ) );
}

std::string 
BuildInType::getTypeName() const
{
    return m_typeName;
}

//void
//BuildInType::setHandler( Semantics::TypesController::Handler _handler )
//{
//    m_handler = _handler;
//}
//
//Semantics::TypesController::Handler
//BuildInType::getTypeHandler() const
//{
//    return m_handler;
//}
    
BuildInType::BuildInType( std::string const & _typeName )
    : m_typeName( _typeName )
{
}

boost::shared_ptr< Type >
PointerType::create( boost::shared_ptr< Type > _type )
{
    return boost::shared_ptr< Type >( new PointerType( _type ) );
}

boost::shared_ptr< Type >
PointerType::getSelf()
{
    return boost::shared_ptr< Type >( new PointerType( m_pointedType ) );
}

boost::shared_ptr< Type >
PointerType::getBasicType()
{
    return m_pointedType->getBasicType();
}

boost::shared_ptr< Type >
PointerType::getPointedType() 
{
    return m_pointedType;
}

boost::shared_ptr< Type >
PointerType::removePointerType()
{
    return m_pointedType;
}

PointerType::PointerType( boost::shared_ptr< Type > _type )
    : m_pointedType( _type )
{
}

}
