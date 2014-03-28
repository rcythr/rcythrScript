// This file is part of rscript.
// rscript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rscript/builtins.h>
#include <rscript/arithmetic.h>
#include <rscript/constants.h>

using namespace std::placeholders;

namespace rscript
{

PL_SYMBOL NIL = WRAP(L_SYMBOL, "nil");
PL_BOOL TRUE = WRAP(L_BOOL, true);
PL_BOOL FALSE = WRAP(L_BOOL, false);

PL_ATOM proc_is_eq(PL_ATOM a, PL_ATOM b, SymbolTable& symbols)
{
    if(a->mType != b->mType)
        return FALSE;

    switch(a->mType)
    {
    case DataType::LIST:
        return (a == b 
                || (AS(L_LIST, a)->mAtoms.empty() && (AS(L_LIST, b)->mAtoms.empty()))) ? TRUE : FALSE;
    
    case DataType::VECTOR:
        return (a == b 
                || (AS(L_VECTOR, a)->mAtoms.empty() && (AS(L_VECTOR, b)->mAtoms.empty()))) ? TRUE : FALSE;
    
    case DataType::SYMBOL:
        return (AS(L_SYMBOL, a)->mName == AS(L_SYMBOL, b)->mName) ? TRUE : FALSE; 
    
    case DataType::BOOL:
        return (AS(L_BOOL, a)->mValue == AS(L_BOOL, b)->mValue) ? TRUE : FALSE;
    
    case DataType::CHAR:
        return (AS(L_CHAR, a)->mValue == AS(L_CHAR, b)->mValue) ? TRUE : FALSE;

    case DataType::BUILTIN_FUNCTION:
    case DataType::FUNCTION:
    case DataType::STRING:
    case DataType::INT:
    case DataType::REAL:
    case DataType::RATIONAL:
    case DataType::COMPLEX:
        return (a == b) ? TRUE : FALSE;

    default:
        break;
    }
    return FALSE;
}

PL_ATOM proc_is_eqv(PL_ATOM a, PL_ATOM b, SymbolTable& symbols)
{
    if(a->mType != b->mType) 
        return FALSE;

    switch(a->mType)
    {

    case DataType::LIST:
        return (a == b 
                || (AS(L_LIST, a)->mAtoms.empty() && (AS(L_LIST, b)->mAtoms.empty()))) ? TRUE : FALSE;
    
    case DataType::VECTOR:
        return (a == b 
                || (AS(L_VECTOR, a)->mAtoms.empty() && (AS(L_VECTOR, b)->mAtoms.empty()))) ? TRUE : FALSE;

    case DataType::BUILTIN_FUNCTION:
    case DataType::FUNCTION:
    case DataType::STRING:
        return (a == b) ? TRUE : FALSE;

    case DataType::SYMBOL:
        return (AS(L_SYMBOL, a)->mName == AS(L_SYMBOL, b)->mName) ? TRUE : FALSE; 

    case DataType::COMPLEX:
    case DataType::INT:
    case DataType::REAL:
    case DataType::RATIONAL:
        return (num_eq(a, b)) ? TRUE : FALSE;
    
    case DataType::BOOL:
        return (AS(L_BOOL, a)->mValue == AS(L_BOOL, b)->mValue) ? TRUE : FALSE;
    
    case DataType::CHAR:
        return (AS(L_CHAR, a)->mValue == AS(L_CHAR, b)->mValue) ? TRUE : FALSE;
    
    default:
        break;
    }
    return FALSE;
}

PL_ATOM proc_is_equal(PL_ATOM a, PL_ATOM b, SymbolTable& symbols)
{
    if(a->mType != b->mType)
        return FALSE;

    switch(a->mType)
    {
    case DataType::LIST:
    {
        PL_LIST a_lst = AS(L_LIST, a);
        PL_LIST b_lst = AS(L_LIST, b);

        auto a_itr = a_lst->mAtoms.begin();
        auto a_end = a_lst->mAtoms.end();

        auto b_itr = b_lst->mAtoms.begin();
        auto b_end = b_lst->mAtoms.end();

        while(a_itr != a_end && b_itr != b_end)
        {
            if(!proc_is_equal(*a_itr, *b_itr, symbols))
                return FALSE;
            ++a_itr;
            ++b_itr;
        }

        if(a_itr != a_end || b_itr != b_end)
            return FALSE;
        else
            return TRUE;

    } break;

    case DataType::VECTOR:
    {
        PL_VECTOR a_vec = AS(L_VECTOR, a);
        PL_VECTOR b_vec = AS(L_VECTOR, b);

        if(a_vec->mAtoms.size() != b_vec->mAtoms.size())
            return FALSE;

        size_t size = a_vec->mAtoms.size();
        for(size_t i=0; i < size; ++i)
        {
            if(!proc_is_equal(a_vec->mAtoms[i], b_vec->mAtoms[i], symbols))
                return FALSE;
        }
        return TRUE;

    } break;

    case DataType::BUILTIN_FUNCTION: 
    case DataType::FUNCTION:
        return (a == b) ? TRUE : FALSE;

    case DataType::SYMBOL:
        return (AS(L_SYMBOL, a)->mName == AS(L_SYMBOL, b)->mName) ? TRUE : FALSE; 

    case DataType::STRING:
        return (AS(L_STRING, a)->mValue == AS(L_STRING, b)->mValue) ? TRUE : FALSE;
    
    case DataType::COMPLEX:
    case DataType::INT:
    case DataType::REAL:
    case DataType::RATIONAL:
    case DataType::BOOL:
    case DataType::CHAR:
        return proc_is_eqv(a, b, symbols);

    default:
        break;
    }
    return FALSE;
}

PL_ATOM proc_apply(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() >= 2)
    {
        if(lst[0]->mType == DataType::BUILTIN_FUNCTION)
        {
            PL_BUILTIN_FUNCTION proc = AS(L_BUILTIN_FUNCTION, lst[0]);

            std::forward_list<PL_ATOM> result;
            auto bb = result.before_begin();

            for(size_t i=1; i < lst.size(); ++i)
            {
                std::vector<PL_ATOM> args;
               
                switch(lst[i]->mType)
                {
                case DataType::LIST:
                    for(auto& arg : AS(L_LIST, lst[i])->mAtoms)
                    {
                        args.push_back(arg);
                    }
                    break;
                case DataType::VECTOR:
                    for(auto& arg : AS(L_VECTOR, lst[i])->mAtoms)
                    {
                        args.push_back(arg);
                    }
                    break;
                default:
                    throw std::runtime_error("apply takes a procedure and at least one argument list.");
                }

                bb = result.insert_after(bb, proc->mFunc->handle(args, symbols));
            }

            return WRAP(L_LIST, std::move(result));
        }
        else if(lst[0]->mType == DataType::FUNCTION)
        {
            PL_FUNCTION proc = AS(L_FUNCTION, lst[0]);
            std::forward_list<PL_ATOM> result;
            auto bb = result.before_begin();

            for(size_t i=1; i < lst.size(); ++i)
            {
                SymbolTable st(symbols);

                switch(lst[i]->mType)
                {
                case DataType::LIST:
                {
                    auto itr = AS(L_LIST, lst[i])->mAtoms.begin();
                    auto end = AS(L_LIST, lst[i])->mAtoms.end();

                    size_t count = 0;
                    while(itr != end)
                    {
                        st.set(proc->mArgs.at(count)->mName, *itr);
                        count += 1;
                        ++itr;
                    }

                    if(count != proc->mArgs.size())
                        throw std::runtime_error("Incorrect number of arguments in apply. Expected: " + 
                                                 std::to_string(proc->mArgs.size()) + 
                                                 ", got: " + 
                                                 std::to_string(count));
                } break;

                case DataType::VECTOR:
                {
                    PL_VECTOR vec = AS(L_VECTOR, lst[i]);

                    if(vec->mAtoms.size() != proc->mArgs.size())
                        throw std::runtime_error("Incorrect number of arguments in apply. Expected: " + 
                                                 std::to_string(proc->mArgs.size()) + 
                                                 ", got: " + 
                                                 std::to_string(vec->mAtoms.size()));

                    for(size_t j=0; j < vec->mAtoms.size(); ++j)
                    {
                        st.set(proc->mArgs[j]->mName, vec->mAtoms[j]);
                    }

                } break;

                default:
                    throw std::runtime_error("apply takes a procedure and at least one argument list.");
                }

                bb = result.insert_after(bb, proc->mFunc(st));
            }

            return WRAP(L_LIST, std::move(result));
        }
    }
    throw std::runtime_error("apply takes a procedure and at least one argument list.");
}

