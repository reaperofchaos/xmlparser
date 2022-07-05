#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include "Types.hpp"
#include "Tokenizer.hpp"
#include "Node.hpp"

/**
 * @brief Class that takes tokens (string_view) and 
 * analyzes them further to assign a type
 * 
 */
class Reader {
    private:
        std::vector<std::string_view> &m_tokens;
        size_t m_index { 0 };
        Node* ast = NULL; 

    public:
        Reader(std::vector<std::string_view> &tokens)
            : m_tokens { tokens } { }

        std::vector<std::string_view> getTokens(){return m_tokens;}
        Node* getAst(){return ast;}
        void setAst(Node* ast){this->ast = ast;}
        std::optional<std::string_view> next() {
            if (m_index < m_tokens.size())
                return m_tokens.at(m_index++);
            return {};
        }
        

        std::optional<std::string_view> peek() {
            if (m_index < m_tokens.size())
                return m_tokens.at(m_index);
            return {};
        }
};

Node* read_str(std::string &input);
Value *readStringValue(std::optional<std::string_view> &token);
Value* readTag(std::optional<std::string_view> &token);
Value *read_form(std::optional<std::string_view> token);