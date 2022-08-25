#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include "Type/Primitive"
#include "Types/Component.hpp"

class ArrayType;
class ObjectType;

enum class ContainerType
{
    Container,
    ArrayType,
    ObjectType
};

class Container{
private:
        std::string value;

    public: 
        virtual ~Character() = default;
        virtual std::string getTypeAsString(CharacterType type){
            switch (type)
            {
                case ContainerType::ArrayType:
                    return "Array type";
                case ContainerType::ObjectType:
                    return "Object Type";
                default: 
                    return "Container"; 
            }
        }

        virtual ContainerType type(){ return ContainerType::Container;}
        virtual std::string inspect() { assert(0); }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}

        ArrayType* as_array(); 
        ObjectType* as_object(); 
}

class ArrayType: Container{
    private:
        std::string value;
        std::vector<std::shared_ptr<Primitive>>  contents; 

    public:
        ArrayType(std::shared_ptr<ArrayOpenBracket> openBracket,
            std::vector<shared_ptr<Component>> components 
            std::shared_ptr<ArrayCloseBracket> closeBracket)
        {
            this->value = str;
            std::cout << this->inspect() << "\n";
        }

        virtual ContainerType type(){ return ContainerType::ArrayType;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ObjectType: Container{
    private:
        std::string value;

    public:
        ObjectType(std::string str){
            this->value = str;
            std::cout << this->inspect() << "\n";
        }

        virtual ContainerType type(){ return ContainerType::ObjectType;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};