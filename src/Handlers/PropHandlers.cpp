#include "PropHandlers.hpp"

std::shared_ptr<Prop> PropHandlers::buildProp(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    size_t start = m_index;
    if(components[start]->type() == ComponentType::Name)
    {
        std::shared_ptr<Name> name = std::dynamic_pointer_cast<Name>(components[start]); 
        m_index++;
        PropHandlers::IgnoreWhiteSpace(components, m_index);
        if(components[m_index]->type() == ComponentType::EqualComponent)
        {
            m_index++;
            PropHandlers::IgnoreWhiteSpace(components, m_index);
            switch(components[m_index]->type())
            {
                case ComponentType::Name:
                    return PropHandlers::buildBooleanProp(components, name, m_index);
                case ComponentType::StringType:
                    return PropHandlers::buildStringProp(components, name, m_index);
                case ComponentType::OpenObject:
                    return PropHandlers::buildObjectProp(components, name, m_index);
                default:
                    m_index++;
                    return NULL; 
            }
        }
        return PropHandlers::buildBooleanProp(name);
    }

    return NULL;
}

std::shared_ptr<StringProp> PropHandlers::buildStringProp(
    std::vector<std::shared_ptr<Component>> &components,
    std::shared_ptr<Name> name,
    size_t &m_index)
{
    std::shared_ptr<StringPrimitive> stringPrimitive = PrimitiveHandlers::buildStringPrimitive(components, m_index);
    return std::make_shared<StringProp>(name, stringPrimitive);
}

std::shared_ptr<ObjectProp> PropHandlers::buildObjectProp(
    std::vector<std::shared_ptr<Component>> &components,
    std::shared_ptr<Name> name,
    size_t &m_index)
{
    std::shared_ptr<ObjectPrimitive> objectPrimitive = PrimitiveHandlers::buildObject(components, m_index);
    return std::make_shared<ObjectProp>(name, objectPrimitive);
}

std::shared_ptr<BooleanProp> PropHandlers::buildBooleanProp(
    std::vector<std::shared_ptr<Component>> &components,
    std::shared_ptr<Name> name,
    size_t &m_index)
{
    std::shared_ptr<BooleanPrimitive> booleanPrimitive = PrimitiveHandlers::buildBooleanPrimitive(components[m_index], m_index);
    return std::make_shared<BooleanProp>(name, booleanPrimitive);
}

std::shared_ptr<BooleanProp> PropHandlers::buildBooleanProp(
    std::shared_ptr<Name> name)
{
    return std::make_shared<BooleanProp>(name);
}

void PropHandlers::IgnoreWhiteSpace( 
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    while(components[m_index]->type() == ComponentType::WhiteSpaces)
    {
        m_index++;
    } 
}