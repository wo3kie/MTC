#ifndef __CODE_GENERATOR_LABEL_GENERATOR_HPP__
#define __CODE_GENERATOR_LABEL_GENERATOR_HPP__

namespace CodeGenerator
{
	
struct LabelGenerator
{
	std::string generate( std::string const & _labelPattern ) const;
};

}

#endif
