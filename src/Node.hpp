#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <optional>
#include "Types.hpp"

class Node{
    public:
        Value* value = NULL; 
        Node* parent = NULL;
        std::vector<Node*> children;
        int level = 0; 

    Node(){};    
    Node(Value* newValue)
    {
        this->value = newValue;
    }
    
    Node(Value* newValue, Node* parentNode)
    {
        this->value = newValue;
        this->parent = parentNode;
    }

    Node(Value* newValue, int level, Node* parentNode)
    {
        this->value = newValue;
        this->level = level;
        this->parent = parentNode;

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
        Node* lastNode = Node::findLastNode(root); 
        std::cout << "The last node is " << lastNode->value->str() << "\n"; 
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
                    node->children.push_back(new Node(valueToAdd, bottomLevel + 1, node));
                }else{
                    insertValue(node->children[node->children.size() - 1], valueToAdd);
                }
            }else{
                int lastLevel = Node::getLastLevel(node);
                std::cout << "The last level is " << lastLevel << "\n"; 

            
                //find opening tag in tree
                    //find the last node
                    //work our way up
                    //find the node of the parent that contains the child node of the opening tag
                    //add the child node here

            }
        }
    }

    /**
     * @brief Traverses the tree and finds the bottom right most node. 
     * @param node, a tree
     * @return int the level of the node
     */
    static Node* findLastNode(Node* node)
    {
        int childNodes = node->children.size();
        std::cout << "There are " << childNodes << " child nodes \n"; 
        if(childNodes > 0)
        {
            findLastNode(node->children[node->children.size() - 1]);
        }
        std::cout << "The last node is " << node->value->str() << "\n"; 
        return node;
    }

   /**
    * @brief Function to display the values 
    * and levels of all nodes in the tree
    * 
    * @param node, a tree node with Values
    */
    static void display(Node* node)
    {
            if(node->level == 0)
            {
                std::cout << "Root is " << node->value->str() << "\n"; 
            }else{
                std::cout << "Child Node: " << node->value->str() <<  " level: " << node->level << " \n";
                std::cout << "Child of parent " << node->parent->value->str() << "level: " << node->parent->level << "\n";
            }
            if(node->children.size() > 0)
            {
                 for(Node* childNode : node->children)
                 {
                    display(childNode);
                };
            }     
    }
   
};
