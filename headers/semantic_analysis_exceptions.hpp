#ifndef __SEMANTIC_ANALYSIS_EXCEPTIONS_HPP__
#define __SEMANTIC_ANALYSIS_EXCEPTIONS_HPP__

#include <exception>

namespace Exceptions
{

class ApplicationsExceptions
	: public std::exception
{
public:
	ApplicationsExceptions();

	/*virtual*/ ~ApplicationsExceptions() throw();
};

class SemanticAnalysisException
	: public ApplicationsExceptions
{
public:
	SemanticAnalysisException();

	/*virtual*/ ~SemanticAnalysisException() throw();
};

class EmptyFileCompilationException
	: public SemanticAnalysisException
{
public:
	EmptyFileCompilationException();
	
	/*virtual*/ ~EmptyFileCompilationException() throw();
	
	/*virtual*/ const char * what() const throw();
};

class TypesIncompatibleException
	: public SemanticAnalysisException
{
public:
	TypesIncompatibleException( std::string const & _operator, std::string const & _lhs, std::string const & _rhs = std::string() );

	/*virtual*/ ~TypesIncompatibleException() throw();
	
	/*virtual*/ const char * what() const throw();
    
private:
    std::string m_what;
};

class VariableIsAlreadyDefinedException
	: public SemanticAnalysisException
{
public:
	VariableIsAlreadyDefinedException();

	/*virtual*/ ~VariableIsAlreadyDefinedException() throw();
	
	/*virtual*/ const char * what() const throw();
};

class VariableIsNotDefinedException
	: public SemanticAnalysisException
{
public:
	VariableIsNotDefinedException();

	/*virtual*/ ~VariableIsNotDefinedException() throw();
	
	/*virtual*/ const char * what() const throw();
};

class FunctionIsAlreadyDefinedException
	: public SemanticAnalysisException
{
public:
	FunctionIsAlreadyDefinedException();

	/*virtual*/ ~FunctionIsAlreadyDefinedException() throw();
	
	/*virtual*/ const char * what() const throw();
};


class FunctionIsNotDefinedException
	: public SemanticAnalysisException
{
public:
	FunctionIsNotDefinedException();

	/*virtual*/ ~FunctionIsNotDefinedException() throw();
	
	/*virtual*/ const char * what() const throw();
};

class NonVoidFunctionNotReturnAnyValue
	: public SemanticAnalysisException
{
public:
	NonVoidFunctionNotReturnAnyValue();

	/*virtual*/ ~NonVoidFunctionNotReturnAnyValue() throw();
	
	/*virtual*/ const char * what() const throw();
};

class CannotCallFunctionWrongParametersNumber
	: public SemanticAnalysisException
{
public:
	CannotCallFunctionWrongParametersNumber();

	/*virtual*/ ~CannotCallFunctionWrongParametersNumber() throw();
	
	/*virtual*/ const char * what() const throw();
};

class CannotCallFunctionWrongParameterType
	: public SemanticAnalysisException
{
public:
	CannotCallFunctionWrongParameterType( int _position );

	/*virtual*/ ~CannotCallFunctionWrongParameterType() throw();
	
	/*virtual*/ const char * what() const throw();

	int getPosition() const;
private:
	int m_position;
};

class BreakIsWrongPlaced
    : public SemanticAnalysisException
{
public:
    BreakIsWrongPlaced( int _breakCount, int _stackSize );
    
    /*virtual*/ ~BreakIsWrongPlaced() throw();
    
    /*virtual*/ const char * what() const throw();
    
private:
    int m_breakCount;
    int m_stackSize;
};

class ContinueIsWrongPlaced
    : public SemanticAnalysisException
{
public:
    ContinueIsWrongPlaced();
    
    /*virtual*/ ~ContinueIsWrongPlaced() throw();
    
    /*virtual*/ const char * what() const throw();
};

}

#endif
