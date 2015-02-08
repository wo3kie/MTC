#include "headers/ph.hpp"

#include "headers/errors_detector.hpp"

#include "headers/precondition.hpp"

#include <boost/optional.hpp>

namespace Semantics
{

ErrorsDetector::ErrorsDetector()
	: m_errorsCount( 0 )
{
}

void
ErrorsDetector::throwIfEmptyFileIsCompiled(
	boost::shared_ptr< Syntax::FunctionsList > _functionsList ) const
{
	if ( ! _functionsList )
	{
		++m_errorsCount;
		throw Exceptions::EmptyFileCompilationException();
	}
}

void
ErrorsDetector::throwIfTypesAreIncompatibile(
	TypesController::Handler _handler1,
	TypesController::Handler _handler2
) const
{
	PRECONDITION2( ! _handler1.isNull(), ! _handler2.isNull() )
	
	if ( _handler1 != _handler2 )
	{
		++m_errorsCount;
		throw Exceptions::TypesIncompatibleException( "", "", "" );
	}
}

boost::shared_ptr< Type >
ErrorsDetector::throwIfTypesAreIncompatibile(
    boost::shared_ptr< Type > _lhsType,
    boost::shared_ptr< Type > _rhsType,
    boost::shared_ptr< Syntax::Operator > _operator
) const
{
    PRECONDITION3( _lhsType, _rhsType, _operator );
    
    boost::optional< TypesMappingInfo > const typesMappingInfo
        = _operator->getTypesMapping().isMappable( _lhsType, _rhsType );
    
    if( ! typesMappingInfo )
    {
        ++m_errorsCount;
        throw Exceptions::TypesIncompatibleException( _operator->getOperatorName(), _lhsType->getTypeName(), _rhsType->getTypeName() );
    }
    
    return ( * typesMappingInfo ).getTypeLazyExpression()->evaluate( _lhsType, _rhsType );
}

boost::shared_ptr< Type >
ErrorsDetector::throwIfTypeIsIncompatibile(
    boost::shared_ptr< Type > _type,
    boost::shared_ptr< Syntax::Operator > _operator
) const
{
    PRECONDITION2( _type, _operator );
    
    boost::optional< TypesMappingInfo > const typesMappingInfo
        = _operator->getTypesMapping().isMappable( _type );
    
    if( ! typesMappingInfo )
    {
        ++m_errorsCount;
        throw Exceptions::TypesIncompatibleException( _operator->getOperatorName(), _type->getTypeName() );
    }
        
    return ( * typesMappingInfo ).getTypeLazyExpression()->evaluate( _type, Semantics::NullType::create() );
}

void
ErrorsDetector::throwIfVariableIsAlreadyDefined(
	VariablesController const & _variablesController,
	std::string const & _variableName,
	Scope _scope
) const
{
	PRECONDITION1( ! _variableName.empty() )
	
	if ( isSymbolAlreadyDefined( _variablesController, _variableName, _scope ) )
	{
		++m_errorsCount;
		throw Exceptions::VariableIsAlreadyDefinedException();
	}
}

void
ErrorsDetector::throwIfVariableIsNotDefined(
	VariablesController const & _variablesController,
	std::string const & _variableName,
	Scope _scope
) const
{
	PRECONDITION1( ! _variableName.empty() )
	
	if ( ! isSymbolAlreadyDefined( _variablesController, _variableName, _scope ) )
	{
		++m_errorsCount;
		throw Exceptions::VariableIsNotDefinedException();
	}
}

void
ErrorsDetector::throwIfFunctionIsAlreadyDefined(
	FunctionsController const & _functionsController,
	std::string const & _functionName,
	Scope _scope
) const
{
	PRECONDITION1( ! _functionName.empty() )
	
	if ( isSymbolAlreadyDefined( _functionsController, _functionName, _scope ) )
	{
		++m_errorsCount;
		throw Exceptions::FunctionIsAlreadyDefinedException();
	}
}

void
ErrorsDetector::throwIfFunctionIsNotDefined(
	FunctionsController const & _functionsController,
	std::string const & _functionName,
	Scope _scope
) const
{
	PRECONDITION1( ! _functionName.empty() )
	
	if ( ! isSymbolAlreadyDefined( _functionsController, _functionName, _scope ) )
	{
		++m_errorsCount;
		throw Exceptions::FunctionIsNotDefinedException();
	}
}

void
ErrorsDetector::throwIfNonVoidFunctionNotReturnAnyValue(
	TypesController const & _typesController,
	TypesController::Handler _returnValueType,
	bool _isReturnInstruction
) const
{
	if ( _returnValueType != _typesController.getHandler( Semantics::BuildInType::create( "void" ), Scope::createGlobalScope() )
		&& ! _isReturnInstruction
	)
	{
		++m_errorsCount;
		throw Exceptions::NonVoidFunctionNotReturnAnyValue();
	}
}

void
ErrorsDetector::throwIfCannotCallFunctionWrongParametersNumber(
	int _functionsArgumentsNumber,
	int _functionsParametersNumber
) const
{
	if ( _functionsArgumentsNumber != _functionsParametersNumber )
	{
		++m_errorsCount;
		throw Exceptions::CannotCallFunctionWrongParametersNumber();
	}
}

void
ErrorsDetector::throwIfCannotCallFunctionWrongParameterType(
    TypesController const & _typesController,
	std::vector< TypesController::Handler > const & _parametersTypes,
	std::vector< TypesController::Handler > const & _argumentsTypes,
    boost::shared_ptr< Syntax::Operator > _operator
) const
{
	for( unsigned current = 0 ; current < _parametersTypes.size() ; ++current )
	{
        try
        {
            boost::shared_ptr< Type > const resultType = throwIfTypesAreIncompatibile(
                _typesController.getData( _parametersTypes[ current ] ).getKey(),
                _typesController.getData( _argumentsTypes[ current ] ).getKey(),
                _operator
            );
        }
        catch( Exceptions::TypesIncompatibleException & _exception )
        {
            throw;
        } 
	}
}

int
ErrorsDetector::getErrorsCount() const
{
	return m_errorsCount;
}

}
