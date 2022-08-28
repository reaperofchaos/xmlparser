#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/Component.hpp"
#include "../Types/Primitive.hpp"
#include "../Types/Prop.hpp"
#include "../Handlers/PrimitiveHandlers.hpp"

/**
 * A class used to create Props from Component vectors
 */
class PropHandlers {
    public:
        static std::shared_ptr<Prop> buildProp(
            std::vector<std::shared_ptr<Component>> &components, 
            size_t &m_index);

        static std::shared_ptr<ObjectProp> buildObjectProp(
            std::vector<std::shared_ptr<Component>> &components,
            std::shared_ptr<Name> name,
            size_t &m_index);
        
        static std::shared_ptr<StringProp> buildStringProp(
            std::vector<std::shared_ptr<Component>> &components,
            std::shared_ptr<Name> name,
            size_t &m_index);
        
        static std::shared_ptr<BooleanProp> buildBooleanProp(
            std::vector<std::shared_ptr<Component>> &components,
            std::shared_ptr<Name> name,
            size_t &m_index);
        
        static std::shared_ptr<BooleanProp> buildBooleanProp(
            std::shared_ptr<Name> name);
        
        static void IgnoreWhiteSpace( 
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
};