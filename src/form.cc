// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rcythrScript/builtins.h>
#include <rcythrScript/constants.h>

namespace rcythr
{

std::unordered_map<std::string,std::function<PL_ATOM(PL_ATOM,SymbolTable&)>> forms =
{
    { "define", form_define },
    { "lambda", form_lambda },
    { "if", form_if },
    { "begin", form_begin },
    { "define-syntax", form_define_syntax},
    { "set!", form_set_exclaim }
};

PL_ATOM form_define(PL_ATOM lst, SymbolTable& symbols)
{
    std::array<PL_ATOM, 3> args;
    if(lst->mType == DataType::LIST)
    {
        PL_LIST list = AS(L_LIST, lst);
        extractArgs(args, list, "define form");
    }
    else if(lst->mType == DataType::VECTOR)
    {
        PL_VECTOR vector = AS(L_VECTOR, lst);
        extractArgs(args, vector, "define form");
    }
    else
        throw std::runtime_error("Input to define must be either a list or a vector.");

    std::string func_name;
    std::vector<PL_SYMBOL> params;
    if(args[1]->mType == DataType::SYMBOL)
    {
        // Variable definition
        symbols.set_global( AS(L_SYMBOL, args[1])->mName, evaluate(args[2], symbols));
        return NIL;
    }
    else if(args[1]->mType == DataType::LIST)
    {
        PL_LIST container = AS(L_LIST, args[1]);
        auto itr = container->mAtoms.begin();
        auto end = container->mAtoms.end();

        PL_ATOM first = *itr;
        if(first->mType != DataType::SYMBOL)
            throw std::runtime_error("Second argument to define takes either symbol or list of symbols.");

        func_name = AS(L_SYMBOL, first)->mName;
        ++itr;

        // Function definition
        while(itr != end)
        {
            auto param = *itr;

            if(param->mType != DataType::SYMBOL)
                throw std::runtime_error("Second argument to define takes either symbol or list of symbols.");
            params.push_back(AS(L_SYMBOL, param));

            ++itr;
        }
    }
    else if(args[1]->mType == DataType::VECTOR)
    {
        PL_VECTOR container = AS(L_VECTOR, args[1]);
        auto itr = container->mAtoms.begin();
        auto end = container->mAtoms.end();

        PL_ATOM first = *itr;
        if(first->mType != DataType::SYMBOL)
            throw std::runtime_error("Second argument to define takes either symbol or list of symbols.");

        func_name = AS(L_SYMBOL, first)->mName;
        ++itr;

        // Function definition
        while(itr != end)
        {
            auto param = *itr;

            if(param->mType != DataType::SYMBOL)
                throw std::runtime_error("Second argument to define takes either symbol or list of symbols.");
            params.push_back(AS(L_SYMBOL, param));

            ++itr;
        }
    }
    else
    {
        throw std::runtime_error("First argument to define form must be either a symbol or list of symbols.");
    }

    UserFunctionType func = std::bind((PL_ATOM (*)(PL_ATOM,SymbolTable&))evaluate, args[2], std::placeholders::_1);

    symbols.set_global(func_name, WRAP(L_FUNCTION, params, func));

    return NIL;
}

PL_ATOM form_lambda(PL_ATOM lst, SymbolTable& symbols)
{
    std::array<PL_ATOM, 3> args;
    if(lst->mType == DataType::LIST)
    {
        PL_LIST list = AS(L_LIST, lst);
        extractArgs(args, list, "define form");
    }
    else if(lst->mType == DataType::VECTOR)
    {
        PL_VECTOR vector = AS(L_VECTOR, lst);
        extractArgs(args, vector, "define form");
    }
    else
        throw std::runtime_error("Input to define must be either a list or a vector.");

    std::string func_name;
    std::vector<PL_SYMBOL> params;
    if(args[1]->mType == DataType::SYMBOL)
    {
        // Variable definition
        symbols.set_global( AS(L_SYMBOL, args[1])->mName, evaluate(args[2], symbols));
        return NIL;
    }
    else if(args[1]->mType == DataType::LIST)
    {
        PL_LIST container = AS(L_LIST, args[1]);
        auto itr = container->mAtoms.begin();
        auto end = container->mAtoms.end();

        // Function definition
        while(itr != end)
        {
            auto param = *itr;

            if(param->mType != DataType::SYMBOL)
                throw std::runtime_error("Second argument to define takes either symbol or list of symbols.");
            params.push_back(AS(L_SYMBOL, param));

            ++itr;
        }
    }
    else if(args[1]->mType == DataType::VECTOR)
    {
        PL_VECTOR container = AS(L_VECTOR, args[1]);
        auto itr = container->mAtoms.begin();
        auto end = container->mAtoms.end();

        // Function definition
        while(itr != end)
        {
            auto param = *itr;

            if(param->mType != DataType::SYMBOL)
                throw std::runtime_error("Second argument to define takes either symbol or list of symbols.");
            params.push_back(AS(L_SYMBOL, param));

            ++itr;
        }
    }
    else
    {
        throw std::runtime_error("First argument to define form must be either a symbol or list of symbols.");
    }

    UserFunctionType func = std::bind((PL_ATOM (*)(PL_ATOM,SymbolTable&))evaluate, args[2], std::placeholders::_1);

    return WRAP(L_FUNCTION, params, func);
}

PL_ATOM form_if(PL_ATOM lst, SymbolTable& symbols)
{
    std::array<PL_ATOM, 4> args;

    if(lst->mType == DataType::LIST)
    {
        PL_LIST list = AS(L_LIST, lst);
        extractArgs(args, list, "if");
    }
    else if(lst->mType == DataType::VECTOR)
    {
        PL_VECTOR vector = AS(L_VECTOR, lst);
        extractArgs(args, vector, "if");
    }
    else
        throw std::runtime_error("if expected list or vector.");

    PL_ATOM cnd = evaluate(args[1], symbols);
    if(cnd->mType == DataType::BOOL)
    {
        if(AS(L_BOOL, cnd)->mValue)
        {
            return evaluate(args[2], symbols);
        }
        else
        {
            return evaluate(args[3], symbols);
        }
    }
    throw std::runtime_error("Condition of if statement must be boolean.");
}

PL_ATOM form_begin(PL_ATOM lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_define_syntax(PL_ATOM lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

PL_ATOM form_set_exclaim(PL_ATOM lst, SymbolTable& symbols)
{
    throw std::runtime_error(std::string(__FUNCTION__) +  " Not Yet Implemented.");
}

}
