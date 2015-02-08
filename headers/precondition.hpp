#ifndef __UTULITY_PRECONDITION_HPP__
#define __UTULITY_PRECONDITION_HPP__

#define SWITCH__PRECONDITION__ON

#ifdef SWITCH__PRECONDITION__ON

#include <cassert>

#define PRECONDITION1( c1 ) \
	(assert( c1 != 0 ));

#define PRECONDITION2( c1, c2 ) \
	(assert( c1 != 0 && c2 != 0 ));

#define PRECONDITION3( c1, c2, c3 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 ));

#define PRECONDITION4( c1, c2, c3, c4 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0 ));

#define PRECONDITION5( c1, c2, c3, c4, c5 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0 && c5 != 0 ));

#define PRECONDITION6( c1, c2, c3, c4, c5, c6 ) \
	(assert( c1 != 0 && c2 != 0 && c3 != 0 && c4 != 0 && c5 != 0 && c6 != 0 ));

#endif

#endif
