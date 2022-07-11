#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "linenoise.hpp"
#include "Tokenizer.hpp"
#include "Reader.hpp"
#include "printer.hpp"
#include "Node.hpp"
Node* READ(std::string input)
{
    std::cout << input << "\n"; 
    return read_str(input); 
}


Node* EVAL(Node* ast)
{
    return ast; 
}

std::string PRINT(Node* result){
    if(result != NULL){
        Node::display(result);
    }
    return ""; 
}

std::string rep(std::string input){
    Node* ast = READ(input);
    Node* result = EVAL(ast);
    return PRINT(result);

}

int main(int argc, char** argv){

    if(argc > 1){
        std::ifstream file;
        std::string line; 
        std::vector<std::string> lines; 
        std::string text; 
        // std::cout << "File name: " << argv[1] << "\n";  
        file.open(argv[1]);
        while (std::getline(file, line)){
            lines.push_back(line); 
        }
        for(std::string l : lines){
            text += l; 
        }
        file.close();
        rep(text);
    }else{
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
    }
    return 0; 
}