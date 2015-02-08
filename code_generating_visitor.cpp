#include "headers/ph.hpp"

#include "headers/code_generating_visitor.hpp"

#include "headers/function_data.hpp"
#include "headers/precondition.hpp"

using std::cin;
using std::cerr;
using std::cout;
using std::endl;

namespace CodeGenerating
{

CodeGeneratingVisitor::CodeGeneratingVisitor(
	Semantics::FunctionsController & _functionsController,
	Semantics::StringsController & _stringsController,
	Semantics::TypesController & _typesController,
	Semantics::VariablesController & _variablesController
)
	: m_functionsController( _functionsController )
	, m_stringsController( _stringsController )
	, m_typesController( _typesController )
	, m_variablesController( _variablesController )
	, m_defaultAlign( 2 )
{
}

void
CodeGeneratingVisitor::Visit( ISyntaxTreeNode & _visitable )
{
	assert( ! typeid( _visitable ).name() );
}

void 
CodeGeneratingVisitor::Visit ( AssignmentExpression & _visitable )
{    
    boost::shared_ptr< Expression > const expression = _visitable.getExpression();
    
    if ( ! expression )
    {
        return;
    }
    
    expression->Accept( * this );
    // w tym miejscu prawa strona jest w rejestrze eax
    
    boost::shared_ptr< AssignmentExpression > const assignmentExpression
        = _visitable.getAssignmentExpression();
    
    if ( ! assignmentExpression )
    {
        return;
    }

    Syntax::IUnit::AddressingMode const targetAddressingMode
        = Syntax::getUnitAssignTo( _visitable )->getAddressingMode();
    assert( targetAddressingMode );
    
    if( targetAddressingMode == & CodeGenerating::CodeGenerator::generateDirectAddressingMode )
    {
        boost::shared_ptr< IUnit > const unit = Syntax::getUnitAssignTo( _visitable );
		boost::shared_ptr< Variable > const variablePointer = boost::dynamic_pointer_cast< Variable >( unit );
		
		assert( variablePointer );
		
		int stackOffset
			= m_variablesController.getData( variablePointer->getHandler() ).getStackOffset();
		
		std::string variableString
			= boost::lexical_cast< std::string >( stackOffset )
			+ generateDereferenceOfAdderess( generateEBPRegister() );
		
		cout
			<< generateTabulatorsAsString( 1 )
			<< generateTwoOperandsInstruction(
				generateMovCommand(),
				generateEAXRegister(),
				variableString )
			<< endl;
        
        return;
    }
    
    // movl %eax, %ebx
    cout
        << generateTabulatorsAsString( 1 )
        << generateTwoOperandsInstruction(
            generateMovCommand(),
            generateEAXRegister(),
            generateEBXRegister() )
        << endl;

    assignmentExpression->getExpression()->Accept( * this );
    
    // w tym miejscu mam lewa strona w rejestrze eax
 
    CodeGenerator const * const castedThis = dynamic_cast< CodeGenerator const * const >( this );
    assert( castedThis );
     
    // movl %ebx, %eax | movl %ebx, ( %eax ) | ... depending on addressing mode
    cout
        << generateTabulatorsAsString( 1 )
        << generateTwoOperandsInstruction(
            generateMovCommand(),
            generateEBXRegister(),
            ( castedThis ->* targetAddressingMode )( generateEAXRegister() )
           )
        << endl;
}

void
CodeGeneratingVisitor::Visit ( BreakInstruction & _visitable )
{
    LoopInstruction const * const loopPointer
        = dynamic_cast< LoopInstruction const * const >( _visitable.getLoop() );
    
    assert( loopPointer );
    
    cout
        << generateTabulatorsAsString( 1 )
        << generateOneOperandInstruction(
			generateGotoCommand(),
			loopPointer->getEndLabel() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( CompoundInstruction & _visitable )
{
	_visitable.getInstructionsList()->Accept( *this );
}

void
CodeGeneratingVisitor::Visit ( ContinueInstruction & _visitable )
{
    LoopInstruction const * const loopPointer
        = dynamic_cast< LoopInstruction const * const >( _visitable.getLoop() );
    
    assert( loopPointer );
    
    cout
        << generateTabulatorsAsString( 1 )
        << generateOneOperandInstruction(
			generateGotoCommand(),
			loopPointer->getContinueLabel() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( Declaration & _visitable )
{
	boost::shared_ptr< Expression > const initializingExpression
		= _visitable.getInitializationChild();

	if ( ! initializingExpression )
	{
		return;
	}
	
	initializingExpression->Accept( *this );
	
 	std::string const variable
 		= boost::lexical_cast< std::string >(
 			m_variablesController.getData( _visitable.getVariableHandler() ).getStackOffset() )
 		+ generateDereferenceOfAdderess( generateEBPRegister() );
 	
 	cout
 		<< generateTabulatorsAsString( 1 )
 		<< generateTwoOperandsInstruction(
 			generateMovCommand(),
 			generateEAXRegister(),
 			variable )
 		<< endl;
}

void
CodeGeneratingVisitor::Visit ( Dereference & _visitable )
{
    boost::shared_ptr< IUnit > const unit = _visitable.getUnit();
    
    unit->Accept( *this );

    if( _visitable.getAssignmentSide() == Dereference::AssignmentSide::Left )
    {
        return;
    }
    
    // movl (%eax), %eax
 	cout
 		<< generateTabulatorsAsString( 1 )
 		<< generateTwoOperandsInstruction(
 			generateMovCommand(),
 			generateDereferenceOfAdderess( generateEAXRegister() ),
 			generateEAXRegister()
           )
        << endl;    
}
	
void
CodeGeneratingVisitor::Visit ( DoWhileInstruction & _visitable )
{
	cout
		<< generateComment( "do while loop begin" )
		<< endl;

	cout
		<< generateLabel( _visitable.getBeginLabel() )
		<< endl;

	_visitable.getBodyChild()->Accept( *this );

	_visitable.getConditionChild()->Accept( *this );

	cout
		// cmpl $1, %eax
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateCompareCommand(),
			generateNumberAsString( 0 ),
			generateEAXRegister() )
		<< endl;
	
	cout
		// je `endLabel'
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateJumpCommand( generateEqualCondition() ),
			_visitable.getEndLabel() )
		<< endl;

	cout
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateGotoCommand(),
			_visitable.getBeginLabel() )
		<< endl;

	cout
		<< generateLabel( _visitable.getEndLabel() )
		<< endl;

	cout
		<< generateComment( "do while loop end" )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( Expression & _visitable )
{
	generateCodeForTwoChildedNode(
		_visitable.getExpression(),
		_visitable.getOperator(),
		_visitable.getSimpleExpression() );
}

void
CodeGeneratingVisitor::Visit ( ExpressionsList & _visitable )
{
	generateCodeForList(
		_visitable.getChildList(),
		_visitable.getChild() );
}

void
CodeGeneratingVisitor::Visit ( Factor & _visitable )
{
	generateCodeForTwoChildedNode(
		_visitable.getFactor(),
		_visitable.getOperator(),
		_visitable.getUnaryFactor() );
}

void
CodeGeneratingVisitor::Visit ( ForInstruction & _visitable )
{
	cout
		<< generateComment( "for loop begin" )
		<< endl;

	_visitable.getDeclarationChild()->Accept( *this );

	cout
		<< generateLabel( _visitable.getBeginLabel() )
		<< endl;

	_visitable.getConditionChild()->Accept( *this );

	cout
		// cmpl $1, %eax
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateCompareCommand(),
			generateNumberAsString( 0 ),
			generateEAXRegister() )
		<< endl;
	
	cout
		// je `endLabel'
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateJumpCommand( generateEqualCondition() ),
			_visitable.getEndLabel() )
		<< endl;

	_visitable.getBodyChild()->Accept( *this );

    cout
        << generateLabel( _visitable.getContinueLabel() )
        << endl;
    
	_visitable.getIncrementationChild()->Accept( *this );

	cout
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateGotoCommand(),
			_visitable.getBeginLabel() )
		<< endl;

