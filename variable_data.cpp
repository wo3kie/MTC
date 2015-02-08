#include "headers/ph.hpp"

#include "headers/variable_data.hpp"

#include "headers/types_controller.hpp"

#include "headers/postcondition.hpp"
#include "headers/precondition.hpp"

namespace Semantics
{

VariableData::VariableData(
	std::string const & _name,
	TypesController::Handler _type,
	Scope _scope,
	VariableType::Enum _variableType,
    AccessPolicy::Enum _accessPolicy 
)
	: SymbolData< std::string >( _name, _scope )
	, m_type( _type )
	, m_stackOffset( 0 )
	, m_variableType( _variableType )
    , m_accessPolicy( _accessPolicy )
{
	POSTCONDITION1( ! getKey().empty() )
}

void
VariableData::setType( TypesController::Handler _type )
{
	m_type = _type;
}

TypesController::Handler
VariableData::getType() const
{
	return m_type;
}

void
VariableData::setStackOffset( int _offset )
{
	m_stackOffset = _offset;
}

int
VariableData::getStackOffset() const
{
	return m_stackOffset;
}

VariableType::Enum
VariableData::getVariableType() const
{
	return m_variableType;
}

AccessPolicy::Enum
VariableData::getAccessPolicy() const
{
    return m_accessPolicy;
}

}
