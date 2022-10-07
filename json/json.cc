#include"json.h"
#include"Parser.h"

#include<sstream>
#include<stdexcept>

using namespace JKYi::json;

Json::Json()
 :m_type(JSON_NULL){
}
Json::Json(Type type)
  :m_type(type){
   switch(type){
       case JSON_NULL:
           break;
        case JSON_BOOL:
           m_value.m_bool = false;
           break;
        case JSON_INT:
           m_value.m_int = 0;
           break;
        case JSON_DOUBLE:
           m_value.m_double = 0.0;
           break;
        case JSON_STRING:
           m_value.m_string = new std::string("");
           break;
        case JSON_ARRAY:
           m_value.m_array = new std::list<Json>();
           break;
        case JSON_OBJECT:
           m_value.m_object = new std::map<std::string,Json>();
           break;
        default:
           break;
   }
}
Json::Json(bool value)
  :m_type(JSON_BOOL){
   m_value.m_bool = value;   
}
Json::Json(int value)
  :m_type(JSON_INT){
   m_value.m_int = value;
}
Json::Json(double value)
   :m_type(JSON_DOUBLE){
    m_value.m_double = value;
}
Json::Json(const char* value)
   :m_type(JSON_STRING){
   m_value.m_string = new std::string(value);
}
Json::Json(const std::string& value)
   :m_type(JSON_STRING){
    m_value.m_string = new std::string(value);
}
Json::Json(const Json& value)
   :m_type(JSON_NULL){
    copy(value);
}
Json::~Json(){
}
Json::Type Json::type()const{
    return m_type;
}
bool Json::isNull()const{
    return m_type == JSON_NULL;
}
bool Json::isBool()const{
    return m_type == JSON_BOOL;
}
bool Json::isInt()const{
    return m_type == JSON_INT;
}
bool Json::isDouble()const{
    return m_type == JSON_DOUBLE;
}
bool Json::isString()const{
    return m_type == JSON_STRING;
}
bool Json::isArray()const{
    return m_type == JSON_ARRAY;
}
bool Json::isObject()const{
    return m_type == JSON_OBJECT;
}
bool Json::asBool()const{
    if(m_type != JSON_BOOL){
        throw new std::logic_error("function Json::asBool value type error");
    }
    return m_value.m_bool;
}
int Json::asInt()const{
    if(m_type != JSON_INT){
        throw new std::logic_error("function Json::asInt value type error");
    }
    return m_value.m_int;
}
double Json::asDouble()const{
    if(m_type != JSON_DOUBLE){
        throw new std::logic_error("function Json::asDouble value type error");
    }
    return m_value.m_double;
}
std::string Json::asString()const{
    if(m_type != JSON_STRING){
        throw new std::logic_error("function Json::asString value type error");
    }
    return *m_value.m_string;
}

int Json::size()const{
    if(m_type == JSON_ARRAY){
        return m_value.m_array->size();
    }else if(m_type == JSON_OBJECT){
        return m_value.m_object->size();
    }
    throw new std::logic_error("fuction Json::size value type is not array or obejct");
}

bool Json::empty()const{
    if(m_type == JSON_NULL){
        return true;
    }else if(m_type == JSON_ARRAY){
        return m_value.m_array->empty();
    }else if(m_type == JSON_OBJECT){
        return m_value.m_object->empty();
    }
    throw new std::logic_error("function Json::empty value type is error");
}

void Json::clear(){
    switch(m_type){
        case JSON_NULL:
        case JSON_BOOL:
        case JSON_INT:
        case JSON_DOUBLE:
            break;
        case JSON_STRING:
            delete m_value.m_string;
            m_value.m_string = nullptr;
            break;
        case JSON_ARRAY:
            {
                for(auto it = m_value.m_array->begin();
                                 it != m_value.m_array->end();++it){
                    it->clear();
                }
                delete m_value.m_array;
                m_value.m_array = nullptr;
            }
            break;
        case JSON_OBJECT:
            {
                for(auto it = m_value.m_object->begin();
                                 it != m_value.m_object->end();++it){
                    it->second.clear();
                }
                delete m_value.m_object;
                m_value.m_object = nullptr;
            }
            break;
        default:
            break;
    }
    m_type = JSON_NULL;
}

bool Json::has(int index){
    if(m_type != JSON_ARRAY){
        throw new std::logic_error("function Json::has(int index) value type error");
    }
    int size = m_value.m_array->size();
    return (index >= 0 && index < size);
}
bool Json::has(const char* key){
    std::string Key(key);
    return has(Key);
}
bool Json::has(const std::string& key){
    if(m_type != JSON_OBJECT){
        throw new std::logic_error("function Json::has value type error");
    }
    return (m_value.m_object->find(key) != m_value.m_object->end());
}

