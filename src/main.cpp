#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include "linenoise.hpp"
#include "ElementBuilder.hpp"
#include "Node.hpp"
#include "printer.hpp"
#include "Writer.hpp"

std::shared_ptr<Node> READ(std::string input)
{
    std::cout << input << "\n"; 
    return ElementBuilder::read_str(input); 
}


std::shared_ptr<Node> EVAL(std::shared_ptr<Node> ast)
{
    return ast; 
}

void PRINT(std::shared_ptr<Node>result)
{
    if(result != NULL){
        Node::display(result);
    }
    std::string fileName = "out.txt";
    std::cout << "Saving parsed tree to " << fileName << "\n"; 
    Writer* writer = new Writer(result);
    writer->createFile(fileName); 
    writer->setFile("out.json");
    writer->writeTreeAsJSON();
}

std::string rep(std::string input)
{
    std::shared_ptr<Node> ast = READ(input);
    std::shared_ptr<Node> result = EVAL(ast);
    PRINT(result);
    return ""; 
}

int main(int argc, char** argv)
{

    if(argc > 1)
    {
        std::ifstream file;
        std::string line; 
        std::vector<std::string> lines; 
        std::string text; 
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