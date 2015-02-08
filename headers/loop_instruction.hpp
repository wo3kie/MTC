#ifndef __LOOP_INSTRUCTION_HPP__
#define	__LOOP_INSTRUCTION_HPP__

#include "headers/instruction.hpp"

namespace Syntax
{

struct LoopInstruction
    : public IInstruction
{
    virtual ~LoopInstruction(){}

    virtual std::string getBeginLabel() const = 0;
	virtual std::string getEndLabel() const = 0;
    virtual std::string getContinueLabel() const = 0;
};
    
}

#endif
