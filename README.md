# JKYi-json 
## 介绍
该项目是一个基于c++语言编写的简单的json解析器，代码量比较少，一共有大概800行左右.

支持的类型有:
   null
   bool
   int 
   double
   string
   array
   object
## 使用方式
```
  //可以直接在最开始using namespace JKYi::json
  JKYi::json::Json json;
  //object类型的使用方式
  json["name"] = "jack";
  json["age"] = 18;
  json["area"] = "c++";
  std::cout << json.toStirng() << std::endl
  
  //array类型的使用方式
  JKYi::json::Json json
  json.append(null);
  json.append(true);
  json.append(1);
  json.append(1.2);
  json[4] = "hell,world";
  std::cout << json.toStirng() << std::endl;
  
  //解析功能的使用
  //1.解析文本
  JKYi::json::Json json;
  json.parse(("{\"1\":null,\"2\":true,\"3\":1,\"4\":1.2,\"5\":[null,1,1.2,\"hello\"]}");
  bool flag = json["2"];
  int val = json["3"];
  
  //2.解析文件
  JKYi::json::Json json;
  json.parseFile("test.json");
  const std::string& name = json["name"];
  int age = json["age"];
  
```
上面简略的介绍了一下常见的使用方式，具体的使用方法可以去查看json/json.h，也可以查看test目录下的测试文件

## 使用的注意事项

该解析器高效很大一部分原因是由于内部对于string、array、object类型进行的是浅拷贝操作，所以在使用时应该避免浅拷贝所带来的一些问题，如:

```

  JKYi::json::Json array(JSON_ARRAY);
  json[0] = "hello";

  JKYi::json::Json object(JSON_OBJECT);
  object["array"] = array;

  .......
  //销毁时只需要调用object的进行销毁就ok了，不需要再去销毁array，否则会出现内存区域重复释放的问题
  object.clear();
  //array.clear() is error

```

## 效率
对同一个复杂的json进行解析
```
JKYi-json -> 0.130ms
jsoncpp   -> 
```
