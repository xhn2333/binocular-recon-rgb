#include <fstream>
#include "config.h"
#include <string>

using namespace std;

Config::Config() {}

Config::Config(string path) {
    this->load_config(path);
}

void Config::load_config(string path) {
    ifstream file(path);
    Json::Reader reader;
    reader.parse(file, this->data);
    return;
}

void Config::show_config() {
    cout << this->data << endl;
    return;
}

Json::Value Config::get_config_value(string key) {
    return this->data[key];
}