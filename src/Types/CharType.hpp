#pragma once
#include <string>
#include <iostream>

class Character;
class WhiteSpace;
class Number; 
class Letter; 
class Lowercase;
class Uppercase; 
class Symbol; 
class Quote; 
class SingleQuote;
class EscapedQuote;
class EscapedSingleQuote;
class UnicodeCharacter; 
class UnknownCharacter;

enum class CharacterType
{
    Character,
    WhiteSpace,
    Number,
    Letter,
    Lowercase,
    Uppercase,
    Symbol,
    Quote,
    SingleQuote,
    EscapedQuote,
    EscapedSingleQuote,
    UnicodeCharacter,
    Unknown,
};

class Character{
    private:
        std::string value;

    public: 
        virtual ~Character() = default;
        virtual std::string getTypeAsString(CharacterType type){
            switch (type)
            {
                case CharacterType::Character:
                    return "Character Type";
                case CharacterType::WhiteSpace:
                    return "White space";
                case CharacterType::Number:
                    return "Number Type";
                case CharacterType::Letter:
                    return "Letter"; 
                case CharacterType::Lowercase:
                    return "Lowercase Letter";
                case CharacterType::Uppercase:
                    return "Uppercase Letter"; 
                case CharacterType::Symbol:
                    return "Symbol";
                case CharacterType::Quote:
                    return "Quote"; 
                case CharacterType::SingleQuote:
                    return "Single Quote"; 
                case CharacterType::EscapedQuote:
                    return "Escaped Quote"; 
                case CharacterType::EscapedSingleQuote:
                    return "Escaped Single Quote"; 
                case CharacterType::UnicodeCharacter:
                    return "Unicode Character"; 
                default: 
                    return "Unknown"; 
            }
        }

        virtual CharacterType type(){ return CharacterType::Character;}
        virtual std::string inspect() { assert(0); }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}

        WhiteSpace* as_whitespace(); 
        Number* as_number(); 
        Letter* as_letter(); 
        Lowercase* as_lowercase(); 
        Uppercase* as_uppercase(); 
        Symbol* as_symbol(); 
        Quote* as_quote(); 
        SingleQuote* as_singleQuote(); 
        EscapedQuote* as_escapedQuote(); 
        EscapedSingleQuote* as_escapedSingleQuote(); 
        UnicodeCharacter* as_unicode(); 
        UnknownCharacter* as_unknown(); 

};

class WhiteSpace: public Character{
    private:
        std::string value;

    public:
        WhiteSpace(std::string str){
            this->value = str;
            std::cout << this->inspect() << "\n";
        }

        virtual CharacterType type(){ return CharacterType::WhiteSpace;}
        std::string getValue(){ return value;}
        std::string displayValue(){
            if(this->value[0] == '\n'){
                return "\\n";
            }else if(this->value[0] == ' '){
                return "\\s";
            }else if(this->value[0] == '\r')
            {
                return "\\r";
            }else if(this->value[0] == '\t')
            {
                return "\\t";
            }else {
                return "unknown whitespace";
            }
        }
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + displayValue();}
};

class Number: public Character{
    private: 
        std::string value; 
    public:
        Number(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";

        }

        virtual CharacterType type(){ return CharacterType::Number;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Letter: public Character{
    private:
        std::string value; 

    public:
        Letter(std::string value)
        {
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }
        
        virtual CharacterType type(){ return CharacterType::Letter;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Lowercase: public Character{
    private: 
        std::string value; 
    public:
        Lowercase(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::Lowercase;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + this->getType() + " - " + this->getValue();}
};

class Uppercase: public Character{
    private:
        std::string value;
    public:
        Uppercase(std::string value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::Uppercase;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Symbol: public Character{
    private:
        std::string value; 
    public:
        Symbol(std::string value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::Symbol;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Quote: public Character{
    private:
        std::string value; 
    public:
        Quote(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";
 
        }
        virtual CharacterType type(){ return CharacterType::Quote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}

};

class EscapedQuote: public Character{
    private:
        std::string value;
    public:
        EscapedQuote(std::string value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::EscapedQuote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class SingleQuote: public Character{
    private:
        std::string value; 
    public:
        SingleQuote(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::SingleQuote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}

};

class EscapedSingleQuote: public Character{
    private:
        std::string value;

    public:
        EscapedSingleQuote(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::EscapedSingleQuote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};


class UnicodeCharacter: public Character{
    private: 
        std::string value;
    public:
        UnicodeCharacter(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::UnicodeCharacter;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}

};

class UnknownCharacter: public Character{
    private: 
        std::string value;
    public:
        UnknownCharacter(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual CharacterType type(){ return CharacterType::Unknown;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};