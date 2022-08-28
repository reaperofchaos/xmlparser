#include "ComponentUtilities.hpp"

void ComponentUtilities::IgnoreWhiteSpace( 
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    while(components[m_index]->type() == ComponentType::WhiteSpaces )
    {
        ComponentUtilities::IncrementIndex(components, m_index);
    } 
}

void ComponentUtilities::IncrementIndex( 
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    if(m_index < components.size()-1)
    {
        m_index++;
    } 
}