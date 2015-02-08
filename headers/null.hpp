#ifndef __NULL_HPP__
#define	__NULL_HPP__

#include "headers/unit.hpp"

namespace Syntax
{

class Null
    : public IUnit
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
    static boost::shared_ptr< Null > create()
    {
        return boost::shared_ptr< Null >( new Null );
    }

    IUnit::AddressingMode getAddressingMode() const
    {
        return & CodeGenerating::CodeGenerator::generateIndirectAddressingMode;
    }
	
private:
    Null(){}
};

}

#endif
