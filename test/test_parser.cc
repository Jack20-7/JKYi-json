#include"../json/Json.h"

#include<iostream>

int main(int argc,char ** argv){
    JKYi::json::Json value;
    //value.parse("123");
    //value.parse("null");
    //value.parse("True");
    //value.parse("\"Hello,World\"");
    //value.parse("[null,true,1,1.2,\"hello,World\"]");
    //value.parse("{\"1\":null,\"2\":true,\"3\":1,\"4\":1.2,\"5\":[null,1,1.2,\"hello\"]}");
    JKYi::json::Json json;
    json.parseFile("/home/admin/JKYi-json/test/test1.json");
    std::cout << json.toString() << std::endl;

    const std::string& name = json["name"];
    int age = json["age"];
    const std::string& area = json["area"][0];

    std::cout << " name = " << name << " age = " << age << " area = " << area << std::endl;
    return 0;
}