void Json::remove(int index){
    if(m_type != JSON_ARRAY){
        return ;
    }
    int size = m_value.m_array->size();
    if(index < 0 || index >= size){
        return ;
    }
    std::list<Json>::iterator it = m_value.m_array->begin();
    //由于Json的析构函数中不会进行资源的释放，所以这里需要先对他clear，在erase
    for(int i = 0;i < index;++i){
        it++;
    }
    it->clear();
    m_value.m_array->erase(it);
}
void Json::remove(const char * key){
    std::string Key(key);
    return remove(Key);
}
void Json::remove(const std::string& key){
    if(m_type != JSON_OBJECT){
        return ;
    }
    auto it = m_value.m_object->find(key);
    if(it != m_value.m_object->end()){
        it->second.clear();
        m_value.m_object->erase(key);
    }
    return ;
}
void Json::append(const Json& value){
    if(m_type != JSON_ARRAY){
        clear();
        m_type = JSON_ARRAY;
        m_value.m_array = new std::list<Json>();
    }
    m_value.m_array->push_back(value);
}

Json& Json::operator= (const Json& rhv){
    if(this == &rhv){
        return *this;
    }
    clear();
    copy(rhv);//进行的是浅拷贝
    return *this;
}

bool Json::operator== (const Json& rhv){
    if(m_type != rhv.m_type){
        return false;
    }
    switch(m_type){
        case JSON_NULL:
            return true;
            break;
        case JSON_BOOL:
            return (m_value.m_bool == rhv.m_value.m_bool);
            break;
        case JSON_INT:
            return (m_value.m_int == rhv.m_value.m_int);
            break; 
        case JSON_DOUBLE:
            return (m_value.m_double == rhv.m_value.m_double);
            break;
        case JSON_STRING:
            return *(m_value.m_string) == *(rhv.m_value.m_string);
            break;
        case JSON_ARRAY:
            return (m_value.m_array) == (rhv.m_value.m_array);
            break;
        case JSON_OBJECT:
            return (m_value.m_object) == (rhv.m_value.m_object);
            break;
        default:
            break;
    }
    return false;
}
bool Json::operator!= (const Json& rhv){
    return !((*this) == rhv);
}

Json& Json::operator[] (int index){
    if(index < 0){
        throw new std::logic_error("function Json::operator[int] index < 0");
    }
    if(m_type != JSON_ARRAY){
        clear();
        m_type = JSON_ARRAY;
        m_value.m_array = new std::list<Json>();
    }
    int size = m_value.m_array->size();
    if(index >= 0 && index < size){
        auto it = m_value.m_array->begin();
        for(int i = 0;i < index;++i){
            ++it;
        }
        return *it;
    }
    if(index >= size){
        for(int i = size;i <= index;++i){
            m_value.m_array->push_back(Json());
        }
    }
    return m_value.m_array->back();
}

Json& Json::operator[] (const char * key){
    std::string Key(key);
    return (*this)[Key];
}
Json& Json::operator[] (const std::string& key){
    if(m_type != JSON_OBJECT){
        clear();
        m_type = JSON_OBJECT;
        m_value.m_object = new std::map<std::string,Json>();
    }
    return (*m_value.m_object)[key];
}

Json::operator bool(){
    if(m_type != JSON_BOOL){
        throw new std::logic_error("function Json::operator bool() value type error");
    }
    return m_value.m_bool;
}
Json::operator int(){
    if(m_type != JSON_INT){
        throw new std::logic_error("function Json::operator int() value type error");
    }
    return m_value.m_int;
}
Json::operator double(){
    if(m_type != JSON_DOUBLE){
        throw new std::logic_error("function Json::operator double value type error");
    }
    return m_value.m_double;
}
Json::operator std::string(){
    if(m_type != JSON_STRING){
        throw new std::logic_error("function Json::operator string value type error");
    }
    return *m_value.m_string;
}

void Json::parse(const std::string& str){
    Parser parser;
    parser.load(str);
    *this = parser.parse();
}
std::string Json::toString()const{
   std::stringstream ss;
   switch(m_type){
       case JSON_NULL:
           ss << "null";
           break;
        case JSON_BOOL:
           {
               if(m_value.m_bool){
                   ss << "true";
               }else{
                   ss << "false";
               }
           }
           break;
        case JSON_INT:
           ss << m_value.m_int;
           break;
        case JSON_DOUBLE:
           ss << m_value.m_double;
           break;
        case JSON_STRING:
           ss << "\"" << *m_value.m_string << "\""; 
           break;
        case JSON_ARRAY:
           {
               ss << "[";
               for(auto it = m_value.m_array->begin();
                          it != m_value.m_array->end();++it){
                   if(it != m_value.m_array->begin()){
                       ss << ",";
                   }
                   ss << it->toString();
               }
               ss << "]";
           }
           break;
        case JSON_OBJECT:
           {
               ss << "{";
               for(auto it = m_value.m_object->begin();
                          it != m_value.m_object->end();++it){
                   if(it != m_value.m_object->begin()){
                       ss << ",";
                   }
                   ss << "\"" << it->first << "\":" << it->second.toString();
               }
               ss << "}";
           }
           break;
        default:
           break;
   }
   return ss.str();
}

//这里进行的是浅拷贝
void Json::copy(const Json& other){
   m_type = other.m_type;
   m_value = other.m_value;
}
 
