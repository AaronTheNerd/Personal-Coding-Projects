#include <iostream>
#include <regex>
#include <string>

static std::vector<std::string> list_to_vector(std::string list) {
    std::vector<std::string> vec;
    list = list.substr(1, list.size() - 2);
    std::regex re("\"([^\"]*)\",?");
    std::smatch sm;
    while (std::regex_search(list, sm, re)) {
        std::string item = sm[1].str();
        vec.push_back(item);
        list = sm.suffix().str();
    }
    return vec;
}

int main(int argc, char** argv) {
    std::string str("[\"Incorrect 1\",\"Incorrect 2\",\"Incorrect 3\"]");
    std::vector<std::string> vec = list_to_vector(str);
    for (std::string s : vec) {
        std::cout << s << std::endl;
    }
}