	cout
		<< generateLabel( _visitable.getEndLabel() )
		<< endl;

	cout
		<< generateComment( "for loop end" )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( Function & _visitable )
{
	Semantics::FunctionData const functionData
		= m_functionsController.getData( _visitable.getHandler() );
		
	std::string const functionName = functionData.getKey();
	
	cout
		<< generateFunctionNameAsGlobalSymbol( functionName )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateFunctionsHeader( functionName )
		<< endl
		<< generateLabel( functionName )
		<< endl;
	
	if ( _visitable.getName() == Function::getMainFunctionName() )
	{
		cout
			<< generateLabel( "_start" )
			<< endl;
	}
	
	cout
		// pushl %ebp
		<< generateComment( "save base register on stack" )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generatePushCommand(),
			generateEBPRegister() )
		<< endl;
		
	cout
		// movl %esp, %ebp
		<< generateComment( "set base register as current stack's address" )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			generateESPRegister(),
			generateEBPRegister() )
		<< endl;
	
	cout
		// movl sub $`liczba`, %esp
		<< generateComment( "make place for local variables on stack" )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateSubCommand(),
			generateNumberAsString(
				m_variablesController.getVariablesCapacity(
					functionData.getFunctionBodyScope() ) ),
			generateESPRegister() )
		<< endl;
	
	_visitable.getFunctionBody()->Accept( *this );
	
	cout
		// movl %ebp, %esp
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			generateEBPRegister(),
			generateESPRegister() )
		<< endl;
		
	cout
		// pop %ebp
		<< generateComment( "restore old base pointer" )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generatePopCommand(),
			generateEBPRegister() )
		<< endl;
	
	if ( _visitable.getName() == Function::getMainFunctionName() )
	{
		generateExitProgramSequenceCode();
	}
	else
	{
		cout
			// ret
			<< generateTabulatorsAsString( 1 )
			<< generateRetCommand()
			<< endl;
	}
	
	cout
		// .size `functionName`, .-`functionName`
		<< generateFunctionSizeString( functionName )
		<< endl
		<< generateAlign( m_defaultAlign )
		<< endl
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( FunctionCall & _visitable )
{
	unsigned memoryCapacityOfParameters = 0;
    
    cout
        << generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generatePushCommand(),
			generateEBXRegister() )
		<< endl;

	boost::shared_ptr< ExpressionsList > expressionsListRoot
		= _visitable.getExpressionsList();

	while ( expressionsListRoot )
	{
		boost::shared_ptr< AssignmentExpression > const assignmentExpression
			= expressionsListRoot->getChild();
		
		assignmentExpression->Accept( *this );
		
		cout
			<< generateComment( "push function call argument on stack" )
			<< endl
			<< generateTabulatorsAsString( 1 )
			<< generateOneOperandInstruction(
				generatePushCommand(),
				generateEAXRegister() )
			<< endl;
			
		memoryCapacityOfParameters
			+= m_typesController.getData(
				assignmentExpression->getTypeHandler() ).getMemoryCapacity();
		
		expressionsListRoot = expressionsListRoot->getChildList();
	}

	cout
		<< generateComment( "call function" )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateCallCommand(),
			_visitable.getFunctionName() )
		<< endl;
		
	cout
		<< generateComment( "remove parameters from stack" )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateAddCommand(),
			generateNumberAsString( memoryCapacityOfParameters ),
			generateESPRegister() )
		<< endl;
       
    cout
        << generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generatePopCommand(),
			generateEBXRegister() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( FunctionsList & _visitable )
{
	generateCodeForList(
		_visitable.getChildList(),
		_visitable.getChild() );
}

