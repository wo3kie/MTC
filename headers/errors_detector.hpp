#ifndef __SEMANTICS_ERRORS_DETECTOR_HPP__
#define __SEMANTICS_ERRORS_DETECTOR_HPP__

#include "headers/break_instruction.hpp"
#include "headers/functions_controller.hpp"
#include "headers/functions_list.hpp"
#include "headers/operators.hpp"
#include "headers/scope.hpp"
#include "headers/semantic_analysis_exceptions.hpp"
#include "headers/types_controller.hpp"
#include "headers/variables_controller.hpp"

namespace Semantics
{

class ErrorsDetector
{
public:
	ErrorsDetector();

	void throwIfEmptyFileIsCompiled(
		boost::shared_ptr< Syntax::FunctionsList > _functionsList ) const;

	void throwIfTypesAreIncompatibile(
		TypesController::Handler _handler1,
		TypesController::Handler _handler2 ) const;
    
    boost::shared_ptr< Type > throwIfTypesAreIncompatibile(
        boost::shared_ptr< Type > _lhsType,
        boost::shared_ptr< Type > _rhsType,
        boost::shared_ptr< Syntax::Operator > _operator
    ) const;

    boost::shared_ptr< Type > throwIfTypeIsIncompatibile(
        boost::shared_ptr< Type > _type,
        boost::shared_ptr< Syntax::Operator > _operator
    ) const;
    
	void throwIfVariableIsAlreadyDefined(
		VariablesController const & _variablesController,
		std::string const & _variableName,
		Scope _scope
	) const;
	
	void throwIfVariableIsNotDefined(
		VariablesController const & _variablesController,
		std::string const & _variableName,
		Scope _scope
	) const;

	void throwIfFunctionIsAlreadyDefined(
		FunctionsController const & _functionsController,
		std::string const & _functionName,
		Scope _scope
	) const;

	void throwIfFunctionIsNotDefined(
		FunctionsController const & _functionsController,
		std::string const & _functionName,
		Scope _scope
	) const;
	
	void throwIfNonVoidFunctionNotReturnAnyValue(
		TypesController const & _typesController,
		TypesController::Handler _returnValueType,
		bool _isReturnInstruction
	) const;

	void throwIfCannotCallFunctionWrongParametersNumber(
		int _functionsArgumentsNumber,
		int _functionsParametersNumber
	) const;

	void throwIfCannotCallFunctionWrongParameterType(
        TypesController const & _typesController,
		std::vector< TypesController::Handler > const & _parametersTypes,
		std::vector< TypesController::Handler > const & _argumentsTypes,
        boost::shared_ptr< Syntax::Operator > _operator = boost::shared_ptr< Syntax::Operator >( new Syntax::AssignOperator )
	) const;
    
    template< typename _Iterator >
    void throwIfBreakIsWrongPlaced( _Iterator _begin, _Iterator _end, int _breakValue ) const;

    template< typename _Iterator >
    void throwIfContinueIsWrongPlaced( _Iterator _begin, _Iterator _end ) const;    
    
	int getErrorsCount() const;

private:
	mutable int m_errorsCount;
};

template< typename _Iterator >
void ErrorsDetector::throwIfBreakIsWrongPlaced(
    _Iterator _begin,
    _Iterator _end,
    int _breakValue
) const
{
    int const stackSize = std::abs( std::distance( _end, _begin ) );
    
    bool const isBreakAllOutsideAnyLoop
        = _breakValue == Syntax::BreakInstruction::BreakAll && stackSize == 0;

    bool const isBreakValueTooBig = stackSize < _breakValue;
    
    if( isBreakAllOutsideAnyLoop || isBreakValueTooBig  )
    {
        ++m_errorsCount;
        throw Exceptions::BreakIsWrongPlaced( _breakValue, stackSize );
    }
}

template< typename _Iterator >
void ErrorsDetector::throwIfContinueIsWrongPlaced(
    _Iterator _begin,
    _Iterator _end
) const
{
    if( _begin == _end  )
    {
        ++m_errorsCount;
        throw Exceptions::ContinueIsWrongPlaced();
    }
}

}

#endif
