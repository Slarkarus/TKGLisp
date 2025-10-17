#include <iostream>
#include <string>
#include <fstream>

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

        // Return true on successful file read
        bool read_file(std::string &result, const std::string &filename)
        {
            std::ifstream file(filename);

            if (!file.is_open())
            {
                return false;
            }

            result = "";

            std::string line;
            while (std::getline(file, line))
            {
                result += line;
                result.push_back('\n');
            }

            file.close();

            return true;
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
                std::cout << "\nThanks for using TKGLisp!\n";
                break;
            }

            if (s[0] == ':')
            {
                if (s == ":q")
                {
                    std::cout << "Thanks for using TKGLisp!\n";
                    break;
                }
                else if (s.rfind(":l ", 0) == 0)
                {
                    std::string filename = s.substr(3);

                    size_t start = filename.find_first_not_of(" \t");
                    size_t end = filename.find_last_not_of(" \t");

                    if (start == std::string::npos)
                    {
                        std::cout << "ReplError: No filename specified after :l\n";
                        continue;
                    }

                    filename = filename.substr(start, end - start + 1);

                    if (!detail::read_file(s, filename))
                    {
                        std::cout << "ReplError: Can't read file with name: " << filename << '\n';
                        continue;
                    }
                }
                else
                {
                    std::cout << "ReplError: unknown command\n";
                    continue;
                }
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