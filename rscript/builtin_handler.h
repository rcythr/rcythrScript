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

struct BuiltinHandler : public BuiltinHandlerInterface
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
    std::map<std::vector<DataType>, BuiltinHandlerInterface*> handlers;
    std::function<PL_ATOM(std::vector<PL_ATOM>&, SymbolTable&)> default_handler;

public:

    BuiltinHandler(std::string name);

    BuiltinHandler(std::string name, std::function<PL_ATOM(std::vector<PL_ATOM>&, SymbolTable&)> func);

    ~BuiltinHandler();

    template<typename A>
    void bind(std::function<PL_ATOM(std::shared_ptr<A>, SymbolTable&)> func)
    {
        std::vector<DataType> key({A::type_value});
        auto lb = handlers.lower_bound(key);
        if(lb != handlers.end() && !(handlers.key_comp()(key, lb->first)))
        {
            delete lb->second;
            lb->second = new HandleWrap1<A>(func);
        }
        else
        {
            handlers.insert(std::make_pair(std::move(key), new HandleWrap1<A>(func)));
        }
    }

    template<typename A, typename B>
    void bind(std::function<PL_ATOM(std::shared_ptr<A>, std::shared_ptr<B>, SymbolTable&)> func)
    {
        std::vector<DataType> key({A::type_value, B::type_value});
        auto lb = handlers.lower_bound(key);
        if(lb != handlers.end() && !(handlers.key_comp()(key, lb->first)))
        {
            delete lb->second;
            lb->second = new HandleWrap2<A, B>(func);
        }
        else
        {
            handlers.insert(std::make_pair(std::move(key), new HandleWrap2<A, B>(func)));
        }
    }
    
    template<typename A, typename B, typename C>
    void bind(std::function<PL_ATOM(std::shared_ptr<A>, std::shared_ptr<B>, std::shared_ptr<C>, SymbolTable&)> func)
    {
        std::vector<DataType> key({A::type_value, B::type_value, C::type_value});
        auto lb = handlers.lower_bound(key);
        if(lb != handlers.end() && !(handlers.key_comp()(key, lb->first)))
        {
            delete lb->second;
            lb->second = new HandleWrap3<A, B, C>(func);
        }
        else
        {
            handlers.insert(std::make_pair(std::move(key), new HandleWrap3<A, B, C>(func)));
        }
    }

    PL_ATOM handle(std::vector<PL_ATOM>& args, SymbolTable& symbols);
};

}
