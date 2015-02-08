#ifndef YY_BisonParser_h_included
#define YY_BisonParser_h_included
#define YY_USE_CLASS

#line 1 "/usr/share/bison++/bison.h"
/* before anything */
#ifdef c_plusplus
 #ifndef __cplusplus
  #define __cplusplus
 #endif
#endif


 #line 8 "/usr/share/bison++/bison.h"
#define YY_BisonParser_STYPE  Syntax::SemanticValueStack
#define YY_BisonParser_CONSTRUCTOR_PARAM 	std::istream* _in, std::ostream* _out
#define YY_BisonParser_CONSTRUCTOR_INIT 	: m_lexer( _in, _out )
#define YY_BisonParser_CONSTRUCTOR_CODE 	{}
#define YY_BisonParser_MEMBERS 		\
	public:			\
		virtual ~BisonParser(){} \
		boost::shared_ptr< Syntax::Program > getProgram(){ return m_program; } \
	protected:		\
		yyFlexLexer m_lexer; \
		boost::shared_ptr< Syntax::Program > m_program;
#define YY_BisonParser_LEX_BODY  { return m_lexer.yylex(); }
#define YY_BisonParser_ERROR_BODY  { std::cerr << "Syntax error" << std::endl; }
#define YY_BisonParser_DEBUG  1

#line 21 "/usr/share/bison++/bison.h"
 /* %{ and %header{ and %union, during decl */
#ifndef YY_BisonParser_COMPATIBILITY
 #ifndef YY_USE_CLASS
  #define  YY_BisonParser_COMPATIBILITY 1
 #else
  #define  YY_BisonParser_COMPATIBILITY 0
 #endif
#endif

#if YY_BisonParser_COMPATIBILITY != 0
/* backward compatibility */
 #ifdef YYLTYPE
  #ifndef YY_BisonParser_LTYPE
   #define YY_BisonParser_LTYPE YYLTYPE
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
/* use %define LTYPE */
  #endif
 #endif
/*#ifdef YYSTYPE*/
  #ifndef YY_BisonParser_STYPE
   #define YY_BisonParser_STYPE YYSTYPE
  /* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
   /* use %define STYPE */
  #endif
/*#endif*/
 #ifdef YYDEBUG
  #ifndef YY_BisonParser_DEBUG
   #define  YY_BisonParser_DEBUG YYDEBUG
   /* WARNING obsolete !!! user defined YYDEBUG not reported into generated header */
   /* use %define DEBUG */
  #endif
 #endif 
 /* use goto to be compatible */
 #ifndef YY_BisonParser_USE_GOTO
  #define YY_BisonParser_USE_GOTO 1
 #endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_BisonParser_USE_GOTO
 #define YY_BisonParser_USE_GOTO 0
#endif

#ifndef YY_BisonParser_PURE

 #line 65 "/usr/share/bison++/bison.h"

#line 65 "/usr/share/bison++/bison.h"
/* YY_BisonParser_PURE */
#endif


 #line 68 "/usr/share/bison++/bison.h"

#line 68 "/usr/share/bison++/bison.h"
/* prefix */

#ifndef YY_BisonParser_DEBUG

 #line 71 "/usr/share/bison++/bison.h"

#line 71 "/usr/share/bison++/bison.h"
/* YY_BisonParser_DEBUG */
#endif

#ifndef YY_BisonParser_LSP_NEEDED

 #line 75 "/usr/share/bison++/bison.h"

#line 75 "/usr/share/bison++/bison.h"
 /* YY_BisonParser_LSP_NEEDED*/
#endif

/* DEFAULT LTYPE*/
#ifdef YY_BisonParser_LSP_NEEDED
 #ifndef YY_BisonParser_LTYPE
  #ifndef BISON_YYLTYPE_ISDECLARED
   #define BISON_YYLTYPE_ISDECLARED
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;
  #endif

  #define YY_BisonParser_LTYPE yyltype
 #endif
