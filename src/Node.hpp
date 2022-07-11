#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <optional>
#include "Types.hpp"

class Node{
    public:
        Value* value = NULL; 
        std::vector<Node*> children;
        int level = 0; 

    Node(){};    
    Node(Value* newValue)
    {
        this->value = newValue;
    }

    Node(Value* newValue, int level)
    {
        this->value = newValue;
        this->level = level; 
    }

    void setValue(Value* value){this->value = value; }

    /**
     * @brief Get the level property of the bottom of the tree
     * Uses recursion to navigate the most right most and most bottom node
     * @param node, a tree
     * @return int the level of the node
     */
    static int getLastLevel(Node* node)
    {
        int childNodes = node->children.size();
        if(childNodes > 0)
        {
            getLastLevel(node->children[node->children.size() - 1]);
        }
        return node->level;
    }

    static Node* createTree(std::vector<Value*> valuesToAdd)
    {
        Node* root =  new Node(); 
        std::cout << "Creating tree from the nodes" << "\n\n"; 
        for(Value* valueToAdd : valuesToAdd)
        {
            root->insertValue(root, valueToAdd);
        }
        return root; 
    }

   void insertValue(Node* node, Value* valueToAdd)
   {
        if (node->value == NULL)
        {
            std::cout << "The first node " << valueToAdd->str() << " has been added" << "\n"; 
            node->setValue(valueToAdd);
        }else{
            int bottomLevel = getLastLevel(node);
            if(valueToAdd->type() != Type::EndTag)
            {
                if(node->children.size() == 0)
                {
                    std::cout << "The child node " << valueToAdd->str() << " has been added below "<< node->value->str() << "\n"; 
                    node->children.push_back(new Node(valueToAdd, bottomLevel + 1));
                }else{
                    insertValue(node->children[node->children.size() - 1], valueToAdd);
                }
            }
        }
    }

    static void display(Node* node)
    {
            std::cout << "Root is " << node->value->str() << "\n"; 
             if(node->children.size() > 0){
                 std::cout << "Child Nodes " << node->children.size() << "\n";
                for(Node* childNode : node->children){
                    std::cout << "Child Node: " << childNode->value->str() <<  " level: " << childNode->level << " \n";
                };
            }       
    }
   
};
