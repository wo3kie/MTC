#ifndef __EQUAL_TYPE_MULTIMETHOD_HPP__
#define __EQUAL_TYPE_MULTIMETHOD_HPP__

#include "headers/type.hpp"

#include "headers/equal_types_nothrowable_dispatcher.hpp"

namespace Semantics
{

struct EqualRecursionPolicy {
    enum Enum {
        Recursive,
        NoRecirsive
    };
};  

bool equal( Type & _lhs, Type & _rhs, EqualRecursionPolicy::Enum _recursive = EqualRecursionPolicy::Recursive );

bool operator== ( boost::shared_ptr< Type > _lhs, boost::shared_ptr< Type > _rhs );
    
struct EqualTypeMultimethod
{
    friend bool equal( Type & _lhs, Type & _rhs, EqualRecursionPolicy::Enum _recursive );

    static void setDispatcher( Loki::FnDispatcher< Type, Type, bool, Loki::DynamicCaster, EqualTypesNoThrowableDispatcher > _dispatcher );
    
    static bool type_type_default( Type & _lhs, Type & _rhs );
    static bool buildIn_buildIn( BuildInType & _lhs, BuildInType & _rhs );
    static bool buildIn_any( BuildInType & _lhs, AnyType & _rhs );
    static bool pointer_pointer( PointerType & _lhs, PointerType & _rhs );
    static bool pointer_any( PointerType & _lhs, AnyType & _rhs );

private:
    static void setRecursive( bool _isRecursive );
    static bool isRecursive();

private:
    static Loki::FnDispatcher< Type, Type, bool, Loki::DynamicCaster, EqualTypesNoThrowableDispatcher > m_dispatcher;
    static bool m_isRecursive;
};
    
}

#endif
