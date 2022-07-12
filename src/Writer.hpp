#pragma once
#include <fstream>
#include "Node.hpp"


class Writer{
    Node* tree;
    std::ofstream out; 

    public:
        Writer(Node* tree)
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

        void writeTreeToFile(){
            this->out << "Parsed Tree \n";
            writeNodes(this->tree); 
            this->out.close(); 

        }

        void writeNodes(Node* node){

            this->out << "Node: " << node->value->str() << 
            " Level: " << node->level << 
            " Type:" << node->value->getTypeAsString(node->value->type()) << "\n";
            if(node->children.size() > 0){
                for(Node* child : node->children)
                {
                    writeNodes(child); 
                }
            }
        }

        void writeNodesAsObject(Node* node)
        {
            std::string spacing = ""; 
            for(int i = 0; i < node->level; i++){
                spacing += "\t";
            }
            std::string elementSpacing = spacing += "\t";
            
            this->out << spacing << "{ \n";
            this->out << "\t" << elementSpacing << "\"name\": \""   << node->value->str() << "\",\n"
                      << "\t" << elementSpacing << "\"level\": \""  << node->level << "\",\n"
                      << "\t" << elementSpacing << "\"type\": \""   << node->value->getTypeAsString(node->value->type()) << "\"";
            if(node->children.size() > 0){
                this->out << ",\n"; 
                this->out << "\t" << elementSpacing << "\"children\": [\n"; 
                for(Node* child : node->children)
                {
                    this->writeNodesAsObject(child); 
                }
                this->out << "\t" << spacing << "]\n";
            }else{
                this->out << "\n"; 
            }
           this->out << elementSpacing << "}\n"; 
        }

        void writeTreeAsJSON(){
            writeNodesAsObject(this->tree); 
            this->out.close(); 
        }
};