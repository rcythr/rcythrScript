#pragma once

#include <rscript/datatypes/atom.h>
#include <rscript/symbol_table.h>
#include <rscript/constants.h>

#include <map>
#include <string>
#include <functional>
#include <vector>

namespace rscript
{

struct BuiltinHandlerInterface
{
    virtual ~BuiltinHandlerInterface() {}
    virtual PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols) = 0;
};

struct SimpleBuiltinHandler : public BuiltinHandlerInterface
{
private:
    typedef std::function<PL_ATOM(std::vector<PL_ATOM>&, SymbolTable&)> FunctionType;
    FunctionType func;

public:

    SimpleBuiltinHandler(FunctionType func)
        : func(func)
    {
    }

    PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols)
    {
        return func(args, symbols);
    }

};

struct BuiltinHandler : public BuiltinHandlerInterface, public std::enable_shared_from_this<BuiltinHandler>
{
private:

    template<typename A>
    struct HandleWrap1 : public BuiltinHandlerInterface
    {
        typedef std::function<PL_ATOM(std::shared_ptr<A>, SymbolTable&)> FuncType;
        FuncType func;
        
        HandleWrap1(FuncType f) : func(f) {}

        PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols)
        {
            return func(AS(A, args.at(0)), symbols);
        }
    };

    template<typename A, typename B>
    struct HandleWrap2 : public BuiltinHandlerInterface
    {
        typedef std::function<PL_ATOM(std::shared_ptr<A>, std::shared_ptr<B>, SymbolTable&)> FuncType;
        FuncType func;

        HandleWrap2(FuncType f) : func(f) {}

        PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols)
        {
            return func(AS(A, args.at(0)), AS(B, args.at(1)), symbols);
        }
    };

    template<typename A, typename B, typename C>
    struct HandleWrap3 : public BuiltinHandlerInterface
    {
        typedef std::function<PL_ATOM(std::shared_ptr<A>, std::shared_ptr<B>, std::shared_ptr<C>)> FuncType;
        FuncType func;

        HandleWrap3(FuncType f) : func(f) {}

        PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols)
        {
            return func(AS(A, args.at(0)), AS(B, args.at(1)), AS(C, args.at(2)), symbols);
        }
    };

    std::string name;
    std::vector<std::pair<std::vector<DataType>, BuiltinHandlerInterface*>> handlers;
    std::function<PL_ATOM(std::vector<PL_ATOM>&, SymbolTable&)> default_handler;

public:

    BuiltinHandler(std::string name);

    BuiltinHandler(std::string name, std::function<PL_ATOM(std::vector<PL_ATOM>&, SymbolTable&)> func);

    ~BuiltinHandler();

    template<typename A>
    std::shared_ptr<BuiltinHandler> bind(std::function<PL_ATOM(std::shared_ptr<A>, SymbolTable&)> func)
    {
        std::vector<DataType> key;
        key.push_back(A::type_value);
        handlers.push_back(std::make_pair(std::move(key), new HandleWrap1<A>(func)));
        return shared_from_this();
    }

    template<typename A, typename B>
    std::shared_ptr<BuiltinHandler> bind(std::function<PL_ATOM(std::shared_ptr<A>, std::shared_ptr<B>, SymbolTable&)> func)
    {
        std::vector<DataType> key;
        key.push_back(A::type_value);
        key.push_back(B::type_value);
        handlers.push_back(std::make_pair(std::move(key), new HandleWrap2<A, B>(func)));
        return shared_from_this();
    }
    
    template<typename A, typename B, typename C>
    std::shared_ptr<BuiltinHandler> bind(std::function<PL_ATOM(std::shared_ptr<A>, std::shared_ptr<B>, std::shared_ptr<C>, SymbolTable&)> func)
    {
        std::vector<DataType> key;

        key.push_back(A::type_value);
        key.push_back(B::type_value);
        key.push_back(C::type_value);
        handlers.push_back(std::make_pair(std::move(key), new HandleWrap3<A, B, C>(func)));
        return shared_from_this();
    }

    PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols);
};

}
