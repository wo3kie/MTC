#ifndef __UTULITY_POSTCONDITION_HPP__
#define __UTULITY_POSTCONDITION_HPP__

#define SWITCH__POSTCONDITION__ON

#ifdef SWITCH__POSTCONDITION__ON

#include <cassert>

#define POSTCONDITION1( c1 ) \
	(assert( c1 != 0 ));

#define POSTCONDITION2( c1, c2 ) \
	(assert( c1 != 0 && c2 != 0 ));

#define POSTCONDITION3( c1, c2, c3 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 ));

#define POSTCONDITION4( c1, c2, c3, c4 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0 ));

#define POSTCONDITION5( c1, c2, c3, c4, c5 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0 && c5 != 0 ));

#define POSTCONDITION6( c1, c2, c3, c4, c5, c6 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0 && c5 != 0 && c6 != 0 ));

#endif

#endif
