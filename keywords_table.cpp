#include "headers/ph.hpp"

#include "headers/keywords_table.hpp"

#include "headers/semantic_value_stack.hpp"
#include "headers/scanner.hpp"
#include "headers/bison_parser.hpp"

#include "headers/postcondition.hpp"

namespace Semantics
{

boost::shared_ptr< KeywordTableSingleton const > KeywordTableSingleton::m_instance;

boost::shared_ptr< KeywordTableSingleton const > const
KeywordTableSingleton::getInstance()
{
	if ( ! m_instance )
	{
		m_instance = makeSharedPtr( new KeywordTableSingleton );
	}
	
	POSTCONDITION1( m_instance )
	
	return m_instance;
}

KeywordTableSingleton::KeywordTableSingleton()
{
	m_keywordsTable[ "all" ] = BisonParser::ALL;
	m_keywordsTable[ "break" ] = BisonParser::BREAK;
	m_keywordsTable[ "continue" ] = BisonParser::CONTINUE;
	m_keywordsTable[ "do" ] = BisonParser::DO;
	m_keywordsTable[ "else" ] = BisonParser::ELSE;
	m_keywordsTable[ "for" ] = BisonParser::FOR;
	m_keywordsTable[ "if" ] = BisonParser::IF;
	m_keywordsTable[ "int" ] = BisonParser::BASIC_TYPE;
	m_keywordsTable[ "null" ] = BisonParser::NULL_UNIT;
	m_keywordsTable[ "return" ] = BisonParser::RETURN;
	m_keywordsTable[ "while" ] = BisonParser::WHILE;
	m_keywordsTable[ "void" ] = BisonParser::BASIC_TYPE;

#ifdef __EEGGS__    
    m_keywordsTable[ "empty" ] = BisonParser::NULL_UNIT;
    m_keywordsTable[ "repeat" ] = BisonParser::FOR;
    //m_keywordsTable[ "result" ] = BisonParser::RETURN;
    m_keywordsTable[ "skip" ] = BisonParser::CONTINUE;
#endif
}

int
KeywordTableSingleton::getIdentifier( std::string const & _text ) const
{
	std::map< std::string const, int >::const_iterator matchedKeyword
		= m_keywordsTable.find( _text );

	if ( matchedKeyword == m_keywordsTable.end() )
	{
		return BisonParser::IDENTIFIER;
	}
	else
	{
		return matchedKeyword->second;
	}
}

}
