#include "Element.hpp"

class PairedTag: Tag{

}

class UnpairedTag: Tag{

}

class ClosingTag: PairedTag{

}

class OpenTag: PairedTag{

}

class SelfClosingTag: UnpairedTag{

}

class XMLTag: UnpairedTag{

}

class CommentTag: UnpairedTag{
    
}

class TagOpenBracket: Symbol{
    public:
        TagOpenBracket(value){
            Character::setValue(value);
        }
        std::string getValue(){return Character::getValue();}
        void setValue(std::string value){Character::setValue(value);}
        virtual Type type(){ return CharacterType::EscapedSingleQuote;}
};

class TagCloseBracket: Symbol{
    public:
        TagOpenBracket(value){
            Character::setValue(value);
        }
        std::string getValue(){return Character::getValue();}
        void setValue(std::string value){Character::setValue(value);}
        virtual Type type(){ return CharacterType::EscapedSingleQuote;}
};