#endif

/* DEFAULT STYPE*/
#ifndef YY_BisonParser_STYPE
 #define YY_BisonParser_STYPE int
#endif

/* DEFAULT MISCELANEOUS */
#ifndef YY_BisonParser_PARSE
 #define YY_BisonParser_PARSE yyparse
#endif

#ifndef YY_BisonParser_LEX
 #define YY_BisonParser_LEX yylex
#endif

#ifndef YY_BisonParser_LVAL
 #define YY_BisonParser_LVAL yylval
#endif

#ifndef YY_BisonParser_LLOC
 #define YY_BisonParser_LLOC yylloc
#endif

#ifndef YY_BisonParser_CHAR
 #define YY_BisonParser_CHAR yychar
#endif

#ifndef YY_BisonParser_NERRS
 #define YY_BisonParser_NERRS yynerrs
#endif

#ifndef YY_BisonParser_DEBUG_FLAG
 #define YY_BisonParser_DEBUG_FLAG yydebug
#endif

#ifndef YY_BisonParser_ERROR
 #define YY_BisonParser_ERROR yyerror
#endif

#ifndef YY_BisonParser_PARSE_PARAM
 #ifndef __STDC__
  #ifndef __cplusplus
   #ifndef YY_USE_CLASS
    #define YY_BisonParser_PARSE_PARAM
    #ifndef YY_BisonParser_PARSE_PARAM_DEF
     #define YY_BisonParser_PARSE_PARAM_DEF
    #endif
   #endif
  #endif
 #endif
 #ifndef YY_BisonParser_PARSE_PARAM
  #define YY_BisonParser_PARSE_PARAM void
 #endif
#endif

/* TOKEN C */
#ifndef YY_USE_CLASS

 #ifndef YY_BisonParser_PURE
  #ifndef yylval
   extern YY_BisonParser_STYPE YY_BisonParser_LVAL;
  #else
   #if yylval != YY_BisonParser_LVAL
    extern YY_BisonParser_STYPE YY_BisonParser_LVAL;
   #else
    #warning "Namespace conflict, disabling some functionality (bison++ only)"
   #endif
  #endif
 #endif


 #line 169 "/usr/share/bison++/bison.h"
#define	NULL_UNIT	258
#define	NUMBER	259
#define	IDENTIFIER	260
#define	STRING	261
#define	ALL	262
#define	BASIC_TYPE	263
#define	BREAK	264
#define	CONTINUE	265
#define	DO	266
#define	IF	267
#define	FOR	268
#define	RETURN	269
#define	WHILE	270
#define	IFX	271
#define	ELSE	272
#define	EQ	273
#define	NEQ	274
#define	OR	275
#define	AND	276


#line 169 "/usr/share/bison++/bison.h"
 /* #defines token */
/* after #define tokens, before const tokens S5*/
#else
 #ifndef YY_BisonParser_CLASS
  #define YY_BisonParser_CLASS BisonParser
 #endif

 #ifndef YY_BisonParser_INHERIT
  #define YY_BisonParser_INHERIT
 #endif

 #ifndef YY_BisonParser_MEMBERS
  #define YY_BisonParser_MEMBERS 
 #endif

 #ifndef YY_BisonParser_LEX_BODY
  #define YY_BisonParser_LEX_BODY  
 #endif

 #ifndef YY_BisonParser_ERROR_BODY
  #define YY_BisonParser_ERROR_BODY  
 #endif

 #ifndef YY_BisonParser_CONSTRUCTOR_PARAM
  #define YY_BisonParser_CONSTRUCTOR_PARAM
 #endif
 /* choose between enum and const */
 #ifndef YY_BisonParser_USE_CONST_TOKEN
  #define YY_BisonParser_USE_CONST_TOKEN 0
  /* yes enum is more compatible with flex,  */
  /* so by default we use it */ 
 #endif
 #if YY_BisonParser_USE_CONST_TOKEN != 0
  #ifndef YY_BisonParser_ENUM_TOKEN
   #define YY_BisonParser_ENUM_TOKEN yy_BisonParser_enum_token
  #endif
 #endif

