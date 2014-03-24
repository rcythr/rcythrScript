// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#pragma once

#include <rscript/rscript.h>
#include <memory>


namespace rscript
{
    extern std::unordered_map<std::string,std::function<PL_ATOM(PL_ATOM,SymbolTable&)>> forms;
    extern std::unordered_map<std::string,PL_BUILTIN_FUNCTION> builtins;

    template<size_t cnt, size_t mincnt=cnt>
    inline void extractArgs(std::array<PL_ATOM, cnt>& args, PL_LIST& lst, const char* name)
    {
        auto itr = lst->mAtoms.begin();
        auto end = lst->mAtoms.end();

        size_t i=0;
        while(itr != end)
        {
            if(i >= cnt)
                break;

            args[i] = *itr;
            ++itr;
            ++i;
        }

        if((i < mincnt) || (i > cnt))
        {
            throw std::runtime_error(std::string(name)+" requires "+std::to_string(cnt)+" parameters, found "+std::to_string(i));
        }
    }

    template<size_t cnt, size_t mincnt=cnt>
    inline void extractArgs(std::array<PL_ATOM, cnt>& args, PL_VECTOR& lst, const char* name)
    {
        size_t len = lst->mAtoms.size();
        if((len < mincnt) || (len > cnt))
        {
            throw std::runtime_error(std::string(name)+" requires "+std::to_string(cnt)+" parameters, found "+std::to_string(len));
        }

        for(size_t i=0; i < len; ++i)
        {
            args[i] = lst->mAtoms[i];
        }
    }

    // FORMS
    PL_ATOM form_define(PL_ATOM lst, SymbolTable& symbols);
    PL_ATOM form_lambda(PL_ATOM lst, SymbolTable& symbols);
    PL_ATOM form_if(PL_ATOM lst, SymbolTable& symbols);
    PL_ATOM form_begin(PL_ATOM lst, SymbolTable& symbols);
    PL_ATOM form_define_syntax(PL_ATOM lst, SymbolTable& symbols);
    PL_ATOM form_set_exclaim(PL_ATOM lst, SymbolTable& symbols);

    // Construction
    PL_ATOM proc_vector(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_make_vector(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_make_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_list(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Equivalence
    PL_ATOM proc_is_eq(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_eqv(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_equal(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_string_eq(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_string_eq_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_eq(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_eq_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Type Conversion
    PL_ATOM proc_vector_to_list(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_list_to_vector(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_number_to_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_to_number(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_symbol_to_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_to_symbol(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_to_integer(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_integer_to_char(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_to_list(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_list_to_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Strings
    PL_ATOM proc_is_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_length(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_ref(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_set_exclaim(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_lt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_lt_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_gt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_gt_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_lte(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_lte_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_gte(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_gte_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_substring(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_append(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_copy(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_string_fill_exclaim(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Characters
    PL_ATOM proc_is_char(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_lt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_lt_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_gt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_gt_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_lte(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_lte_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_gte(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_gte_ci(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_alphabetic(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_numeric(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_whitespace(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_uppercase(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_lowercase(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_upcase(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_char_downcase(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Vectors
    PL_ATOM proc_is_vector(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_vector_length(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_vector_ref(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_vector_set_exclaim(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_vector_fill_exclaim(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Symbols
    PL_ATOM proc_is_symbol(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Pairs/Lists
    PL_ATOM proc_is_pair(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_cons(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_car(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_cdr(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_set_car_exclaim(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_set_cdr_exclaim(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_null(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_list(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_length(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_append(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_reverse(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_list_tail(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_list_ref(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_memq(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_memv(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_member(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_assq(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_assv(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_assoc(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Continuations
    PL_ATOM proc_call_cc(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_values(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_call_with_values(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_dynamic_wind(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Environments
    PL_ATOM proc_eval(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_report_environment(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_null_environment(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_interaction_environment(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Input/Output
    PL_ATOM proc_display(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_newline(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_read(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_write(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_read_char(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_write_char(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_peek_char(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_char_ready(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_eof_object(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_open_input_file(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_open_output_file(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_close_input_port(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_close_output_port(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_input_port(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_output_port(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_current_input_port(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_current_output_port(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_call_with_input_file(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_call_with_output_file(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_with_input_file(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_with_output_file(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // System Interface
    PL_ATOM proc_load(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_transcript_on(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_transcript_off(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Functional programming
    PL_ATOM proc_is_procedure(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_apply(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_map(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_for_each(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Boolean
    PL_ATOM proc_is_bool(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_not(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Basic Arithmetic
    PL_ATOM proc_add(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_substract(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_multiply(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_divide(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_abs(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_quotient(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_remainder(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_modulo(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_gcd(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_lcm(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_expt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_sqrt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Rational
    PL_ATOM proc_numerator(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_denominator(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_rational(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_simplest(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Approximation
    PL_ATOM proc_rationalize(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_floor(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_ceiling(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_truncate(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_round(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Exactness
    PL_ATOM proc_inexact_to_exact(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_exact_to_inexact(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_exact(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_inexact(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Inequality
    PL_ATOM proc_lt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_lte(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_gt(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_gte(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_eq(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Misc predicates
    PL_ATOM proc_is_zero(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_negative(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_positive(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_odd(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_even(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Misc Func
    PL_ATOM proc_max(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_min(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Trig
    PL_ATOM proc_sin(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_cos(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_tan(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_asin(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_acos(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_atan(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Exponents
    PL_ATOM proc_exp(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_log(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    // Complex
    PL_ATOM proc_make_rectangular(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_make_polar(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_real_part(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_imag_part(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_magnitude(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_angle(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_complex(std::vector<PL_ATOM>& lst, SymbolTable& symbols);

    //Type Predicates
    PL_ATOM proc_is_integer(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_real(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
    PL_ATOM proc_is_number(std::vector<PL_ATOM>& lst, SymbolTable& symbols);
}
