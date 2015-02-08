#include "headers/ph.hpp"

#include "headers/operators.hpp"

namespace Syntax
{

Semantics::TypesMapping AssignOperator::m_typesMapping;    
Semantics::TypesMapping AdditionOperator::m_typesMapping;    
Semantics::TypesMapping AndOperator::m_typesMapping;    
Semantics::TypesMapping DivisionOperator::m_typesMapping;    
Semantics::TypesMapping DereferenceOperator::m_typesMapping;    
Semantics::TypesMapping EqualOperator::m_typesMapping;    
Semantics::TypesMapping GreaterOperator::m_typesMapping;    
Semantics::TypesMapping LessOperator::m_typesMapping;    
Semantics::TypesMapping MinusOperator::m_typesMapping;    
Semantics::TypesMapping MultiplicationOperator::m_typesMapping;    
Semantics::TypesMapping NotEqualOperator::m_typesMapping;    
Semantics::TypesMapping OrOperator::m_typesMapping;    
Semantics::TypesMapping PlusOperator::m_typesMapping;    
Semantics::TypesMapping SubtractionOperator::m_typesMapping;    
Semantics::TypesMapping UnaryAndOperator::m_typesMapping;    

AssignOperator::AssignOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::AnyType::create(),
        Semantics::AnyType::create(),
        Semantics::_1::create(),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

AdditionOperator::AdditionOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );
    
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );

    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::_2::create()
    );
}

AndOperator::AndOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::LazyType::create( Semantics::BuildInType::create( "int" ) ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

DereferenceOperator::DereferenceOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::RemovePointer::create( Semantics::_1::create() ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

DivisionOperator::DivisionOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );
}

EqualOperator::EqualOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::LazyType::create( Semantics::BuildInType::create( "int" ) ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

GreaterOperator::GreaterOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::LazyType::create( Semantics::BuildInType::create( "int" ) ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

LessOperator::LessOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::LazyType::create( Semantics::BuildInType::create( "int" ) ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

MinusOperator::MinusOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create(),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

MultiplicationOperator::MultiplicationOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );
}

NotEqualOperator::NotEqualOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::_1::create(),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

OrOperator::OrOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::LazyType::create( Semantics::BuildInType::create( "int" ) ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

PlusOperator::PlusOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );
}

SubtractionOperator::SubtractionOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );
    
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::BuildInType::create( "int" ),
        Semantics::_1::create()
    );
    
    m_typesMapping.addMappingRule(
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::PointerType::create( Semantics::AnyType::create() ),
        Semantics::_1::create(),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

UnaryAndOperator::UnaryAndOperator()
{
    m_typesMapping.addMappingRule(
        Semantics::BuildInType::create( "int" ),
        Semantics::AddPointer::create( Semantics::_1::create() ),
        & Semantics::TypesMappingPolicy::areCorresponding
    );
}

}
