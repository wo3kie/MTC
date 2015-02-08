#ifndef __SEMANTICS_SCOPE_HPP__
#define __SEMANTICS_SCOPE_HPP__

namespace Semantics
{

class Scope
{
friend class VariablesController;

public:
	Scope();
	
	static Scope createGlobalScope();
	
	bool operator== ( Scope const & _scope ) const;
	bool operator!= ( Scope const & _scope ) const;

	void enterFunction();
	void leaveFunction();
	
	static const int Global = 0;
	static const int Null = -1;

protected:
	int m_namespace;
	int m_function;
	int m_local;
};

}

#endif
