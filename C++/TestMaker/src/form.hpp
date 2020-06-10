// Written by Aaron Barge
// Copyright 2020

#include <iostream>
#include "../src/question.hpp"

#ifndef _SRC_FORM_HPP_
#define _SRC_FORM_HPP_

class form {
  public:
    std::string title, desc;
    std::vector<Qs> questions;
    form() : title(""), desc(""), questions() {}
    form(std::string title, std::string desc, std::vector<Qs> questions) :
            title(title),
            desc(desc),
            questions(questions) {}
    void set_title(std::string title) {
        this->title = title;
    }
    void set_desc(std::string desc) {
        this->desc = desc;
    }
    void add(Qs q) {
        this->questions.push_back(q);
    }
    void remove(size_t index) {
        this->questions.erase(questions.begin() + index);
    }
    void print() {
        std::cout << "Title: " << this->title << std::endl;
        std::cout << "Description: " << this->desc << std::endl;
        for (size_t i = 0; i < this->questions.size(); ++i) {
            std::cout << "Q" << i + 1 << ": ";
            this->questions[i].print();
        }
    }
};

#endif // _SRC_FORM_HPP_