#include <string>
#include <iostream>
#include <unordered_map>
#include "linenoise.hpp"
#include "Tokenizer.hpp"
#include "Reader.hpp"
#include "printer.hpp"
#include "Node.hpp"
Node *READ(std::string input)
{
    std::cout << input << "\n"; 
    return read_str(input); 
}


Node* EVAL(Node* ast)
{
    return ast; 
}

std::string PRINT(Node* input){
    return Node::LevelOrderTraversal(input); 
}

std::string rep(std::string input){
    Node* ast = READ(input);
    Node* result = EVAL(ast);
    return PRINT(result);

}

int main(){
    const auto history_path = "history.txt"; 
    linenoise::LoadHistory(history_path); 

    std::string input;
    for (;;){

        auto quit = linenoise::Readline("hello> ", input); 

        if(quit)
            break;
        if(input == "exit()" || input == "quit()")
        {
            std::cout << "Exiting the XML parser \n"; 
            return 0; 
        }
        std::cout << rep(input) << std::endl; 

        //add text to history
        linenoise::AddHistory(input.c_str()); 

    }
    linenoise::SaveHistory(history_path);
    return 0; 
}