#include "headers/ph.hpp"

#include "headers/semantic_analysis_exceptions.hpp"

#include "headers/break_instruction.hpp"

#include <sstream>

namespace Exceptions
{

ApplicationsExceptions::ApplicationsExceptions()
{
}

ApplicationsExceptions::~ApplicationsExceptions() throw()
{
}

SemanticAnalysisException::SemanticAnalysisException()
{
}

SemanticAnalysisException::~SemanticAnalysisException() throw()
{
}

EmptyFileCompilationException::EmptyFileCompilationException()
{
}

EmptyFileCompilationException::~EmptyFileCompilationException() throw()
{
}

const char *
EmptyFileCompilationException::what() const throw()
{
	return "Specified file is empty. Compilation stoped.";
}

TypesIncompatibleException::TypesIncompatibleException(
    std::string const & _operator,
    std::string const & _lhs,
    std::string const & _rhs
)
{
	m_what
        = std::string( "Type(s) are incompatible for: " )
        + _operator
        + " ("
        + _lhs;
    
    if( ! _rhs.empty() )
    {
        m_what += ", ";
        m_what += _rhs;
    }
    
    m_what += ")";
}

TypesIncompatibleException::~TypesIncompatibleException() throw()
{
}

const char *
TypesIncompatibleException::what() const throw()
{
    return m_what.c_str();
}

VariableIsAlreadyDefinedException::VariableIsAlreadyDefinedException()
{
}

VariableIsAlreadyDefinedException::~VariableIsAlreadyDefinedException() throw()
{
}

const char *
VariableIsAlreadyDefinedException::what() const throw()
{
	return "Variable is already defined.";
}

VariableIsNotDefinedException::VariableIsNotDefinedException()
{
}

VariableIsNotDefinedException::~VariableIsNotDefinedException() throw()
{
}

const char *
VariableIsNotDefinedException::what() const throw()
{
	return "Variable is undefined.";
}

FunctionIsAlreadyDefinedException::FunctionIsAlreadyDefinedException()
{
}

FunctionIsAlreadyDefinedException::~FunctionIsAlreadyDefinedException() throw()
{
}

const char *
FunctionIsAlreadyDefinedException::what() const throw()
{
	return "Function is already defined.";
}

FunctionIsNotDefinedException::FunctionIsNotDefinedException()
{
}

FunctionIsNotDefinedException::~FunctionIsNotDefinedException() throw()
{
}

const char *
FunctionIsNotDefinedException::what() const throw()
{
	return "Function is undefined.";
}

NonVoidFunctionNotReturnAnyValue::NonVoidFunctionNotReturnAnyValue()
{
}

NonVoidFunctionNotReturnAnyValue::~NonVoidFunctionNotReturnAnyValue() throw()
{
}

const char *
NonVoidFunctionNotReturnAnyValue::what() const throw()
{
	return "Non void function does not return any value.";
}

CannotCallFunctionWrongParametersNumber::CannotCallFunctionWrongParametersNumber()
{
}

CannotCallFunctionWrongParametersNumber::~CannotCallFunctionWrongParametersNumber() throw()
{
}

const char *
CannotCallFunctionWrongParametersNumber::what() const throw()
{
	return "Cannot call function. Wrong arguments/parameters number.";
}

CannotCallFunctionWrongParameterType::CannotCallFunctionWrongParameterType(
	int _position
)
	: m_position( _position )
{
}

CannotCallFunctionWrongParameterType::~CannotCallFunctionWrongParameterType() throw()
{
}

const char *
CannotCallFunctionWrongParameterType::what() const throw()
{
	return "Cannot call function. Wrong arguments/parameters types.";
}

int
CannotCallFunctionWrongParameterType::getPosition() const
{
	return m_position;
}

BreakIsWrongPlaced::BreakIsWrongPlaced( int _breakCount, int _stackSize )
    : m_breakCount( _breakCount )
    , m_stackSize( _stackSize )
{
}
    
BreakIsWrongPlaced::~BreakIsWrongPlaced() throw()
{
}
    
const char *
BreakIsWrongPlaced::what() const throw()
{
    std::ostringstream sstream;
    
    sstream
        << std::string( "`break' (" )
        << ( m_breakCount == Syntax::BreakInstruction::BreakAll ? std::string( "all" ) : boost::lexical_cast< std::string >( m_breakCount ) )
        << std::string( ") used outside of properly amount of loop(s): " )
        << m_stackSize;
    
    return sstream.str().c_str();
}

ContinueIsWrongPlaced::ContinueIsWrongPlaced()
{
}
    
ContinueIsWrongPlaced::~ContinueIsWrongPlaced() throw()
{
}
    
const char *
ContinueIsWrongPlaced::what() const throw()
{
    return "`continue' is placed outside of any loop(s)";
}

}
