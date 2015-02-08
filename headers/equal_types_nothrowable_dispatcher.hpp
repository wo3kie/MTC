#ifndef __EQUAL_TYPES_NOTHROWABLE_DISPATCHER_HPP__
#define	__EQUAL_TYPES_NOTHROWABLE_DISPATCHER_HPP__

#include "headers/equal_types_nothrowable_dispatcher.hpp"

#include <loki/MultiMethods.h>

namespace Semantics
{
    
template<
    class BaseLhs,
    class BaseRhs = BaseLhs,
    typename ResultType = void,
    typename CallbackType = ResultType (*)(BaseLhs&, BaseRhs&)
>
class EqualTypesNoThrowableDispatcher : protected Loki::BasicDispatcher< BaseLhs, BaseRhs, ResultType, CallbackType >
{
public:
    using Loki::BasicDispatcher< BaseLhs, BaseRhs, ResultType, CallbackType >::Add;
    using Loki::BasicDispatcher< BaseLhs, BaseRhs, ResultType, CallbackType >::Remove;
    
    ResultType Go( BaseLhs & lhs, BaseRhs & rhs )
    {
        try{
            return Loki::BasicDispatcher< BaseLhs, BaseRhs, ResultType, CallbackType >::Go( lhs, rhs );
        }
        catch( std::runtime_error & ){
            return false;
        }        
    }
};
    
}

#endif
