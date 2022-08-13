#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "CharType.hpp"
#include "Symbol.hpp"

class Primitive;
class Name;
class StringType;
class ArrayType;
class ObjectType;
class NumberType;
class CloseObject;
class OpenObject;
class ObjectPair;
class OpenTag;
class CloseTag;
class OpenArray;
class CloseArray;
class CommaPrimitive;
class ColonPrimitive;
class ExclamationPrimitive;
class QuestionPrimitive;
class DashPrimitive;
class WhiteSpaces;
class ClosingOpenTag;
class ClosingCloseTag;
class EqualPrimitive;

enum class PrimitiveType
{
    Name, 
    StringType,
    ArrayType,
    ObjectType,
    NumberType,
    Unknown,
    CloseObject,
    OpenObject,
    OpenTag,
    CloseTag,
    OpenArray,
    CloseArray,
    ColonPrimitive,
    CommaPrimitive, 
    ExclamationPrimitive,
    QuestionPrimitive,
    DashPrimitive,
    WhiteSpaces,
    ClosingCloseTag,
    ClosingOpenTag,
    EqualPrimitive
};

class Primitive{
    private:
        std::string value;
    public:
        Primitive(){};
        virtual ~Primitive() = default;
        virtual std::string getTypeAsString(PrimitiveType type){
            switch (type)
            {
                case PrimitiveType::Name:
                    return "Name";
                case PrimitiveType::StringType:
                    return "String";
                case PrimitiveType::NumberType:
                    return "Number";
                case PrimitiveType::OpenTag:
                    return "Open Tag";
                case PrimitiveType::OpenArray:
                    return "Open array";
                case PrimitiveType::OpenObject:
                    return "Open object";
                case PrimitiveType::CloseTag:
                    return "Close tag";
                case PrimitiveType::CloseArray:
                    return "Close array";
                case PrimitiveType::CloseObject:
                    return "Close object";
                case PrimitiveType::WhiteSpaces:
                    return "White spaces";
                case PrimitiveType::ExclamationPrimitive:
                    return "Exclamation";
                case PrimitiveType::ClosingCloseTag:
                    return "Closing Close Tag";
                case PrimitiveType::ClosingOpenTag:
                    return "Closing Open Tag";
                case PrimitiveType::EqualPrimitive:
                    return "Equal";
                default: 
                    return "Unknown";
            }
        }
        
        virtual PrimitiveType type(){ return PrimitiveType::Unknown;}
        virtual std::string inspect() { assert(0); }
        virtual std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
};

class StringType: public Primitive{
    private:
        std::string value;

    public:
        StringType(std::shared_ptr<Quote> q, std::vector<std::shared_ptr<Character>> characters, std::shared_ptr<Quote> q2): Primitive(){
            std::string value = "";
            value += q->getValue();
            for(std::shared_ptr<Character> character : characters){
                value += character->getValue(); 
            }
            value += q2->getValue(); 
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        StringType(std::shared_ptr<SingleQuote> q, std::vector<std::shared_ptr<Character>> characters, std::shared_ptr<SingleQuote> q2){
            std::string value = "";
            value += q->getValue();
            for(std::shared_ptr<Character> character : characters){
                value += character->getValue(); 
            }
            value += q2->getValue();
            this->value = value;
            std::cout << this->inspect() << "\n";
        }
        virtual PrimitiveType type(){ return PrimitiveType::StringType;}
        std::string getValue(){ return value;}
        virtual void setValue(std::shared_ptr<Quote> q, std::vector<std::shared_ptr<Character>> characters, std::shared_ptr<Quote> q2)
        {
            std::string value = "";
            value += q->getValue();
            for(std::shared_ptr<Character> character : characters){
                value += character->getValue(); 
            }
            value += q2->getValue();
            this->value = value;
        }
        virtual void setValue(std::shared_ptr<SingleQuote> q, std::vector<std::shared_ptr<Character>> characters, std::shared_ptr<SingleQuote> q2)
        {
            std::string value = "";
            value += q->getValue();
            for(std::shared_ptr<Character> character : characters){
                value += character->getValue(); 
            }
            value += q2->getValue();
            this->value = value;
        }
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};



class NumberType: public Primitive{
    private:
        std::string value;

