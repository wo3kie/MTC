#ifndef __CONTINUE_INSTRUCTION_HPP__
#define	__CONTINUE_INSTRUCTION_HPP__

#include "headers/instruction.hpp"
#include "headers/postcondition.hpp"

namespace Syntax
{
    
struct ContinueInstruction
    : public IInstruction
{
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    static boost::shared_ptr< ContinueInstruction > create()
    {
        return boost::shared_ptr< ContinueInstruction >( new ContinueInstruction );
    }
    
    void setLoop( IInstruction const * _loop )
    {
        m_loop = _loop;
        POSTCONDITION1( m_loop );
    }
    
    IInstruction const * getLoop() const
    {
        return m_loop;
    }
    
private:
    ContinueInstruction()
    {
    }
    
private:
    IInstruction const * m_loop;
};
    
}

#endif
