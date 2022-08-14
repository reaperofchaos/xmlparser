#include "Container.hpp"

ArrayType* Container::as_array()
{
    assert(type() == ContainerType::ArrayType);
    return static_cast<ArrayType*>(this);
}

ObjectType* Container::as_object()
{
    assert(type() == ContainerType::ObjectType);
    return static_cast<ObjectType*>(this);
}

class Key{
    private:
        std::shared_ptr<Name> key;

    public: 
        Key(std::shared_ptr<Name> key)
        {
            this->key = key;
        }
        virtual CharacterType type(){ return CharacterType::Key;}
        virtual std::string inspect() { return this->getType  + " - " + this->getValue();  }
        virtual std::string getValue(){ return this->key->getValue();}
        virtual std::string getType(){return this->getTypeAsString(this->type());}
}

class Entry{
    private:
        std::shared_ptr<key> key;
        std::shared_ptr<Primitive> value;

    public: 
        Entry(std::shared_ptr<Key> key, 
            std::shared_ptr<ColonPrimitive> colon,
            std::shared_ptr<Primitive> value)
        {
            this->key = key;
            this->value = value;
        }

}


// object - open object, entries[], close object


// entry - key, colon, value
// key - name
// value - string
// value - name
// value- whitespaces, name, comma, whitespaces, name, semicolon
// entry - name, colon, whiteSpaces, name
// 