template<typename T>
struct ContainerIterator
{
    struct IteratorConcept
    {
        virtual ~IteratorConcept() {}
        virtual T& operator*() = 0;
        virtual void next() = 0;
        virtual bool valid() = 0;
    };

    template<typename C>
    struct IteratorImpl : public IteratorConcept
    {
        typename C::iterator itr, end;
        IteratorImpl(typename C::iterator itr, typename C::iterator end) : itr(itr) , end(end) { }
        virtual T& operator*() { return *itr; }
        virtual void next() { ++itr; }
        virtual bool valid() { return itr != end; }
    };

    std::unique_ptr<IteratorConcept> impl;

    ContainerIterator(IteratorConcept* impl) : impl(impl) { }

    T& operator*() { return **impl; }

    void next() { return impl->next(); }

    bool valid() { return impl->valid(); }

};

PL_ATOM proc_map(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    if(lst.size() >= 2)
    {
        if(lst[0]->mType == DataType::BUILTIN_FUNCTION)
        {
            PL_BUILTIN_FUNCTION proc = AS(L_BUILTIN_FUNCTION, lst[0]);
            std::forward_list<PL_ATOM> result;
            auto bb = result.before_begin();


            // Construct iterators into Lists and vectors using Type Erasure.
            std::vector<ContainerIterator<PL_ATOM>> iterators;
            for(size_t i=1; i < lst.size(); ++i)
            {
                switch(lst[i]->mType)
                {
                case DataType::LIST:
                {
                    PL_LIST list = AS(L_LIST, lst[i]);
                    iterators.push_back(ContainerIterator<PL_ATOM>(
                        new typename ContainerIterator<PL_ATOM>::IteratorImpl<std::forward_list<PL_ATOM>>(list->mAtoms.begin(), list->mAtoms.end()))
                        );
                } break;

                case DataType::VECTOR:
                {
                    PL_VECTOR vec = AS(L_VECTOR, lst[i]);
                    iterators.push_back(ContainerIterator<PL_ATOM>(
                        new typename ContainerIterator<PL_ATOM>::IteratorImpl<std::vector<PL_ATOM>>(vec->mAtoms.begin(), vec->mAtoms.end()))
                        );
                } break;

                default:
                    throw std::runtime_error("map takes a procedure and at least one argument list.");
                }
            }

            bool atEnd; 
            do
            {
                atEnd = !iterators.at(0).valid();

                std::vector<PL_ATOM> args;
                for(auto& itr : iterators)
                {
                    if(atEnd != !itr.valid())
                    {
                        throw std::runtime_error("map requires that all list arguments be of the same size.");
                    }
                    else if(!atEnd)
                    {
                        args.push_back(*itr);
                        itr.next();
                    }
                }
                
                if(!atEnd)
                {
                    bb = result.insert_after(bb, proc->mFunc->handle(args, symbols));
                }
            }
            while(!atEnd);

            return WRAP(L_LIST, std::move(result));
        }
        else if(lst[0]->mType == DataType::FUNCTION)
        {
            PL_FUNCTION proc = AS(L_FUNCTION, lst[0]);
            std::forward_list<PL_ATOM> result;
            auto bb = result.before_begin();

            if(lst.size() - 1 != proc->mArgs.size())
                throw std::runtime_error("map requires N lists where N is the number of arguments supported by the given proc.");

            // Construct iterators into Lists and vectors using Type Erasure.
            std::vector<ContainerIterator<PL_ATOM>> iterators;
            for(size_t i=1; i < lst.size(); ++i)
            {
                switch(lst[i]->mType)
                {
                case DataType::LIST:
                {
                    PL_LIST list = AS(L_LIST, lst[i]);
                    iterators.push_back(ContainerIterator<PL_ATOM>(
                        new typename ContainerIterator<PL_ATOM>::IteratorImpl<std::forward_list<PL_ATOM>>(list->mAtoms.begin(), list->mAtoms.end()))
                        );
                } break;

                case DataType::VECTOR:
                {
                    PL_VECTOR vec = AS(L_VECTOR, lst[i]);
                    iterators.push_back(ContainerIterator<PL_ATOM>(
                        new typename ContainerIterator<PL_ATOM>::IteratorImpl<std::vector<PL_ATOM>>(vec->mAtoms.begin(), vec->mAtoms.end()))
                        );
                } break;

                default:
                    throw std::runtime_error("map takes a procedure and at least one argument list.");
                }
            }

            bool atEnd; 
            do
            {
                atEnd = !iterators.at(0).valid();

                SymbolTable st(symbols);

                for(size_t i=0; i < proc->mArgs.size(); ++i)
                {
                    if(atEnd != !iterators[i].valid())
                    {
                        throw std::runtime_error("map requires that all list arguments be of the same size.");
                    }
                    else if(!atEnd)
                    {
                        st.set(proc->mArgs[i]->mName, *iterators[i]);
                        iterators[i].next();
                    }
                }
                
                if(!atEnd)
                {
                    bb = result.insert_after(bb, proc->mFunc(st));
                }
            }
            while(!atEnd);
            
            return WRAP(L_LIST, std::move(result));
        }

    }
    throw std::runtime_error("map takes a procedure and at least one list.");
}

