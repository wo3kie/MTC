#ifndef __SYNTAX_TREE_LIST_HPP__
#define __SYNTAX_TREE_LIST_HPP__

#include "headers/syntax_tree_node.hpp"

#include <loki/static_check.h>
#include <loki/Typelist.h>

#include <boost/shared_ptr.hpp>

#include <algorithm>
#include <deque>

namespace Syntax
{

template< typename _Element >
class SyntaxTreeList
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )

public:
	SyntaxTreeList(
		boost::shared_ptr< SyntaxTreeList > _list,
		boost::shared_ptr< _Element > _element );

	explicit SyntaxTreeList(
		boost::shared_ptr< _Element > _element );

	SyntaxTreeList();
	
	boost::shared_ptr< SyntaxTreeList > getChildList();
	boost::shared_ptr< _Element > getChild();

protected:
	boost::shared_ptr< SyntaxTreeList > const m_list;
	boost::shared_ptr< _Element > const m_element;
};

template< typename _Element >
SyntaxTreeList< _Element >::SyntaxTreeList(
	boost::shared_ptr< SyntaxTreeList > _list,
	boost::shared_ptr< _Element > _element
)
	: m_list( _list )
	, m_element( _element )
{
	POSTCONDITION2( m_list, m_element )
}

template< typename _Element >
SyntaxTreeList< _Element >::SyntaxTreeList(
	boost::shared_ptr< _Element > _element
)
	: m_list( boost::shared_ptr< SyntaxTreeList >() )
	, m_element( _element )
{
	POSTCONDITION1( m_element )
}

template< typename _Element >
SyntaxTreeList< _Element >::SyntaxTreeList()
	: m_list( boost::shared_ptr< SyntaxTreeList >() )
	, m_element( boost::shared_ptr< _Element >() )
{
}

template< typename _Element >
boost::shared_ptr< SyntaxTreeList< _Element > >
SyntaxTreeList< _Element >::getChildList()
{
	return m_list;
}

template< typename _Element >
boost::shared_ptr< _Element >
SyntaxTreeList< _Element >::getChild()
{
	return m_element;
}

template< typename _Element >
inline std::vector< boost::shared_ptr< _Element > >
convertTreeListToVector( boost::shared_ptr< SyntaxTreeList< _Element > > _root )
{
	std::vector< boost::shared_ptr< _Element > > result;
	std::deque< boost::shared_ptr< _Element > > resultTemp;
	
	while( _root )
	{
		resultTemp.push_front( _root->getChild() );
		_root = _root->getChildList();
	}
	
	result.resize( resultTemp.size() );
	std::copy( resultTemp.begin(), resultTemp.end(), result.begin() );
	
	return result;
}

}

#endif
