#ifndef __SEMANTICS_KEYWORD_TABLE_HPP__
#define __SEMANTICS_KEYWORD_TABLE_HPP__

namespace Semantics
{

class KeywordTableSingleton
	: public boost::noncopyable
{
public:
	static boost::shared_ptr< KeywordTableSingleton const > const getInstance();

	int getIdentifier( std::string const & _text ) const;

protected: /*singleton data*/
	std::map< std::string const, int > m_keywordsTable;

private:
	KeywordTableSingleton();

private:
	static boost::shared_ptr< KeywordTableSingleton const > m_instance;
};

typedef KeywordTableSingleton KeywordsTable;

}

#endif
