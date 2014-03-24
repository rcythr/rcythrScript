
#include <rscript/symbol_table.h>

using namespace rscript;

SymbolTable::SymbolTable()
    : next(nullptr)
{
}

SymbolTable::SymbolTable(SymbolTable& next)
    : next(&next)
{
}

void SymbolTable::set(std::string key, PL_ATOM value)
{
    auto lb = lookup.insert(std::make_pair(key, value));
    if(!lb.second)
    {
        lb.first->second = value;
    }
}

void SymbolTable::set_global(std::string key, PL_ATOM value)
{
    get_global_table()->set(key, value);
}

PL_ATOM SymbolTable::get(std::string key)
{
    auto find_itr = lookup.find(key);
    if(find_itr != lookup.end())
    {
        return find_itr->second;
    }
    return (next != nullptr) ? next->get(key) : nullptr;
}

PL_ATOM SymbolTable::get_global(std::string key)
{
    return get_global_table()->get(key);
}

void SymbolTable::clear()
{
    lookup.clear();
}

SymbolTable* SymbolTable::get_global_table()
{
    if(next == nullptr)
        return this;
    else
        return next;
}
