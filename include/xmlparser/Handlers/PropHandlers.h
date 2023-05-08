#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "XMLParser/Types/Component.h"
#include "XMLParser/Types/Primitive.h"
#include "XMLParser/Types/Prop.h"
#include "XMLParser/Handlers/PrimitiveHandlers.h"
#include "XMLParser/Utils/ComponentUtilities.h"

/**
 * A class used to create Props from Component vectors
 */
class PropHandlers
{
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
};