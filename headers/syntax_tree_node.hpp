#ifndef __SYNTAX_SYNTAX_TREE_NODE_HPP__
#define __SYNTAX_SYNTAX_TREE_NODE_HPP__

#include "headers/postcondition.hpp"
#include "headers/types_controller.hpp"

#include <loki/Visitor.h>

#include <boost/noncopyable.hpp>

namespace Syntax
{

class ISyntaxTreeNode
	: public boost::noncopyable
	, public Loki::BaseVisitable<>
{
public:
	LOKI_DEFINE_VISITABLE()
	
	virtual ~ISyntaxTreeNode() {}
	
	void setTypeHandler( Semantics::TypesController::Handler _handler )
		{ m_handler = _handler; }//POSTCONDITION1( ! _handler.isNull() ); }
	
	Semantics::TypesController::Handler getTypeHandler() const
		{ return m_handler; }

private:
	Semantics::TypesController::Handler m_handler;
};

}

#endif
