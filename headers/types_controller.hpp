#ifndef __SEMANTICS_TYPES_CONTROLLER_HPP__
#define __SEMANTICS_TYPES_CONTROLLER_HPP__

#include "headers/symbols_table.hpp"
#include "headers/type_data.hpp"

#include <loki/Singleton.h>

namespace Semantics
{

typedef SymbolsTable< TypeData > TypesTable;

class TypesController
{
public:
	typedef TypesTable::Handler Handler;

public:
	Handler insert( TypeData const & _data )
	{
        return m_typesTable.insert( _data ); 
    }
		
 	Handler getHandler( boost::shared_ptr< Type > _type, Scope const & _scope ) const
 	{
        return m_typesTable.getHandler( _type, _scope );
    }
 		
 	TypeData getData( Handler _handler ) const
 	{
        return m_typesTable.getData( _handler );
    }
    
    Handler smartInsert( boost::shared_ptr< Type > _type, Scope const & _scope )
    {
        if( getHandler( _type->getBasicType(), _scope ).isNull() )
        {
            return Handler();
        }
        
        if( getHandler( _type, _scope ).isNull() )
        {
            return insert( TypeData( _type ) );
        }
        
        return getHandler( _type, _scope );
    }

protected:
	TypesTable m_typesTable;
};

typedef Loki::SingletonHolder< TypesController > TypesControllerSingleton;

}

#endif
