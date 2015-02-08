#include "headers/ph.hpp"

#include "headers/code_generator.hpp"

namespace CodeGenerating
{

std::string
CodeGenerator::getCompilerVersion() const
{
    // Master Thesis Compiler
	return "mtc-1.0";
}

std::string
CodeGenerator::generateEAXRegister() const
{
	return std::string( "%eax" );
}
	
std::string
CodeGenerator::generateALRegister() const
{
	return std::string( "%al" );
}
	
std::string
CodeGenerator::generateEBXRegister() const
{
	return std::string( "%ebx" );
}

std::string
CodeGenerator::generateEBPRegister() const
{
	return std::string( "%ebp" );
}

std::string
CodeGenerator::generateESPRegister() const
{
	return std::string( "%esp" );
}

std::string
CodeGenerator::generateTabulatorsAsString( int _count ) const
{
	std::string tabulators;
	
	for ( int count = 0 ; count < _count ; ++count )
	{
		tabulators += '\t';
	}
	
	return tabulators;
}

std::string
CodeGenerator::generateStringLabelPattern() const
{
	return std::string( ".LSTRING" );
}

std::string
CodeGenerator::generateLabel( std::string const & _label ) const
{
	return _label + std::string( ":" );
}

std::string
CodeGenerator::generateReadOnlySection() const
{
	return std::string( ".section .rodata" );
}
	
std::string
CodeGenerator::generateTextSection() const
{
	return std::string( ".section .text" );
}

std::string
CodeGenerator::generateComment( std::string const & _comment ) const
{
    return std::string( "# " ) + _comment;
}

std::string
CodeGenerator::generateFileName( std::string const & _filename ) const
{
	return std::string( ".file \"" ) + _filename + std::string( "\"" );
}

std::string
CodeGenerator::generateIdentifier( std::string const & _compilerVersion ) const
{
	return std::string( ".ident \"" ) + _compilerVersion + std::string( "\"" );
}

std::string
CodeGenerator::generateFunctionSizeString( std::string const & _functionName ) const
{
	return
		std::string( ".size " ) + std::string( _functionName )
			+ std::string( ", .-" ) + _functionName;
}

std::string
CodeGenerator::generateFunctionNameAsGlobalSymbol( std::string const & _functionName ) const
{
	return std::string( ".globl " ) + _functionName;
}

std::string
CodeGenerator::generateAlign( unsigned _value ) const
{
	return std::string( ".align " ) + boost::lexical_cast< std::string >( _value );
}

std::string
CodeGenerator::generateStringType() const
{
	return std::string( ".string" );
}

std::string
CodeGenerator::generateFunctionsHeader( std::string const & _functionName ) const
{
	return std::string( ".type " ) + _functionName + std::string( ", @function" );
}

std::string
CodeGenerator::generateNumberAsString( int _value ) const
{
	return std::string( "$" ) + boost::lexical_cast< std::string >( _value );
}

std::string
CodeGenerator::generateHexadecimal( std::string const & _value ) const
{
	return std::string( "$" ) + _value;
}

std::string
CodeGenerator::generatePushCommand() const
{
	return std::string( "pushl" );
}
		
std::string
CodeGenerator::generatePopCommand() const
{
	return std::string( "popl" );
}

std::string
CodeGenerator::generateCompareCommand() const
{
	return std::string( "cmpl" );
}

std::string
CodeGenerator::generateMovCommand() const
{
	return std::string( "movl" );
}

std::string
CodeGenerator::generateLeaCommand() const
{
    return std::string( "leal" );
}

std::string
CodeGenerator::generateIntCommand() const
{
	return std::string( "int" );
}

std::string
CodeGenerator::generateSetCommand( std::string const & _condition ) const
{
	return std::string( "set" ) + _condition;
}

std::string
CodeGenerator::generateCallCommand() const
{
	return std::string( "call" );
}

std::string
CodeGenerator::generateEqualCondition() const
{
	return std::string( "e" );
}

std::string
CodeGenerator::generateNotEqualCondition() const
{
	return std::string( "ne" );
}

std::string
CodeGenerator::generateLessCondition() const
{
	return std::string( "l" );
}

std::string
CodeGenerator::generateGreaterCondition() const
{
	return std::string( "g" );
}

std::string
CodeGenerator::generateNegCommand() const
{
	return std::string( "negl" );
}

std::string
CodeGenerator::generateImulCommand() const
{
	return std::string( "imull" );
}

std::string
CodeGenerator::generateDivCommand() const
{
	return std::string( "divl" );
}

std::string
CodeGenerator::generateAddCommand() const
{
	return std::string( "addl" );
}

std::string
CodeGenerator::generateSubCommand() const
{
	return std::string( "subl" ) ;
}

std::string
CodeGenerator::generateExchangeCommand() const
{
	return std::string( "xchgl" );
}

std::string
CodeGenerator::generateAndCommand() const
{
	return std::string( "andl" );
}

std::string
CodeGenerator::generateJumpCommand( std::string const & _condition ) const
{
	return std::string( "j" ) + _condition;
}

std::string
CodeGenerator::generateGotoCommand() const
{
	return std::string( "jmp" );
}

std::string
CodeGenerator::generateOrCommand() const
{
	return std::string( "or" );
}

std::string
CodeGenerator::generateDereferenceOfAdderess( std::string const & _address ) const
{
	return std::string( "(" ) + _address + std::string( ")" );
}

std::string
CodeGenerator::generateDirectAddressingMode( std::string const & _address ) const
{
	return _address;
}

std::string
CodeGenerator::generateIndirectAddressingMode( std::string const & _address ) const
{
	return generateDereferenceOfAdderess( _address );
}

std::string
CodeGenerator::generateOneOperandInstruction(
	std::string const _instruction,
	std::string const & _operand
) const
{
	return _instruction + std::string( " " ) + _operand;
}

std::string
CodeGenerator::generateRetCommand() const
{
	return std::string( "ret" );
}

std::string
CodeGenerator::generateTwoOperandsInstruction(
	std::string const & _instruction,
	std::string const & _leftOperand,
	std::string const & _rightOperand
) const
{
	return
		_instruction
		+ std::string( " " )
		+ _leftOperand
		+ std::string( ", " )
		+ _rightOperand;
}

}
