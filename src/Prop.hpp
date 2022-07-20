#pragma once
#include <cassert>
#include <string>
#include <string_view>
#include <vector>
#include "Types.hpp"

class ObjectProp;
class StringProp;
class BooleanProp; 

enum class PropType
{
    STRING_PROP, //name=""
    BOOLEAN_PROP, //name
    OBJECT_PROP // name={stuffInside}
};


class Prop {
    private: 
        std::string propName; 
        std::string propValue; 
    
    public: 
        virtual PropType type(){ assert(0);}

        virtual std::string getTypeAsString(PropType type){
            switch (type)
            {
                case PropType::STRING_PROP:
                    return "String Prop";
                case PropType::BOOLEAN_PROP:
                    return "Boolean Prop";
                case PropType::OBJECT_PROP:
                    return "Object Prop";
                default: 
                    return ""; 
            }
        }

        virtual  std::string  name(){ return propName;}
        virtual  std::string  value(){ return propValue;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        ObjectProp* as_object_prop(); 
        StringProp* as_string_prop(); 
        BooleanProp* as_boolean_prop(); 
};

class StringProp: public Prop {
    private:
        std::string propName; 
        std::string propValue; 

    public:
        StringProp(std::string propName, std::string value){
            this->propName = propName;
            this->propValue = value; 
        }
        virtual  std::string  name(){ return propName;}
        virtual  std::string  value(){ return propValue;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual PropType type(){ return PropType::STRING_PROP;}
};

class ObjectProp: public Prop {
    private:
        std::string propName; 
        std::string propValue; 

    public:
        ObjectProp(std::string propName, std::string value){
            this->propName = propName;
            this->propValue = value; 
        }
        virtual std::string  name(){ return propName;}
        virtual std::string  value(){ return propValue;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual PropType type(){ return PropType::OBJECT_PROP;}
};

class BooleanProp: public Prop {
    private:
        std::string propName; 
        std::string propValue; 

    public:
        BooleanProp(std::string propName, std::string value){
            this->propName = propName;
            this->propValue = value; 
        }
        virtual  std::string  name(){ return propName;}
        virtual  std::string  value(){ return propValue;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual PropType type(){ return PropType::BOOLEAN_PROP;}
};