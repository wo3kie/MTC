## Copyright (C) 2007 Łukasz Czerwiński

## Master Thesis Compiler
This project it a practical part of my master thesis `Syntax, semantics analysis methods and assembly code generating for Intel x86 architecture' describes lexical analysis, parsing theory, semantic analysis focused on types and classes and computer's architecture basics. It contains a source code of a compiler for a simplified version of C language.

## Website
https://github.com/wo3kie/mtc

## Requirements
* C++03
* flex++ >=2.5.35, optional, only if you change scanner.l
* bison++ >= 1.21.9-1, optional, only if you change bison_parser.y
* loki library, included as part of my code in version 0.1.7 [link](http://loki-lib.sourceforge.net/)
  
## How to build code?
make

## How to run it?
./mtc.sh tests/expression_1.mtc

## How to write your own program
Please follow examples in 'tests' directory. Shortly speaking mtc has C like syntax with no struct support.
  
```{r, engine='cpp'}
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

