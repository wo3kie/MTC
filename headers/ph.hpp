#ifndef __PRECOMPILED_HEADER_HPP__
#define __PRECOMPILED_HEADER_HPP__

#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <cassert>
#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <vector>

#define __EEGGS__

template < typename T >
inline boost::shared_ptr< T >
makeSharedPtr( T * _rawPointer )
{
	return boost::shared_ptr< T >( _rawPointer );
}

#endif
