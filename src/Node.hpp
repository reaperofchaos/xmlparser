#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <optional>
#include "Types.hpp"

class Node{
    public:
        Value* value; 
        std::vector<Node*> children;

    Node(Value* newValue){
        this->value = newValue;
    }

    void setValue(Value* value){this->value = value; }

    static Node* createTree(std::vector<Value*> valuesToAdd){
        Node* root =  NULL; 
        std::cout << "Creating tree from the nodes" << "\n\n"; 
        for(Value* valueToAdd : valuesToAdd){
            root = Node::insertValue(root, valueToAdd);
        }
        return root; 
    }

    static Node* insertValue(Node* root, Value* valueToAdd){
        if(valueToAdd->type() != Type::EndTag){
            Node* node  = new Node(valueToAdd);
            //First node
            if (root == NULL){
                root = node;
            }
            // add to the children array
            else{
                root->children.push_back(node);
                //We have one or more child nodes (get the last one) and check if we have children
            }
        }
        return root;
    }

    // void addNode(Value* value){

    //     if(child.size() == 0 ){
    //         setValue(value); 
    //     }else{
    //         Node* newChildNode = new Node(*value); 
    //         child.push_back(newChildNode); 
    //     }
    // }

    // static std::string LevelOrderTraversal(Node* root)
    // {
    //     if (root==NULL)
    //         return "EOF";
    
    //     // Standard level order traversal code
    //     // using queue
    //     std::queue<Node *> q;  // Create a queue
    //     q.push(root); // Enqueue root
    //     while (!q.empty())
    //     {
    //         int n = q.size();
    
    //         // If this node has children
    //         while (n > 0)
    //         {
    //             // Dequeue an item from queue and print it
    //             Node * p = q.front();
    //             q.pop();
    //             Value nodeValue = p->value; 
    //             std::cout << nodeValue.str() << " ";
    
    //             // Enqueue all children of the dequeued item
    //             for (int i=0; i< (int)p->child.size(); i++)
    //                 q.push(p->child[i]);
    //             n--;
    //         }
    
    //         std::cout << std::endl; // Print new line between two levels
    //     }
    //     return "EOF";
    // }
};
