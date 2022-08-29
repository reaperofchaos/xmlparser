#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <optional>
#include <memory>
#include "Types/Element.hpp"
class Node{
    public:
        std::shared_ptr<Element> value = NULL; 
        std::shared_ptr<Node> parent = NULL;
        std::vector<std::shared_ptr<Node>> children;
        int level = 0; 

    Node(){};    
    Node(std::shared_ptr<Element> element)
    {
        this->value = element;
    }
    
    Node(std::shared_ptr<Element> newValue, std::shared_ptr<Node> parentNode)
    {
        this->value = newValue;
        this->parent = parentNode;
    }

    Node(std::shared_ptr<Element> newValue, int level, std::shared_ptr<Node> parentNode)
    {
        this->value = newValue;
        this->level = level;
        this->parent = parentNode;

    }

    void setValue(std::shared_ptr<Element> value){this->value = value; }

    /**
     * @brief Get the level property of the bottom of the tree
     * Uses recursion to navigate the most right most and most bottom node
     * @param node, a tree
     * @return int the level of the node
     */
    static int getLastLevel(std::shared_ptr<Node> node)
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
    static std::shared_ptr<Node> findNode(std::shared_ptr<Node> tree, std::shared_ptr<Element> currentValue)
    {
        int numberOfChildren = tree->children.size();
        // Tree is root (no parents) and currentValue is an end tag and has a value
        // string equal to the tree's value string then return the root node
        if(tree->parent == NULL && tree->value->getValue() == currentValue->getValue())
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
                if(tree->children[i]->value->getValue() == currentValue->getValue())
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
                                << " for " << currentValue->getValue()
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
                        << " for " << currentValue->getValue()
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
    static std::shared_ptr<Node> getLastNode(std::shared_ptr<Node> node)
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
    static std::shared_ptr<Node> createTree(std::vector<std::shared_ptr<Element>> valuesToAdd)
    {
        std::shared_ptr<Node> root =  std::make_shared<Node>(); 
        std::cout << "Creating tree from the nodes" << "\n\n"; 
        for(std::shared_ptr<Element> valueToAdd : valuesToAdd)
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
    static bool isPair(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
    {
        if(node1 && node2)
        {
            if(node1->value->getValue() == node2->value->getValue())
            {
                if(node1->value->type() == TagType::CloseTagElement)
                {
                    return node2->value->type() == TagType::OpenTagElement;
                }

                if(node1->value->type() == TagType::OpenTagElement
                {
                    return node2->value->type() == TagType::CloseTagElement;
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
    static bool isPair(std::shared_ptr<Node> node1, std::shared_ptr<Element> valueToCompare){
        if(node1->value->getName() == valueToCompare->getName())
        {
            if(node1->value->type() == TagType::CloseTagElement)
            {
                return valueToCompare->type() == TagType::OpenTagElement;
            }

            if(node1->value->type() == TagType::OpenTagElement)
            {
                return valueToCompare->type() == TagType::CloseTagElement;
            }
        }

        return false;
    }

    void insertValue(std::shared_ptr<Node> node, std::shared_ptr<Element> valueToAdd)
    {
        //if Node pointer is null, create a root node
        if (node->value == NULL)
        {
            std::cout << "The first node " << valueToAdd->getValue() << " has been added" << "\n"; 
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
    static std::shared_ptr<Node> findLastNode(Node* node)
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
    static void display(std::shared_ptr<Node> node)
    {
            if(node->level == 0)
            {
                std::cout   << "Root is " << node->value->getValue() << "\n"; 
            }else{
                std::cout   << "Child Node: " << node->value->getValue() 
                            << " - " << node->value->getType()
                            <<  " level: " << node->level << " \n";
                std::cout   << "Child of parent " << node->parent->value->getValue() 
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
