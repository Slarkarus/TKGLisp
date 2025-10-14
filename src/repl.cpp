#include <iostream>
#include <string>

#include "repl.hpp"
#include "value.hpp"
#include "parser.hpp"

std::string read(){
    std::string result;
    
    std::getline(std::cin, result);

    return result;
}

tkg::Value eval(tkg::Value input){
    return input;
}

void print(tkg::Value output){
    std::cout << output;
}

void tkg::repl(){
    std::string s;
    
    while(true){
        // Read
        std::cin >> s;
        Parser parser(s);
        Value input = parser.parse();

        
        switch(parser.get_current_state()){
            
        }

        // Evaluate
        Value evaluated = eval(input);

        // Print
        std::cout << evaluated << '\n';

    }
}