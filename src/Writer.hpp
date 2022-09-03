#pragma once
#include <fstream>
#include <memory>
#include "Types/Node.hpp"
#include "Types/Element.hpp"
#include "Types/Prop.hpp"


class Writer
{
    std::shared_ptr<Node> tree;
    std::ofstream out; 

    public:
        Writer(std::shared_ptr<Node> tree)
        {
            this->tree = tree;
        }

        ~Writer()
        {
            this->out.close(); 
        }

        void setFile(std::string fileName){ this->out = std::ofstream(fileName);};
        
        void createFile(std::string fileName)
        {
            this->out = std::ofstream(fileName);
            this->writeTreeToFile();
        }

        void writeTreeToFile()
        {
            this->out << "Parsed Tree \n";
            writeNodes(this->tree); 
            this->out.close(); 
        }

        void writeNodes(std::shared_ptr<Node> node)
        {

            this->out << "Node: " << node->value->getValue() << 
            " Level: " << node->level;
            if(node->value->type() == ElementType::Tag){
                this->out << " Type: " 
                    << node->value->getTagTypeAsString(node->value->tagType()) << "\n";
            }else{
                this->out << " Type: " 
                    << node->value->getTypeAsString(node->value->type()) << "\n";
            }
            if(node->value->type() == ElementType::Tag ||
                node->value->type() == ElementType::DocumentTag)
            {
                std::vector<std::shared_ptr<Prop>> props = node->value->getProps();
                if(props.size() > 0)
                {
                    this->out << "Props: [" << "\n";
                    int i = 0; 
                    for(std::shared_ptr<Prop> prop : props)
                    {
                        if(i != 0)
                        {
                            this->out << ",\n";
                        }
                        this->out << "\t{";
                        this->out << "\t\tName: " << prop->getName() << ", \n";
                        this->out << "\t\tType: " << prop->getType() << ", \n";
                        this->out << "\t\tName: " << prop->getValue() << ", \n";
                        this->out << "\t}";
                        i++;
                    }
                    this->out << "\n";
                    this->out << "]\n";  
                }
            }
            if(node->children.size() > 0)
            {
                for(std::shared_ptr<Node> child : node->children)
                {
                    writeNodes(child); 
                }
            }
        }

        void writePair(
            std::string elementSpacing, 
            std::string key, 
            std::string value)
        {
            this->out   << "\t" << elementSpacing 
                        << "\"" << key << "\": \""  
                        << value<< "\"";
        }

        void writeTypePair(
            std::string elementSpacing, 
            std::shared_ptr<Element> value)
        {
            if(value->type() == ElementType::Tag)
            {
                writePair(elementSpacing, "type", 
                    value->getTagType());
            }else{
                writePair(elementSpacing, "type", 
                    value->getType());
            }
        }

        void writeProps(
            std::string elementSpacing, 
            std::vector<std::shared_ptr<Prop>> props)
        {
            this->out   << "\t" << elementSpacing 
                        << "\"" << "props" << "\": [\n";
            int i = 0; 
            for(std::shared_ptr<Prop> prop : props)
            {
                if(i != 0)
                {
                    this->out << ",\n";
                }

                this->out << elementSpacing << "\t\t{\n";
                writePair(elementSpacing+"\t\t", "name", prop->getName() );
                this->out << ", \n"; 
                writePair(elementSpacing+"\t\t", "type", prop->getType() );
                this->out << ", \n"; 
                writePair(elementSpacing+"\t\t", "value", prop->getValue()->getValue() );
                this->out << ", \n"; 
                writePair(elementSpacing+"\t\t", "value-type", prop->getValue()->getType() );
                this->out << "\n"; 
                this->out << elementSpacing << "\t\t}";
                i++;
            }
            this->out << "\n"; 
            this->out   << "\t" << elementSpacing 
                        << "]";
        }

        void writeNodesAsObject(std::shared_ptr<Node> node, bool isChild)
        {
            std::string spacing = ""; 
            for(int i = 0; i < node->level; i++)
            {
                spacing += "\t";
            }

            std::string elementSpacing = spacing += "\t";
            
            this->out   << spacing << "{ \n";
            writePair(elementSpacing, "name", node->value->getValue() );
            this->out   << ",\n";
            writePair(elementSpacing, "level", std::to_string(node->level) );
            this->out   << ",\n";
            writeTypePair(elementSpacing, node->value);

            if(node->value->type() == ElementType::Tag ||
                node->value->type() == ElementType::DocumentTag)
            {
                std::vector<std::shared_ptr<Prop>> props = node->value->getProps();

                if(props.size() > 0)
                {
                    this->out << ",\n";
                    writeProps(elementSpacing, props);
                }
            }
            if(node->children.size() > 0)
            {
                this->out << ",\n"; 
                this->out << "\t" << elementSpacing << "\"children\": [\n"; 
                size_t i = 0; 
                for(std::shared_ptr<Node> child : node->children)
                {

                    this->writeNodesAsObject(child, i < node->children.size() -1); 
                    i++; 
                }
                this->out << "\t" << spacing << "]\n";

            }else{
                
                this->out << "\n"; 
            }

            if(isChild)
            {
                this->out << elementSpacing << "},\n"; 
            }
            else{
                this->out << elementSpacing << "}\n"; 
            }
        }
        

        void writeTreeAsJSON()
        {
            writeNodesAsObject(this->tree, false); 
            this->out.close(); 
        }
};