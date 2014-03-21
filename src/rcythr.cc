// This file is part of rcythrScript.
// rcythrScript is licensed under the MIT LICENSE. For more info see the LICENSE file.

#include <rcythrScript/rcythr.h>
#include <rcythrScript/builtins.h>
#include <rcythrScript/constants.h>

using namespace rcythr;

namespace rcythr
{

PL_ATOM evaluate(PL_ATOM expr, SymbolTableType& globalSymbolTable, SymbolTableType& localSymbolTable)
{
    switch(expr->mType)
    {
    case DataType::VECTOR:
    case DataType::LITERAL:
    case DataType::CHAR:
    case DataType::RATIONAL:
    case DataType::COMPLEX:
    case DataType::REAL:
    case DataType::INT:
    case DataType::STRING:
    case DataType::BUILTIN_FUNCTION:
    case DataType::FUNCTION:
    case DataType::BOOL:
    {
        return expr;
    } break;

    case DataType::SYMBOL:
    {
        PL_SYMBOL symbol = std::static_pointer_cast<L_SYMBOL>(expr);

        auto builtin_itr = builtins.find(symbol->mName);
        if(builtin_itr != builtins.end())
        {
            return builtin_itr->second;
        }

        auto local_itr = localSymbolTable.find(symbol->mName);
        if(local_itr != localSymbolTable.end())
        {
            return local_itr->second;
        }

        auto global_itr = globalSymbolTable.find(symbol->mName);
        if(global_itr != globalSymbolTable.end())
        {
            return global_itr->second;
        }

        throw std::runtime_error("Unable to locate value for symbol: "+symbol->mName);

    } break;

    case DataType::LIST:
    {
        PL_LIST lst = std::static_pointer_cast<L_LIST>(expr);
        if(!lst->mAtoms.empty())
        {
            if(lst->mAtoms.front()->mType == DataType::SYMBOL)
            {
                auto forms_itr = forms.find(AS(L_SYMBOL, lst->mAtoms.front())->mName);
                if(forms_itr != forms.end())
                {
                    return forms_itr->second(lst, globalSymbolTable, localSymbolTable);
                }
            }

            auto itr = lst->mAtoms.begin();
            auto end = lst->mAtoms.end();
            PL_ATOM first = evaluate(*itr, globalSymbolTable, localSymbolTable);
            ++itr;

            switch(first->mType)
            {

            case DataType::BUILTIN_FUNCTION:
            {
                std::vector<PL_ATOM> args;
                while(itr != end)
                {
                    args.push_back(evaluate(*itr, globalSymbolTable, localSymbolTable));
                    ++itr;
                }
                return AS(L_BUILTIN_FUNCTION, first)->mFunc(args, globalSymbolTable, localSymbolTable);
            } break;

            case DataType::FUNCTION:
            {
                PL_FUNCTION func = AS(L_FUNCTION, first);

                SymbolTableType newLocals = localSymbolTable;

                size_t count = 0;
                while(itr != end)
                {
                    newLocals[func->mArgs.at(count)->mName] = evaluate(*itr, globalSymbolTable, localSymbolTable);
                    count += 1;
                    ++itr;
                }

                if(count != func->mArgs.size())
                    throw std::runtime_error("Incorrect number of arguments. Expected: "+std::to_string(func->mArgs.size())+", got: "+std::to_string(count));

                return func->mFunc(globalSymbolTable, newLocals);

            } break;

            default:
            {
                std::forward_list<PL_ATOM> ret;
                auto bb = ret.before_begin();
                bb = ret.insert_after(bb, first);
                while(itr != end)
                {
                    bb = ret.insert_after(bb, evaluate(*itr, globalSymbolTable, localSymbolTable));
                    ++itr;
                }
                return WRAP(L_LIST, ret);

            } break;
            }
        }
        return lst;

    } break;

    }

    return expr;
}

PL_ATOM evaluate(PL_ATOM expr)
{
    SymbolTableType global;
    SymbolTableType local;
    return evaluate(expr, global, local);
}

PL_ATOM parseExpression(const std::string& input, size_t& offset)
{
    size_t lookahead = offset;
    while(true)
    {
        switch(input.at(lookahead))
        {

        // White space
        case ' ':
        case '\r':
        case '\n':
        case '\t':
            offset = lookahead;
            break;

        // Line comment
        case ';':
            while(input.at(lookahead) != '\n')
                ++lookahead;
            offset = lookahead;
            break;

        case '\'':
            ++offset;
            return WRAP(L_LITERAL, parseExpression(input, offset));
            break;

        // String
        case '"':
            return parseString(input, offset);

        // List
        case '(':
        case '[':
            return parseList(input, offset);

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return parseNumeric(input, offset);

        // Indeterminate. Could be numeric or special symbol.
        case '+':
        case '-':
        {
            ++lookahead;
            if(lookahead < input.size())
            {
                char c = input.at(lookahead);
                if(c >= '0' && c <= '9')
                {
                    return parseNumeric(input, offset);
                }
            }
            return parseSymbol(input, offset);
        } break;

        // Evil. Could be: Bool, Vector, Bytevector, Nesting comment, Numeric, or Char.
        case '#':
        {
            ++lookahead;
            switch(input.at(lookahead))
            {

            //  Vector
            case '(':
            case '[':
                return parseVector(input, offset);

            // Bool
            case 't':
            case 'T':
            case 'f':
            case 'F':
                return parseBool(input, offset);

            // Numeric
            case 'I':
            case 'i':
            case 'e':
            case 'E':
                return parseNumeric(input, offset);

            // Char
            case '\\':
                return parseChar(input, offset);

            // Nesting Comment
            case '|':
            {
                size_t nesting = 1;
                char c;
                while(true)
                {
                    if(nesting == 0)
                        break;

                    c = input.at(lookahead++);
                    if(c == '#')
                    {
                        if(input.at(lookahead++) == '|')
                            nesting += 1;
                    }
                    else if(c == '|')
                    {
                        if(input.at(lookahead++) == '#')
                            nesting -= 1;
                    }
                }
            } break;

            }
        } break;

        // Symbol or error
        default:
        {
            char c = input[lookahead];
            if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '$' && c <= '&') ||
                (c >= '<' && c <= '?') ||  c == '!' || c == '*'  ||  c == '/' || c == ':'  ||
                 c == '^' || c == '_'  ||  c == '~')
            {
                return parseSymbol(input, offset);
            }
            throw std::runtime_error(std::string("Unrecognized character: ")+c);
        } break;

        }
        ++lookahead;
    }
}

PL_ATOM deepCopy(PL_ATOM expr)
{
    throw std::runtime_error("Deepcopy NYI");
}

}
