// Written by Aaron Barge
// Copyright 2020

#include <iostream>
#include <variant>
#include <vector>
#include "../src/form.hpp"
#include "../src/json.hpp"
#include "../src/question.hpp"
#include "../src/to_tex.hpp"

enum main {NEW_QUIZ = 1, LOAD_QUIZ, QUIT};

void print_menu() {
    std::cout << "============================================================" << std::endl;
    std::cout << "                         Main  Menu                         " << std::endl;
    std::cout << "============================================================" << std::endl;
    for (int i = 1; i <= QUIT; ++i) {
        if (i == NEW_QUIZ)
            std::cout << NEW_QUIZ << ". Generate a new quiz" << std::endl;
        else if (i == LOAD_QUIZ)
            std::cout << LOAD_QUIZ << ". Load a previous quiz" << std::endl;
        else
            std::cout << QUIT << ". Quit" << std::endl;
    }
}

void new_quiz() {

}

void load_quiz() {

}

int main(int argc, char** argv) {
    /*
    int option = 0;
    while (true) {
        print_menu();
        std::cout << "Please enter an option: ";
        std::cin >> option;
        if (QUIT == option)
            break;
        if (NEW_QUIZ == option)
            new_quiz();
        if (LOAD_QUIZ == option)
            load_quiz();
    }
    */
    form f;
    f.set_title("Quiz 1");
    f.set_desc("Sample quiz");
    std::vector<std::string> mc;
    mc.push_back("Incorrect 1");
    mc.push_back("Incorrect 2");
    f.add(Qs(multiple_choice("Multiple choice question", 5, "Correct", mc)));
    f.add(Qs(true_or_false("True or false question", 5, true)));
    f.add(Qs(extended_response("Extended Response question", 5, "Expected answer")));
    f.add(Qs(multiple_choice("Multiple choice question 2", 10, "Correct", mc)));
    f.add(Qs(true_or_false("True or false question 2", 102, true)));
    f.print();
    json::to_json(f);
    f = json::load_json("Test.json");
    
    return 0;
}