#include "CharacterUtilities.h"

void CharacterUtilities::IgnoreWhiteSpace( 
    std::vector<std::shared_ptr<Character>> &characters,
    size_t &m_index)
{
    while(characters[m_index]->type() == CharacterType::WhiteSpace )
    {
        CharacterUtilities::IncrementIndex(characters, m_index);
    } 
}

void CharacterUtilities::IncrementIndex( 
    std::vector<std::shared_ptr<Character>> &characters,
    size_t &m_index)
{
    if(m_index < characters.size())
    {
        m_index++;
    }
}