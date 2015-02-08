#ifndef __SEMANTICS_SEMANTIC_ANALYSIS_VISITOR_HPP__
#define __SEMANTICS_SEMANTIC_ANALYSIS_VISITOR_HPP__

#include "headers/functions_controller.hpp"
#include "headers/strings_controller.hpp"
#include "headers/types_controller.hpp"
#include "headers/variables_controller.hpp"

#include "headers/errors_detector.hpp"
#include "headers/scope.hpp"

#include "headers/assignment_expression.hpp"
#include "headers/break_instruction.hpp"
#include "headers/compound_instruction.hpp"
#include "headers/continue_instruction.hpp"
#include "headers/declaration.hpp"
#include "headers/dereference.hpp"
#include "headers/do_while_instruction.hpp"
#include "headers/expression.hpp"
#include "headers/expressions_list.hpp"
#include "headers/factor.hpp"
#include "headers/for_instruction.hpp"
#include "headers/function.hpp"
#include "headers/function_call.hpp"
#include "headers/functions_list.hpp"
#include "headers/get_address.hpp"
#include "headers/if_instruction.hpp"
#include "headers/instructions_list.hpp"
#include "headers/null.hpp"
#include "headers/number.hpp"
#include "headers/parameter.hpp"
#include "headers/parameters_list.hpp"
#include "headers/parenthesis.hpp"
#include "headers/program.hpp"
#include "headers/return_instruction.hpp"
#include "headers/simple_expression.hpp"
#include "headers/string.hpp"
#include "headers/type.hpp"
#include "headers/unary_factor.hpp"
#include "headers/unit.hpp"
#include "headers/variable.hpp"
#include "headers/while_instruction.hpp"

#include <loki/Visitor.h>

#include <stack>

namespace Semantics
{

using namespace Syntax;

class SemanticAnalysisVisitor
	: public Loki::BaseVisitor
	, public Loki::Visitor< AssignmentExpression >
	, public Loki::Visitor< BreakInstruction >
	, public Loki::Visitor< Syntax::BuildInType >
	, public Loki::Visitor< CompoundInstruction >
	, public Loki::Visitor< ContinueInstruction >
	, public Loki::Visitor< Declaration >
	, public Loki::Visitor< Dereference >
	, public Loki::Visitor< DoWhileInstruction >
	, public Loki::Visitor< Expression >
	, public Loki::Visitor< ExpressionsList >
	, public Loki::Visitor< Factor >
	, public Loki::Visitor< ForInstruction >
	, public Loki::Visitor< Function >
	, public Loki::Visitor< FunctionCall >
	, public Loki::Visitor< FunctionsList >
	, public Loki::Visitor< GetAddress >
	, public Loki::Visitor< IfInstruction >
	, public Loki::Visitor< InstructionsList >
	, public Loki::Visitor< Null >
	, public Loki::Visitor< Number >
	, public Loki::Visitor< Parameter >
	, public Loki::Visitor< ParametersList >
	, public Loki::Visitor< Parenthesis >
	, public Loki::Visitor< Syntax::PointerType >
	, public Loki::Visitor< Program >
	, public Loki::Visitor< ReturnInstruction >
	, public Loki::Visitor< SimpleExpression >
	, public Loki::Visitor< String >
	, public Loki::Visitor< UnaryFactor >
	, public Loki::Visitor< Variable >
	, public Loki::Visitor< WhileInstruction >
	, protected ErrorsDetector
{
public:
	SemanticAnalysisVisitor(
		FunctionsController & _functionsController,
		StringsController & _stringsController,
		TypesController & _typesController,
		VariablesController & _variablesController
	);
	
	/*default visitor*/ void Visit( ISyntaxTreeNode & _visitable );

	void Visit ( AssignmentExpression & _visitable );
	void Visit ( BreakInstruction & _visitable );
	void Visit ( Syntax::BuildInType & _visitable );
	void Visit ( CompoundInstruction & _visitable );
	void Visit ( ContinueInstruction & _visitable );
	void Visit ( Declaration & _visitable );
	void Visit ( Dereference & _visitable );
	void Visit ( DoWhileInstruction & _visitable );
	void Visit ( Expression & _visitable );
	void Visit ( ExpressionsList & _visitable );
	void Visit ( Factor & _visitable );
	void Visit ( ForInstruction & _visitable );
	void Visit ( Function & _visitable );
	void Visit ( FunctionCall & _visitable );
	void Visit ( FunctionsList & _visitable );
	void Visit ( GetAddress & _visitable );
	void Visit ( IfInstruction & _visitable );
	void Visit ( InstructionsList & _visitable );
	void Visit ( Null & _visitable );
	void Visit ( Number & _visitable );
	void Visit ( Parameter & _visitable );
	void Visit ( ParametersList & _visitable );
	void Visit ( Parenthesis & _visitable );
	void Visit ( Syntax::PointerType & _visitable );
	void Visit ( Program & _visitable );
	void Visit ( ReturnInstruction & _visitable );
	void Visit ( SimpleExpression & _visitable );
	void Visit ( String & _visitable );
	void Visit ( UnaryFactor & _visitable );
	void Visit ( Variable & _visitable );
	void Visit ( WhileInstruction & _visitable );

	using ErrorsDetector::getErrorsCount;

protected:
	template< typename _List, typename _Element >
	void analiseList(
		_List _list,
		_Element _element
	);

protected:
	FunctionsController & m_functionsController;
	StringsController & m_stringsController;
	TypesController & m_typesController;
	VariablesController & m_variablesController;
	
	std::vector< TypesController::Handler > m_functionParametersTypes;
	std::stack< std::vector< TypesController::Handler > > m_functionArgumentsTypes;
	Function * m_currentFunction;
    std::vector< IInstruction const * > m_currentLoop;
    
	Scope m_scope;
	 
	bool m_isReturnInstruction;
    
    std::stack< Dereference::AssignmentSide::Enum > m_assignmentSide;
    
    boost::shared_ptr< Semantics::Type > m_type;
};

}

#endif
