#ifndef __SEMANTICS_SYMBOLS_CONTROLLER_FACTORY_HPP__
#define __SEMANTICS_SYMBOLS_CONTROLLER_FACTORY_HPP__

#include "headers/functions_controller.hpp"
#include "headers/strings_controller.hpp"
#include "headers/types_controller.hpp"
#include "headers/variables_controller.hpp"

namespace CodeGenerating
{

class CodeGenerator;

}

namespace Semantics
{

struct SymbolsControllerFactory
{

static FunctionsController & createFunctionsController();
static StringsController & createStringsController();
static TypesController & createTypesController();
static VariablesController & createVariablesController();

};

};

#endif
