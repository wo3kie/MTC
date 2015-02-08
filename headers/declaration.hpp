#ifndef __SYNTAX_DECLARATION_HPP__
#define __SYNTAX_DECLARATION_HPP__

#include "headers/instruction.hpp"
#include "headers/types_controller.hpp"
#include "headers/variables_controller.hpp"

#include <loki/Visitor.h>

namespace Syntax
{

class Expression;
class IType;

class Type
    : public Loki::BaseVisitable<>
{        
public:
    LOKI_DEFINE_VISITABLE()
    
    virtual ~Type(){}
    
    virtual std::string getTypeName()const = 0;
};

class Declaration
	: public IInstruction
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	Declaration(
		boost::shared_ptr< Type > _type,
		std::string const & _variable,
		boost::shared_ptr< Expression > _initializingExpression );
		
	Declaration(
		boost::shared_ptr< Type > _type,
		std::string const & _variable );
	
	/* compiler's generated destructor is fine */
    
    boost::shared_ptr< Type > getType() const
    {
        return m_type;
    }
    
	std::string getVariableName() const;
	void setVariableHandler( Semantics::VariablesController::Handler _handler );
	Semantics::VariablesController::Handler getVariableHandler() const;
	
	boost::shared_ptr< Expression > getInitializationChild();

protected:
	boost::shared_ptr< Type > const m_type;
    Semantics::TypesController::Handler m_typeHandler;

	std::string const m_variableName;
	Semantics::VariablesController::Handler m_variableHandler;
	
	boost::shared_ptr< Expression > const m_initializingExpression;
};

class BuildInType
    : public Type
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )

    static boost::shared_ptr< Type > create( std::string const & _typeName )
    {
        return boost::shared_ptr< Type >( new BuildInType( _typeName ) );
    }
    
    std::string getTypeName()const
    {
        return m_typeName;
    }
    
private:
    BuildInType( std::string const & _typeName )
        : m_typeName( _typeName )
    {
    }
    
private:
    std::string const m_typeName;
};

class PointerType
    : public Type
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )

    static boost::shared_ptr< Type > create( boost::shared_ptr< Type > _type )
    {
        return boost::shared_ptr< Type >( new PointerType( _type ) );
    }
    
    boost::shared_ptr< Type > getPointedType()const
    {
        return m_type;
    }
    
    std::string getTypeName()const
    {
        return m_type->getTypeName();
    }
    
private:
    PointerType( boost::shared_ptr< Type > _type )
        : m_type( _type )
    {
    }
    
private:
    boost::shared_ptr< Type > m_type;
};

}

#endif
