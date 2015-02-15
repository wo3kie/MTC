# CXX
CXX= clang++

INC= -I. -I./loki/include

LIBS= -lloki
LIBS_DIR= -L./loki/lib

CXXFLAG_DEBUG= -pg -g $(INC)
CXXFLAG_RELEASE= -O2 -DNDEBUG $(INC)
CXXFLAG = $(CXXFLAG_DEBUG)

PH_FILE= ./headers/ph.hpp
PHFLAG = -c -o ./headers/ph.gch -x c++

# BISON
BISON = bison++
PARSER_DEFINITION_FILE = ./bison_parser.y
PARSER_SOURCE_CODE_FILE = ./bison_parser.cpp
PARSER_HEADER_FILE_NAME = ./headers/bison_parser.hpp
BISONFLAG = -v -d -h$(PARSER_HEADER_FILE_NAME) -o$(PARSER_SOURCE_CODE_FILE)

# FLEX
FLEX = flex++
LEXER_DEFINITION_FILE = ./scanner.l
LEXER_SOURCE_CODE_FILE = ./scanner.cpp
FLEXFLAG = -I

OBJS= main.o \
	application.o \
	assignment_expression.o \
	bison_parser.o \
	code_generating_visitor.o \
	code_generator.o \
	compound_instruction.o \
	declaration.o \
	dereference.o \
	do_while_instruction.o \
	equal_types_multimethod.o \
	equal_types_nothrowable_dispatcher.o \
	errors_detector.o \
	expression.o \
	factor.o \
	for_instruction.o \
	function_call.o \
	function.o \
	function_data.o \
	get_address.o \
	if_instruction.o \
	keywords_table.o \
	label_generator.o \
	number.o \
	operators.o \
	parameter.o \
	parser.o \
	parenthesis.o \
	program.o \
	return_instruction.o \
	scanner.o \
	scope.o \
	semantic_analysis_exceptions.o \
	semantic_analysis_visitor.o \
	simple_expression.o \
	string.o \
	string_data.o \
	strings_controller.o \
	symbol_data.o \
	symbols_controller_factory.o \
	type.o \
	type_data.o \
	types_mapping.o \
	unary_factor.o \
	variable.o \
	variable_data.o \
	variables_controller.o \
	while_instruction.o

PROG= mtc

DEP= makefile.dep

%.o: %.cpp
	$(CXX) $(CXXFLAG) -c $<

$(PROG):$(OBJS) 
	$(CXX) $(OBJS) $(LIBS) $(LIBS_DIR) -o $@

all: ccomp $(PROG)

ccomp: $(PARSER_DEFINITION_FILE) $(LEXER_DEFINITION_FILE)
	$(BISON) $(BISONFLAG) $(PARSER_DEFINITION_FILE)
	$(FLEX) $(FLEXFLAG) $(LEXER_DEFINITION_FILE)

ph: $(PH_FILE)
	$(CXX) $(PHFLAG) $(PH_FILE)
	
depend: 
	$(CXX) -I. -MM $(OBJS:.o=.cpp) > $(DEP)

clean:
	rm -f $(OBJS) $(PROG)

clean_all:
	rm -f $(OBJS) $(PROG)
	rm -f $(PARSER_SOURCE_CODE_FILE) $(LEXER_SOURCE_CODE_FILE) $(PARSER_SOURCE_CODE_FILE:.cpp=.output)

run_tests:
	./start_tests.sh

clean_tests:
	rm -f ./tests/*.s
	rm -f ./tests/*.o
	rm -f ./tests/*.exe
		
check_syntax_only: $(OBJS)
	$(CXX) $(CXXFLAG) -S $<

ifeq ($(wildcard $(DEP)), $(DEP))
include $(DEP)
endif

