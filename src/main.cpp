#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>
#include "linenoise.hpp"
#include "Tokenizer/Tokenizer.h"
#include "Tokenizer/Types/CharType.h"
#include "XMLParser/Builders/ComponentBuilder.h"
#include "XMLParser/Builders/ElementBuilder.h"
#include "XMLParser/Types/Node.h"
#include "XMLParser/Types/Component.h"
#include "Writer.h"

std::shared_ptr<Node> READ(std::string input)
{
    std::cout << "Parsing the file: "
              << "\n";
    std::cout << "\n";
    Tokenizer tokenizer = Tokenizer(input);
    tokenizer.tokenize();
    std::vector<std::shared_ptr<Character>> tokens = tokenizer.getTokens();
    std::cout << "Number of tokens(characters) found: " << tokens.size() << "\n";
    std::shared_ptr<ComponentBuilder> componentBuilder = std::make_shared<ComponentBuilder>(tokens);
    componentBuilder->build_components();
    std::vector<std::shared_ptr<Component>> components = componentBuilder->getComponents();
    std::cout << "Number of components found: " << components.size() << "\n";
    ElementBuilder elementBuilder(components);
    elementBuilder.buildElements();
    std::vector<std::shared_ptr<Element>> elements = elementBuilder.getElements();
    std::cout << "Number of elements found: " << elements.size() << "\n";
    std::shared_ptr<Node> targetNode;
    std::shared_ptr<Node> tree = targetNode->createTree(elements);

    return tree;
}

std::shared_ptr<Node> EVAL(std::shared_ptr<Node> ast)
{
    return ast;
}

void PRINT(std::shared_ptr<Node> result)
{
    if (result != NULL)
    {
        Node::display(result);
    }
    std::string fileName = "out.txt";
    std::cout << "\n";
    Writer *writer = new Writer(result);
    writer->createFile(fileName);
    std::cout << "Parsed tree level information saved to " << fileName << "\n";
    std::string jsonFileName = "out.json";
    writer->setFile(jsonFileName);
    writer->writeTreeAsJSON();
    std::cout << "Parsed tree saved as JSON to " << jsonFileName << "\n";
}

std::string rep(std::string input)
{
    std::shared_ptr<Node> ast = READ(input);
    std::shared_ptr<Node> result = EVAL(ast);
    PRINT(result);
    return "";
}

int main(int argc, char **argv)
{

    if (argc > 1)
    {
        std::ifstream file;
        std::string line;
        std::vector<std::string> lines;
        std::string text;
        file.open(argv[1]);
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        for (std::string l : lines)
        {
            text += l;
        }
        file.close();
        rep(text);
    }
    else
    {
        const auto history_path = "history.txt";
        linenoise::LoadHistory(history_path);

        std::string input;
        for (;;)
        {

            auto quit = linenoise::Readline("hello> ", input);

            if (quit)
                break;
            if (input == "exit()" || input == "quit()")
            {
                std::cout << "Exiting the XML parser \n";
                return 0;
            }
            std::cout << rep(input) << std::endl;

            // add text to history
            linenoise::AddHistory(input.c_str());
        }
        linenoise::SaveHistory(history_path);
    }
    return 0;
}