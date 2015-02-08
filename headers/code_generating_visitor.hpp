/*
* $LastChangedRevision$
*/

#ifndef __CODE_GENERATING_CODE_GENERATING_VISITOR_HPP__
#define __CODE_GENERATING_CODE_GENERATING_VISITOR_HPP__

#include "headers/functions_controller.hpp"
#include "headers/strings_controller.hpp"
#include "headers/types_controller.hpp"
#include "headers/variables_controller.hpp"

#include "headers/code_generator.hpp"

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
#include "headers/operators.hpp"
#include "headers/parameters_list.hpp"
#include "headers/parenthesis.hpp"
#include "headers/program.hpp"
#include "headers/return_instruction.hpp"
#include "headers/simple_expression.hpp"
#include "headers/string.hpp"
#include "headers/unary_factor.hpp"
#include "headers/unit.hpp"
#include "headers/variable.hpp"
#include "headers/while_instruction.hpp"

#include <loki/Visitor.h>

namespace CodeGenerating
{

using namespace Syntax;

class CodeGeneratingVisitor
	: public Loki::BaseVisitor
	// syntax tree nodes
	, public Loki::Visitor< AssignmentExpression >
	, public Loki::Visitor< BreakInstruction >
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
	, public Loki::Visitor< ParametersList >
	, public Loki::Visitor< Parenthesis >
	, public Loki::Visitor< Program >
	, public Loki::Visitor< ReturnInstruction >
	, public Loki::Visitor< SimpleExpression >
	, public Loki::Visitor< String >
	, public Loki::Visitor< UnaryFactor >
	, public Loki::Visitor< Variable >
	, public Loki::Visitor< WhileInstruction >
	// operators
	, public Loki::Visitor< AssignOperator >
	, public Loki::Visitor< EqualOperator >
	, public Loki::Visitor< NotEqualOperator >
	, public Loki::Visitor< LessOperator >
	, public Loki::Visitor< GreaterOperator >
	, public Loki::Visitor< AndOperator >
	, public Loki::Visitor< OrOperator >
	, public Loki::Visitor< AdditionOperator >
	, public Loki::Visitor< SubtractionOperator >
	, public Loki::Visitor< MultiplicationOperator >
	, public Loki::Visitor< DivisionOperator >
	, public Loki::Visitor< PlusOperator >
	, public Loki::Visitor< MinusOperator >
	// implementation
	, protected CodeGenerator
{
public:
	CodeGeneratingVisitor(
		Semantics::FunctionsController & _functionsController,
		Semantics::StringsController & _stringsController,
		Semantics::TypesController & _typesController,
		Semantics::VariablesController & _variablesController
	);

	void Visit( ISyntaxTreeNode & _visitable );

	void Visit ( AssignmentExpression & _visitable );
	void Visit ( BreakInstruction & _visitable );
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
	void Visit ( ParametersList & _visitable );
	void Visit ( Parenthesis & _visitable );
	void Visit ( Program & _visitable );
	void Visit ( ReturnInstruction & _visitable );
	void Visit ( SimpleExpression & _visitable );
	void Visit ( String & _visitable );
	void Visit ( UnaryFactor & _visitable );
	void Visit ( Variable & _visitable );
	void Visit ( WhileInstruction & _visitable );
	
	// operators
	void Visit ( AssignOperator & _visitable );
	void Visit ( EqualOperator & _visitable );
	void Visit ( NotEqualOperator & _visitable );
	void Visit ( LessOperator & _visitable );
	void Visit ( GreaterOperator & _visitable );
	void Visit ( AndOperator & _visitable );
	void Visit ( OrOperator & _visitable );
	void Visit ( AdditionOperator & _visitable );
	void Visit ( SubtractionOperator & _visitable );
	void Visit ( MultiplicationOperator & _visitable );
	void Visit ( DivisionOperator & _visitable );
	void Visit ( PlusOperator & _visitable );
	void Visit ( MinusOperator & _visitable );
	
protected:
	template< typename _Left, typename _Operator, typename _Right >
	void generateCodeForTwoChildedNode(
		boost::shared_ptr< _Left > _left,
		boost::shared_ptr< _Operator > _operator,
		boost::shared_ptr< _Right > _right );
	
	template< typename _List, typename _Element >
	void generateCodeForList(
		_List _list,
		_Element _element );
	
	void generateRelationalConditionCode( std::string const & _operator ) const;
	void generateLogicalConditionCode( std::string const & _operator ) const;
	void generateExitProgramSequenceCode() const;
	
protected:
	Semantics::FunctionsController & m_functionsController;
	Semantics::StringsController & m_stringsController;
	Semantics::TypesController & m_typesController;
	Semantics::VariablesController & m_variablesController;
	
	int m_defaultAlign;
	
	mutable std::string m_leftOperand;
	mutable std::string m_rightOperand;
};

}

#endif
