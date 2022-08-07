#include "Container.hpp"

ArrayType* Container::as_array()
{
    assert(type() == ContainerType::ArrayType);
    return static_cast<ArrayType*>(this);
}

ObjectType* Container::as_object()
{
    assert(type() == ContainerType::ObjectType);
    return static_cast<ObjectType*>(this);
}