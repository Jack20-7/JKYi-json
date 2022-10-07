#include"../json/Json.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<sys/time.h>

int main(int argc,char ** argv){
    try{
        std::ifstream ifs("/home/admin/JKYi-json/test/test2.json");
        std::stringstream ss;
        ss << ifs.rdbuf();
        ifs.close();
        const std::string& data = ss.str();

        struct timeval tv;
        gettimeofday(&tv,NULL);
        int start_sec = tv.tv_sec;
        int start_usec = tv.tv_usec;
        const int max = 1;
        for(int i = 0;i < max;++i){
            JKYi::json::Json json;
            json.parse(data);
        }

        gettimeofday(&tv,NULL);
        int end_sec = tv.tv_sec;
        int end_usec = tv.tv_usec;
        double time_diff = (end_sec - start_sec) * 1000000 +(end_usec - start_usec);
        
        std::cout << time_diff / 1000 / max << "ms" << std::endl;
    }catch(...){
        std::cout << "catch exception " << std::endl;
    }
    return 0;
}
