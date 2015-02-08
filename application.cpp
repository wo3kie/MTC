#include "headers/ph.hpp"

#include "headers/application.hpp"

#include "headers/code_generating_visitor.hpp"
#include "headers/code_generator.hpp"
#include "headers/semantic_analysis_visitor.hpp"
#include "headers/symbols_controller_factory.hpp"
#include "headers/type_data.hpp"

#include <boost/program_options.hpp>

#include <fstream>

namespace Framework
{

Application::Application()
{
}
	
int
Application::execute( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        std::cerr << "Usage: " << argv[0] << " file" << std::endl;
        return 1;
    }

	Semantics::FunctionsController & functionsController
		= Semantics::SymbolsControllerFactory::createFunctionsController();
		
	Semantics::StringsController & stringsController
		= Semantics::SymbolsControllerFactory::createStringsController();
		
	Semantics::TypesController & typesController
		= Semantics::SymbolsControllerFactory::createTypesController();
	
	Semantics::TypesController::Handler const voidHandler
		= typesController.insert( Semantics::TypeData( Semantics::BuildInType::create( "void" ) ) );
		
	Semantics::TypesController::Handler const stringHandler
		= typesController.insert( Semantics::TypeData( Semantics::BuildInType::create( "int" ) ) );
		
	Semantics::VariablesController & variablesController
		= Semantics::SymbolsControllerFactory::createVariablesController();

	m_parser.reset( new Syntax::Parser( new std::ifstream( argv[ 1 ] ), &std::cout ) );
	if( m_parser->yyparse() )
	{
		std::cerr << "Syntax error." << std::endl;
	}
	
	Semantics::SemanticAnalysisVisitor semanticAnalysisVisitor(
		functionsController,
		stringsController,
		typesController,
		variablesController );
	
	m_parser->getProgram()->Accept( semanticAnalysisVisitor );
		
	int const errorCount = semanticAnalysisVisitor.getErrorsCount();

	if ( ! errorCount )
	{
		CodeGenerating::CodeGeneratingVisitor codeGeneratingVisitor(
			functionsController,
			stringsController,
			typesController,
			variablesController );
		
		m_parser->getProgram()->Accept( codeGeneratingVisitor );
	}
	
// 	std::cerr
// 		<< "Compilation finished with... ["
// 		<< semanticAnalysisVisitor.getWarningsCount()
// 		<< "] warning(s), ["
// 		<< errorCount
// 		<< "] error(s)."
// 		<< std::endl;
	
	return errorCount ? 1 : 0;
}

}
