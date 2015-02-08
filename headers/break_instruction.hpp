#ifndef __BREAK_INSTRUCTION_HPP__
#define	__BREAK_INSTRUCTION_HPP__

#include "headers/instruction.hpp"
#include "headers/postcondition.hpp"

namespace Syntax
{
    
struct BreakInstruction
    : public IInstruction
{
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
     
    static int const BreakAll = -1;
            
    static boost::shared_ptr< BreakInstruction > create( int _value )
    {
        return boost::shared_ptr< BreakInstruction >( new BreakInstruction( _value ) );
    }
    
    static boost::shared_ptr< BreakInstruction > createBreakAll()
    {
        return boost::shared_ptr< BreakInstruction >( new BreakInstruction( BreakAll ) );
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
    
    int getBreakValue() const
    {
        return m_value;
    }
    
private:
    BreakInstruction( int _value )
        : m_value( _value )
    {
        POSTCONDITION1( _value == BreakAll || _value > 0 ); 
    }
    
private:
    int const m_value;
    IInstruction const * m_loop;
};
    
}

#endif
