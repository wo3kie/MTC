#include "headers/ph.hpp"

#include "headers/symbols_controller_factory.hpp"

#include "headers/postcondition.hpp"

namespace Semantics
{

FunctionsController &
SymbolsControllerFactory::createFunctionsController()
{
	return FunctionsControllerSingleton::Instance();
}

StringsController &
SymbolsControllerFactory::createStringsController()
{
	return StringsControllerSingleton::Instance();
}

TypesController &
SymbolsControllerFactory::createTypesController()
{	
	return TypesControllerSingleton::Instance();
}

VariablesController &
SymbolsControllerFactory::createVariablesController()
{	
	return VariablesControllerSingleton::Instance();
}

}
