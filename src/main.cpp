#include <string>
#include <iostream>
#include <unordered_map>
#include "linenoise.hpp"
#include "Tokenizer.hpp"
#include "Reader.hpp"
#include "printer.hpp"

Value *READ(std::string input)
{
    return read_str(input); 
}


Value* EVAL(Value* ast)
{
    std::cout << "ast is " << ast->str() << "\n"; 
    return ast; 
}

std::string PRINT(Value* input){
    return pr_str(input);  
}

std::string rep(std::string input){
    Value* ast = READ(input);
    auto result = EVAL(ast);
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
        std::cout << rep(input) << std::endl; 
        //add text to history
        linenoise::AddHistory(input.c_str()); 
    }
    linenoise::SaveHistory(history_path);
    return 0; 
}