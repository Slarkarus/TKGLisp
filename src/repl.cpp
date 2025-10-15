#include <iostream>
#include <string>

#include "magic_enum.hpp"

#include "repl.hpp"
#include "value.hpp"
#include "parser.hpp"

std::string read()
{
    std::string result;

    std::cout << ">>> ";

    std::getline(std::cin, result);

    return result;
}

tkg::Value eval(tkg::Value input)
{
    return input;
}

void print(tkg::Value output)
{
    std::cout << output;
}

template <typename T>
void print_error(T error, std::string line, std::pair<uint32_t, uint32_t> pos)
{
    std::cout << "Error on line: " << pos.first << ", column: " << pos.second << '\n';
    std::cout << "Line: " << line << '\n';
    std::cout << "      ";
    
    for (int i = 1; i < pos.second; ++i)
        std::cout << '^';
    

    std::cout << '#';
    
    for (int i = pos.second + 1; i <= line.size(); ++i)
        std::cout << "^";
    
    std::cout << '\n';
    std::cout << magic_enum::enum_type_name<T>() << ": " << magic_enum::enum_name(error) << '\n';
}

void tkg::repl()
{
    std::string s;

    while (true)
    {
        // Read
        std::string s = read();
        Parser parser(s);

        Value input = parser.parse();

        ParserState current_state = parser.get_current_state();
        if (current_state != ParserState::Done)
        {
            std::cout << "ParserState: " << magic_enum::enum_name(current_state) << '\n';

            if (current_state == ParserState::Error)
            {
                print_error<ParserError>(parser.get_current_error(), parser.get_current_line(), parser.get_current_position());
            }

            continue;
        }

        // Evaluate
        Value evaluated = eval(input);

        // Print
        std::cout << evaluated << '\n';
    }
}