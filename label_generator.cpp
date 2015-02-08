#include "headers/ph.hpp"

#include "headers/label_generator.hpp"

namespace CodeGenerator
{

std::string
LabelGenerator::generate( std::string const & _labelPattern ) const
{
	static unsigned labelID = 0;
	
	return _labelPattern + boost::lexical_cast< std::string >( ++labelID );
}

}
