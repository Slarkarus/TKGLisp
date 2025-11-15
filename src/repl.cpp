#include <iostream>
#include <string>
#include <fstream>

#include "string_utils.hpp"
#include "repl.hpp"
#include "value/value.hpp"
#include "parser.hpp"
#include "evaluator.hpp"

namespace tkg
{
    namespace detail
    {
        void read(std::string &input)
        {
            std::cout << ">>> ";

            std::getline(std::cin, input);
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
        Parser parser;
        Evaluator evaluator;

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

            Value input = parser.parse(s);

            ParserState parser_state = parser.get_current_state();
            if (parser_state != ParserState::Done)
            {
                std::cout << "ParserState: " << magic_enum::enum_name(parser_state) << '\n';

                if (parser_state == ParserState::Error)
                {
                    print_error<ParserError>(
                        parser.get_current_error(),
                        get_current_line(parser.get_input(), parser.get_offset()),
                        get_current_position(parser.get_input(), parser.get_offset()));
                }

                continue;
            }

            if constexpr(DEBUG){
                std::cout << input.get_as_debug_string() << '\n';
            }
            
            // Evaluate
            
            Value evaluated = evaluator.evaluate(input);

            EvaluatorState evaluator_state = evaluator.get_current_state();
            if (evaluator_state != EvaluatorState::Done)
            {
                std::cout << "EvaluatorState: " << magic_enum::enum_name(evaluator_state) << '\n';

                if(evaluator_state == EvaluatorState::Error){
                    std::string error_line = "undefined line";

                    print_error<EvaluatorError>(
                        evaluator.get_current_error(),
                        error_line,
                        {0, 0}
                    );
                }
            }

            // Print
            std::cout << evaluated << '\n';
        }
    }
}