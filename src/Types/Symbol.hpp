#ifndef SYMBOL_H
#define SYMBOL_H
#pragma once
#include <string>
#include <iostream>
#include "CharType.cpp"

class Symbol;
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

class Symbol: public Character{
    private: 
        std::string value; 
    public:
        Symbol(std::string value){
            this->value = value;
            std::cout << this->inspect() << "\n";

        }
        
        virtual std::string getSymbolTypeAsString(SymbolType type){
            switch (type)
            {
                case SymbolType::NotASymbol:
                    return "Not a symbol";
                case SymbolType::Quote:
                    return "Quote";
                case SymbolType::SingleQuote:
                    return "Single Quote";
                case SymbolType::EscapedQuote:
                    return "Escaped Quote"; 
                case SymbolType::EscapedSingleQuote:
                    return "Escaped Single Quote";
                case SymbolType::Colon:
                    return "Colon";
                case SymbolType::Comma:
                    return "Comma";
                case SymbolType::OpenBracket:
                    return "Open Bracket";
                case SymbolType::CloseBracket:
                    return "Close Bracket"; 
                case SymbolType::ObjectOpenBracket:
                    return "Object Open Bracket"; 
                case SymbolType::ObjectCloseBracket:
                    return "Object Close Bracket"; 
                case SymbolType::ArrayOpenBracket:
                    return "Array Open Bracket"; 
                case SymbolType::ArrayCloseBracket:
                    return "Array Close Bracket"; 
                case SymbolType::Exclamation:
                    return "Exclamation";
                case SymbolType::Dash:
                    return "Dash";
                case SymbolType::QuestionMark:
                    return "Question Mark"; 
                default: 
                    return "Unknown"; 
            }
        }
        virtual CharacterType type(){ return CharacterType::Symbol;}
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};
class Quote: public Symbol{
    private:
        std::string value; 
    public:
        Quote(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ObjectOpenBracket: public Symbol{
    private:
        std::string value;

    public:
        ObjectOpenBracket(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ObjectOpenBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}

};
class ObjectCloseBracket: public Symbol{
    private:
        std::string value;

    public:
        ObjectCloseBracket(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ObjectCloseBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}

};
class ArrayOpenBracket: public Symbol{
    private:
        std::string value;

    public:
        ArrayOpenBracket(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ArrayOpenBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ArrayCloseBracket: public Symbol{
    private:
        std::string value;

    public:
        ArrayCloseBracket(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::ArrayCloseBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class OpenBracket: public Symbol{
    private:
        std::string value;

    public:
        OpenBracket(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";            
        }

        virtual SymbolType symbolType(){ return SymbolType::OpenBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class CloseBracket: public Symbol{
    private:
        std::string value;

    public:
        CloseBracket(std::string value): Symbol(value){
            this->value = value; 
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::CloseBracket;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Colon: public Symbol{
    private:
        std::string value;

    public:
        Colon(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Colon;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Comma: public Symbol{
    private:
        std::string value;

    public:
        Comma(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Colon;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Exclamation: public Symbol{
    private:
        std::string value;

    public:
        Exclamation(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Exclamation;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Dash: public Symbol{
    private:
        std::string value;

    public:
        Dash(std::string value): Symbol(value){
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual SymbolType symbolType(){ return SymbolType::Dash;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
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
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
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
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
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
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
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
        virtual std::string getType(){return this->getSymbolTypeAsString(this->symbolType());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};
#endif