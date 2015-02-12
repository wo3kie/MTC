# MTC

## Master Thesis Compiler
My master thesis `Syntax, semantics analysis methods and assembly code generating for Intel x86 architecture' describes lexical analysis, parsing theory, semantic analysis focused on types and classes and computer's architecture basics. A compiler was done as a practical part of it.


## Copyright (C) 2007 Lukasz Czerwinski


## Most important links:
GitHub source code  : https://github.com/wo3kie/MTC

  
## Requirements
* C++03
* flex++
* bison++
* loki library (http://loki-lib.sourceforge.net/) (included as part of my code in version 0.1.7)
  
  
## How to build code?
* make all


## How to run a code?
./mtc.sh tests/expression_1.mtc


## How to write your own program
Please follow examples in 'tests' directory. Shortly speaking mtc supports C syntax with no structs.

tests/factorial.mtc
  1 int factorial_recursive( int _value ){
  2     if( _value == 0 ) return 1;
  3     else return _value * factorial_recursive( _value - 1 );
  4 }
  5 
  6 int factorial_for( int _value ){
  7     int result = 1;
  8 
  9     for( int start = 1 ; start < _value + 1; start = start + 1 ){
 10         result = result * start;
 11     }
 12 
 13     return result;
 14 }
 15 
 16 int main(){
 17     return factorial_recursive( 4 ) - factorial_for( 4 );
 18 }
~

tests/function_arguments_2.mtc
  1 int * Pint_F_Pint( int * p ){
  2     return p;
  3 }
  4 
  5 int int_F_Pint( int * p ){
  6     return * p;
  7 }
  8 
  9 int int_F_int_Pint( int i, int * p ){
 10     return i + * p;
 11 }
 12 
 13 int main(){
 14     int i1 = 3;
 15     int * p1 = & i1;
 16 
 17     if( Pint_F_Pint( & i1 ) != & i1 ) return 1;
 18     if( Pint_F_Pint( p1 ) != p1 ) return 2;
 19 
 20     if( int_F_Pint( & i1 ) != i1 ) return 3;
 21     if( int_F_Pint( p1 ) != i1 ) return 4;
 22     if( int_F_Pint( Pint_F_Pint( & i1 ) ) != i1 ) return 5;
 23     if( int_F_Pint( Pint_F_Pint( p1 ) ) != i1 ) return 6;
 24 
 25     if( int_F_int_Pint( 3, p1 ) != 6 ) return 7;
 26     if( int_F_int_Pint( int_F_Pint( p1 ), & i1 ) != 6 ) return 8;
 27 
 28     return 0;
 29 }
~           
