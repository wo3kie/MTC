#ifndef __CODE_GENERATING_CODE_GENERATOR_HPP__
#define __CODE_GENERATING_CODE_GENERATOR_HPP__

namespace CodeGenerating
{

class CodeGenerator
{
public:
	std::string getCompilerVersion() const;
	
	std::string generateEAXRegister() const;
	
	std::string generateALRegister() const;
	
	std::string generateEBXRegister() const;
	
	std::string generateEBPRegister() const;
	
	std::string generateESPRegister() const;
	
	std::string generateStringLabelPattern() const;
		
	std::string generateReadOnlySection() const;
	
	std::string generateTextSection() const;
	
	std::string generateTabulatorsAsString( int _count ) const;
	
	std::string generateLabel( std::string const & _label ) const;
		
	std::string generateComment( std::string const & _comment ) const;
	
	std::string generateFileName( std::string const & _filename ) const;
	
	std::string generateIdentifier( std::string const & _compilerVersion ) const;
		
	std::string generateFunctionSizeString( std::string const & _functionName ) const;
	
	std::string generateFunctionNameAsGlobalSymbol( std::string const & _functionName ) const;
	
	std::string generateAlign( unsigned _value ) const;
	
	std::string generateStringType() const;
	
	std::string generateNumberAsString( int _value ) const;

	std::string generateHexadecimal( std::string const & _value ) const;

	std::string generateFunctionsHeader( std::string const & _functionName ) const;
	
	std::string generatePushCommand() const;
		
	std::string generatePopCommand() const;
	
	std::string generateCompareCommand() const;
	
	std::string generateMovCommand() const;
    
    std::string generateLeaCommand() const;
	
	std::string generateIntCommand() const;
	
	std::string generateSetCommand( std::string const & _condition ) const;
	
	std::string generateJumpCommand( std::string const & _condition ) const;
	
	std::string generateGotoCommand() const;
	
	std::string generateAndCommand() const;
	
	std::string generateOrCommand() const;
		
	std::string generateEqualCondition() const;
	
	std::string generateNotEqualCondition() const;
	
	std::string generateLessCondition() const;
	
	std::string generateGreaterCondition() const;
	
	std::string generateNegCommand() const;
	
	std::string generateImulCommand() const;
	
	std::string generateCallCommand() const;
	
	std::string generateDivCommand() const;
	
	std::string generateAddCommand() const;
	
	std::string generateSubCommand() const;
	
	std::string generateExchangeCommand() const;
	
	std::string generateDereferenceOfAdderess( std::string const & _address ) const;
    
	std::string generateDirectAddressingMode( std::string const & _address ) const;
	
    std::string generateIndirectAddressingMode( std::string const & _address ) const;
	
	std::string generateRetCommand() const;
	
	std::string generateOneOperandInstruction(
		std::string const _instruction,
		std::string const & _operand
	) const;
	
	std::string generateTwoOperandsInstruction(
		std::string const & _instruction,
		std::string const & _leftOperand,
		std::string const & _rightOperand
	) const;
};

}

#endif
