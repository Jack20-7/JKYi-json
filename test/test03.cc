#include"../json/Json.h"

#include<iostream>
#include<fstream>
#include<sstream>

int main(int argc,char ** argv){
    try{
        std::ifstream ifs("../test/test1.json");
        std::stringstream ss;
        ss << ifs.rdbuf();
        const std::string& data = ss.str();
        std::cout << data << std::endl;

        JKYi::json::Json json;
        json.parse(data);

        std::cout << json.toString() << std::endl;

        const std::string& name = json["name"];
        int age = json["age"];
        const std::string& area = json["area"][0];

        std::cout << "name = " << name  << "age = " << age 
                  << "area = " << area << std::endl;
        json.clear();
    }catch(std::exception& e){
        std::cout << "catch exception: " << e.what() << std::endl;
    }catch(...){
        std::cout << "catch exceptopn" << std::endl;
    }
   return 0;
}
