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

    static Node* findNode(Node* tree, Value* currenetValue)
    {
        int numberOfChildren = tree->children.size(); 
        if(numberOfChildren > 0)
        {
            //Check to see if parent has children with a match
            //go right to left
            int i = numberOfChildren -1; 
            while(numberOfChildren >= 0)
            {
                if(tree->children[i]->value->str() == currenetValue->str())
                {
                    if(Node::isPair(tree->children.at(i), currenetValue))
                    {
                        std::cout << "A pair was found" << "\n"; 
                        return tree->children.at(i)->parent;
                    }
                    std::cout   << "Error: A " << tree->children.at(i)->value->getType() 
                                << " for " << currenetValue->str()
                                << " was found after a " << currenetValue->getType()  
                                << "\n"; 
                    return NULL;
                }
                i--; 
            }
        }
        if(tree->parent->parent != NULL){
                //no nodes at this level, go up one
                Node::findNode(tree->parent->parent, currenetValue);
            }
            std::cout   << "Error: A " << currenetValue->getType() 
                        << " for " << currenetValue->str()
                        << " was found without a starting tag "   
                        << "\n"; 
                    return NULL;
        return NULL; 
    }

    /**
     * @brief Get the bottom right node of the tree
     * Uses recursion to navigate the most right most and most bottom node
     * @param node, a tree
     * @return int the level of the node
     */
    static Node* getLastNode(Node* node)
    {
        int childNodes = node->children.size();
        std::cout << "NUmber of child nodes " << childNodes << "\n"; 
        if(childNodes > 0)
        {
            Node::getLastNode(node->children[childNodes - 1]);
        }
        return node;
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

    /**
     * @brief Checks if two nodes are a match
     * 
     * @param node1 a node
     * @param node2 a different node
     * @return boolean
     */
    static bool isPair(Node* node1, Node* node2)
    {
        if(node1 && node2){
        if(node1->value->str() == node2->value->str())
        {
            if(node1->value->type() == Type::EndTag)
            {
                return node2->value->type() == Type::StartTag;
            }

            if(node1->value->type() == Type::StartTag)
            {
                return node2->value->type() == Type::EndTag;
            }
        }
        }

        return false;
    }

      /**
     * @brief Checks if two nodes are a match
     * 
     * @param node1 a node
     * @param node2 a different node
     * @return boolean
     */
    static bool isPair(Node* node1, Value* valueToCompare){
        if(node1->value->str() == valueToCompare->str())
        {
            if(node1->value->type() == Type::EndTag)
            {
                return valueToCompare->type() == Type::StartTag;
            }

            if(node1->value->type() == Type::StartTag)
            {
                return valueToCompare->type() == Type::EndTag;
            }
        }

        return false;
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
                    std::cout << "The child node " << node->children[0]->value->str() << " is below " << node->children[0]->parent->value->str() << "\n";
                }else{
                    insertValue(node->children[node->children.size() - 1], valueToAdd);
                }
            }else{
                Node* lastNode = Node::getLastNode(node);

                std::cout << "The last node is " << lastNode->value->str() << "\n"; 
                if(lastNode->parent != NULL){
                    std::cout << "The last node parent is " << lastNode->parent->value->str() << "\n";
                    Node* foundParentNode = Node::findNode(lastNode->parent, valueToAdd); 
                    if(foundParentNode != nullptr)
                    {
                        std::cout   << "Adding " << valueToAdd->str() 
                                    << " - " <<valueToAdd->getType() 
                                    << " has been added to " 
                                    << foundParentNode->value->str()
                                    << "\n"; 
                        foundParentNode->children.push_back(new Node(valueToAdd, bottomLevel + 1, foundParentNode));
                    }else{
                        std::cout << "No parent was found" << "\n"; 
                    }
                    
                }else{
                    std::cout << "The last node's parent is evidently not set \n"; 
                }

            
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
