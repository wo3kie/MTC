/* LEXICAL CONVENTIONS*/

%{
#include "headers/ph.hpp"

#include "headers/semantic_value_stack.hpp"

#include "headers/bison_parser.hpp"

#include "headers/keywords_table.hpp"

%}

%option outfile="scanner.cpp" header-file="./headers/scanner.hpp"
%option c++ 8bit warn debug
%option yylineno

whiteChar				[ \t]
newLine					\n

letter					[_a-zA-Z]

digit					[0-9]

identifier				{letter}({letter}|{digit})*
string					\"[^"\n]*\"

integer					{digit}{1,4}
/*number					{digit}+(\.{digit}*)?([eE][-+]?{digit}+)?*/

%%

"//".*$					{ // match one line C++ styled comment
						}

{identifier}			{
							boost::shared_ptr< Semantics::KeywordsTable const > const keywordsTable
								= Semantics::KeywordsTable::getInstance();
							
							return keywordsTable->getIdentifier( yytext );
						}

{string}				{
							return BisonParser::STRING;
						}

{integer}				{
							return BisonParser::NUMBER;
						}

"=="					{
							return BisonParser::EQ;
						}

"!="					{
							return BisonParser::NEQ;
						}

"||"					{
							return BisonParser::OR;
						}

"&&"					{
							return BisonParser::AND;
						}


 /* operators */
[-()<>=+*/;{}.,^&]		{
							return yytext[ 0 ];
						}


{whiteChar}				{/*do nothing*/}
{newLine}				{
						}

.						{
							std::cerr << "Unknown character: `" << yytext << '\'' << std::endl;
						}

%%

// Note this needs to be here
// If you define no yywrap() in the options it gets added to the header file
// which leads to multiple definitions if you are not careful.
// http://stackoverflow.com/questions/8013755/using-lex-generated-source-code-in-another-file
int yyFlexLexer::yywrap()   { return 1;}
