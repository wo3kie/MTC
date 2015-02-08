#ifndef __SYNTAX_OPERATORS_HPP__
#define __SYNTAX_OPERATORS_HPP__

#include "headers/syntax_tree_node.hpp"

#include "headers/types_mapping.hpp"

namespace Syntax
{
 
class Operator
	: public ISyntaxTreeNode
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	/*virtual*/ ~Operator() {}
    
    virtual std::string getOperatorName() const = 0;
    virtual Semantics::TypesMapping & getTypesMapping() const = 0;
};

class AssignOperator
	: public Operator
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
	
	AssignOperator();

    std::string getOperatorName() const { return "operator ="; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class LogicalOperator
	: public Operator
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
};

class EqualOperator
    : public LogicalOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
                
    EqualOperator();
            
    std::string getOperatorName() const { return "operator =="; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class NotEqualOperator
    : public LogicalOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    NotEqualOperator();
            
    std::string getOperatorName() const { return "operator !="; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class LessOperator
    : public LogicalOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    LessOperator();
            
    std::string getOperatorName() const { return "operator <"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class GreaterOperator
    : public LogicalOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    GreaterOperator();
            
    std::string getOperatorName() const { return "operator >"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class AndOperator
    : public LogicalOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    AndOperator();
            
    std::string getOperatorName() const { return "operator &&"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class OrOperator
    : public LogicalOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
           
    OrOperator();
            
    std::string getOperatorName() const { return "operator ||"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class AdditiveOperator
	: public Operator
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
};

class AdditionOperator
    : public AdditiveOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* TypesMappingMacro Defined in loki/Visitor.h */ )
            
    AdditionOperator();
    
    std::string getOperatorName() const { return "operator +"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;
};

class SubtractionOperator
    : public AdditiveOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
    
    SubtractionOperator();
    
    std::string getOperatorName() const { return "operator -"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;
};

class MultiplicativeOperator
	: public Operator
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
};

class MultiplicationOperator
    : public MultiplicativeOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
    
    MultiplicationOperator();
    
    std::string getOperatorName() const { return "operator *"; }    
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;            
};

class DivisionOperator
    : public MultiplicativeOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    DivisionOperator();
    
    std::string getOperatorName() const { return "operator /"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;            
};

class UnaryOperator
	: public Operator
{
public:
	LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )

	/*virtual*/ ~UnaryOperator() {}
};

class PlusOperator
    : public UnaryOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    PlusOperator();
            
    std::string getOperatorName() const { return "operator +"; }
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class MinusOperator
    : public UnaryOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )
            
    MinusOperator();
            
    std::string getOperatorName() const { return "operator -"; }   
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;    
};

class UnaryAndOperator
    : public UnaryOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )

    UnaryAndOperator();
    
    std::string getOperatorName() const { return "operator &"; }    
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;            
};

class DereferenceOperator
    : public UnaryOperator
{
public:
    LOKI_DEFINE_VISITABLE( /* Macro Defined in loki/Visitor.h */ )

    DereferenceOperator();
    
    std::string getOperatorName() const { return "operator *"; }    
    
    Semantics::TypesMapping & getTypesMapping() const { return m_typesMapping; }

private:
    static Semantics::TypesMapping m_typesMapping;            
};

}

#endif
