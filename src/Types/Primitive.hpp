#pragma once
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "Component.hpp"

enum class PrimitiveType
{
    Primitive,
    StringPrimitive, 
    NumberPrimitive,
    BooleanPrimitive,
    ArrayPrimitive,
    ObjectPrimitive,
};

class Primitive{
    private:
        std::string name;
        std::string value;

    public:
        Primitive(){};
        virtual ~Primitive() = default;
        virtual std::string getTypeAsString(PrimitiveType type){
            switch (type)
            {
                case PrimitiveType::StringPrimitive:
                    return "String";
                case PrimitiveType::NumberPrimitive:
                    return "Number";
                case PrimitiveType::BooleanPrimitive:
                    return "Boolean";
                case PrimitiveType::ArrayPrimitive:
                    return "Array";
                case PrimitiveType::ObjectPrimitive:
                    return "Object";
                default: 
                    return "Unknown";
            }
        }
        
        virtual PrimitiveType type(){ return PrimitiveType::Primitive;}
        virtual std::string inspect() { assert(0); }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};

class StringPrimitive: public Primitive{
    private:
        std::string name;
        std::string value;

    public:
        StringPrimitive(std::shared_ptr<StringType> text): Primitive()
        {
            this->name = text->getValue();
            this->value = text->getValue();
        }
        virtual PrimitiveType type(){ return PrimitiveType::StringPrimitive;}
        virtual std::string inspect() { return this->getType() + " - " + this->getValue(); }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};

class NumberPrimitive: public Primitive{
    private:
        std::string name;
        std::string value;

    public:
        NumberPrimitive(std::shared_ptr<NumberType> number): Primitive()
        {
            this->name = number->getValue();
            this->value = number->getValue();
        }
        virtual PrimitiveType type(){ return PrimitiveType::NumberPrimitive;}
        virtual std::string inspect() { return this->getType() + " - " + this->getValue(); }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){ return this->getTypeAsString(this->type());}
};

class BooleanPrimitive: public Primitive
{
    private:
        std::string name; 
        std::string value;

    public:
        BooleanPrimitive(std::shared_ptr<Name> name): Primitive()
        {
            this->name = name->getValue();
            this->value = "true";
        }

        BooleanPrimitive(std::shared_ptr<Name> name, 
            std::shared_ptr<Name> value ): Primitive()
        {
            this->name = name->getValue();
            this->value = value->getValue();
        }
        virtual PrimitiveType type(){ return PrimitiveType::BooleanPrimitive;}
        virtual std::string inspect() { return this->getType() + " - " + this->getValue(); }
        virtual std::string getValue(){ return value;}
        bool getValueAsBool(){ 
            if(this->value == "true"){
                return true; 
            }
            return false;
        }
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};
