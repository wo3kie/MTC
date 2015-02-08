#include "headers/ph.hpp"

#include "headers/scope.hpp"

namespace Semantics
{

Scope
Scope::createGlobalScope()
{
	Scope scope;
	scope.m_namespace = Global;
	scope.m_function = Global;
	scope.m_local = Null;
	
	return scope;
}

Scope::Scope()
	: m_namespace( Global )
	, m_function( Global )
	, m_local( Null )
{
}

bool
Scope::operator== ( Scope const & _scope ) const
{
	return
		   m_namespace == _scope.m_namespace
		&& m_function == _scope.m_function
		&& m_local == _scope.m_local;
}

bool
Scope::operator!= ( Scope const & _scope ) const
{
	return ! (*this == _scope);
}

void
Scope::enterFunction()
{
	++m_function;
}

void
Scope::leaveFunction()
{
	//--m_global;
}

}
