/**/
%{
#include "headers/ph.hpp"

#include "headers/semantic_value_stack.hpp"

#include "headers/operators.hpp"
#include "headers/scanner.hpp"

using namespace Syntax;
%}

%name BisonParser

//%union - cannot be used since shared pointers

%define STYPE Syntax::SemanticValueStack

%type< m_assignmentExpression > assignment_expression
%type< m_breakInstruction > break_instruction
%type< m_compoundInstruction > compound_instruction
%type< m_continueInstruction > continue_instruction
%type< m_declaration > declaration
%type< m_dereference > dereference
%type< m_doWhile > do_while_instruction
%type< m_expression > expression
%type< m_expressionsList > expressions_list
%type< m_factor > factor
%type< m_forInstruction > for_instruction
%type< m_function > function
%type< m_functionCall > function_call
%type< m_functionsList > functions_list
%type< m_getAddress > get_address
%type< m_string > identifier;
%type< m_ifInstruction > if_instruction
%type< m_instruction > instruction
%type< m_instructionsList > instructions_list
%type< m_number > number
%type< m_parametersList > paramaters_list
%type< m_parenthesis > parenthesis
%type< m_program > program
%type< m_returnInstruction > return_instruction
%type< m_simpleExpression > simple_expression
%type< m_type > type
%type< m_unaryFactor > unary_factor
%type< m_unit > unit
%type< m_whileInstruction > while_instruction

%token < m_null > NULL_UNIT
%token < m_number > NUMBER
%token < m_string > IDENTIFIER STRING

%token ALL BASIC_TYPE BREAK CONTINUE DO IF FOR RETURN WHILE
%nonassoc IFX
%nonassoc ELSE

%left '>' '<' EQ NEQ OR AND
%left '+' '-'
%left '*' '/'
%right '='

%define CONSTRUCTOR_PARAM	std::istream* _in, std::ostream* _out
%define CONSTRUCTOR_INIT	: m_lexer( _in, _out )
%define CONSTRUCTOR_CODE	{}

%define MEMBERS		\
	public:			\
		virtual ~BisonParser(){} \
		boost::shared_ptr< Syntax::Program > getProgram(){ return m_program; } \
	protected:		\
		yyFlexLexer m_lexer; \
		boost::shared_ptr< Syntax::Program > m_program;

%define LEX_BODY { return m_lexer.yylex(); }
%define ERROR_BODY { std::cerr << "Syntax error" << std::endl; }

%define DEBUG 1

%%

program:
	functions_list
				{ $$ = makeSharedPtr( new Program( $1 ) ); 
					m_program = $$;
				}
	;
	
functions_list:
	  functions_list function
	  			{ $$ = makeSharedPtr( new FunctionsList( $1, $2 ) ); }
	| function
				{ $$ = makeSharedPtr( new FunctionsList( $1 ) ); }
	;

function:
	  type identifier '(' paramaters_list ')' instruction
				{ $$ = makeSharedPtr( new Function( $1, $2, $4, $6 ) ); }
    | identifier '(' paramaters_list ')' '-' '>' type '{' instruction '}'
                { $$ = makeSharedPtr( new Function( $7, $1, $3, $9 ) ); }
    ;

paramaters_list:
	  paramaters_list ',' declaration
				{ $$ = makeSharedPtr( new ParametersList( $1, makeSharedPtr( new Parameter( $3 ) ) ) ); }
	| declaration
				{ $$ = makeSharedPtr( new ParametersList( makeSharedPtr( new Parameter( $1 ) ) ) ); }
	| /*empty*/
				{ $$ = makeSharedPtr( new ParametersList() ); }
	;

instruction:
	  compound_instruction
	  			{ $$ = $1; }
	| if_instruction
				{ $$ = $1; }
	| while_instruction
				{ $$ = $1; }
	| for_instruction
				{ $$ = $1; }
	| do_while_instruction
				{ $$ = $1; }
    | break_instruction
                { $$ = $1; }
    | continue_instruction
                { $$ = $1; }
	| return_instruction
				{ $$ = $1; }
	| declaration ';'
				{ $$ = $1; }
	| assignment_expression ';'
				{ $$ = $1; }
	;

declaration:
	  type identifier
				{ $$ = makeSharedPtr( new Declaration( $1, $2 ) ); }
	| type identifier '=' expression
				{ $$ = makeSharedPtr( new Declaration( $1, $2, $4 ) ); }
	;

type:
      type '*'
                { $$ = PointerType::create( $1 ); }
    | BASIC_TYPE
                { $$ = BuildInType::create( m_lexer.YYText() ); }
    ;

compound_instruction:
	'{' instructions_list '}'
				{ $$ = makeSharedPtr( new CompoundInstruction( $2 ) ); }
	;

instructions_list:
	  instructions_list instruction
	  			{ $$ = makeSharedPtr( new InstructionsList( $1, $2 ) ); }
	| instruction
				{ $$ = makeSharedPtr( new InstructionsList( $1 ) ); }
	;

if_instruction:
	  IF '(' assignment_expression ')' instruction %prec IFX
				{ $$ = makeSharedPtr( new IfInstruction( $3, $5 ) ); }
	| IF '(' assignment_expression ')' instruction ELSE instruction
				{ $$ = makeSharedPtr( new IfInstruction( $3, $5, $7 ) ); }
	;

while_instruction:
	WHILE '(' assignment_expression ')' instruction
				{ $$ = makeSharedPtr( new WhileInstruction( $3, $5 ) ); }
	;

for_instruction:
	FOR '(' declaration ';' assignment_expression ';' assignment_expression ')' instruction
				{ $$ = makeSharedPtr( new ForInstruction( $3, $5, $7, $9 ) ); }
	;