class YY_BisonParser_CLASS YY_BisonParser_INHERIT
{
public: 
 #if YY_BisonParser_USE_CONST_TOKEN != 0
  /* static const int token ... */
  
 #line 212 "/usr/share/bison++/bison.h"
static const int NULL_UNIT;
static const int NUMBER;
static const int IDENTIFIER;
static const int STRING;
static const int ALL;
static const int BASIC_TYPE;
static const int BREAK;
static const int CONTINUE;
static const int DO;
static const int IF;
static const int FOR;
static const int RETURN;
static const int WHILE;
static const int IFX;
static const int ELSE;
static const int EQ;
static const int NEQ;
static const int OR;
static const int AND;


#line 212 "/usr/share/bison++/bison.h"
 /* decl const */
 #else
  enum YY_BisonParser_ENUM_TOKEN { YY_BisonParser_NULL_TOKEN=0
  
 #line 215 "/usr/share/bison++/bison.h"
	,NULL_UNIT=258
	,NUMBER=259
	,IDENTIFIER=260
	,STRING=261
	,ALL=262
	,BASIC_TYPE=263
	,BREAK=264
	,CONTINUE=265
	,DO=266
	,IF=267
	,FOR=268
	,RETURN=269
	,WHILE=270
	,IFX=271
	,ELSE=272
	,EQ=273
	,NEQ=274
	,OR=275
	,AND=276


#line 215 "/usr/share/bison++/bison.h"
 /* enum token */
     }; /* end of enum declaration */
 #endif
public:
 int YY_BisonParser_PARSE(YY_BisonParser_PARSE_PARAM);
 virtual void YY_BisonParser_ERROR(char *msg) YY_BisonParser_ERROR_BODY;
 #ifdef YY_BisonParser_PURE
  #ifdef YY_BisonParser_LSP_NEEDED
   virtual int  YY_BisonParser_LEX(YY_BisonParser_STYPE *YY_BisonParser_LVAL,YY_BisonParser_LTYPE *YY_BisonParser_LLOC) YY_BisonParser_LEX_BODY;
  #else
   virtual int  YY_BisonParser_LEX(YY_BisonParser_STYPE *YY_BisonParser_LVAL) YY_BisonParser_LEX_BODY;
  #endif
 #else
  virtual int YY_BisonParser_LEX() YY_BisonParser_LEX_BODY;
  YY_BisonParser_STYPE YY_BisonParser_LVAL;
  #ifdef YY_BisonParser_LSP_NEEDED
   YY_BisonParser_LTYPE YY_BisonParser_LLOC;
  #endif
  int YY_BisonParser_NERRS;
  int YY_BisonParser_CHAR;
 #endif
 #if YY_BisonParser_DEBUG != 0
  public:
   int YY_BisonParser_DEBUG_FLAG;	/*  nonzero means print parse trace	*/
 #endif
public:
 YY_BisonParser_CLASS(YY_BisonParser_CONSTRUCTOR_PARAM);
public:
 YY_BisonParser_MEMBERS 
};
/* other declare folow */
#endif


#if YY_BisonParser_COMPATIBILITY != 0
 /* backward compatibility */
 /* Removed due to bison problems
 /#ifndef YYSTYPE
 / #define YYSTYPE YY_BisonParser_STYPE
 /#endif*/

 #ifndef YYLTYPE
  #define YYLTYPE YY_BisonParser_LTYPE
 #endif
 #ifndef YYDEBUG
  #ifdef YY_BisonParser_DEBUG 
   #define YYDEBUG YY_BisonParser_DEBUG
  #endif
 #endif

#endif
/* END */

 #line 267 "/usr/share/bison++/bison.h"
#endif
