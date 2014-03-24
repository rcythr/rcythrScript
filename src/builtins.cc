// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/constants.h>

namespace rscript
{

PL_SYMBOL NIL = WRAP(L_SYMBOL, "nil");
PL_BOOL TRUE = WRAP(L_BOOL, true);
PL_BOOL FALSE = WRAP(L_BOOL, false);

PL_ATOM proc_is_eq(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_eqv(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_equal(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_symbol(PL_ATOM atom, SymbolTable& symbols) 
{
    if(atom->mType == DataType::SYMBOL)
        return TRUE;
    else if(atom->mType == DataType::LITERAL)
        return (AS(L_LITERAL, atom)->mLiteral->mType == DataType::SYMBOL) ? TRUE : FALSE;
    else
        return FALSE;
}

PL_ATOM proc_is_procedure(PL_ATOM atom, SymbolTable& symbols) 
{ 
    return (atom->mType == DataType::BUILTIN_FUNCTION || atom->mType == DataType::FUNCTION) ? TRUE : FALSE; 
}

PL_ATOM proc_apply(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_map(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_for_each(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_bool(PL_ATOM atom, SymbolTable& symbols)
{
    return (atom->mType == DataType::BOOL) ? TRUE : FALSE;
}

PL_ATOM proc_not(PL_BOOL atom, SymbolTable& symbols)
{
    return (atom->mValue) ? FALSE : TRUE;
}

#define MAKE_SIMPLE_BUILTIN(A, B) \
{ A, std::make_shared<L_BUILTIN_FUNCTION>( \
        std::make_shared<SimpleBuiltinHandler>(\
            std::bind(B, \
                std::placeholders::_1, \
                std::placeholders::_2) \
            )\
        )\
}

#define MAKE_BUILTIN(A, B) { A, std::make_shared<L_BUILTIN_FUNCTION>(B) }

std::unordered_map<std::string, PL_BUILTIN_FUNCTION> builtins =
{
    MAKE_SIMPLE_BUILTIN("vector", proc_vector),
    MAKE_SIMPLE_BUILTIN("make-vector", proc_make_vector),
    MAKE_SIMPLE_BUILTIN("make-string", proc_make_string),
    MAKE_SIMPLE_BUILTIN("list", proc_list),
    MAKE_SIMPLE_BUILTIN("eq?", proc_is_eq),
    MAKE_SIMPLE_BUILTIN("eqv?", proc_is_eqv),
    MAKE_SIMPLE_BUILTIN("equal?", proc_is_equal),
    MAKE_SIMPLE_BUILTIN("string=?", proc_is_string_eq),
    MAKE_SIMPLE_BUILTIN("stirng-ci=?", proc_is_string_eq_ci),
    MAKE_SIMPLE_BUILTIN("char=?", proc_is_char_eq),
    MAKE_SIMPLE_BUILTIN("char-ci=?", proc_is_char_eq_ci),
    MAKE_SIMPLE_BUILTIN("vector->list", proc_vector_to_list),
    MAKE_SIMPLE_BUILTIN("list->vector", proc_list_to_vector),
    MAKE_SIMPLE_BUILTIN("number->string", proc_number_to_string),
    MAKE_SIMPLE_BUILTIN("string->number", proc_string_to_number),
    MAKE_SIMPLE_BUILTIN("symbol->string", proc_symbol_to_string),
    MAKE_SIMPLE_BUILTIN("string->symbol", proc_string_to_symbol),
    MAKE_SIMPLE_BUILTIN("char->integer", proc_char_to_integer),
    MAKE_SIMPLE_BUILTIN("integer->char", proc_integer_to_char),
    MAKE_SIMPLE_BUILTIN("string->list", proc_string_to_list),
    MAKE_SIMPLE_BUILTIN("list->string", proc_list_to_string),
    MAKE_SIMPLE_BUILTIN("string?", proc_is_string),
    MAKE_SIMPLE_BUILTIN("string", proc_string),
    MAKE_SIMPLE_BUILTIN("string-length", proc_string_length),
    MAKE_SIMPLE_BUILTIN("string-ref", proc_string_ref),
    MAKE_SIMPLE_BUILTIN("string-set!", proc_string_set_exclaim),
    MAKE_SIMPLE_BUILTIN("string<?", proc_string_lt),
    MAKE_SIMPLE_BUILTIN("string-ci<?", proc_string_lt_ci),
    MAKE_SIMPLE_BUILTIN("string<=?", proc_string_lte),
    MAKE_SIMPLE_BUILTIN("string-ci<=?", proc_string_lte_ci),
    MAKE_SIMPLE_BUILTIN("string>?", proc_string_gt),
    MAKE_SIMPLE_BUILTIN("string-ci>?", proc_string_gt_ci),
    MAKE_SIMPLE_BUILTIN("string>=?", proc_string_gte_ci),
    MAKE_SIMPLE_BUILTIN("string-ci>=?", proc_string_gte_ci),
    MAKE_SIMPLE_BUILTIN("substring", proc_substring),
    MAKE_SIMPLE_BUILTIN("string-append", proc_append),
    MAKE_SIMPLE_BUILTIN("string-copy", proc_string_copy),
    MAKE_SIMPLE_BUILTIN("string-fill!", proc_string_fill_exclaim),
    MAKE_BUILTIN("char?", std::make_shared<BuiltinHandler>("char?")
        ->bind<L_ATOM>(std::bind(proc_is_char, std::placeholders::_1, std::placeholders::_2))
        ),
    MAKE_SIMPLE_BUILTIN("char<?", proc_char_lt),
    MAKE_SIMPLE_BUILTIN("char-ci<?", proc_char_lt_ci),
    MAKE_SIMPLE_BUILTIN("char<=?", proc_char_lte),
    MAKE_SIMPLE_BUILTIN("char-ci<=?", proc_char_lte_ci),
    MAKE_SIMPLE_BUILTIN("char>?", proc_char_gt),
    MAKE_SIMPLE_BUILTIN("char-ci>?", proc_char_gt_ci),
    MAKE_SIMPLE_BUILTIN("char>=?", proc_char_gte),
    MAKE_SIMPLE_BUILTIN("char-ci>=?", proc_char_gte_ci),
    MAKE_SIMPLE_BUILTIN("char-alphabetic?", proc_is_char_alphabetic),
    MAKE_SIMPLE_BUILTIN("char-numeric?", proc_is_char_numeric),
    MAKE_SIMPLE_BUILTIN("char-whitespace?", proc_is_char_whitespace),
    MAKE_SIMPLE_BUILTIN("char-upper-case?", proc_is_char_uppercase),
    MAKE_SIMPLE_BUILTIN("char-lower-case?", proc_is_char_lowercase),
    MAKE_SIMPLE_BUILTIN("char-upcase", proc_char_upcase),
    MAKE_SIMPLE_BUILTIN("char-downcase", proc_char_downcase),
    MAKE_SIMPLE_BUILTIN("vector?", proc_is_vector),
    MAKE_SIMPLE_BUILTIN("vector-length", proc_vector_length),
    MAKE_SIMPLE_BUILTIN("vector-ref", proc_vector_ref),
    MAKE_SIMPLE_BUILTIN("vector-set!", proc_vector_set_exclaim),
    MAKE_SIMPLE_BUILTIN("vector-fill!", proc_vector_fill_exclaim),
    MAKE_BUILTIN("symbol?", 
        std::make_shared<BuiltinHandler>("symbol?")
            ->bind<L_ATOM>(std::bind(proc_is_symbol, std::placeholders::_1, std::placeholders::_2))
        ),
    MAKE_SIMPLE_BUILTIN("pair?", proc_is_pair),
    MAKE_SIMPLE_BUILTIN("cons", proc_cons),
    MAKE_SIMPLE_BUILTIN("car", proc_car),
    MAKE_SIMPLE_BUILTIN("cdr", proc_cdr),
    MAKE_SIMPLE_BUILTIN("set-car!", proc_set_car_exclaim),
    MAKE_SIMPLE_BUILTIN("set-cdr!", proc_set_cdr_exclaim),
    MAKE_SIMPLE_BUILTIN("null?", proc_is_null),
    MAKE_SIMPLE_BUILTIN("list?", proc_is_list),
    MAKE_SIMPLE_BUILTIN("list", proc_list),
    MAKE_SIMPLE_BUILTIN("length", proc_length),
    MAKE_SIMPLE_BUILTIN("append", proc_append),
    MAKE_SIMPLE_BUILTIN("reverse", proc_reverse),
    MAKE_SIMPLE_BUILTIN("list-tail", proc_list_tail),
    MAKE_SIMPLE_BUILTIN("list-ref", proc_list_ref),
    MAKE_SIMPLE_BUILTIN("memq", proc_memq),
    MAKE_SIMPLE_BUILTIN("memv", proc_memv),
    MAKE_SIMPLE_BUILTIN("member", proc_member),
    MAKE_SIMPLE_BUILTIN("assq", proc_assq),
    MAKE_SIMPLE_BUILTIN("assv", proc_assv),
    MAKE_SIMPLE_BUILTIN("assoc", proc_assoc),
    MAKE_SIMPLE_BUILTIN("call-with-current-continuation", proc_call_cc),
    MAKE_SIMPLE_BUILTIN("values", proc_values),
    MAKE_SIMPLE_BUILTIN("call-with-values", proc_call_with_values),
    MAKE_SIMPLE_BUILTIN("dynamic-wind", proc_dynamic_wind),
    MAKE_SIMPLE_BUILTIN("eval", proc_eval),
    MAKE_SIMPLE_BUILTIN("scheme-report-environment", proc_report_environment),
    MAKE_SIMPLE_BUILTIN("null-environment", proc_null_environment),
    MAKE_SIMPLE_BUILTIN("interaction-environment", proc_interaction_environment),
    MAKE_SIMPLE_BUILTIN("display", proc_display),
    MAKE_SIMPLE_BUILTIN("newline", proc_newline),
    MAKE_SIMPLE_BUILTIN("read", proc_read),
    MAKE_SIMPLE_BUILTIN("write", proc_write),
    MAKE_SIMPLE_BUILTIN("read-char", proc_read_char),
    MAKE_SIMPLE_BUILTIN("write-char", proc_write_char),
    MAKE_SIMPLE_BUILTIN("peek-char", proc_peek_char),
    MAKE_SIMPLE_BUILTIN("char-ready?", proc_is_char_ready),
    MAKE_SIMPLE_BUILTIN("eof-object?", proc_is_eof_object),
    MAKE_SIMPLE_BUILTIN("open-input-file", proc_open_input_file),
    MAKE_SIMPLE_BUILTIN("open-output-file", proc_open_output_file),
    MAKE_SIMPLE_BUILTIN("close-input-port", proc_close_input_port),
    MAKE_SIMPLE_BUILTIN("close-output-port", proc_close_output_port),
    MAKE_SIMPLE_BUILTIN("input-port?", proc_is_input_port),
    MAKE_SIMPLE_BUILTIN("output-port?", proc_is_output_port),
    MAKE_SIMPLE_BUILTIN("current-input-port", proc_current_input_port),
    MAKE_SIMPLE_BUILTIN("current-output-port", proc_current_output_port),
    MAKE_SIMPLE_BUILTIN("call-with-input-file", proc_call_with_input_file),
    MAKE_SIMPLE_BUILTIN("call-with-output-file", proc_call_with_output_file),
    MAKE_SIMPLE_BUILTIN("with-input-from-file", proc_with_input_file),
    MAKE_SIMPLE_BUILTIN("with-output-to-file", proc_with_output_file),
    MAKE_SIMPLE_BUILTIN("load", proc_load),
    MAKE_SIMPLE_BUILTIN("transcript-on", proc_transcript_on),
    MAKE_SIMPLE_BUILTIN("transcript-off", proc_transcript_off),
    MAKE_BUILTIN("procedure?", 
        std::make_shared<BuiltinHandler>("procedure?")
            ->bind<L_ATOM>(std::bind(proc_is_procedure, std::placeholders::_1, std::placeholders::_2))
        ),
    MAKE_SIMPLE_BUILTIN("apply", proc_apply),
    MAKE_SIMPLE_BUILTIN("map", proc_map),
    MAKE_SIMPLE_BUILTIN("for-each", proc_for_each),
    MAKE_BUILTIN("boolean?", 
        std::make_shared<BuiltinHandler>("boolean?")
        ->bind<L_ATOM>(std::bind(proc_is_bool, std::placeholders::_1, std::placeholders::_2))
        ),
    MAKE_BUILTIN("not", 
        std::make_shared<BuiltinHandler>("not")
        ->bind<L_BOOL>(std::bind(proc_not, std::placeholders::_1, std::placeholders::_2))
        ),
    MAKE_SIMPLE_BUILTIN("+", proc_add),
    MAKE_SIMPLE_BUILTIN("-", proc_substract),
    MAKE_SIMPLE_BUILTIN("*", proc_multiply),
    MAKE_SIMPLE_BUILTIN("/", proc_divide),
    MAKE_SIMPLE_BUILTIN("abs", proc_abs),
    MAKE_SIMPLE_BUILTIN("quotient", proc_quotient),
    MAKE_SIMPLE_BUILTIN("remainder", proc_remainder),
    MAKE_SIMPLE_BUILTIN("modulo", proc_modulo),
    MAKE_SIMPLE_BUILTIN("gcd", proc_gcd),
    MAKE_SIMPLE_BUILTIN("lcm", proc_lcm),
    MAKE_SIMPLE_BUILTIN("expt", proc_expt),
    MAKE_SIMPLE_BUILTIN("sqrt", proc_sqrt),
    MAKE_SIMPLE_BUILTIN("numerator", proc_numerator),
    MAKE_SIMPLE_BUILTIN("denominator", proc_denominator),
    MAKE_SIMPLE_BUILTIN("rational?", proc_is_rational),
    MAKE_SIMPLE_BUILTIN("simplest", proc_simplest),
    MAKE_SIMPLE_BUILTIN("rationalize", proc_rationalize),
    MAKE_SIMPLE_BUILTIN("floor", proc_floor),
    MAKE_SIMPLE_BUILTIN("ceiling", proc_ceiling),
    MAKE_SIMPLE_BUILTIN("truncate", proc_truncate),
    MAKE_SIMPLE_BUILTIN("round", proc_round),
    MAKE_SIMPLE_BUILTIN("inexact->exact", proc_inexact_to_exact),
    MAKE_SIMPLE_BUILTIN("exact->inexact", proc_exact_to_inexact),
    MAKE_SIMPLE_BUILTIN("exact?", proc_is_exact),
    MAKE_SIMPLE_BUILTIN("inexact?", proc_is_inexact),
    MAKE_SIMPLE_BUILTIN("<", proc_lt),
    MAKE_SIMPLE_BUILTIN("<=", proc_lte),
    MAKE_SIMPLE_BUILTIN(">", proc_gt),
    MAKE_SIMPLE_BUILTIN(">=", proc_gte),
    MAKE_SIMPLE_BUILTIN("=", proc_eq),
    MAKE_SIMPLE_BUILTIN("zero?", proc_is_zero),
    MAKE_SIMPLE_BUILTIN("negative?", proc_is_negative),
    MAKE_SIMPLE_BUILTIN("positive?", proc_is_positive),
    MAKE_SIMPLE_BUILTIN("even?", proc_is_even),
    MAKE_SIMPLE_BUILTIN("odd?", proc_is_odd),
    MAKE_SIMPLE_BUILTIN("max", proc_max),
    MAKE_SIMPLE_BUILTIN("min", proc_min),
    MAKE_SIMPLE_BUILTIN("sin", proc_sin),
    MAKE_SIMPLE_BUILTIN("cos", proc_cos),
    MAKE_SIMPLE_BUILTIN("tan", proc_tan),
    MAKE_SIMPLE_BUILTIN("asin", proc_asin),
    MAKE_SIMPLE_BUILTIN("acos", proc_acos),
    MAKE_SIMPLE_BUILTIN("atan", proc_atan),
    MAKE_SIMPLE_BUILTIN("exp", proc_exp),
    MAKE_SIMPLE_BUILTIN("log", proc_log),
    MAKE_SIMPLE_BUILTIN("make-rectangular", proc_make_rectangular),
    MAKE_SIMPLE_BUILTIN("make-polar", proc_make_polar),
    MAKE_SIMPLE_BUILTIN("real-part", proc_real_part),
    MAKE_SIMPLE_BUILTIN("imag-part", proc_imag_part),
    MAKE_SIMPLE_BUILTIN("magnitude", proc_magnitude),
    MAKE_SIMPLE_BUILTIN("angle", proc_angle),
    MAKE_SIMPLE_BUILTIN("complex?", proc_is_complex),
    MAKE_SIMPLE_BUILTIN("integer?", proc_is_integer),
    MAKE_SIMPLE_BUILTIN("rational?", proc_is_rational),
    MAKE_SIMPLE_BUILTIN("real?", proc_is_real),
    MAKE_SIMPLE_BUILTIN("complex?", proc_is_complex),
    MAKE_SIMPLE_BUILTIN("number?", proc_is_number),
};

}