PL_ATOM proc_for_each(std::vector<PL_ATOM>& lst, SymbolTable& symbols)
{
    return proc_map(lst, symbols);
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
    MAKE_BUILTIN("eq?", 
        (std::make_shared<BuiltinHandler>("eq?")->bind<L_ATOM, L_ATOM>(std::bind(proc_is_eq, _1, _2, _3)))),
    MAKE_BUILTIN("eqv?", 
        (std::make_shared<BuiltinHandler>("eqv?")->bind<L_ATOM, L_ATOM>(std::bind(proc_is_eqv, _1, _2, _3)))),
    MAKE_BUILTIN("equal?", 
        (std::make_shared<BuiltinHandler>("equal?")->bind<L_ATOM, L_ATOM>(std::bind(proc_is_equal, _1, _2, _3)))),
    MAKE_BUILTIN("string=?", 
        (std::make_shared<BuiltinHandler>("string=?")->bind<L_STRING, L_STRING>(std::bind(proc_is_string_eq, _1, _2, _3)))),
    MAKE_BUILTIN("string-ci=?", 
        (std::make_shared<BuiltinHandler>("string-ci=?")->bind<L_STRING, L_STRING>(std::bind(proc_is_string_eq_ci, _1, _2, _3)))),
    MAKE_BUILTIN("char=?", 
        (std::make_shared<BuiltinHandler>("char=?")->bind<L_CHAR, L_CHAR>(std::bind(proc_is_char_eq, _1, _2, _3)))),
    MAKE_BUILTIN("char-ci=?", 
        (std::make_shared<BuiltinHandler>("char-ci=?")->bind<L_CHAR, L_CHAR>(std::bind(proc_is_char_eq_ci, _1, _2, _3)))),
    MAKE_BUILTIN("vector->list", 
        (std::make_shared<BuiltinHandler>("vector->list")->bind<L_VECTOR>(std::bind(proc_vector_to_list, _1, _2)))),
    MAKE_BUILTIN("list->vector", 
        (std::make_shared<BuiltinHandler>("list->vector")->bind<L_LIST>(std::bind(proc_list_to_vector, _1, _2)))),
    MAKE_BUILTIN("number->string", 
        (std::make_shared<BuiltinHandler>("number->string")->bind<L_ATOM>(std::bind(proc_number_to_string, _1, _2)))),
    MAKE_BUILTIN("string->number", 
        (std::make_shared<BuiltinHandler>("string->number")->bind<L_STRING>(std::bind(proc_string_to_number, _1, _2)))),
    MAKE_BUILTIN("symbol->string", 
        (std::make_shared<BuiltinHandler>("symbol->string")->bind<L_SYMBOL>(std::bind(proc_symbol_to_string, _1, _2)))),
    MAKE_BUILTIN("string->symbol", 
        (std::make_shared<BuiltinHandler>("string->symbol")->bind<L_STRING>(std::bind(proc_string_to_symbol, _1, _2)))),
    MAKE_BUILTIN("char->integer", 
        (std::make_shared<BuiltinHandler>("char->integer")->bind<L_CHAR>(std::bind(proc_char_to_integer, _1, _2)))),
    MAKE_BUILTIN("integer->char", 
        (std::make_shared<BuiltinHandler>("integer->char")->bind<L_INT>(std::bind(proc_integer_to_char, _1, _2)))),
    MAKE_BUILTIN("string->list", 
        (std::make_shared<BuiltinHandler>("string->list")->bind<L_STRING>(std::bind(proc_string_to_list, _1, _2)))),
    MAKE_BUILTIN("list->string", 
        (std::make_shared<BuiltinHandler>("list->string")->bind<L_LIST>(std::bind(proc_list_to_string, _1, _2)))),
    MAKE_SIMPLE_BUILTIN("string", proc_string),
    MAKE_BUILTIN("string-length", 
        (std::make_shared<BuiltinHandler>("string-length")->bind<L_STRING>(std::bind(proc_string_length, _1, _2)))),
    MAKE_BUILTIN("string-ref", 
        (std::make_shared<BuiltinHandler>("string-ref")->bind<L_STRING, L_INT>(std::bind(proc_string_ref, _1, _2, _3)))),
    MAKE_BUILTIN("string<?", 
        (std::make_shared<BuiltinHandler>("string<?")->bind<L_STRING, L_STRING>(std::bind(proc_string_lt, _1, _2, _3)))),
    MAKE_BUILTIN("string-ci<?", 
        (std::make_shared<BuiltinHandler>("string-ci<?")->bind<L_STRING, L_STRING>(std::bind(proc_string_lt_ci, _1, _2, _3)))),
    MAKE_BUILTIN("string<=?", 
        (std::make_shared<BuiltinHandler>("string<=?")->bind<L_STRING, L_STRING>(std::bind(proc_string_lte, _1, _2, _3)))),
    MAKE_BUILTIN("string-ci<=?", 
        (std::make_shared<BuiltinHandler>("string-ci<=?")->bind<L_STRING, L_STRING>(std::bind(proc_string_lte_ci, _1, _2, _3)))),
    MAKE_BUILTIN("string>?", 
        (std::make_shared<BuiltinHandler>("string>?")->bind<L_STRING, L_STRING>(std::bind(proc_string_gt, _1, _2, _3)))),
    MAKE_BUILTIN("string-ci>?", 
        (std::make_shared<BuiltinHandler>("string-ci>?")->bind<L_STRING, L_STRING>(std::bind(proc_string_gt_ci, _1, _2, _3)))),
    MAKE_BUILTIN("string>=?", 
        (std::make_shared<BuiltinHandler>("string>=?")->bind<L_STRING, L_STRING>(std::bind(proc_string_gte_ci, _1, _2, _3)))),
    MAKE_BUILTIN("string-ci>=?", 
        (std::make_shared<BuiltinHandler>("string-ci>=?")->bind<L_STRING, L_STRING>(std::bind(proc_string_gte_ci, _1, _2, _3)))),
    MAKE_BUILTIN("substring", 
        (std::make_shared<BuiltinHandler>("substring")->bind<L_STRING, L_INT, L_INT>(std::bind(proc_substring, _1, _2, _3, _4)))),
    MAKE_SIMPLE_BUILTIN("string-append", proc_string_append),
    MAKE_BUILTIN("char<?", 
        (std::make_shared<BuiltinHandler>("char<?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_lt, _1, _2, _3)))),
    MAKE_BUILTIN("char-ci<?", 
        (std::make_shared<BuiltinHandler>("char-ci<?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_lt_ci, _1, _2, _3)))),
    MAKE_BUILTIN("char<=?", 
        (std::make_shared<BuiltinHandler>("char<=?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_lte, _1, _2, _3)))),
    MAKE_BUILTIN("char-ci<=?", 
        (std::make_shared<BuiltinHandler>("char-ci<=?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_lte_ci, _1, _2, _3)))),
    MAKE_BUILTIN("char>?", 
        (std::make_shared<BuiltinHandler>("char>?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_gt, _1, _2, _3)))),
    MAKE_BUILTIN("char-ci>?", 
        (std::make_shared<BuiltinHandler>("char-ci>?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_gt_ci, _1, _2, _3)))),
    MAKE_BUILTIN("char>=?", 
        (std::make_shared<BuiltinHandler>("char>=?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_gte, _1, _2, _3)))),
    MAKE_BUILTIN("char-ci>=?", 
        (std::make_shared<BuiltinHandler>("char-ci>=?")->bind<L_CHAR, L_CHAR>(std::bind(proc_char_gte_ci, _1, _2, _3)))),
    MAKE_BUILTIN("char-alphabetic?", 
        (std::make_shared<BuiltinHandler>("char-alphabetic?")->bind<L_CHAR>(std::bind(proc_is_char_alphabetic, _1, _2)))),
    MAKE_BUILTIN("char-numeric?", 
        (std::make_shared<BuiltinHandler>("char-numeric?")->bind<L_CHAR>(std::bind(proc_is_char_numeric, _1, _2)))),
    MAKE_BUILTIN("char-whitespace?", 
        (std::make_shared<BuiltinHandler>("char-whitespace?")->bind<L_CHAR>(std::bind(proc_is_char_whitespace, _1, _2)))),
    MAKE_BUILTIN("char-upper-case?", 
        (std::make_shared<BuiltinHandler>("char-upper-case?")->bind<L_CHAR>(std::bind(proc_is_char_uppercase, _1, _2)))),
    MAKE_BUILTIN("char-lower-case?", 
        (std::make_shared<BuiltinHandler>("char-lower-case?")->bind<L_CHAR>(std::bind(proc_is_char_lowercase, _1, _2)))),
    MAKE_BUILTIN("char-upcase", 
        (std::make_shared<BuiltinHandler>("char-upcase")->bind<L_CHAR>(std::bind(proc_char_upcase, _1, _2)))),
    MAKE_BUILTIN("char-downcase", 
        (std::make_shared<BuiltinHandler>("char-downcase")->bind<L_CHAR>(std::bind(proc_char_downcase, _1, _2)))),
    MAKE_SIMPLE_BUILTIN("vector-length", proc_vector_length),
    MAKE_SIMPLE_BUILTIN("vector-ref", proc_vector_ref),
    MAKE_SIMPLE_BUILTIN("pair?", proc_is_pair),
    MAKE_SIMPLE_BUILTIN("cons", proc_cons),
    MAKE_SIMPLE_BUILTIN("car", proc_car),
    MAKE_SIMPLE_BUILTIN("cdr", proc_cdr),
    MAKE_SIMPLE_BUILTIN("null?", proc_is_null),
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
    MAKE_SIMPLE_BUILTIN("apply", proc_apply),
    MAKE_SIMPLE_BUILTIN("map", proc_map),
    MAKE_SIMPLE_BUILTIN("for-each", proc_for_each),
    MAKE_BUILTIN("not", 
        (std::make_shared<BuiltinHandler>("not")->bind<L_BOOL>(std::bind(proc_not, _1, _2)))),
    MAKE_SIMPLE_BUILTIN("+", proc_add),
    MAKE_SIMPLE_BUILTIN("-", proc_substract),
    MAKE_SIMPLE_BUILTIN("*", proc_multiply),
    MAKE_SIMPLE_BUILTIN("/", proc_divide),
    MAKE_SIMPLE_BUILTIN("abs", proc_abs),
    MAKE_BUILTIN("quotient", 
        (std::make_shared<BuiltinHandler>("quotient")->bind<L_INT, L_INT>(std::bind(proc_quotient, _1, _2, _3)))),
    MAKE_BUILTIN("remainder", 
        (std::make_shared<BuiltinHandler>("remainder")->bind<L_INT, L_INT>(std::bind(proc_remainder, _1, _2, _3)))),
    MAKE_BUILTIN("modulo", 
        (std::make_shared<BuiltinHandler>("modulo")->bind<L_INT, L_INT>(std::bind(proc_modulo, _1, _2, _3)))),
    MAKE_BUILTIN("gcd", 
        (std::make_shared<BuiltinHandler>("gcd")->bind<L_INT, L_INT>(std::bind(proc_gcd, _1, _2, _3)))),
    MAKE_BUILTIN("lcm", 
        (std::make_shared<BuiltinHandler>("lcm")->bind<L_INT, L_INT>(std::bind(proc_lcm, _1, _2, _3)))),
    MAKE_SIMPLE_BUILTIN("expt", proc_expt),
    MAKE_SIMPLE_BUILTIN("sqrt", proc_sqrt),
    MAKE_BUILTIN("numerator", 
        (std::make_shared<BuiltinHandler>("numerator")->bind<L_RATIONAL>(std::bind(proc_numerator, _1, _2)))),
    MAKE_BUILTIN("denominator", 
        (std::make_shared<BuiltinHandler>("denominator")->bind<L_RATIONAL>(std::bind(proc_denominator, _1, _2)))),
    MAKE_BUILTIN("simplest", 
        (std::make_shared<BuiltinHandler>("simplest")->bind<L_RATIONAL>(std::bind(proc_simplest, _1, _2)))),
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
    MAKE_BUILTIN("even?", 
        (std::make_shared<BuiltinHandler>("even?")->bind<L_INT>(std::bind(proc_is_even, _1, _2)))),
    MAKE_BUILTIN("odd?", 
        (std::make_shared<BuiltinHandler>("odd?")->bind<L_INT>(std::bind(proc_is_odd, _1, _2)))),
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
    MAKE_BUILTIN("boolean?", 
        (std::make_shared<BuiltinHandler>("boolean?")->bind<L_ATOM>(std::bind(proc_is_bool, _1, _2)))),
    MAKE_BUILTIN("char?", 
        (std::make_shared<BuiltinHandler>("char?")->bind<L_ATOM>(std::bind(proc_is_char, _1, _2)))),
    MAKE_BUILTIN("complex?", 
        (std::make_shared<BuiltinHandler>("complex?")->bind<L_ATOM>(std::bind(proc_is_complex, _1, _2)))),
    MAKE_BUILTIN("integer?", 
        (std::make_shared<BuiltinHandler>("integer?")->bind<L_ATOM>(std::bind(proc_is_integer, _1, _2)))),
    MAKE_BUILTIN("list?", 
        (std::make_shared<BuiltinHandler>("list?")->bind<L_ATOM>(std::bind(proc_is_list, _1, _2)))),
    MAKE_BUILTIN("number?", 
        (std::make_shared<BuiltinHandler>("number?")->bind<L_ATOM>(std::bind(proc_is_number, _1, _2)))),
    MAKE_BUILTIN("procedure?", 
        (std::make_shared<BuiltinHandler>("procedure?")->bind<L_ATOM>(std::bind(proc_is_procedure, _1, _2)))),
    MAKE_BUILTIN("rational?", 
        (std::make_shared<BuiltinHandler>("rational?")->bind<L_ATOM>(std::bind(proc_is_rational, _1, _2)))),
    MAKE_BUILTIN("real?", 
        (std::make_shared<BuiltinHandler>("real?")->bind<L_ATOM>(std::bind(proc_is_real, _1, _2)))),
    MAKE_BUILTIN("string?", 
        (std::make_shared<BuiltinHandler>("string?")->bind<L_ATOM>(std::bind(proc_is_string, _1, _2)))),
    MAKE_BUILTIN("symbol?", 
        (std::make_shared<BuiltinHandler>("symbol?")->bind<L_ATOM>(std::bind(proc_is_symbol, _1, _2)))),
    MAKE_BUILTIN("vector?", 
        (std::make_shared<BuiltinHandler>("vector?")->bind<L_ATOM>(std::bind(proc_is_vector, _1, _2)))),
};

}
