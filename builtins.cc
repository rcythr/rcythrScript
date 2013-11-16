
#include "builtins.h"

namespace rcythr
{

PL_SYMBOL NIL = std::make_shared<L_SYMBOL>("nil");

PL_ATOM proc_is_eq(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_eqv(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_equal(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_symbol(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_procedure(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_apply(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_map(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_for_each(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_is_bool(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_not(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_lt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_lte(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_gt(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_gte(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM proc_eq(std::vector<PL_ATOM>& lst, SymbolTableType& globals, SymbolTableType& locals)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

#define MAKE_BUILTIN(A, B) { A, std::make_shared<L_BUILTIN_FUNCTION>(std::bind(B, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)) }
std::unordered_map<std::string,PL_BUILTIN_FUNCTION> builtins =
{
    MAKE_BUILTIN("vector", proc_vector),
    MAKE_BUILTIN("make-vector", proc_make_vector),
    MAKE_BUILTIN("make-string", proc_make_string),
    MAKE_BUILTIN("list", proc_list),
    MAKE_BUILTIN("eq?", proc_is_eq),
    MAKE_BUILTIN("eqv?", proc_is_eqv),
    MAKE_BUILTIN("equal?", proc_is_equal),
    MAKE_BUILTIN("string=?", proc_is_string_eq),
    MAKE_BUILTIN("stirng-ci=?", proc_is_string_eq_ci),
    MAKE_BUILTIN("char=?", proc_is_char_eq),
    MAKE_BUILTIN("char-ci=?", proc_is_char_eq_ci),
    MAKE_BUILTIN("vector->list", proc_vector_to_list),
    MAKE_BUILTIN("list->vector", proc_list_to_vector),
    MAKE_BUILTIN("number->string", proc_number_to_string),
    MAKE_BUILTIN("string->number", proc_string_to_number),
    MAKE_BUILTIN("symbol->string", proc_symbol_to_string),
    MAKE_BUILTIN("string->symbol", proc_string_to_symbol),
    MAKE_BUILTIN("char->integer", proc_char_to_integer),
    MAKE_BUILTIN("integer->char", proc_integer_to_char),
    MAKE_BUILTIN("string->list", proc_string_to_list),
    MAKE_BUILTIN("list->string", proc_list_to_string),
    MAKE_BUILTIN("string?", proc_is_string),
    MAKE_BUILTIN("string", proc_string),
    MAKE_BUILTIN("string-length", proc_string_length),
    MAKE_BUILTIN("string-ref", proc_string_ref),
    MAKE_BUILTIN("string-set!", proc_string_set_exclaim),
    MAKE_BUILTIN("string<?", proc_string_lt),
    MAKE_BUILTIN("string-ci<?", proc_string_lt_ci),
    MAKE_BUILTIN("string<=?", proc_string_lte),
    MAKE_BUILTIN("string-ci<=?", proc_string_lte_ci),
    MAKE_BUILTIN("string>?", proc_string_gt),
    MAKE_BUILTIN("string-ci>?", proc_string_gt_ci),
    MAKE_BUILTIN("string>=?", proc_string_gte_ci),
    MAKE_BUILTIN("string-ci>=?", proc_string_gte_ci),
    MAKE_BUILTIN("substring", proc_substring),
    MAKE_BUILTIN("string-append", proc_append),
    MAKE_BUILTIN("string-copy", proc_string_copy),
    MAKE_BUILTIN("string-fill!", proc_string_fill_exclaim),
    MAKE_BUILTIN("char?", proc_is_char),
    MAKE_BUILTIN("char<?", proc_char_lt),
    MAKE_BUILTIN("char-ci<?", proc_char_lt_ci),
    MAKE_BUILTIN("char<=?", proc_char_lte),
    MAKE_BUILTIN("char-ci<=?", proc_char_lte_ci),
    MAKE_BUILTIN("char>?", proc_char_gt),
    MAKE_BUILTIN("char-ci>?", proc_char_gt_ci),
    MAKE_BUILTIN("char>=?", proc_char_gte),
    MAKE_BUILTIN("char-ci>=?", proc_char_gte_ci),
    MAKE_BUILTIN("char-alphabetic?", proc_is_char_alphabetic),
    MAKE_BUILTIN("char-numeric?", proc_is_char_numeric),
    MAKE_BUILTIN("char-whitespace?", proc_is_char_whitespace),
    MAKE_BUILTIN("char-upper-case?", proc_is_char_uppercase),
    MAKE_BUILTIN("char-lower-case?", proc_is_char_lowercase),
    MAKE_BUILTIN("char-upcase", proc_char_upcase),
    MAKE_BUILTIN("char-downcase", proc_char_downcase),
    MAKE_BUILTIN("vector?", proc_is_vector),
    MAKE_BUILTIN("vector-length", proc_vector_length),
    MAKE_BUILTIN("vector-ref", proc_vector_ref),
    MAKE_BUILTIN("vector-set!", proc_vector_set_exclaim),
    MAKE_BUILTIN("vector-fill!", proc_vector_fill_exclaim),
    MAKE_BUILTIN("symbol?", proc_is_symbol),
    MAKE_BUILTIN("pair?", proc_is_pair),
    MAKE_BUILTIN("cons", proc_cons),
    MAKE_BUILTIN("car", proc_car),
    MAKE_BUILTIN("cdr", proc_cdr),
    MAKE_BUILTIN("set-car!", proc_set_car_exclaim),
    MAKE_BUILTIN("set-cdr!", proc_set_cdr_exclaim),
    MAKE_BUILTIN("null?", proc_is_null),
    MAKE_BUILTIN("list?", proc_is_list),
    MAKE_BUILTIN("list", proc_list),
    MAKE_BUILTIN("length", proc_length),
    MAKE_BUILTIN("append", proc_append),
    MAKE_BUILTIN("reverse", proc_reverse),
    MAKE_BUILTIN("list-tail", proc_list_tail),
    MAKE_BUILTIN("list-ref", proc_list_ref),
    MAKE_BUILTIN("memq", proc_memq),
    MAKE_BUILTIN("memv", proc_memv),
    MAKE_BUILTIN("member", proc_member),
    MAKE_BUILTIN("assq", proc_assq),
    MAKE_BUILTIN("assv", proc_assv),
    MAKE_BUILTIN("assoc", proc_assoc),
    MAKE_BUILTIN("call-with-current-continuation", proc_call_cc),
    MAKE_BUILTIN("values", proc_values),
    MAKE_BUILTIN("call-with-values", proc_call_with_values),
    MAKE_BUILTIN("dynamic-wind", proc_dynamic_wind),
    MAKE_BUILTIN("eval", proc_eval),
    MAKE_BUILTIN("scheme-report-environment", proc_report_environment),
    MAKE_BUILTIN("null-environment", proc_null_environment),
    MAKE_BUILTIN("interaction-environment", proc_interaction_environment),
    MAKE_BUILTIN("display", proc_display),
    MAKE_BUILTIN("newline", proc_newline),
    MAKE_BUILTIN("read", proc_read),
    MAKE_BUILTIN("write", proc_write),
    MAKE_BUILTIN("read-char", proc_read_char),
    MAKE_BUILTIN("write-char", proc_write_char),
    MAKE_BUILTIN("peek-char", proc_peek_char),
    MAKE_BUILTIN("char-ready?", proc_is_char_ready),
    MAKE_BUILTIN("eof-object?", proc_is_eof_object),
    MAKE_BUILTIN("open-input-file", proc_open_input_file),
    MAKE_BUILTIN("open-output-file", proc_open_output_file),
    MAKE_BUILTIN("close-input-port", proc_close_input_port),
    MAKE_BUILTIN("close-output-port", proc_close_output_port),
    MAKE_BUILTIN("input-port?", proc_is_input_port),
    MAKE_BUILTIN("output-port?", proc_is_output_port),
    MAKE_BUILTIN("current-input-port", proc_current_input_port),
    MAKE_BUILTIN("current-output-port", proc_current_output_port),
    MAKE_BUILTIN("call-with-input-file", proc_call_with_input_file),
    MAKE_BUILTIN("call-with-output-file", proc_call_with_output_file),
    MAKE_BUILTIN("with-input-from-file", proc_with_input_file),
    MAKE_BUILTIN("with-output-to-file", proc_with_output_file),
    MAKE_BUILTIN("load", proc_load),
    MAKE_BUILTIN("transcript-on", proc_transcript_on),
    MAKE_BUILTIN("transcript-off", proc_transcript_off),
    MAKE_BUILTIN("procedure?", proc_is_procedure),
    MAKE_BUILTIN("apply", proc_apply),
    MAKE_BUILTIN("map", proc_map),
    MAKE_BUILTIN("for-each", proc_for_each),
    MAKE_BUILTIN("boolean?", proc_is_bool),
    MAKE_BUILTIN("not", proc_not),
    MAKE_BUILTIN("+", proc_add),
    MAKE_BUILTIN("-", proc_substract),
    MAKE_BUILTIN("*", proc_multiply),
    MAKE_BUILTIN("/", proc_divide),
    MAKE_BUILTIN("abs", proc_abs),
    MAKE_BUILTIN("quotient", proc_quotient),
    MAKE_BUILTIN("remainder", proc_remainder),
    MAKE_BUILTIN("modulo", proc_modulo),
    MAKE_BUILTIN("gcd", proc_gcd),
    MAKE_BUILTIN("lcm", proc_lcm),
    MAKE_BUILTIN("expt", proc_expt),
    MAKE_BUILTIN("sqrt", proc_sqrt),
    MAKE_BUILTIN("numerator", proc_numerator),
    MAKE_BUILTIN("denominator", proc_denominator),
    MAKE_BUILTIN("rational?", proc_is_rational),
    MAKE_BUILTIN("rationalize", proc_rationalize),
    MAKE_BUILTIN("floor", proc_floor),
    MAKE_BUILTIN("ceiling", proc_ceiling),
    MAKE_BUILTIN("truncate", proc_truncate),
    MAKE_BUILTIN("round", proc_round),
    MAKE_BUILTIN("inexact->exact", proc_inexact_to_exact),
    MAKE_BUILTIN("exact->inexact", proc_exact_to_inexact),
    MAKE_BUILTIN("exact?", proc_is_exact),
    MAKE_BUILTIN("inexact?", proc_is_inexact),
    MAKE_BUILTIN("<", proc_lt),
    MAKE_BUILTIN("<=", proc_lte),
    MAKE_BUILTIN(">", proc_gt),
    MAKE_BUILTIN(">=", proc_gte),
    MAKE_BUILTIN("=", proc_eq),
    MAKE_BUILTIN("zero?", proc_is_zero),
    MAKE_BUILTIN("negative?", proc_is_negative),
    MAKE_BUILTIN("positive?", proc_is_positive),
    MAKE_BUILTIN("even?", proc_is_even),
    MAKE_BUILTIN("odd?", proc_is_odd),
    MAKE_BUILTIN("max", proc_max),
    MAKE_BUILTIN("min", proc_min),
    MAKE_BUILTIN("sin", proc_sin),
    MAKE_BUILTIN("cos", proc_cos),
    MAKE_BUILTIN("tan", proc_tan),
    MAKE_BUILTIN("asin", proc_asin),
    MAKE_BUILTIN("acos", proc_acos),
    MAKE_BUILTIN("atan", proc_atan),
    MAKE_BUILTIN("exp", proc_exp),
    MAKE_BUILTIN("log", proc_log),
    MAKE_BUILTIN("make-rectangular", proc_make_rectangular),
    MAKE_BUILTIN("make-polar", proc_make_polar),
    MAKE_BUILTIN("real-part", proc_real_part),
    MAKE_BUILTIN("imag-part", proc_imag_part),
    MAKE_BUILTIN("magnitude", proc_magnitude),
    MAKE_BUILTIN("angle", proc_angle),
    MAKE_BUILTIN("complex?", proc_is_complex),
    MAKE_BUILTIN("integer?", proc_is_integer),
    MAKE_BUILTIN("rational?", proc_is_rational),
    MAKE_BUILTIN("real?", proc_is_real),
    MAKE_BUILTIN("complex?", proc_is_complex),
    MAKE_BUILTIN("number?", proc_is_number),
};

}
