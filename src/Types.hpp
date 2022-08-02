#pragma once
#include <cassert>
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include "Prop.hpp"

class TagValue;
class StringValue;
class CommentValue; 
class SymbolValue; 
class DocumentTagValue;
class XmlTagValue; 
class StartTagValue; 
class EndTagValue; 
class SelfClosingTagValue; 

enum class Type
{
    Tag,
    String,
    Comment,
    DocumentTag,
    XmlTag,
    StartTag,
    EndTag,
    SelfClosingTag,
    Symbol
};
class Value {
    private: 
        std::string m_str; 
    public:

        
        virtual std::string getTypeAsString(Type type){
            switch (type)
            {
                case Type::Tag:
                    return "Tag";
                case Type::String:
                    return "string";
                case Type::Comment:
                    return "Comment";
                case Type::DocumentTag:
                    return "Document Tag"; 
                case Type::XmlTag:
                    return "Xml Tag";
                case Type::StartTag:
                    return "Start Tag"; 
                case Type::EndTag:
                    return "End Tag";
                case Type::SelfClosingTag:
                    return "Self closing Tag";
                case Type::Symbol:
                    return "Symbol"; 
                default: 
                    return ""; 
            }
        }

        virtual Type type(){ assert(0);}
        virtual std::string inspect() { assert(0); }
        virtual  std::string  str(){ return m_str;}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
        TagValue* as_tag(); 
        StringValue* as_string(); 
        CommentValue* as_comment(); 
        SymbolValue* as_symbol(); 
        DocumentTagValue* as_document_tag(); 
        XmlTagValue* as_xml_tag(); 
        EndTagValue* as_end_tag(); 
        StartTagValue* as_start_tag(); 
        SelfClosingTagValue* as_self_closing_tag(); 
};

class TagValue: public Value {
    private:
        std::string m_str; 
        std::vector<std::pair<std::string, std::string>> properties;

    public:
        TagValue(std::string_view str){
            typedef std::size_t count_t, pos_t;
            this->m_str = str.substr(pos_t(1), count_t(str.length()-2));
        }

        std::string  str(){ return m_str;}

        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}
        virtual Type type(){ return Type::Tag;}
};

class DocumentTagValue: public Value {
    private:
        std::string m_str; 
        std::vector<std::pair<std::string, std::string>> properties;

    public:
        DocumentTagValue(std::string_view str){
            // std::string tagContents= std::string(str.substr(1, str.length()-2));
            // std::string* pointer = &m_str; 
            m_str=str; 

        }

        std::string  str(){ return m_str;}

        virtual std::string inspect(){ return str();}
        virtual Type type(){ return Type::DocumentTag;}
};

class XmlTagValue: public Value {
    private:
        std::string m_str; 
        std::vector<std::pair<std::string, std::string>> properties;

    public:
        XmlTagValue(std::string_view str){
            //<tag> to tag
            this->m_str = str.substr(1, str.length()-1);
        }

        std::string  str(){ return m_str;}

        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}
        virtual Type type(){ return Type::XmlTag;}
};

class StartTagValue: public Value {
    private:
        std::string m_str; 
        // std::vector<Prop> properties = {};

    public:
        StartTagValue(std::string_view str){

            //<tag> to tag
            // std::string tagContents = std::string(str.substr(1, str.length()-2)); 
            // std::string* pointer = &m_str;
            m_str=str; 
        }

        

        std::string  str(){ return m_str;}

        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}
        virtual Type type(){ return Type::StartTag;}
};

class EndTagValue: public Value {
    private:
        std::string m_str; 
        std::vector<std::pair<std::string, std::string>> properties;

    public:
        EndTagValue(std::string_view str){
            //</tag> to tag
            this->m_str = str.substr(2, str.length() -3);
        } 
        std::string  str(){ return m_str;}

        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}
        virtual Type type(){ return Type::EndTag;}
};

class SelfClosingTagValue: public Value {
    private:
        std::string m_str; 
        std::vector<std::pair<std::string, std::string>> properties;

    public:
        SelfClosingTagValue(std::string_view str){
            //<tag /> to tag
            if(str.at(str.length()-3)== ' '){
                this->m_str = str.substr(1, str.length()-4); 
            //<tag/> to tag
            }else{
                this->m_str = str.substr(1, str.length()-3); 
            }
        }
        std::string  str(){ return m_str;}

        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}
        virtual Type type(){ return Type::SelfClosingTag;}
};

class StringValue: public Value {
    private:
        std::string m_str; 

    public:
        StringValue(std::string_view str): m_str {str} {}

        std::string str(){ return m_str;}

        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}
        virtual Type type(){ return Type::String;}
};

class CommentValue: public Value {
    private: 
        std::string m_str; 

    public:
        CommentValue(std::string_view str): m_str {str} {}
        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}

        virtual Type type(){ return Type::Comment;}
};

class SymbolValue: public Value
{
    private: 
        std::string m_str; 

     public:
        SymbolValue(std::string_view str): m_str {str} {}

        std::string str(){ return m_str;}
        virtual std::string inspect(){ return "Type " + getTypeAsString(type()) + " - " + str();}

        virtual Type type(){ return Type::Symbol;}

};