    public:
        NumberType(std::vector<std::shared_ptr<Number>> numbers): Primitive(){
            std::string numberString = "";
            for(std::shared_ptr<Number> number : numbers ){
                numberString += number->getValue(); 
            }
            this->value = numberString;
            std::cout << this->inspect() << "\n";
        }
        virtual void setValue(std::vector<std::shared_ptr<Number>> numbers)
        {
            std::string numberString = "";
            for(std::shared_ptr<Number> number : numbers ){
                numberString += number->getValue(); 
            }
            this->value = numberString;
        }
        std::string getValue(){ return this->value; }
        virtual PrimitiveType type(){ return PrimitiveType::NumberType;}
        int getValueAsNumber(){ return std::stoi(this->value);}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class Name: public Primitive{
    private:
        std::string value;

    public:
        Name(std::shared_ptr<Letter> letter, std::vector<std::shared_ptr<Character>> characters){
            std::string value = letter->getValue();
            for(std::shared_ptr<Character> character : characters){
                value += character->getValue();
            }
            this->value = value;
            std::cout << this->inspect() << "\n";
        }

        virtual PrimitiveType type(){ return PrimitiveType::Name;}
        virtual void setValue(std::shared_ptr<Letter> letter, std::vector<std::shared_ptr<Character>> characters)
        {
            std::string value = letter->getValue();
            for(std::shared_ptr<Character> character : characters){
                value += character->getValue();
            }
            this->value = value;
        }
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class OpenObject: public Primitive{
    private:
        std::string value;

    public:
        OpenObject(std::shared_ptr<ObjectOpenBracket> openBracket){
            this->value = openBracket->getValue();
        }

        OpenObject(std::shared_ptr<ObjectOpenBracket> openBracket, std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces){
            std::string value = "";
            value += openBracket->getValue();
        
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::OpenObject;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};
class CloseObject: public Primitive{
    private:
        std::string value;

    public:
        CloseObject(std::shared_ptr<ObjectCloseBracket> closeBracket){
            this->value = closeBracket->getValue();
        }

        CloseObject(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<ObjectCloseBracket> closeBracket){
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += closeBracket->getValue();
            this->value = value;
        }

        virtual PrimitiveType type(){ return PrimitiveType::CloseObject;}
        virtual void setValue(std::shared_ptr<ObjectCloseBracket> closeBracket){this->value = closeBracket->getValue();}
        virtual void setValue(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<ObjectCloseBracket> closeBracket)
        {
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += closeBracket->getValue();
            this->value = value;
        }

        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};
class OpenArray: public Primitive{
    private:
        std::string value;

    public:
        OpenArray(std::shared_ptr<ArrayOpenBracket> openBracket){
            this->value = openBracket->getValue();
        }

        OpenArray(std::shared_ptr<ArrayOpenBracket> openBracket, std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces){
            std::string value = "";
            value += openBracket->getValue();

            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::OpenArray;}
        virtual void setValue(std::shared_ptr<ArrayOpenBracket> openBracket){
            this->value = openBracket->getValue();
        }
        virtual void setValue(std::shared_ptr<ArrayOpenBracket> openBracket, std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces){
            std::string value = "";
            value += openBracket->getValue();

            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            this->value = value; 
        }
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class CloseArray: public Primitive{
    private:
        std::string value;

    public:
        CloseArray(std::shared_ptr<ArrayCloseBracket> closeBracket){
            this->value = closeBracket->getValue();
        }

        CloseArray(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<ArrayCloseBracket> closeBracket){
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += closeBracket->getValue();
            this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::CloseArray;}
        std::string getValue(){ return value;}
        virtual void setValue(std::shared_ptr<ArrayCloseBracket> closeBracket){this->value = closeBracket->getValue();}
        virtual void setValue(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<ArrayCloseBracket> closeBracket)
        {
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += closeBracket->getValue();
            this->value = value; 
        }

        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class OpenTag: public Primitive{
    private:
        std::string value;

    public:
        OpenTag(std::shared_ptr<OpenBracket> openBracket){
            this->value = openBracket->getValue();
        }

        OpenTag(std::shared_ptr<OpenBracket> openBracket, std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces){
            std::string value = "";
            value += openBracket->getValue();
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            
            this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::OpenTag;}
        std::string getValue(){ return value;}
        
        virtual void setValue(std::shared_ptr<OpenBracket> openBracket){
            this->value = openBracket->getValue();
        }

        virtual void setValue(std::shared_ptr<OpenBracket> openBracket, std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces){
            std::string value = "";
            value += openBracket->getValue();
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            
            this->value = value;
        }

        virtual std::string getType(){return this->getTypeAsString(this->type());}
        
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ClosingCloseTag: public Primitive{
    private:
        std::string value;

    public:
        ClosingCloseTag(std::shared_ptr<ForwardSlash> forwardSlash, std::shared_ptr<CloseBracket> closeBracket){
                std::string value = "";
                value += forwardSlash->getValue();
                value += closeBracket->getValue();
                this->value = value; 
        }

        ClosingCloseTag(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<ForwardSlash> forwardSlash, std::shared_ptr<CloseBracket> closeBracket){
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += forwardSlash->getValue();
            value += closeBracket->getValue();
            this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::ClosingCloseTag;}
        std::string getValue(){ return value;}
        virtual void setValue(std::shared_ptr<ForwardSlash> forwardSlash, std::shared_ptr<CloseBracket> closeBracket){
            std::string value = "";
            value += forwardSlash->getValue();
            value += closeBracket->getValue();
            this->value = value; 
        }
        virtual void setValue(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<ForwardSlash> forwardSlash, std::shared_ptr<CloseBracket> closeBracket)
        {
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += forwardSlash->getValue();
            value += closeBracket->getValue();
            this->value = value; 
        }
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ClosingOpenTag: public Primitive{
    private:
        std::string value;

    public:
        ClosingOpenTag(std::shared_ptr<OpenBracket> openBracket, std::shared_ptr<ForwardSlash> forwardSlash){
                std::string value = "";
                value += openBracket->getValue();
                value += forwardSlash->getValue();
                this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::ClosingCloseTag;}
        std::string getValue(){ return value;}
        virtual void setValue(std::shared_ptr<OpenBracket> openBracket, std::shared_ptr<ForwardSlash> forwardSlash){
            std::string value = "";
            value += openBracket->getValue();
            value += forwardSlash->getValue();
            this->value = value; 
        }
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class CloseTag: public Primitive{
    private:
        std::string value;

    public:
        CloseTag(std::shared_ptr<CloseBracket> closeBracket){
                this->value = closeBracket->getValue();
        }

        CloseTag(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<CloseBracket> closeBracket){
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += closeBracket->getValue();
            this->value = value; 
        }

        virtual PrimitiveType type(){ return PrimitiveType::CloseTag;}
        std::string getValue(){ return value;}
        virtual void setValue(std::shared_ptr<CloseBracket> closeBracket){this->value = closeBracket->getValue();}
        virtual void setValue(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces, std::shared_ptr<CloseBracket> closeBracket)
        {
            std::string value = "";
            for(std::shared_ptr<WhiteSpace> whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            value += closeBracket->getValue();
            this->value = value; 
        }
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ColonPrimitive: public Primitive{
    private:
        std::string value;

    public:
        ColonPrimitive(std::shared_ptr<Colon> colon ){
            this->value = colon->getValue();
        }

        virtual PrimitiveType type(){ return PrimitiveType::ColonPrimitive;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class CommaPrimitive: public Primitive{
    private:
        std::string value;

    public:
        CommaPrimitive(std::shared_ptr<Comma> comma ){
            this->value = comma->getValue();
        }

        virtual PrimitiveType type(){ return PrimitiveType::CommaPrimitive;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class WhiteSpaces: public Primitive{
    private:
        std::string value;

    public:
        WhiteSpaces(std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces ){
            std::string value = "";
            for(auto whiteSpace : whiteSpaces)
            {
                value += whiteSpace->getValue();
            }
            this->value = value;
        }

        virtual PrimitiveType type(){ return PrimitiveType::WhiteSpaces;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class ExclamationPrimitive: public Primitive{
    private:
        std::string value;

    public:
        ExclamationPrimitive(std::shared_ptr<Exclamation> exclamation ){
            this->value = exclamation->getValue();
        }

        virtual PrimitiveType type(){ return PrimitiveType::ExclamationPrimitive;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};

class EqualPrimitive: public Primitive{
    private:
        std::string value;

    public:
        EqualPrimitive(std::shared_ptr<EqualSymbol> equal ){
            this->value = equal->getValue();
        }

        virtual PrimitiveType type(){ return PrimitiveType::EqualPrimitive;}
        std::string getValue(){ return value;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        virtual std::string inspect(){ return "Type " + getType() + " - " + getValue();}
};