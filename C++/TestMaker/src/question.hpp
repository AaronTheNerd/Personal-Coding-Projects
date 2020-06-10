// Written by Aaron Barge
// Copyright 2020

#include <functional>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

#ifndef _SRC_QUESTION_HPP_
#define _SRC_QUESTION_HPP_

std::string NONE = "NONE";
std::string MULTIPLE_CHOICE = "MULTIPLE_CHOICE";
std::string EXTENDED_RESPONSE = "EXTENDED_RESPONSE";
std::string FILL_IN_THE_BLANKS = "FILL_IN_THE_BLANKS";
std::string TRUE_OR_FALSE = "TRUE_OR_FALSE";

class question {
  public:
    std::string type, prompt;
    int pts;

    question() :
            type(NONE),
            prompt(""),
            pts(1) {}

    question(std::string prompt, int pts) :
            type(NONE),
            prompt(prompt),
            pts(pts) {}
};

class multiple_choice : public question {
  public:
    std::string correct;
    std::vector<std::string> incorrects;
    
    multiple_choice() :
            correct(""),
            incorrects() {
        this->type = MULTIPLE_CHOICE;
        this->prompt = "";
        this->pts = 1;
    }
    
    multiple_choice(std::string prompt, int pts, std::string correct, std::vector<std::string> incorrects) :
            correct(correct),
            incorrects(incorrects) {
        this->type = MULTIPLE_CHOICE;
        this->prompt = prompt;
        this->pts = pts;
    }

    void print() {
        std::cout << this->prompt << std::endl;
        std::cout << "    A. " << this->correct << std::endl;
        for (int i = 0; i < this->incorrects.size(); ++i)
            std::cout << "    " << char(int('B') + i) << ". " << this->incorrects[i] << std::endl;
        std::cout << std::endl;
    }
};

class extended_response : public question {
  public:
    std::string correct;
    extended_response() :
            correct("") {
        this->type = EXTENDED_RESPONSE;
        this->prompt = "";
        this->pts = 1;
    }
    extended_response(std::string prompt, int pts, std::string correct) :
            correct(correct) {
        this->type = EXTENDED_RESPONSE;
        this->prompt = prompt;
        this->pts = pts;
    }

    void print() {
        std::cout << this->prompt << std::endl;
        std::cout << "    Expected: " << this->correct << std::endl << std::endl;
    }
};

class fill_in_the_blanks : public question {
  public:
    std::vector<std::string> corrects;
    
    fill_in_the_blanks() :
            corrects() {
        this->type = FILL_IN_THE_BLANKS;
        this->prompt = "";
        this->pts = 1;
    }
    
    fill_in_the_blanks(std::string prompt, int pts, std::vector<std::string> corrects) : 
            corrects(corrects) {
        this->type = FILL_IN_THE_BLANKS;
        this->prompt = prompt;
        this->pts = pts;
    }
    
    void print() {

    }
};

class true_or_false : public question {
  public:
    bool correct;
    
    true_or_false() :
            correct(false) {
        this->type = TRUE_OR_FALSE;
        this->prompt = "";
        this->pts = 1;
    }
    
    true_or_false(std::string prompt, int pts, bool correct) :
            correct(correct) {
        this->type = TRUE_OR_FALSE;
        this->prompt = prompt;
        this->pts = pts;
    }

    void print() {
        std::cout << prompt << std::endl;
        std::cout << "    A. " << (this->correct ? "true" : "false") << std::endl;
        std::cout << "    B. " << (!this->correct ? "true" : "false") << std::endl;
        std::cout << std::endl;
    }
};

using question_types = std::variant<question, multiple_choice, extended_response, fill_in_the_blanks, true_or_false>;

class Qs {
  public:
    question_types var;
    
    Qs() {}
    
    Qs(question q) : var(question_types(q)) {}
    
    Qs(multiple_choice q) : var(question_types(q)) {}
    
    Qs(extended_response q) : var(question_types(q)) {}
    
    Qs(fill_in_the_blanks q) : var(question_types(q)) {}
    
    Qs(true_or_false q) : var(question_types(q)) {}
    
    template<class T>
    T* get() {
        return std::get_if<T>(&var);
    }

    std::string type() {
        if (auto mc = std::get_if<multiple_choice>(&var))
            return mc->type;
        if (auto er = std::get_if<extended_response>(&var))
            return er->type;
        if (auto fb = std::get_if<fill_in_the_blanks>(&var))
            return fb->type;
        if (auto tf = std::get_if<true_or_false>(&var))
            return tf->type;
    }

    std::string prompt() {
        if (auto mc = std::get_if<multiple_choice>(&var))
            return mc->prompt;
        if (auto er = std::get_if<extended_response>(&var))
            return er->prompt;
        if (auto fb = std::get_if<fill_in_the_blanks>(&var))
            return fb->prompt;
        if (auto tf = std::get_if<true_or_false>(&var))
            return tf->prompt;
    }

    int pts() {
        if (auto mc = std::get_if<multiple_choice>(&var))
            return mc->pts;
        if (auto er = std::get_if<extended_response>(&var))
            return er->pts;
        if (auto fb = std::get_if<fill_in_the_blanks>(&var))
            return fb->pts;
        if (auto tf = std::get_if<true_or_false>(&var))
            return tf->pts;
    }

    void print() {
        if (auto mc = std::get_if<multiple_choice>(&var))
            mc->print();
        else if (auto er = std::get_if<extended_response>(&var))
            er->print();
        else if (auto fb = std::get_if<fill_in_the_blanks>(&var))
            fb->print();
        else if (auto tf = std::get_if<true_or_false>(&var))
            tf->print();
    }
};

#endif // _SRC_QUESTION_HPP_