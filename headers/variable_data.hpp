#ifndef __SEMANTICS_VARIABLE_DATA_HPP__
#define __SEMANTICS_VARIABLE_DATA_HPP__

#include "headers/symbol_data.hpp"
#include "headers/types_controller.hpp"

namespace Semantics
{

struct VariableType
{
	enum Enum
	{
		Variable,
		Parameter
	};

private:
	VariableType();
};

struct AccessPolicy
{
	enum Enum
	{
		ReadOnly,
		ReadWrite
	};

private:
	AccessPolicy();
};

class VariableData
	: public SymbolData< std::string >
{
public:
	VariableData(
		std::string const & _variableName,
		TypesController::Handler _type,
		Scope _scope,
		VariableType::Enum _variableType,
        AccessPolicy::Enum _accessPolicy = AccessPolicy::ReadWrite );
		
	/* compiler's generated assignment constructor is fine */
	/* compiler's generated destructor is fine */
	/* compiler's generated operator= is fine */
	
	void setType( TypesController::Handler _type );
	TypesController::Handler getType() const;
	
	void setStackOffset( int _offset );
	int getStackOffset() const;
	
	VariableType::Enum getVariableType() const;
    AccessPolicy::Enum getAccessPolicy() const;
	
private:
	TypesController::Handler m_type;
	int m_stackOffset;
	VariableType::Enum m_variableType;
    AccessPolicy::Enum m_accessPolicy;
};

}

#endif
