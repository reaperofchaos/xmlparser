#include "TokenizerUtilities.h"

void TokenizerUtilities::IncrementIndex( 
    std::string text,
    size_t &m_index)
{
    if(m_index < text.size())
    {
        m_index++;
    } 
}