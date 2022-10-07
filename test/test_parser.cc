#include"../json/Json.h"

#include<iostream>

int main(int argc,char ** argv){
    JKYi::json::Json value;
    //value.parse("123");
    //value.parse("null");
    //value.parse("True");
    //value.parse("\"Hello,World\"");
    //value.parse("[null,true,1,1.2,\"hello,World\"]");
    value.parse("{\"1\":null,\"2\":true,\"3\":1,\"4\":1.2,\"5\":[null,1,1.2,\"hello\"]}");
    std::cout << value.toString() << std::endl;
    return 0;
}
