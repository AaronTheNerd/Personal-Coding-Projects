// Written by Aaron Barge
// Copyright 2020

#include <algorithm>
#include <fstream>
#include <map>
#include <regex>
#include <string>
#include "../src/form.hpp"
#include "../src/question.hpp"

#ifndef _SRC_JSON_HPP_
#define _SRC_JSON_HPP_

namespace json {

const std::string TITLE = "\"title\"";
const std::string DESC = "\"desc\"";
const std::string NUMS = "\"nums\"";
const std::string TYPE = "\"type\"";
const std::string PROMPT = "\"prompt\"";
const std::string PTS = "\"pts\"";
const std::string CORRECT = "\"correct\"";
const std::string INCORRECTS = "\"incorrects\"";
const std::string CORRECTS = "\"corrects\"";
const std::string TRUE = "true";
const std::string FALSE = "false";

static std::string tab_offset(const int depth) {
    std::string str;
    for (int i = 0; i < depth; ++i)
        str += "\t";
    return str;
}

static std::string name(std::string s) {
    return "\"" + s + "\"";
}

static std::string attr(std::string s) {
    return "\"" + s + "\"";
}

static std::string attr(size_t i) {
    return std::to_string(i);
}

static std::string attr(int i) {
    return std::to_string(i);
}

static std::string attr(bool b) {
    return (b ? TRUE : FALSE);
}

template <typename T>
static std::string attr(std::vector<T> vals) {
    std::string s;
    s += "[";
    for (size_t i = 0; i < vals.size(); ++i) {
        s += attr(vals[i]);
        if (i + 1 != vals.size())
            s += ",";
    }
    s += "]";
    return s;
}

static std::string attr_to_string(std::string s) {
    return s.substr(1, s.size() - 2);
}

static std::vector<std::string> list_to_vector(std::string list) {
    std::vector<std::string> vec;
    list = list.substr(1, list.size() - 2);
    std::regex re("\"([^\"]*)\",");
    std::smatch sm;
    while (std::regex_search(list, sm, re)) {
        std::string item = sm[1].str();
        vec.push_back(item);
        list = sm.suffix().str();
    }
    return vec;
}

static bool attr_to_bool(std::string attr) {
    return (attr == TRUE);
}

class json_class {
  public:
    std::string name;
    std::map<std::string, std::string> attrs;
    std::vector<json_class> classes;
    
    json_class(): name("\"Test\""), attrs(), classes() {}
    
    json_class(std::string name): name("\"" + name + "\""), attrs(), classes() {}

    void add_attr(std::string name, std::string val) {
        this->attrs.insert(std::pair<std::string, std::string>(name, val));
    }

    void add_class(std::string name) {
        this->classes.push_back(json_class(name));
    }

    void add_class(json_class c) {
        this->classes.push_back(c);
    }

    void to_file(std::ofstream& json, int offset) {
        json << tab_offset(offset) << this->name << ": {\n";
        offset++;
        for (auto it = this->attrs.begin(); it != this->attrs.end(); ++it) {
            json << tab_offset(offset) << it->first << ": " << it->second;
            if (std::next(it) != this->attrs.end() || this->classes.size() != 0)
                json << ",";
            json << "\n";
        }
        for (size_t i = 0; i < this->classes.size(); ++i) {
            this->classes[i].to_file(json, offset);
            if (i + 1 != this->classes.size())
                json << ",";
            json << "\n";
        }
        json << tab_offset(offset - 1) << "}";
    }
};

class editor {
  public:
    json_class main;
    
    editor() : main() {}
    
    void to_file(std::string file_name) {
        std::ofstream json;
        json.open(file_name, std::ios::trunc);
        json << "{\n";
        this->main.to_file(json, 1);
        json << "\n}";
    }

    json_class from_file(std::string file_name) {
        std::ifstream in(file_name);
        std::string input, in_str;
        std::smatch sm;
        json_class main;
        if (in) {
            while (std::getline(in, input)) {
                
            }
        }
        
        return this->main;
    }
};

void to_json(form f) {
    editor w;
    w.main.add_attr(TITLE, attr(f.title));
    w.main.add_attr(DESC, attr(f.desc));
    w.main.add_attr(NUMS, attr(f.questions.size()));
    for (size_t i = 0; i < f.questions.size(); ++i) {
        json_class c("Q" + std::to_string(i + 1));
        std::string type = f.questions[i].type();
        c.add_attr(TYPE, attr(type));
        c.add_attr(PROMPT, attr(f.questions[i].prompt()));
        c.add_attr(PTS, attr(f.questions[i].pts()));
        if (type == MULTIPLE_CHOICE) {
            auto mc = f.questions[i].get<multiple_choice>();
            c.add_attr(CORRECT, attr(mc->correct));
            c.add_attr(INCORRECTS, attr(mc->incorrects));
        } else if (type == EXTENDED_RESPONSE) {
            auto er = f.questions[i].get<extended_response>();
            c.add_attr(CORRECT, attr(er->correct));
        } else if (type == FILL_IN_THE_BLANKS) {
            auto fb = f.questions[i].get<fill_in_the_blanks>();
        } else if (type == TRUE_OR_FALSE) {
            auto tf = f.questions[i].get<true_or_false>();
            c.add_attr(CORRECT, attr(tf->correct));
        }
        w.main.add_class(c);
    }
    w.to_file("Test.json");
}

form load_json(std::string file_name) {
    editor r;
    json_class main = r.from_file(file_name);
    form f;
    f.title = attr_to_string(main.attrs[TITLE]);
    f.desc = attr_to_string(main.attrs[DESC]);
    size_t size = std::stoi(main.attrs[NUMS]);
    for (size_t i = 0; i < size; ++i) {
        std::string type = attr_to_string(main.classes[i].attrs[TYPE]);
        std::string prompt = attr_to_string(main.classes[i].attrs[PROMPT]);
        int pts = std::stoi(main.classes[i].attrs[PTS]);
        if (type == MULTIPLE_CHOICE) {
            std::string correct = attr_to_string(main.classes[i].attrs[CORRECT]);
            std::vector<std::string> incorrects = list_to_vector(main.classes[i].attrs[INCORRECTS]);
            f.questions.push_back(Qs(multiple_choice(prompt, pts, correct, incorrects)));
        } else if (type == EXTENDED_RESPONSE) {
            std::string correct = attr_to_string(main.classes[i].attrs[CORRECT]);
            f.questions.push_back(Qs(extended_response(prompt, pts, correct)));
        } else if (type == FILL_IN_THE_BLANKS) {
            std::vector<std::string> corrects = list_to_vector(main.classes[i].attrs[CORRECTS]);
            f.questions.push_back(Qs(fill_in_the_blanks(prompt, pts, corrects)));
        } else if (type == TRUE_OR_FALSE) {
            bool correct = attr_to_bool(main.classes[i].attrs[CORRECT]);
            f.questions.push_back(Qs(true_or_false(prompt, pts, correct)));
        }
    }
    return f;
}

}; // End namespace json

#endif // _SRC_JSON_HPP_