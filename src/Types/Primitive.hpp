#include "Element.hpp"
#include "CharType.hpp"
class Name: Primitive{

    Name(firstLetter: Letter,  )
}
class StringType: Primitive{

};

class ArrayType: Primitive{

};

class ObjectType: Primitive{

};

class NumberType: Primitive{

};

class Name: Primitive{
};



class ObjectOpenBracket{
    public:
        ObjectOpenBracket(value: Symbol, ){
            Character::setValue(value);
        }
        std::string getValue(){return Character::getValue();}
        void setValue(std::string value){Character::setValue(value);}
        virtual Type type(){ return CharacterType::EscapedSingleQuote;}
};

class ObjectCloseBracket: Symbol{
    public:
        ObjectCloseBracket(value){
            Character::setValue(value);
        }
        std::string getValue(){return Character::getValue();}
        void setValue(std::string value){Character::setValue(value);}
        virtual Type type(){ return CharacterType::ObjectCloseBracket;}
};

class ArrayOpenBracket: Symbol{
    public:
        ArrayOpenBracket(value){
            Character::setValue(value);
        }
        std::string getValue(){return Character::getValue();}
        void setValue(std::string value){Character::setValue(value);}
        virtual Type type(){ return CharacterType::EscapedSingleQuote;}
};

class ArrayCloseBracket: Symbol{
    public:
        ArrayOpenBracket(value){
            Character::setValue(value);
        }
        std::string getValue(){return Character::getValue();}
        void setValue(std::string value){Character::setValue(value);}
        virtual Type type(){ return CharacterType::EscapedSingleQuote;}
};