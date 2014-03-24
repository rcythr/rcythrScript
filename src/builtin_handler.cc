
#include <rscript/builtin_handler.h>

#include <sstream>

using namespace rscript;

BuiltinHandler::BuiltinHandler(std::string name) 
    : name(name)
    , default_handler(nullptr) 
{
}

BuiltinHandler::BuiltinHandler(std::string name, std::function<PL_ATOM(std::vector<PL_ATOM>&, SymbolTable&)> func) 
    : name(name)
    , default_handler(func) 
{
}

BuiltinHandler::~BuiltinHandler()
{
    for(auto& binding : handlers)
    {
        delete binding.second;
    }
}

PL_ATOM BuiltinHandler::handle(std::vector<PL_ATOM>& args, SymbolTable& symbols)
{
    std::vector<DataType> key;
    for(size_t i=0; i < args.size(); ++i)
    {
        key.push_back(args[i]->mType);
    }

    auto find_itr = handlers.find(key);
    if(find_itr != handlers.end())
    {
        return find_itr->second->handle(args, symbols);
    }
    else if(default_handler != nullptr)
    {
        return default_handler(args, symbols);
    }

    std::stringstream input_args;
    for(DataType d : key)
    {
        input_args << TYPE_NAME_LOOKUP[(int)d];
        input_args << " ";
    }

    throw std::runtime_error(name + " has no overload which takes arguments ( " + input_args.str() + "). ");

    return nullptr;
}
