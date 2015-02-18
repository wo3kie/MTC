# MTC

## Master Thesis Compiler
My master thesis `Syntax, semantics analysis methods and assembly code generating for Intel x86 architecture' describes lexical analysis, parsing theory, semantic analysis focused on types and classes and computer's architecture basics. A compiler was done as a practical part of it.


## Copyright (C) 2007 Lukasz Czerwinski


## Most important links:
GitHub source code  : https://github.com/wo3kie/MTC

  
## Requirements
* C++03
* flex++, optional, only if you change scanner.l, tested with flex++ 2.5.35
* bison++, optional, only if you change bison_parser.y, tested with bison++ 1.21.9-1
* loki library, included as part of my code in version 0.1.7 (http://loki-lib.sourceforge.net/)
  
  
## How to build code?
* make


## How to run a code?
./mtc.sh tests/expression_1.mtc


## How to write your own program
Please follow examples in 'tests' directory. Shortly speaking mtc supports C syntax with no structs.

```
// tests/factorial.mtc

int factorial_recursive( int _value ){
    if( _value == 0 ) return 1;
    else return _value * factorial_recursive( _value - 1 );
}

int factorial_for( int _value ){
    int result = 1;

    for( int start = 1 ; start < _value + 1; start = start + 1 ){
        result = result * start;
    }

    return result;
}

int main(){
    return factorial_recursive( 4 ) - factorial_for( 4 );
}
```

```
// tests/function_arguments_2.mtc

int * Pint_F_Pint( int * p ){
    return p;
}

int int_F_Pint( int * p ){
    return * p;
}

int int_F_int_Pint( int i, int * p ){
    return i + * p;
}

int main(){
    int i1 = 3;
    int * p1 = & i1;

    if( Pint_F_Pint( & i1 ) != & i1 ) return 1;
    if( Pint_F_Pint( p1 ) != p1 ) return 2;

    if( int_F_Pint( & i1 ) != i1 ) return 3;
    if( int_F_Pint( p1 ) != i1 ) return 4;
    if( int_F_Pint( Pint_F_Pint( & i1 ) ) != i1 ) return 5;
    if( int_F_Pint( Pint_F_Pint( p1 ) ) != i1 ) return 6;

    if( int_F_int_Pint( 3, p1 ) != 6 ) return 7;
    if( int_F_int_Pint( int_F_Pint( p1 ), & i1 ) != 6 ) return 8;

    return 0;
}
```

