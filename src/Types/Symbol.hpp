#pragma once
#include <string>
#include <iostream>
#include "CharType.cpp"

class Colon;
class Comma;
class OpenBracket;
class CloseBracket;
class ArrayOpenBracket;
class ArrayCloseBracket;
class ObjectOpenBracket;
class ObjectCloseBracket;
class Exclamation;
class Dash;
class QuestionMark;
class EscapedSingleQuote;
class EscapedQuote;
class Quote;
class SingleQuote;

class Quote: public Symbol{
    private:
        std::string value; 
    public:
        Quote(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
        virtual SymbolType symbolType(){ return SymbolType::Quote;}

};

class ObjectOpenBracket: Symbol{
    private:
        std::string value;

    public:
        ObjectOpenBracket(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ObjectOpenBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};
class ObjectCloseBracket: Symbol{
    private:
        std::string value;

    public:
        ObjectCloseBracket(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ObjectCloseBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};
class ArrayOpenBracket: Symbol{
    private:
        std::string value;

    public:
        ArrayOpenBracket(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ArrayOpenBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ArrayCloseBracket: Symbol{
    private:
        std::string value;

    public:
        ArrayCloseBracket(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ArrayCloseBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class OpenBracket: Symbol{
    private:
        std::string value;

    public:
        OpenBracket(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";            
        }

        virtual SymbolType symbolType(){ return SymbolType::OpenBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class CloseBracket: Symbol{
    private:
        std::string value;

    public:
        CloseBracket(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::CloseBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Colon: Symbol{
    private:
        std::string value;

    public:
        Colon(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Colon;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Comma: Symbol{
    private:
        std::string value;

    public:
        Comma(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Colon;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Exclamation: Symbol{
    private:
        std::string value;

    public:
        Exclamation(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Exclamation;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Dash: Symbol{
    private:
        std::string value;

    public:
        Dash(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Dash;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class QuestionMark: public Symbol{
    private:
        std::string value;

    public:
        QuestionMark(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::QuestionMark;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class EscapedQuote: public Symbol{
    private:
        std::string value;
    public:
        EscapedQuote(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }
        virtual SymbolType symbolType(){ return SymbolType::EscapedQuote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class SingleQuote: public Symbol{
    private:
        std::string value; 
    public:
        SingleQuote(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual SymbolType symbolType(){ return SymbolType::SingleQuote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}

};

class EscapedSingleQuote: public Symbol{
    private:
        std::string value;

    public:
        EscapedSingleQuote(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual SymbolType symbolType(){ return SymbolType::EscapedSingleQuote;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};