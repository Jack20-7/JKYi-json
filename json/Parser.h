#ifndef _JKYI_JSON_PARSER_H_
#define _JKYI_JSON_PARSER_H_

#include"json.h"
#include<string>

namespace JKYi{
namespace json{

class Parser{
public:
    Parser();
    ~Parser();

    void load(const std::string& str);
    Json parse();
private:
    //辅助函数
    void skip_white_space(); //跳过无关字符
    char get_next_token();  //获取下一个有效字符

    Json parse_null();
    Json parse_bool();
    Json parse_number();
    std::string parse_string();
    Json parse_array();
    Json parse_object();

    bool in_range(int idx,int lower,int upper){
        return (idx >= lower && idx <= upper);
    }

private:
    std::string m_str;  //要解析的字符串
    size_t m_idx;
};

}
}

#endif
