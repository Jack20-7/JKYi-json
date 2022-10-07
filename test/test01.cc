#include"../json/json.h"

#include<iostream>

void test01(){
  JKYi::json::Json a;
  JKYi::json::Json b = true;
  JKYi::json::Json c = 5;
  JKYi::json::Json d = 5.02213123214351;
  JKYi::json::Json e = "Hello,world";

#define XX(x) \
  std::cout << x.toString() << std::endl;

  //XX(a);
  //XX(b);
  //XX(c);
  //XX(d);
  //XX(e);

#undef XX

  JKYi::json::Json array;
  array[1] = 1;
  array[2] = true;
  array[3] = "hello,world";
  array[4] = d;

  std::cout << array.toString() << std::endl;
  std::cout << array.size() << std::endl;
  std::cout << array.empty() << std::endl;

  std::cout << array.has(4) << std::endl;
  array.remove(4);
  std::cout << array.has(4) << std::endl;
  std::cout << array.toString() << std::endl;

  array.clear();
  std::cout << array.toString() << std::endl;

  array.append(1);
  array.append(true);
  array.append(1.23);
  array.append("wwww");

  std::cout << array.toString() << std::endl;

  for(auto it = array.begin();it != array.end();++it){
      std::cout << it->toString() << " ";
  }
  std::cout << std::endl;
}

void test_object(){
    JKYi::json::Json array;
    array[1] = 1;
    array[2] = true;
    array[3] = "hello,world";

    JKYi::json::Json object;
    object["1"] = 1;
    object["2"] = 1.23;
    object["3"] = "3";
    object["4"] = true;
    object["5"] = array;

    std::cout << object.toString() << std::endl;

    std::cout << object.has("1") << std::endl;
    object.remove("1");
    std::cout << object.has("1") << std::endl;
}

int main(int argc,char ** argv){
    //test01();
    test_object();
    return 0;
}