do_while_instruction:
	DO '{' instruction '}' WHILE '(' assignment_expression ')' ';'
				{ $$ = makeSharedPtr( new DoWhileInstruction( $3, $7 ) ); }
	;

break_instruction:
      BREAK ';'
                { $$ = BreakInstruction::create( 1 ); }
    | BREAK '(' number ')' ';'
                { $$ = BreakInstruction::create( $3 ); }
    | BREAK '(' ALL ')' ';'
                { $$ = BreakInstruction::createBreakAll(); }
    ;

continue_instruction:
      CONTINUE ';'
                { $$ = ContinueInstruction::create(); }
    ;

return_instruction:
	  RETURN ';'
				{ $$ = makeSharedPtr( new ReturnInstruction ); }
	| RETURN assignment_expression ';'
				{ $$ = makeSharedPtr( new ReturnInstruction( $2 ) ); }
	;

assignment_expression:
	  assignment_expression '=' expression
	  			{ $$ = makeSharedPtr( new AssignmentExpression( $1, $3 ) ); }
	| expression
				{ $$ = makeSharedPtr( new AssignmentExpression ( $1 ) ); }
	;

expression:
      expression '<' simple_expression
    			{ $$ = makeSharedPtr(
    				new Expression(
    					$1,
    					makeSharedPtr( new LessOperator() ),
    					$3) ); }
	| expression '>' simple_expression
				{ $$ = makeSharedPtr(
    				new Expression(
    					$1,
    					makeSharedPtr( new GreaterOperator() ),
    					$3) ); }
	| expression EQ simple_expression
				{ $$ = makeSharedPtr(
    				new Expression(
    					$1,
    					makeSharedPtr( new EqualOperator() ),
    					$3) ); }
	| expression NEQ simple_expression
				{ $$ = makeSharedPtr(
    				new Expression(
    					$1,
    					makeSharedPtr( new NotEqualOperator() ),
    					$3) ); }
	| expression OR simple_expression
				{ $$ = makeSharedPtr(
    				new Expression(
    					$1,
    					makeSharedPtr( new OrOperator() ),
    					$3) ); }
	| expression AND simple_expression
				{ $$ = makeSharedPtr(
    				new Expression(
    					$1,
    					makeSharedPtr( new AndOperator() ),
    					$3) ); }
	| simple_expression
				{ $$ = makeSharedPtr( new Expression( $1 ) ); }
	;

simple_expression:
	  simple_expression '+' factor
  				{ $$ = makeSharedPtr(
  					new SimpleExpression(
  						$1,
  						makeSharedPtr( new AdditionOperator() ),
  						$3 ) ); }
 	| simple_expression '-' factor
  				{ $$ = makeSharedPtr(
  					new SimpleExpression(
  						$1,
  						makeSharedPtr( new SubtractionOperator() ),
  						$3 ) ); }
	| factor
				{ $$ = boost::shared_ptr< SimpleExpression >( new SimpleExpression( $1 ) ); }
	;

factor:
	  factor '*' unary_factor
				{ $$ = makeSharedPtr(
					new Factor(
						$1,
						makeSharedPtr( new MultiplicationOperator() ),
						$3 ) ); }
	| factor '/' unary_factor
				{ $$ = makeSharedPtr(
					new Factor(
						$1,
						makeSharedPtr( new DivisionOperator() ),
						$3 ) ); }
	| unary_factor
				{ $$ = makeSharedPtr( new Factor( $1 ) ); }
	;

unary_factor:
	  '+' unit
				{ $$ = makeSharedPtr( new UnaryFactor( boost::shared_ptr< UnaryOperator >( ) ,$2 ) ); }
	| '-' unit
				{ $$ = makeSharedPtr( new UnaryFactor( makeSharedPtr( new MinusOperator ) ,$2 ) ); }
	| unit	
				{ $$ = makeSharedPtr( new UnaryFactor( $1 ) ); }
	;

unit:
	  identifier
  				{ $$ = boost::shared_ptr< IUnit >( new Variable( $1 ) ); }
	| function_call
				{ $$ = $1; }
	| number
				{ $$ = boost::shared_ptr< IUnit >( new Number( $1 ) ); }
	| STRING
				{ $$ = boost::shared_ptr< IUnit >( new String( m_lexer.YYText() ) ); }
	| parenthesis
				{ $$ = $1; }
    | get_address
                { $$ = $1; }
    | dereference
                { $$ = $1; }
    | NULL_UNIT
                { $$ = Null::create(); }
	;

get_address:
      '&' identifier
                { $$ = GetAddress::create( makeSharedPtr( new Variable( $2 ) ) ); }
    ;

dereference:
      '*' unit
                { $$ = Dereference::create( $2 ); }
    ;

function_call:
	identifier '(' expressions_list ')'
				{ $$ = makeSharedPtr( new FunctionCall( $1, $3 ) ); }
	;

expressions_list:
	  expressions_list ',' assignment_expression
				{ $$ = makeSharedPtr( new ExpressionsList( $1, $3 ) ); }
	| assignment_expression
				{ $$ = makeSharedPtr( new ExpressionsList( $1 ) ); }
	| /* NULL */
				{ $$ = boost::shared_ptr< ExpressionsList >(); }
	;

parenthesis:
	'(' assignment_expression ')'
				{ $$ = makeSharedPtr( new Parenthesis( $2 ) ); }
	;

number:
      NUMBER
                { $$ = boost::lexical_cast< int >( m_lexer.YYText() ); }

identifier:
	IDENTIFIER
				{ $$ = m_lexer.YYText(); }
	;

%%
