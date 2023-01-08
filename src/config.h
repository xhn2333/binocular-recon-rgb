#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Config {
   public:
    Config();
    Config(string path);

    Json::Value get_config_value(string key);

    void load_config(string path);
    void show_config();

   private:
    Json::Value data;
};