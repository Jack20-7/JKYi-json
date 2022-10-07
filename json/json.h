#ifndef _JKYI_JSON_H_
#define _JKYI_JSON_H_

#include<string>
#include<map>
#include<list>

namespace JKYi{
namespace json{

class Json{
public:
    enum Type{
       JSON_NULL = 0,
       JSON_BOOL,
       JSON_INT,
       JSON_DOUBLE,
       JSON_STRING,
       JSON_ARRAY,
       JSON_OBJECT
    };
    
    Json();
    Json(Type type);
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char* value);
    Json(const std::string& value);
    Json(const Json& value);
    ~Json();

    Type type()const;
    bool isNull()const;
    bool isBool()const;
    bool isInt()const;
    bool isDouble()const;
    bool isString()const;
    bool isArray()const;
    bool isObject()const;

    bool asBool()const;
    int asInt()const;
    double asDouble()const;
    std::string asString()const;

    int size()const; //number of values in array or object
    bool empty()const; //return true if empty array, empty object, or null, otherwise, false.

    void clear();//you should call if json object is used completely

    bool has(int index);
    bool has(const char * key);
    bool has(const std::string& key);

    void remove(int index);
    void remove(const char * key);
    void remove(const std::string& key);

    void append(const Json& value);

    Json& operator= (const Json& rhv);
    bool operator== (const Json& rhv);
    bool operator!= (const Json& rhv);

    Json& operator[] (int index);
    Json& operator[] (const char * key);
    Json& operator[] (const std::string& key);

    operator bool();
    operator int();
    operator double();
    operator std::string();

    void parse(const std::string& str);
    
    std::string toString()const;

    typedef std::list<Json>::iterator iterator;

    iterator begin()const{
        return m_value.m_array->begin();
    }
    iterator end()const{
        return m_value.m_array->end();
    }
private:
    void copy(const Json& other);
private:
    union Value{
        bool m_bool;
        int m_int;
        double m_double;
        std::string* m_string;
        std::list<Json>* m_array;
        std::map<std::string,Json>* m_object;
    };
    Type m_type;
    Value m_value;
};

}
}

#endif