void
CodeGeneratingVisitor::Visit ( GetAddress & _visitable )
{
    // -`offset`(%ebp)
	std::string const variable
		= boost::lexical_cast< std::string >(
			m_variablesController.getData(
                _visitable.getVariable()->getHandler()
            ).getStackOffset() )
		+ generateDereferenceOfAdderess( generateEBPRegister() );
			
    cout
        // leal -`offset', (%ebp)
        << generateTabulatorsAsString( 1 )
        << generateTwoOperandsInstruction(
            generateLeaCommand(),
            variable,
            generateEAXRegister()
           )
        << endl;
}

void
CodeGeneratingVisitor::Visit ( IfInstruction & _visitable )
{
	cout
		<< generateComment( "if instruction begin" )
		<< endl;
	
	_visitable.getConditionChild()->Accept( *this );
	
	cout
		// cmpl $1, %eax
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateCompareCommand(),
			generateNumberAsString( 1 ),
			generateEAXRegister() )
		<< endl;

    cout
        // je `trueBranchLabel'
        << generateTabulatorsAsString( 1 )
        << generateOneOperandInstruction(
            generateJumpCommand( generateEqualCondition() ),
            _visitable.getTrueBranchLabel() )
        << endl;
    
    if( _visitable.getFalseBranchChild() )
    {
        cout
            << generateLabel( _visitable.getFalseBranchLabel() )
            << endl;

        _visitable.getFalseBranchChild()->Accept( *this );
    }
    
    cout
        // jmp `endLabel'
        << generateTabulatorsAsString( 1 )
        << generateOneOperandInstruction(
            generateGotoCommand(),
            _visitable.getEndLabel() )
        << endl;
    
    cout
        << generateLabel( _visitable.getTrueBranchLabel() )
        << endl;
		
	_visitable.getTrueBranchChild()->Accept( *this );
		
	cout	
		<< generateLabel( _visitable.getEndLabel() )
		<< endl;
	
	cout
		<< generateComment( "if instruction end" )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( InstructionsList & _visitable )
{
	generateCodeForList(
		_visitable.getChildList(),
		_visitable.getChild() );
}

