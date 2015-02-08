#ifndef __SYNTAX_SEMANTIC_VALUE_STACK_HPP__
#define __SYNTAX_SEMANTIC_VALUE_STACK_HPP__

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
#include "headers/instruction.hpp"
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
#include "headers/unary_factor.hpp"
#include "headers/unit.hpp"
#include "headers/variable.hpp"
#include "headers/while_instruction.hpp"

#include <boost/shared_ptr.hpp>

namespace Syntax
{

struct SemanticValueStack
{
	int m_number;
	std::string m_string;
	
	boost::shared_ptr< AssignmentExpression > m_assignmentExpression;
	boost::shared_ptr< BreakInstruction > m_breakInstruction;
	boost::shared_ptr< CompoundInstruction > m_compoundInstruction;
	boost::shared_ptr< ContinueInstruction > m_continueInstruction;
	boost::shared_ptr< Declaration > m_declaration;
    boost::shared_ptr< Dereference > m_dereference;
	boost::shared_ptr< DoWhileInstruction > m_doWhile;
	boost::shared_ptr< Expression > m_expression;
	boost::shared_ptr< ExpressionsList > m_expressionsList;
	boost::shared_ptr< Factor > m_factor;
	boost::shared_ptr< ForInstruction > m_forInstruction;
	boost::shared_ptr< Function > m_function;
	boost::shared_ptr< FunctionCall > m_functionCall;
	boost::shared_ptr< FunctionsList > m_functionsList;
    boost::shared_ptr< GetAddress > m_getAddress;
	boost::shared_ptr< IfInstruction > m_ifInstruction;
	boost::shared_ptr< IInstruction > m_instruction;
	boost::shared_ptr< InstructionsList > m_instructionsList;
	boost::shared_ptr< Null > m_null;
	boost::shared_ptr< Parenthesis > m_parenthesis;
	boost::shared_ptr< ParametersList > m_parametersList;
	boost::shared_ptr< Program > m_program;
	boost::shared_ptr< ReturnInstruction > m_returnInstruction;
	boost::shared_ptr< SimpleExpression > m_simpleExpression;
    boost::shared_ptr< Type > m_type;
	boost::shared_ptr< UnaryFactor > m_unaryFactor;
	boost::shared_ptr< IUnit > m_unit;
	boost::shared_ptr< Variable > m_variable;
	boost::shared_ptr< WhileInstruction > m_whileInstruction;
};

}

#endif
