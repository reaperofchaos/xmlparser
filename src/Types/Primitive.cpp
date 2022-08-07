#include "Primitive.hpp"

Name* Primitive::as_name() 
{
    assert(type() == PrimitiveType::Name);
    return static_cast<Name*>(this);
}

NumberType* Primitive::as_number() 
{
    assert(type() == PrimitiveType::NumberType);
    return static_cast<NumberType*>(this);
}

StringType* Primitive::as_string() 
{
    assert(type() == PrimitiveType::StringType);
    return static_cast<StringType*>(this);
}

OpenTag* Primitive::as_open_tag()
{
    assert(type() == PrimitiveType::OpenTag);
    return static_cast<OpenTag*>(this);
}

CloseTag* Primitive::as_close_tag()
{
    assert(type() == PrimitiveType::CloseTag);
    return static_cast<CloseTag*>(this);
}

OpenArray* Primitive::as_open_array()
{
    assert(type() == PrimitiveType::OpenArray);
    return static_cast<OpenArray*>(this);
}

CloseArray* Primitive::as_close_array()
{
    assert(type() == PrimitiveType::CloseArray);
    return static_cast<CloseArray*>(this);
}

OpenObject* Primitive::as_open_object()
{
    assert(type() == PrimitiveType::OpenObject);
    return static_cast<OpenObject*>(this);
}

CloseObject* Primitive::as_close_object()
{
    assert(type() == PrimitiveType::CloseObject);
    return static_cast<CloseObject*>(this);
}