void
CodeGeneratingVisitor::Visit ( Number & _visitable )
{
	cout
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			generateNumberAsString( _visitable.getValue() ),
			generateEAXRegister() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( Null & _visitable )
{
    int const nullValue = 0;

	cout
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			generateNumberAsString( nullValue ),
			generateEAXRegister() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( ParametersList & _visitable )
{	
}

void
CodeGeneratingVisitor::Visit ( Parenthesis & _visitable )
{
	_visitable.getAssignmentExpression()->Accept( *this );
}

void
CodeGeneratingVisitor::Visit ( Program & _visitable )
{
	cout
		<< generateFileName( "main.cpp" )
		<< endl
		<< generateAlign( m_defaultAlign )
		<< endl;
	
	m_stringsController.generateCode( CodeGeneratingVisitor::CodeGenerator() );
	m_variablesController.calculateVariablesOffsetOnStack( m_typesController );
	
	cout
		<< generateTextSection()
		<< endl
		<< endl
		<< generateFunctionNameAsGlobalSymbol( "_start" )
		<< endl;
	
	boost::shared_ptr< FunctionsList > const functionsList = _visitable.getFunctionsList();
	functionsList->Accept( *this );
	
	cout
		<< generateIdentifier( getCompilerVersion() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( ReturnInstruction & _visitable )
{
	boost::shared_ptr< AssignmentExpression > const assignmentExpression
		= _visitable.getAssignmentExpression();
	
	if ( ! assignmentExpression )
	{
		return;
	}
	
	assignmentExpression->Accept( *this );
    
    if( _visitable.isProgramFinish() )
    {
        generateExitProgramSequenceCode();
    }
}

void
CodeGeneratingVisitor::Visit ( SimpleExpression & _visitable )
{
	generateCodeForTwoChildedNode(
		_visitable.getSimpleExpression(),
		_visitable.getOperator(),
		_visitable.getFactor() );
}

void
CodeGeneratingVisitor::Visit ( String & _visitable )
{
}

void
CodeGeneratingVisitor::Visit ( UnaryFactor & _visitable )
{	
	boost::shared_ptr< IUnit > const unit = _visitable.getUnit();
	unit->Accept( *this );
	
	boost::shared_ptr< UnaryOperator > const unaryOperator = _visitable.getOperator();
	
	if ( unaryOperator )
	{
		unaryOperator->Accept( *this );
		
		cout
			// negl %eax
			<< generateTabulatorsAsString( 1 )
			<< generateNegCommand()
			<< ' '
			<< generateEAXRegister()
			<< endl;
	}
}

void
CodeGeneratingVisitor::Visit ( Variable & _visitable )
{
	// -`offset`(%ebp)
	std::string const variable
		= boost::lexical_cast< std::string >(
			m_variablesController.getData( _visitable.getHandler() ).getStackOffset() )
		+ generateDereferenceOfAdderess( generateEBPRegister() );
		
	cout
		// movl `variable`, %eax
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			variable,
			generateEAXRegister() )
		<< endl;
}

void
CodeGeneratingVisitor::Visit ( WhileInstruction & _visitable )
{
	cout
		<< generateComment( "while loop begin" )
		<< endl;

	cout
		<< generateLabel( _visitable.getConditionLabel() )
		<< endl;
	
	_visitable.getConditionChild()->Accept( *this );
	
	cout
		// cmpl $1, %eax
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateCompareCommand(),
			generateNumberAsString( 0 ),
			generateEAXRegister() )
		<< endl;
	
	cout
		// je `endLabel'
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateJumpCommand( generateEqualCondition() ),
			_visitable.getEndLabel() )
		<< endl;
	
	cout
		<< generateLabel( _visitable.getBeginLabel() )
		<< endl;
	
	_visitable.getBodyChild()->Accept( *this );
	
	cout
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateGotoCommand(),
			_visitable.getConditionLabel() )
		<< endl;
	
	cout
		<< generateLabel( _visitable.getEndLabel() )
		<< endl;
	
	cout
		<< generateComment( "while loop end" )
		<< endl;

}

