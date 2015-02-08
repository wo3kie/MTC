#ifndef __SEMANTICS_SYMBOLS_TABLE_HPP__
#define __SEMANTICS_SYMBOLS_TABLE_HPP__

#include "headers/equal_types_multimethod.hpp"
#include "headers/precondition.hpp"
#include "headers/scope.hpp"

#include <vector>

namespace Semantics
{

class FunctionData;

template< typename _Data  >
class SymbolsTable
{
public:
 	class Handler
 	{
 	public:
 		Handler();
		explicit Handler( int _handler );
		
		/* constructor generated copy constructor is fine */
		/* constructor generated destructor is fine */
		/* constructor generated operator= is fine */
		
		bool operator== ( Handler const & _typeHandler ) const;
		bool operator!= ( Handler const & _typeHandler ) const;
		
		void setHandler( int _handler );
		
		bool isNull() const;
		
		int getRawHandler() const;
		
		static const int EmptyHandlerValue = -1;
		
	protected:
		int m_handler;
	};

public:
	typedef typename std::vector< _Data >::iterator iterator;
	typedef typename std::vector< _Data >::const_iterator const_iterator;

public:
	/* constructor generated copy constructor is fine */
	/* constructor generated destructor is fine */
 	/* constructor generated operator= is fine */
 		
 	iterator begin(){ return m_datas.begin(); }
 	const_iterator begin() const { return m_datas.begin(); }
 	
 	iterator end(){ return m_datas.end(); }
 	const_iterator end() const { return m_datas.end(); }
 		
 	Handler insert( _Data const & _data );
 	Handler getHandler( typename _Data::SymbolDataKey const & _key, Scope const & _scope ) const;
 	_Data getData( Handler _handler ) const;

private:
	typename std::vector< _Data >::const_iterator
	reverse_find( typename _Data::SymbolDataKey const & _key, Scope const & _scope ) const;

private:
	std::vector< _Data > m_datas;
};

template< typename _Data >
typename SymbolsTable< _Data >::Handler
SymbolsTable< _Data >::insert( _Data const & _data )
{
 	m_datas.push_back( _data );
 	return Handler( m_datas.size() - 1 );
}

template< typename _Data >
typename SymbolsTable< _Data >::Handler
SymbolsTable< _Data >::getHandler(
	typename _Data::SymbolDataKey const & _key,
	Scope const & _scope
) const
{	
	typename std::vector< _Data >::const_iterator const matched = this->reverse_find( _key, _scope );
	
	if ( matched == m_datas.end() )
 	{
 		return Handler();
 	}
 	else
 	{
 		return Handler( matched - m_datas.begin() );
 	}
}

template< typename _Data >
typename std::vector< _Data >::const_iterator
SymbolsTable< _Data >::reverse_find(
	typename _Data::SymbolDataKey const & _key,
	Scope const & _scope
) const
{
 	for ( typename std::vector< _Data >::const_reverse_iterator
 			current = m_datas.rbegin(),
 			end = m_datas.rend()
 		; current != end
 		; ++current
 	)
 	{
 		if ( current->getKey() == _key && current->getScope() == _scope )
 		{
 			typename std::vector< _Data >::const_iterator result = current.base();
 			return --result;
 		}
 	}
 
 	return m_datas.end();
}

template< typename _Data >
_Data
SymbolsTable< _Data >::getData(
	typename SymbolsTable< _Data >::Handler _handler
) const
{
	PRECONDITION1( ! _handler.isNull() )

	return m_datas[ _handler.getRawHandler() ];
}

template< typename _Data >
SymbolsTable< _Data >::Handler::Handler()
	: m_handler( EmptyHandlerValue )
{
}

template< typename _Data >
SymbolsTable< _Data >::Handler::Handler( int _handler )
	: m_handler( _handler )
{
}

template< typename _Data >
bool
SymbolsTable< _Data >::Handler::operator== (
	SymbolsTable< _Data >::Handler const & _handler
) const
{
	return m_handler == _handler.m_handler;
}

template< typename _Data >
bool
SymbolsTable< _Data >::Handler::operator!= (
	SymbolsTable< _Data >::Handler const & _handler
) const
{
	return ! (*this == _handler);
}

template< typename _Data >
void
SymbolsTable< _Data >::Handler::setHandler ( int _handler )
{
	m_handler = _handler;
}

template< typename _Data >
bool
SymbolsTable< _Data >::Handler::isNull () const
{
	return m_handler == EmptyHandlerValue;
}

template< typename _Data >
int
SymbolsTable< _Data >::Handler::getRawHandler() const
{
	return m_handler;
}

template< typename _Container, typename _Key >
bool
isSymbolAlreadyDefined(
	_Container const & _container,
	_Key const & _key,
	Scope _scope
)
{
	return ! _container.getHandler( _key, _scope ).isNull();
}

}

#endif
