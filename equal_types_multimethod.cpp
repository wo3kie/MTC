#include "headers/ph.hpp"

#include "headers/equal_types_multimethod.hpp"

namespace Semantics
{

bool EqualTypeMultimethod::m_isRecursive = true;
Loki::FnDispatcher< Type, Type, bool, Loki::DynamicCaster, EqualTypesNoThrowableDispatcher > EqualTypeMultimethod::m_dispatcher;        
    
void
EqualTypeMultimethod::setDispatcher(
    Loki::FnDispatcher< Type, Type, bool, Loki::DynamicCaster, EqualTypesNoThrowableDispatcher > _dispatcher
)
{
    m_dispatcher = _dispatcher;
}

void
EqualTypeMultimethod::setRecursive( bool _isRecursive )
{
    m_isRecursive = _isRecursive;
}

bool
EqualTypeMultimethod::isRecursive()
{
    return m_isRecursive;
}

bool
EqualTypeMultimethod::type_type_default( Type & _lhs, Type & _rhs )
{
    std::cerr
        << "EqualTypeMultimethod::type_type_default "
        << typeid( _lhs ).name()
        << ' '
        << typeid( _rhs ).name()
        << std::endl;
    
    return false;
}

bool
EqualTypeMultimethod::buildIn_buildIn( BuildInType & _lhs, BuildInType & _rhs )
{
    return _lhs.getTypeName() == _rhs.getTypeName();
}

bool
EqualTypeMultimethod::buildIn_any( BuildInType & , AnyType & )
{
    return true;
}

bool
EqualTypeMultimethod::pointer_pointer( PointerType & _lhs, PointerType & _rhs )
{
    if( m_isRecursive ){
        return m_dispatcher.Go( * _lhs.getPointedType(), * _rhs.getPointedType() );
    }
    else{
        return true;
    }
}

bool
EqualTypeMultimethod::pointer_any( PointerType & , AnyType & )
{
    return true;
}

bool equal( Type & _lhs, Type & _rhs, EqualRecursionPolicy::Enum _recursive )
{
    static Loki::FnDispatcher< Type, Type, bool, Loki::DynamicCaster, EqualTypesNoThrowableDispatcher > equalTypeMultimethod;
    static bool isFirstTimeCalled = true;
    
    if( isFirstTimeCalled )
    {
        equalTypeMultimethod.Add< BuildInType, BuildInType, EqualTypeMultimethod::buildIn_buildIn >();
        equalTypeMultimethod.Add< BuildInType, AnyType, EqualTypeMultimethod::buildIn_any >();
        equalTypeMultimethod.Add< PointerType, PointerType, EqualTypeMultimethod::pointer_pointer >();
        equalTypeMultimethod.Add< PointerType, AnyType, EqualTypeMultimethod::pointer_any >();
    
        isFirstTimeCalled = false;
    }
    
    EqualTypeMultimethod::setDispatcher( equalTypeMultimethod );
    EqualTypeMultimethod::setRecursive( _recursive == EqualRecursionPolicy::Recursive );
    return equalTypeMultimethod.Go( _lhs, _rhs );
}

bool operator== ( boost::shared_ptr< Type > _lhs, boost::shared_ptr< Type > _rhs )
{
    return equal( * _lhs, * _rhs );
}

}
