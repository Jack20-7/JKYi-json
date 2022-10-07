#include"Parser.h"

#include<string.h>
#include<cstdlib>
#include<stdexcept>

using namespace JKYi::json;

Parser::Parser()
    :m_idx(0){
}
Parser::~Parser(){
}

void Parser::load(const std::string& str){
    m_str = str;
    m_idx = 0;
}
void Parser::skip_white_space(){
    while(m_str[m_idx] == ' ' || m_str[m_idx] == '\r' || m_str[m_idx] == '\n' ||
             m_str[m_idx] == '\t'){
        m_idx++;
    }
}
char Parser::get_next_token(){
    skip_white_space();
    if(m_idx == m_str.size()){
        throw new std::logic_error("unexpected end of input");
    }
    return m_str[m_idx++];
}

Json Parser::parse(){
    char ch = get_next_token();
    switch(ch){
        case 'n':
            m_idx--;
            return parse_null();
        case 't':
        case 'T':
        case 'f':
        case 'F':
            m_idx--;
            return parse_bool();
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            m_idx--;
            return parse_number();
        case '"':
            return Json(parse_string());
        case '[':
            return parse_array();
        case '{':
            return parse_object();
        default:
            break;
    }
    throw new std::logic_error("unexpected char in parse json");
}

Json Parser::parse_null(){
    if(m_str.compare(m_idx,4,"null") == 0){
        m_idx += 4;
        return Json();
    }
    throw new std::logic_error("parse null error");
}

Json Parser::parse_bool(){
    if(m_str.compare(m_idx,4,"true") == 0){
        m_idx += 4;
        return Json(true);
    }else if(m_str.compare(m_idx,4,"True") == 0){
        m_idx += 4;
        return Json(true);
    }else if(m_str.compare(m_idx,5,"false") == 0){
        m_idx += 5;
        return Json(false);
    }else if(m_str.compare(m_idx,5,"False") == 0){
        m_idx += 5;
        return Json(false);
    }
    throw new std::logic_error("parse null error");
}

Json Parser::parse_number(){
    size_t pos = m_idx;
    if(m_str[m_idx] == '-'){
        m_idx++;
    }
    if(m_str[m_idx] == '0'){
        m_idx++;
    }else if(in_range(m_str[m_idx],'1','9')){
        m_idx++;
        while(m_idx < m_str.size() && in_range(m_str[m_idx],'0','9')){
            m_idx++;
        }
    }else{
        throw new std::logic_error("invalid char in number");
    }
    //下面判断是否是小数
    if(m_str[m_idx] != '.'){
        return Json(std::atoi(m_str.c_str() + pos));
    }
    //如果是浮点数的话
    m_idx++;
    if(!in_range(m_str[m_idx],'0','9')){
        throw new std::logic_error("at least one digit required in fractional part");
    }
    while(m_idx < m_str.size() && in_range(m_str[m_idx],'0','9')){
        m_idx++;
    }
    return Json(std::atof(m_str.c_str() + pos));
}

std::string Parser::parse_string(){
    int pos = m_idx;
    while(true){
        if(m_idx == m_str.size()){
            throw new std::logic_error("unexpected end of input in string");
        }
        char ch = m_str[m_idx++];
        if(ch == '"'){
            break;
        }

        if(ch == '\\'){
            ch = m_str[m_idx++];
            switch(ch){
                case 'b':
                case 't':
                case 'n':
                case 'f':
                case 'r':
                case '"':
                case '\\':
                    break;
                case 'u':
                    m_idx += 4;
                    break;
                default:
                    break;
            }
        }
    }
    return m_str.substr(pos,m_idx - pos -1);
}

Json Parser::parse_array(){
    Json arr(Json::JSON_ARRAY);
    char ch = get_next_token();
    if(ch == ']'){
        return arr;
    }
    m_idx--;
    while(true){
        arr.append(parse());
        ch = get_next_token();
        if(ch == ']'){
            break;
        }
        if(ch != ','){
            throw new std::logic_error("expected ',' in array");
        }
    }
    return arr;
}

Json Parser::parse_object(){
    Json obj(Json::JSON_OBJECT);
    char ch = get_next_token();
    if(ch == '}'){
        return obj;
    }
    m_idx--;
    while(true){
        ch = get_next_token();
        if(ch != '"'){
            throw new std::logic_error("object key is not string");
        }
        std::string key = parse_string();
        ch = get_next_token();
        if(ch != ':'){
            throw new std::logic_error("expected ':' is object");
        }
        obj[key] = parse();
        ch = get_next_token();
        if(ch == '}'){
            break;
        }
        if(ch != ','){
            throw new std::logic_error("expected ',' is object");
        }
    }
    return obj;
}

