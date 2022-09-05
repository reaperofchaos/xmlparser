#include "TokenizerUtilities.h"

void TokenizerUtilities::IncrementIndex( 
    std::string text,
    size_t &m_index)
{
    std::cout << "Current index " << m_index << " total " << text.size()-1 << "\n";
    std::cout << text.at(m_index) << "\n";
    if(m_index < text.size())
    {
        m_index++;
    } 
}