void
CodeGeneratingVisitor::Visit ( AssignOperator & _visitable )
{
}

void
CodeGeneratingVisitor::Visit ( EqualOperator & _visitable )
{
	generateRelationalConditionCode( generateEqualCondition() );
}

void
CodeGeneratingVisitor::Visit ( NotEqualOperator & _visitable )
{
	generateRelationalConditionCode( generateNotEqualCondition() );	
}

void
CodeGeneratingVisitor::Visit ( LessOperator & _visitable )
{
	generateRelationalConditionCode( generateLessCondition() );
}

void
CodeGeneratingVisitor::Visit ( GreaterOperator & _visitable )
{
	generateRelationalConditionCode( generateGreaterCondition() );
}

void
CodeGeneratingVisitor::Visit ( AndOperator & _visitable )
{
	generateLogicalConditionCode( generateAndCommand() );
}

void
CodeGeneratingVisitor::Visit ( OrOperator & _visitable )
{
	generateLogicalConditionCode( generateOrCommand() );
}

void
CodeGeneratingVisitor::Visit ( AdditionOperator & _visitable )
{
	PRECONDITION2( ! m_leftOperand.empty(), ! m_rightOperand.empty() )
	
	cout
		// addl `left`, `right`
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateAddCommand(),
			m_leftOperand,
			m_rightOperand );

	m_leftOperand = m_rightOperand = "";
}

void
CodeGeneratingVisitor::Visit ( SubtractionOperator & _visitable )
{
	PRECONDITION2( ! m_leftOperand.empty(), ! m_rightOperand.empty() )
	
	cout
		// xchgl `left`, `right`
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateExchangeCommand(),
			m_leftOperand,
			m_rightOperand )
		<< endl
		// subl `left`, `right`
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateSubCommand(),
			m_leftOperand,
			m_rightOperand );

	m_leftOperand = m_rightOperand = "";
}

