#include <iostream>
#include <string>

#include "string_utils.hpp"
#include "repl.hpp"
#include "value.hpp"
#include "parser.hpp"

namespace tkg
{
    namespace detail
    {
        void read(std::string &input)
        {
            std::cout << ">>> ";

            std::getline(std::cin, input);
        }

        tkg::Value eval(tkg::Value input)
        {
            return input;
        }

        void print(tkg::Value output)
        {
            std::cout << output;
        }
    }

    void repl()
    {
        while (true)
        {
            // Read
            std::string s;

            detail::read(s);

            if (std::cin.eof())
            {
                std::cout << "\nThanks for using TKGLisp!";
                break;
            }

            Parser parser(s);

            Value input = parser.parse();

            ParserState current_state = parser.get_current_state();
            if (current_state != ParserState::Done)
            {
                std::cout << "ParserState: " << magic_enum::enum_name(current_state) << '\n';

                if (current_state == ParserState::Error)
                {
                    print_error<ParserError>(
                        parser.get_current_error(),
                        get_current_line(parser.get_input(), parser.get_offset()),
                        get_current_position(parser.get_input(), parser.get_offset()));
                }

                continue;
            }

            // Evaluate
            Value evaluated = detail::eval(input);

            // Print
            std::cout << evaluated << '\n';
        }
    }
}