
#include "Types.hpp"

TagValue* Value::as_tag() 
{
    assert(type() == Type::Tag);
    return static_cast<TagValue*>(this);
}

DocumentTagValue* Value::as_document_tag() 
{
    assert(type() == Type::DocumentTag);
    return static_cast<DocumentTagValue*>(this);
}


XmlTagValue* Value::as_xml_tag() 
{
    assert(type() == Type::XmlTag);
    return static_cast<XmlTagValue*>(this);
}

StringValue* Value::as_string() 
{
    assert(type() == Type::String);
    return static_cast<StringValue*>(this);
}

CommentValue* Value::as_comment() 
{
    assert(type() == Type::Comment);
    return static_cast<CommentValue*>(this);
}

EndTagValue* Value::as_end_tag() 
{
    assert(type() == Type::EndTag);
    return static_cast<EndTagValue*>(this);
}

SelfClosingTagValue* Value::as_self_closing_tag() 
{
    assert(type() == Type::SelfClosingTag);
    return static_cast<SelfClosingTagValue*>(this);
}

StartTagValue* Value::as_start_tag() 
{
    assert(type() == Type::StartTag);
    return static_cast<StartTagValue*>(this);
}


SymbolValue* Value::as_symbol()
{
    assert(type() == Type::Symbol);
    return static_cast<SymbolValue*>(this); 
}