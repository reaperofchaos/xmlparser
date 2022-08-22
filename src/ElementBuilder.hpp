#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Types/Component.hpp"
#include "Types/Primitive.hpp"
#include "Types/Element.hpp"
#include "CharacterReader.hpp"
#include "Handlers/ComponentHandlers.hpp"
#include "Tokenizer.hpp"
#include "CharacterReader.hpp"

class ElementBuilder 
{
    private:
        std::vector<std::shared_ptr<Component>> m_components;
        std::vector<std::shared_ptr<Primitive>> m_primitives;
        std::vector<std::shared_ptr<Element>> m_elements; 
        size_t m_index = 0; // position in string

    public:
        ElementBuilder(std::vector<std::shared_ptr<Component>> components)
        {
            this->m_components = components; 
        }

        std::vector<std::shared_ptr<Component>> getComponents(){return m_components;}
        std::vector<std::shared_ptr<Primitive>> getPrimitives(){return m_primitives;}
        std::vector<std::shared_ptr<Element>> getElements(){return m_elements;}

        static void read_str(std::string input);
        std::shared_ptr<Element> next();
        void displayComponents();
        void displayElements();
        void buildElements();
};

