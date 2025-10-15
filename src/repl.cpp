#include <iostream>
#include <string>

#include "repl.hpp"
#include "value.hpp"
#include "parser.hpp"

std::string read()
{
    std::string result;

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
        switch (current_state)
        {
        case ParserState::Done:
            break;
        case ParserState::Empty:
            std::cout << "Empty\n";
            break;
        case ParserState::Error:
        {
            ParserError current_error = parser.get_current_error();
            switch (current_error)
            {
            case ParserError::MissingGlobalLeftBracket:
                std::cout << "mglb\n";
                break;
            case ParserError::MissingLeftBracket:
                std::cout << "mlb\n";
                break;
            case ParserError::MissingRightBracket:
                std::cout << "mrb\n";
                break;
            case ParserError::MissingSecondDoubleQuote:
                std::cout << "msdq\n";
                break;
            case ParserError::MissingSecondSemilicon:
                std::cout << "mss\n";
                break;
            }
            std::cout << "Error\n";
            break;
        }
        case ParserState::Processing:
            std::cout << "Processing\n";
            break;
        default:
            break;
        }

        // Evaluate
        Value evaluated = eval(input);

        // Print
        std::cout << evaluated << '\n';
    }
}