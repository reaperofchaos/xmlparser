#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "Types/CharType.hpp"
#include "Types/Primitive.hpp"

class TokenHandlers {
    public:
        static std::shared_ptr<NumberType> buildNumberPrimitive(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            std::vector<std::shared_ptr<Number>> &numbers);

        static std::shared_ptr<CloseTag> buildCloseTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static std::shared_ptr<CloseArray> buildCloseArray(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);
        
        static std::shared_ptr<CloseObject> buildCloseObject(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static std::shared_ptr<CloseObject> buildCloseObject(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static std::shared_ptr<WhiteSpaces> buildWhiteSpaces(
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static std::shared_ptr<Name> buildName(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<Character>> &characters);

        static std::shared_ptr<ClosingCloseTag> buildClosingCloseTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start);

        static std::shared_ptr<StringType> buildString(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<Character>> &characters, 
            SymbolType symbolType);

        static std::shared_ptr<OpenArray> buildOpenArray(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static std::shared_ptr<OpenObject> buildOpenObject(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static std::shared_ptr<ExclamationPrimitive> buildExclamation(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start);

        static std::shared_ptr<EqualPrimitive> buildEqual(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index);
        
        static std::shared_ptr<SemicolonPrimitive> buildSemicolon(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index);
        
        static std::shared_ptr<ColonPrimitive> buildColon(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index);
        
        static std::shared_ptr<PercentagePrimitive> buildPercentage(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index);
        
        static std::shared_ptr<CommaPrimitive> buildComma(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index);
        
        static std::shared_ptr<HashTagPrimitive> buildHashTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index);

        static std::shared_ptr<StringType> buildNestedString(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            std::vector<std::shared_ptr<Character>> &characters);
        
        static std::shared_ptr<ClosingOpenTag> buildClosingOpenTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start);
        
        static std::shared_ptr<CommentOpenTag> buildCommentOpenTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);
        
        static std::shared_ptr<CommentCloseTag> buildCommentCloseTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);
        
        static std::shared_ptr<DocumentTypeOpenTag> buildDocumentTypeOpenTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);
        
        static std::shared_ptr<OpenTag> buildOpenTag(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            size_t &start,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);

        static void findWhiteSpace(
            std::vector<std::shared_ptr<Character>> &m_tokens, 
            size_t &m_index,
            std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces);
};
