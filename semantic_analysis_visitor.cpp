#include "headers/ph.hpp"

#include "headers/semantic_analysis_visitor.hpp"
#include "headers/semantic_analysis_exceptions.hpp"
#include "headers/types_mapping.hpp"

namespace Semantics
{

SemanticAnalysisVisitor::SemanticAnalysisVisitor(
	FunctionsController & _functionsController,
	StringsController & _stringsController,
	TypesController & _typesController,
	VariablesController & _variablesController
)
	: m_functionsController( _functionsController )
	, m_stringsController( _stringsController )
	, m_typesController( _typesController )
	, m_variablesController( _variablesController )
{
    m_assignmentSide.push( Dereference::AssignmentSide::Right );
}

void
SemanticAnalysisVisitor::Visit( ISyntaxTreeNode & _visitable )
{
	assert( ! typeid( _visitable ).name() );
}

void
SemanticAnalysisVisitor::Visit ( AssignmentExpression & _visitable )
{
	boost::shared_ptr< AssignmentExpression > const assignmentExpression
		= _visitable.getAssignmentExpression();

	if ( assignmentExpression )
	{
        m_assignmentSide.push( Dereference::AssignmentSide::Left );
		assignmentExpression->Accept( *this );
        m_assignmentSide.top() = Dereference::AssignmentSide::Right;
	}

	boost::shared_ptr< Expression > const expression = _visitable.getExpression();
	expression->Accept( *this );

	TypesController::Handler const expressionTypeHandler = expression->getTypeHandler();

	if ( assignmentExpression )
	{	
        try
        {
            boost::shared_ptr< Type > const resultType = throwIfTypesAreIncompatibile(
                m_typesController.getData( assignmentExpression->getTypeHandler() ).getKey(),
                m_typesController.getData( expressionTypeHandler ).getKey(),
                boost::shared_ptr< Syntax::AssignOperator >( new Syntax::AssignOperator )
            );

            _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
        }
        catch( Exceptions::TypesIncompatibleException & _exception )
        {
            std::cerr
                << _exception.what()
                << std::endl;
        }
	}
    else
    {
        _visitable.setTypeHandler( expressionTypeHandler );
    }
    
    if( assignmentExpression )
    {
        m_assignmentSide.pop();
    }
}

void
SemanticAnalysisVisitor::Visit ( BreakInstruction & _visitable )
{    
    try
    {
        throwIfBreakIsWrongPlaced( m_currentLoop.begin(), m_currentLoop.end(), _visitable.getBreakValue() );
    }
    catch( Exceptions::BreakIsWrongPlaced const & _exception )
    {
        std::cerr
            << _exception.what()
            << std::endl;
        
        return;
    }
    
    _visitable.setLoop( m_currentLoop.back() );
}

void
SemanticAnalysisVisitor::Visit ( Syntax::BuildInType & _visitable )
{
    m_type = Semantics::BuildInType::create( _visitable.getTypeName() );
}

void
SemanticAnalysisVisitor::Visit ( CompoundInstruction & _visitable )
{
	boost::shared_ptr< InstructionsList > const instructionsList
		= _visitable.getInstructionsList();

	instructionsList->Accept( *this );
	_visitable.setTypeHandler( instructionsList->getTypeHandler() );
}

void
SemanticAnalysisVisitor::Visit ( ContinueInstruction & _visitable )
{    
    try
    {
        throwIfContinueIsWrongPlaced( m_currentLoop.begin(), m_currentLoop.end() );
    }
    catch( Exceptions::ContinueIsWrongPlaced const & _exception )
    {
        std::cerr
            << _exception.what()
            << std::endl;
        
        return;
    }
    
    _visitable.setLoop( m_currentLoop.back() );
}

void
SemanticAnalysisVisitor::Visit ( Declaration & _visitable )
{
	std::string const variableName = _visitable.getVariableName();
	
    _visitable.getType()->Accept( *this );
    assert( m_type );

	TypesController::Handler const typeHandler
		= m_typesController.smartInsert( m_type, Scope::createGlobalScope() );

	VariablesController::Handler const variableHandler
		= m_variablesController.getHandler( variableName, m_scope );

	try
	{
		throwIfVariableIsAlreadyDefined( m_variablesController, variableName, m_scope );
	}
	catch( Exceptions::VariableIsAlreadyDefinedException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< variableName
			<< std::endl;
		
		return;
	}

	_visitable.setVariableHandler(
		m_variablesController.insert(
			VariableData( variableName, typeHandler, m_scope, VariableType::Variable )
		)
	);
	
	boost::shared_ptr< Expression > const initialization
		= _visitable.getInitializationChild();
	
	if ( initialization )
	{
		initialization->Accept( *this );
	}
}

void
SemanticAnalysisVisitor::Visit ( Dereference & _visitable )
{
    _visitable.getUnit()->Accept( *this ); 
    _visitable.setAssignmentSide( m_assignmentSide.top() );
    
    try
    {
        boost::shared_ptr< Type > const resultType = throwIfTypeIsIncompatibile(
            m_typesController.getData( _visitable.getUnit()->getTypeHandler() ).getKey(),
            boost::shared_ptr< Syntax::DereferenceOperator >( new Syntax::DereferenceOperator )
        );

        _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
    }
    catch( Exceptions::TypesIncompatibleException & _exception )
    {
        std::cerr
            << _exception.what()
            << std::endl;
    }    
}

void
SemanticAnalysisVisitor::Visit ( DoWhileInstruction & _visitable )
{
	_visitable.getConditionChild()->Accept( *this );
	_visitable.getBodyChild()->Accept( *this );
}

void
SemanticAnalysisVisitor::Visit ( Expression & _visitable )
{
	boost::shared_ptr< Expression > const expression = _visitable.getExpression();
	if ( expression )
	{
		expression->Accept( *this );
	}
	
	boost::shared_ptr< SimpleExpression > const simpleExpression
		= _visitable.getSimpleExpression();
	simpleExpression->Accept( *this );

	TypesController::Handler const simpleExpressionTypeHandler
		= simpleExpression->getTypeHandler();

	if ( expression )
	{
        try
        {
            boost::shared_ptr< Type > const resultType = throwIfTypesAreIncompatibile(
                m_typesController.getData( expression->getTypeHandler() ).getKey(),
                m_typesController.getData( simpleExpressionTypeHandler ).getKey(),
                _visitable.getOperator()
            );

            _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
        }
        catch( Exceptions::TypesIncompatibleException & _exception )
        {
            std::cerr
                << _exception.what()
                << std::endl;
        }        
	}
    else
    {
        _visitable.setTypeHandler( simpleExpressionTypeHandler );
    }
}

void
SemanticAnalysisVisitor::Visit ( ExpressionsList & _visitable )
{
	boost::shared_ptr< SyntaxTreeList< AssignmentExpression > > const expressionsList
		= _visitable.getChildList();

	if ( expressionsList )
	{
		expressionsList->Accept( *this );
	}

	boost::shared_ptr< AssignmentExpression > const expression = _visitable.getChild();

	if ( expression )
	{
		expression->Accept( *this );
		m_functionArgumentsTypes.top().push_back( expression->getTypeHandler() );
	}
}

void
SemanticAnalysisVisitor::Visit ( Factor & _visitable )
{
	boost::shared_ptr< Factor > const factor = _visitable.getFactor();
	if ( factor )
	{
		factor->Accept( *this );
	}

	boost::shared_ptr< UnaryFactor > const unaryFactor = _visitable.getUnaryFactor();
	unaryFactor->Accept( *this );

	TypesController::Handler const unaryFactorTypeHandler = unaryFactor->getTypeHandler();

	if ( factor )
	{	   
        try
        {
            boost::shared_ptr< Type > const resultType = throwIfTypesAreIncompatibile(
                m_typesController.getData( factor->getTypeHandler() ).getKey(),
                m_typesController.getData( unaryFactorTypeHandler ).getKey(),
                _visitable.getOperator()
            );

            _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
        }
        catch( Exceptions::TypesIncompatibleException & _exception )
        {
            std::cerr
                << _exception.what()
                << std::endl;
        }
	}

	_visitable.setTypeHandler( unaryFactorTypeHandler );
}

void
SemanticAnalysisVisitor::Visit ( ForInstruction & _visitable )
{
    m_currentLoop.push_back( & _visitable );
    
	_visitable.getDeclarationChild()->Accept( *this );
	_visitable.getConditionChild()->Accept( *this );
	_visitable.getIncrementationChild()->Accept( *this );
	_visitable.getBodyChild()->Accept( *this );
    
    m_currentLoop.pop_back();
}

void
SemanticAnalysisVisitor::Visit ( Function & _visitable )
{
    m_currentFunction = & _visitable;
    
	Scope const functionDefinedIn = m_scope;
	m_scope.enterFunction();
	
	m_isReturnInstruction = false;

	std::string const functionName = _visitable.getName();

    _visitable.getReturnType()->Accept( *this );
    
	TypesController::Handler const returnTypeHandler
		= m_typesController.smartInsert( m_type, Scope::createGlobalScope() );
	
	try
	{
		throwIfFunctionIsAlreadyDefined(
			m_functionsController,
			functionName,
			functionDefinedIn );
	}
	catch( Exceptions::FunctionIsAlreadyDefinedException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< functionName
			<< std::endl;
		
		return;
	}

	boost::shared_ptr< ParametersList > const parametersList = _visitable.getParametersList();

	if ( parametersList )
	{
		parametersList->Accept( *this );
	}

	FunctionData const functionData
		= m_functionParametersTypes.empty()
		? FunctionData(
			functionName,
			returnTypeHandler,
			Scope::createGlobalScope(),
			m_scope )
		: FunctionData(
			functionName,
			returnTypeHandler,
			m_functionParametersTypes,
			Scope::createGlobalScope(),
			m_scope );


	_visitable.setHandler( m_functionsController.insert( functionData ) );
	
	m_functionParametersTypes.clear();

	_visitable.getFunctionBody()->Accept( *this );

	try
	{
		throwIfNonVoidFunctionNotReturnAnyValue(
			m_typesController,
			functionData.getReturnValueType(),
			m_isReturnInstruction );
	}
	catch( Exceptions::NonVoidFunctionNotReturnAnyValue const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< functionName
			<< std::endl;
	}
	
	m_isReturnInstruction = false;
}

void
SemanticAnalysisVisitor::Visit ( FunctionCall & _visitable )
{
	m_functionArgumentsTypes.push( std::vector< TypesController::Handler >() );

	std::string const functionName = _visitable.getFunctionName();

	FunctionsController::Handler const functionHandler
		= m_functionsController.getHandler( functionName, Scope::createGlobalScope() );

	try
	{
		throwIfFunctionIsNotDefined(
			m_functionsController,
			functionName,
			Scope::createGlobalScope() );
	}
	catch( Exceptions::FunctionIsNotDefinedException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< functionName
			<< std::endl;
		
		return;
	}

	boost::shared_ptr< ExpressionsList > const expressionsList = _visitable.getExpressionsList();

	if ( expressionsList )
	{
		expressionsList->Accept( *this );
	}

	std::vector< TypesController::Handler > const parametersTypes
		= m_functionsController.getData( functionHandler ).getParametersTypes();
	
	std::vector< TypesController::Handler > const argumentsTypes
		= m_functionArgumentsTypes.top();

	try
	{
		throwIfCannotCallFunctionWrongParametersNumber(
			parametersTypes.size(),
			argumentsTypes.size() );
	}
	catch( Exceptions::CannotCallFunctionWrongParametersNumber const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< functionName
			<< " "
			<< parametersTypes.size()
			<< "/"
			<< argumentsTypes.size()
			<< std::endl;
		
		return;
	}

	try
	{
		throwIfCannotCallFunctionWrongParameterType(
            m_typesController,
			parametersTypes,
			argumentsTypes );
	}
	catch( Exceptions::TypesIncompatibleException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< functionName
			//<< ": "
			//<< _exception.getPosition()
			<< std::endl;
		
		return;
	}

	_visitable.setTypeHandler(
		m_functionsController.getData( functionHandler ).getReturnValueType()
	);
	
	m_functionArgumentsTypes.pop();
}

void
SemanticAnalysisVisitor::Visit( FunctionsList & _visitable )
{
	analiseList(
		_visitable.getChildList(),
		_visitable.getChild() );
}

void
SemanticAnalysisVisitor::Visit( GetAddress & _visitable )
{
	boost::shared_ptr< Variable > const variable = _visitable.getVariable();
	variable->Accept( *this );
	
    try
    {
        boost::shared_ptr< Type > const resultType = throwIfTypeIsIncompatibile(
            m_typesController.getData( variable->getTypeHandler() ).getKey(),
            boost::shared_ptr< Syntax::UnaryAndOperator >( new Syntax::UnaryAndOperator )
        );

        _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
    }
    catch( Exceptions::TypesIncompatibleException & _exception )
    {
        std::cerr
            << _exception.what()
            << std::endl;
    }
}

void
SemanticAnalysisVisitor::Visit ( IfInstruction & _visitable )
{
	boost::shared_ptr< AssignmentExpression > const condition = _visitable.getConditionChild();
	boost::shared_ptr< IInstruction > const trueBranchChild
		= _visitable.getTrueBranchChild();

	condition->Accept( *this );
	trueBranchChild->Accept( *this );

	boost::shared_ptr< IInstruction > const falseBranchChild
		= _visitable.getFalseBranchChild();

	if ( falseBranchChild )
	{
		falseBranchChild->Accept( *this );
	}
}

void
SemanticAnalysisVisitor::Visit ( InstructionsList & _visitable )
{
	analiseList(
		_visitable.getChildList(),
		_visitable.getChild() );
}

void
SemanticAnalysisVisitor::Visit ( Number & _visitable )
{
	_visitable.setTypeHandler( m_typesController.getHandler( Semantics::BuildInType::create( "int" ), Scope::createGlobalScope() ) );
}

void
SemanticAnalysisVisitor::Visit ( Null & _visitable )
{
	_visitable.setTypeHandler(
        m_typesController.getHandler(
            Semantics::PointerType::create( Semantics::AnyType::create() ),
            Scope::createGlobalScope()
        )
    );
}

void
SemanticAnalysisVisitor::Visit( Parameter & _visitable )
{
	std::string const variableName = _visitable.getVariableName();
	_visitable.getType()->Accept( *this );
    assert( m_type );

	TypesController::Handler const typeHandler
		= m_typesController.smartInsert( m_type, Scope::createGlobalScope() );
    
    assert( ! typeHandler.isNull() );

	VariablesController::Handler const variableHandler
		= m_variablesController.getHandler( variableName, m_scope );
    
	try
	{
		throwIfVariableIsAlreadyDefined( m_variablesController, variableName, m_scope );
	}
	catch( Exceptions::VariableIsAlreadyDefinedException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< variableName
			<< std::endl;
		
		return;
	}
	
	_visitable.setVariableHandler(
		m_variablesController.insert(
			VariableData( variableName, typeHandler, m_scope, VariableType::Parameter )
		)
	);
	
	m_functionParametersTypes.push_back( typeHandler );
}

void
SemanticAnalysisVisitor::Visit ( ParametersList & _visitable )
{
	analiseList(
		_visitable.getChildList(),
		_visitable.getChild() );
}

void
SemanticAnalysisVisitor::Visit ( Parenthesis & _visitable )
{
	boost::shared_ptr< AssignmentExpression > const assignmentExpression
		= _visitable.getAssignmentExpression();
	assignmentExpression->Accept( *this );
	
	_visitable.setTypeHandler( assignmentExpression->getTypeHandler() );
}

void
SemanticAnalysisVisitor::Visit ( Syntax::PointerType & _visitable )
{
    _visitable.getPointedType()->Accept( *this );
    m_type = Semantics::PointerType::create( m_type );
}

void
SemanticAnalysisVisitor::Visit ( Program & _visitable )
{
	boost::shared_ptr< FunctionsList > const functionsList
		= _visitable.getFunctionsList();

	if ( functionsList )
	{
		functionsList->Accept( *this );
	}

	try
	{
		throwIfEmptyFileIsCompiled( functionsList );
	}
	catch( Exceptions::EmptyFileCompilationException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< std::endl;
		
		return;
	}
	
	try
	{
		throwIfFunctionIsNotDefined(
			m_functionsController,
			Function::getMainFunctionName(),
			Scope::createGlobalScope() );
	}
	catch( Exceptions::FunctionIsNotDefinedException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< Function::getMainFunctionName()
			<< std::endl;
			
		return;
	}
}

void
SemanticAnalysisVisitor::Visit ( ReturnInstruction & _visitable )
{
	boost::shared_ptr< AssignmentExpression > const assignmentExpression
		= _visitable.getAssignmentExpression();

	if ( assignmentExpression )
	{
		assignmentExpression->Accept( *this );
		_visitable.setTypeHandler( assignmentExpression->getTypeHandler() );
		
		m_isReturnInstruction = true;
	}
	else
	{
		_visitable.setTypeHandler(
			m_typesController.getHandler( Semantics::BuildInType::create( "void" ), Scope::createGlobalScope() ) );
	}
    
    try
    {
        boost::shared_ptr< Type > const resultType = throwIfTypesAreIncompatibile(
            m_typesController.getData( m_functionsController.getData( m_currentFunction->getHandler() ).getReturnValueType() ).getKey(),
            m_typesController.getData( _visitable.getTypeHandler() ).getKey(),
            boost::shared_ptr< Syntax::AssignOperator >( new Syntax::AssignOperator )
        );

        _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
    }
    catch( Exceptions::TypesIncompatibleException & _exception )
    {
        std::cerr
            << "In return function type: "
            << _exception.what()
            << std::endl;
    }
    
    if( m_currentFunction->getName() == Function::getMainFunctionName() )
    {
        _visitable.setProgramFinish( true );
    }
}

void
SemanticAnalysisVisitor::Visit ( SimpleExpression & _visitable )
{
	boost::shared_ptr< SimpleExpression > const simpleExpression
		= _visitable.getSimpleExpression();
	if ( simpleExpression )
	{
		simpleExpression->Accept( *this );
	}

	boost::shared_ptr< Factor > const factor = _visitable.getFactor();
	factor->Accept( *this );
    TypesController::Handler const factorTypeHandler = factor->getTypeHandler();

	if ( ! simpleExpression )
	{		
        _visitable.setTypeHandler( factorTypeHandler );
        return;
    }
    
    try
    {
        boost::shared_ptr< Type > const resultType = throwIfTypesAreIncompatibile(
            m_typesController.getData( simpleExpression->getTypeHandler() ).getKey(),
            m_typesController.getData( factorTypeHandler ).getKey(),
            _visitable.getOperator()
        );

        _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
    }
    catch( Exceptions::TypesIncompatibleException & _exception )
    {
        std::cerr
            << _exception.what()
            << std::endl;
    }
}

void
SemanticAnalysisVisitor::Visit ( String & _visitable )
{
	std::string const stringName = _visitable.getValue();
	
	if ( isSymbolAlreadyDefined( m_stringsController, stringName, Scope::createGlobalScope() ) )
	{
		return;
	}
	
	// all strings are created in the same `global scope'
	// two the same strings in two different places in code,
	// are kept in the same memory location
	
	_visitable.setHandler(
		m_stringsController.insert( StringData( stringName, Scope::createGlobalScope() ) ) );
}

void
SemanticAnalysisVisitor::Visit ( UnaryFactor & _visitable )
{
	boost::shared_ptr< IUnit > const unit = _visitable.getUnit();
	unit->Accept( *this );
    
    if( ! _visitable.getOperator() )
    {
        _visitable.setTypeHandler( unit->getTypeHandler() );
        return;
    }
    
    try
    {
        boost::shared_ptr< Type > const resultType = throwIfTypeIsIncompatibile(
            m_typesController.getData( unit->getTypeHandler() ).getKey(),
            _visitable.getOperator()
        );

        _visitable.setTypeHandler( m_typesController.smartInsert( resultType, Scope::createGlobalScope() ) );
    }
    catch( Exceptions::TypesIncompatibleException & _exception )
    {
        std::cerr
            << _exception.what()
            << std::endl;
    }
}

void
SemanticAnalysisVisitor::Visit ( Variable & _visitable )
{
	std::string const variableName = _visitable.getName();
	
	try
	{
		throwIfVariableIsNotDefined(
			m_variablesController,
			variableName,
			m_scope );
	}
	catch( Exceptions::VariableIsNotDefinedException const & _exception )
	{
		std::cerr
			<< _exception.what()
			<< ": "
			<< variableName
			<< std::endl;
		
		return;
	}

	VariablesController::Handler const variableHandler
		= m_variablesController.getHandler( variableName, m_scope );

	_visitable.setHandler( variableHandler );

	_visitable.setTypeHandler( m_variablesController.getData( variableHandler ).getType() );
}

void
SemanticAnalysisVisitor::Visit ( WhileInstruction & _visitable )
{
    m_currentLoop.push_back( & _visitable );
    
	_visitable.getConditionChild()->Accept( *this );	
	_visitable.getBodyChild()->Accept( *this );
    
    m_currentLoop.pop_back();
}

template< typename _List, typename _Element >
void
SemanticAnalysisVisitor::analiseList(
	_List _list,
	_Element _element
)
{
	if ( _list )
	{
		_list->Accept( *this );
	}

	if ( _element )
	{
		_element->Accept( *this );
	}
}

}
