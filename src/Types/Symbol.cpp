#include "Symbol.hpp"

    ObjectOpenBracket* Symbol::as_object_open_bracket(){
        assert(SymbolType() == Symbol::ObjectOpenBracket);
        return static_cast<ObjectOpenBracket*>(this);
    }; 
