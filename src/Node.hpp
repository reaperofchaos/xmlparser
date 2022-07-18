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

    /**
     * @brief Function to navigate the tree and find the next 
     * node with a value equal to the string of the value provided
     * Reads trees bottom up
     * @param tree pointer to a node on the tree
     * @param currenetValue value to find
     * @return Node* 
     */
    static Node* findNode(Node* tree, Value* currentValue)
    {
        int numberOfChildren = tree->children.size();
        // Tree is root (no parents) and currentValue is an end tag and has a value
        // string equal to the tree's value string then return the root node
        if(tree->parent == NULL && tree->value->str() == currentValue->str())
        {
            if(Node::isPair(tree, currentValue))
            {
                return tree;
            }
        }

        //if the node has children check to see if we have a tag that is a pair
        // for the current value going most recently added to oldest (right to left)
        if(numberOfChildren > 0)
        {
            //Check to see if parent has children with a match
            //go right to left
            int i = numberOfChildren -1; 
            while(i >= 0)
            {
                //If we get a matching name
                if(tree->children[i]->value->str() == currentValue->str())
                {
                    //if we get a maching pair
                    if(Node::isPair(tree->children.at(i), currentValue))
                    {
                        //return the parent of the found element
                        return tree->children.at(i)->parent;
                    }
                    //if the pair doesn't match, we have a linting error,
                    // an end tag without a start tag
                    std::cout   << "Error: A " << tree->children.at(i)->value->getType() 
                                << " for " << currentValue->str()
                                << " was found after a " << currentValue->getType()  
                                << "\n"; 
                    return NULL;
                }
                i--; 
            }
        }
        //No matches were found in the children
        //Check if we have a parent node
        if(tree->parent != NULL){
                //no nodes at this level, go up one
                return Node::findNode(tree->parent, currentValue);
            }else{
                std::cout   << "Error: A " << currentValue->getType() 
                        << " for " << currentValue->str()
                        << " was found without a starting tag "   
                        << "\n"; 
                    return NULL;
            }
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
        if(childNodes > 0)
        {
            return Node::getLastNode(node->children[childNodes - 1]);   
        }

        return node;
    }

    /**
     * @brief Create a Tree object
     * 
     * @param valuesToAdd 
     * @return Node* 
     */
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
        //if Node pointer is null, create a root node
        if (node->value == NULL)
        {
            std::cout << "The first node " << valueToAdd->str() << " has been added" << "\n"; 
            node->setValue(valueToAdd);
        }else{
            Node* lastNode = Node::getLastNode(node);
            int bottomLevel = getLastLevel(node);
            //add tag to children vector if no children exist
            if(valueToAdd->type() != Type::EndTag)
            {
                if(node->children.size() == 0)
                {
                    node->children.push_back(new Node(valueToAdd, bottomLevel + 1, node));
                }else{
                    // we have more than one child node
                    // if the last node was a start tag, 
                    // this next start tag should be nested under it
                    if(lastNode->value->type() == Type::StartTag)
                    {
                        insertValue(node->children[node->children.size() - 1], valueToAdd);
                    // This is a sibling node, so just add it to the child array
                    }else{
                        //Add to the children of the parent of the last node. (Node is a sibling of last node)
                        lastNode->parent->children.push_back(new Node(valueToAdd, lastNode->parent->level +1, lastNode->parent));
                    }
                }
            //We have an end tag, so we need to find the start tag before adding
            }else{
                if(lastNode->parent != NULL){
                        //Navigate through the tree and check to find a start tag with a string value equal
                        // to the value of the string of the value being added. 
                        Node* foundParentNode = Node::findNode(lastNode->parent, valueToAdd); 
                        
                        if(foundParentNode != NULL)
                        {
                            foundParentNode->children.push_back(new Node(valueToAdd, foundParentNode->level +1, foundParentNode));
                        }else{
                            std::cout << "Linting Error: No start tag was found for end tag named  " << valueToAdd->str()  << "\n"; 
                        }
                }else{
                    std::cout << "Tree Error: The last node's parent is evidently not set \n"; 
                }

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
        if(childNodes > 0)
        {
            findLastNode(node->children[node->children.size() - 1]);
        }
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
                std::cout   << "Root is " << node->value->str() << "\n"; 
            }else{
                std::cout   << "Child Node: " << node->value->str() 
                            << " - " << node->value->getType()
                            <<  " level: " << node->level << " \n";
                std::cout   << "Child of parent " << node->parent->value->str() 
                            << " - " << node->value->getType()
                            << " level: " << node->parent->level << "\n";
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
