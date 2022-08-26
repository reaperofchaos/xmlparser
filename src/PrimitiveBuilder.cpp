#include "PrimitiveBuilder.hpp"

std::shared_ptr<Primitive>PrimitiveBuilder::next(){
    // size_t start = this->m_index;

    while (this->m_index < this->m_components.size())
    {
        switch(m_components[m_index]->type())
        {
            case ComponentType::StringType:
                return ComponentHandlers::buildStringPrimitive(m_components, m_index);

            default:
                    m_index++;
                    return {};
        }
        return {};

    } 
    return {};

}

/**
 * @brief Builds primitives from components
 * 
 */
void PrimitiveBuilder::build_primitives() 
{
    while (auto primitive = this->next()) 
    {
        this->m_primitives.push_back(primitive);
    }
}

/**
 * @brief Displays the type and value of the primitives
 * 
 */
void PrimitiveBuilder::displayPrimitives()
{
    for(auto primitive : this->m_primitives)
    {
        std::cout << primitive->getType() << " - " << primitive->getValue() << "\n";
    }
}