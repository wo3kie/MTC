#ifndef __SEMANTICS_SYMBOL_DATA_HPP__
#define __SEMANTICS_SYMBOL_DATA_HPP__

#include "headers/postcondition.hpp"
#include "headers/scope.hpp"

#include <string>

namespace Semantics
{

template < typename _Key >
class SymbolData
{
public:
    typedef _Key SymbolDataKey;

public:
	explicit SymbolData(
		_Key const & _key,
		Scope _scope
    )
    	: m_key( _key )
        , m_scope( _scope )
    {
    }
    
    virtual ~SymbolData(){}
	
    virtual _Key getKey() const{ return m_key; }
	
    Scope & getScope(){ return m_scope; }
    Scope const & getScope() const{ return m_scope; }

private:
	_Key m_key;
	Scope m_scope;
};

}

#endif