void
CodeGeneratingVisitor::Visit ( MultiplicationOperator & _visitable )
{
	PRECONDITION2( ! m_leftOperand.empty(), ! m_rightOperand.empty() )
	
	cout
		// imull `left`, `right`
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateImulCommand(),
			m_leftOperand,
			m_rightOperand );

	m_leftOperand = m_rightOperand = "";
}

void
CodeGeneratingVisitor::Visit ( DivisionOperator & _visitable )
{
	PRECONDITION2( ! m_leftOperand.empty(), ! m_rightOperand.empty() )
	
	cout
		// divl `left`, `right`
		<< generateTwoOperandsInstruction(
			generateDivCommand(),
			m_leftOperand,
			m_rightOperand );

	m_leftOperand = m_rightOperand = "";
}

void
CodeGeneratingVisitor::Visit ( PlusOperator & _visitable )
{
	return /*empty*/;
}

void
CodeGeneratingVisitor::Visit ( MinusOperator & _visitable )
{
	return /*empty*/;
}

template< typename _Left, typename _Operator, typename _Right >
void
CodeGeneratingVisitor::generateCodeForTwoChildedNode(
	boost::shared_ptr< _Left > _left,
	boost::shared_ptr< _Operator > _operator,
	boost::shared_ptr< _Right > _right
)
{
	if ( _left )
	{
		_left->Accept( *this );
	
		cout
			// pushl %eax
			<< generateTabulatorsAsString( 1 )
			<< generateOneOperandInstruction(
				generatePushCommand(),
				generateEAXRegister() )
			<< endl;
	}
	
	_right->Accept( *this );
	
	if ( _left )
	{
		cout
			// popl %ebx
			<< generateTabulatorsAsString( 1 )
			<< generateOneOperandInstruction(
				generatePopCommand(),
				generateEBXRegister() )
			<< endl;
		
		m_leftOperand = generateEBXRegister();
		m_rightOperand = generateEAXRegister();
		
		_operator->Accept( *this );
			
		cout << endl;
	}
}

template< typename _List, typename _Element >
void
CodeGeneratingVisitor::generateCodeForList(
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

void
CodeGeneratingVisitor::generateExitProgramSequenceCode() const
{
	std::string const exitFunctionSystemCallID = "0x80";
	
	cout
		// movl %eax, %ebx
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			generateEAXRegister(),
			generateEBXRegister() )
		<< endl
		// movl $1, %eax
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateMovCommand(),
			generateNumberAsString( 1 ),
			generateEAXRegister() )
		<< endl
		// int $0x80
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateIntCommand(),
			generateHexadecimal( exitFunctionSystemCallID ) )
		<< endl;
}

void
CodeGeneratingVisitor::generateRelationalConditionCode( std::string const & _condition ) const
{
	PRECONDITION2( ! m_leftOperand.empty(), ! m_rightOperand.empty() )
	
	cout
		<< generateTabulatorsAsString( 1 )
		<< generateTwoOperandsInstruction(
			generateCompareCommand(),
			m_rightOperand,
			m_leftOperand )
		<< endl
		<< generateTabulatorsAsString( 1 )
		<< generateOneOperandInstruction(
			generateSetCommand( _condition ),
			generateALRegister() );

	m_leftOperand = m_rightOperand = "";
}

void
CodeGeneratingVisitor::generateLogicalConditionCode( std::string const & _operator ) const
{
	PRECONDITION2( ! m_leftOperand.empty(), ! m_rightOperand.empty() )
	
	cout
		// or `left`, `right`
		<< generateTwoOperandsInstruction(
			_operator,
			m_leftOperand,
			m_rightOperand );

	m_leftOperand = m_rightOperand = "";
}

}
