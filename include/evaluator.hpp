#ifndef TKG_EVALUATOR_HPP
#define TKG_EVALUATOR_HPP

#include "value/value.hpp"
#include "config.hpp"

namespace tkg
{

    enum class EvaluatorState
    {
        Empty,
        Processing,
        Done,
        Error
    };

    enum class EvaluatorError
    {
        Empty,
        WrongHeadForm,
        TooManyArgumentsAfterHead,
        LeftArgumentForBinaryOperationIsNotANumber,
        RightArgumentForBinaryOperationIsNotANumber,
        DontCollectStrConcat
    };

    class Evaluator
    {
    private:
        EvaluatorState current_state_;
        EvaluatorError current_error_;

        template <EvaluatorError error>
        inline Value process_error()
        {
            current_state_ = EvaluatorState::Error;
            current_error_ = error;
            return None;
        }

        inline Value evaluator_result(const Value &value)
        {
            if (current_state_ == EvaluatorState::Error)
            {
                return None;
            }
            current_state_ = EvaluatorState::Done;
            return value;
        }

        Value eval_binary_operation(BinaryOperation operation, Value tail)
        {
            Value left = car(tail);
            Value right = car(cdr(tail));

            if (cdr(cdr(tail)) != NIL)
            {
                return process_error<EvaluatorError::TooManyArgumentsAfterHead>();
            }

            if (operation == BinaryOperation::StrConcat)
            {
                return left.get_as_string() + right.get_as_string();
            }

            ValueType left_type = left.get_type();
            ValueType right_type = right.get_type();

            if (left_type != ValueType::Integer && left_type != ValueType::Double)
            {
                return process_error<EvaluatorError::LeftArgumentForBinaryOperationIsNotANumber>();
            }

            if (right_type != ValueType::Integer && right_type != ValueType::Double)
            {
                return process_error<EvaluatorError::RightArgumentForBinaryOperationIsNotANumber>();
            }

            if (left_type == right_type && left_type == ValueType::Integer)
            {
                Integer left_int = left.get_as_raw<Integer>();
                Integer right_int = right.get_as_raw<Integer>();
                switch (operation)
                {
                case BinaryOperation::Add:
                    return left_int + right_int;
                case BinaryOperation::Sub:
                    return left_int - right_int;
                case BinaryOperation::Mul:
                    return left_int * right_int;
                case BinaryOperation::Div:
                    return left_int / right_int;
                case BinaryOperation::Mod:
                    return left_int % right_int;
                case BinaryOperation::StrConcat:
                    return process_error<EvaluatorError::DontCollectStrConcat>();
                }
            }
            else
            {
                auto convert_to_double = [](const Value &value, ValueType type)
                {
                    if (type == ValueType::Integer)
                    {
                        return (double)value.get_as_raw<Integer>();
                    }
                    return value.get_as_raw<double>();
                };

                double left_dob = convert_to_double(left, left_type);
                double right_dob = convert_to_double(right, right_type);

                switch (operation)
                {
                case BinaryOperation::Add:
                    return left_dob + right_dob;
                case BinaryOperation::Sub:
                    return left_dob - right_dob;
                case BinaryOperation::Mul:
                    return left_dob * right_dob;
                case BinaryOperation::Div:
                    return left_dob / right_dob;
                case BinaryOperation::Mod:
                    return operator_percent_between_doubles(left_dob, right_dob);
                case BinaryOperation::StrConcat:
                    return process_error<EvaluatorError::DontCollectStrConcat>();
                }
            }
        }

        Value eval_binary_predicate(BinaryPredicate predicate, Value tail)
        {
            return tail;
        }

        Value eval_special_form(SpecialForm form, Value tail)
        {
            return tail;
        }

    public:
        Evaluator()
        {
            current_state_ = EvaluatorState::Empty;
        }

        EvaluatorError get_current_error()
        {
            return current_error_;
        }

        EvaluatorState get_current_state()
        {
            return current_state_;
        }

        Value evaluate(Value expression)
        {
            current_state_ = EvaluatorState::Processing;
            switch (expression.get_type())
            {
            case ValueType::List:
            {
                if (expression == NIL)
                {
                    return NIL; // TODO: move to config
                }

                Value head = evaluate(car(expression));
                Value tail = cdr(expression);

                switch (head.get_type())
                {
                case ValueType::BinaryOperation:
                    return evaluator_result(eval_binary_operation(head.get_as_raw<BinaryOperation>(), tail));
                case ValueType::BinaryPredicate:
                    return evaluator_result(eval_binary_predicate(head.get_as_raw<BinaryPredicate>(), tail));
                case ValueType::SpecialForm:
                    return evaluator_result(eval_special_form(head.get_as_raw<SpecialForm>(), tail));
                default:
                    return process_error<EvaluatorError::WrongHeadForm>();
                }
            }
            default:
                break;
            }
            current_state_ = EvaluatorState::Done;
            return expression;
        }
    };
}

#endif // TKG_EVALUATOR_HPP
