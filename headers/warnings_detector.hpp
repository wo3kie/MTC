#ifndef __SEMANTICS_WARNINGS_DETECTOR_HPP__
#define __SEMANTICS_WARNINGS_DETECTOR_HPP__

namespace Semantics
{

class WarningsDetector
{
public:
	void unusedVariable() const;	
	void variableNotInitialized() const;
};

}

#endif
