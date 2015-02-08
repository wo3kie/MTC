#ifndef __SYNTAX_UNIT_HPP__
#define __SYNTAX_UNIT_HPP__

#include "headers/syntax_tree_node.hpp"
#include "headers/code_generator.hpp"

namespace Syntax
{

class IUnit
	: public ISyntaxTreeNode
{
public:
    //struct AssignValueType { enum Enum { LValue, RValue }; };

public:
    /*virtual*/ ~IUnit() {}
    
    typedef std::string ( CodeGenerating::CodeGenerator::* AddressingMode )( std::string const & _address ) const;
    
    virtual AddressingMode getAddressingMode() const = 0;
    
    //virtual AssignValueType::Enum getAssignValueType() const = 0;
};

}

#endif
