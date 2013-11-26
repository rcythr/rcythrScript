// Copyright (c) 2013 Richard Laughlin
// All Rights Reserved

#include "lisp.h"
#include "builtins.h"
#include <iostream>
#include <fstream>

using namespace rcythr;

namespace rcythr
{

PL_ATOM evaluate(PL_ATOM expr, SymbolTableType& globalSymbolTable, SymbolTableType& localSymbolTable)
{
    switch(expr->mType)
    {
    case LispType::VECTOR:
    case LispType::LITERAL:
    case LispType::CHAR:
    case LispType::RATIONAL:
    case LispType::COMPLEX:
    case LispType::REAL:
    case LispType::INT:
    case LispType::STRING:
    case LispType::BUILTIN_FUNCTION:
    case LispType::FUNCTION:
    case LispType::BOOL:
    {
        return expr;
    } break;

    case LispType::SYMBOL:
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

    case LispType::LIST:
    {
        PL_LIST lst = std::static_pointer_cast<L_LIST>(expr);
        if(!lst->mAtoms.empty())
        {
            if(lst->mAtoms.front()->mType == LispType::SYMBOL)
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

            case LispType::BUILTIN_FUNCTION:
            {
                std::vector<PL_ATOM> args;
                while(itr != end)
                {
                    args.push_back(evaluate(*itr, globalSymbolTable, localSymbolTable));
                    ++itr;
                }
                return AS(L_BUILTIN_FUNCTION, first)->mFunc(args, globalSymbolTable, localSymbolTable);
            } break;

            case LispType::FUNCTION:
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

#define UNEXPECTED_TOKEN(A, B) throw std::runtime_error(std::string("Unexpected token: ")+A+", Expected"+B)
#define EXPECT_CHAR(A, B) if(A != B) UNEXPECTED_TOKEN(A, B)
#define VALIDATE_LENGTH(A, B) if(A >= B) throw std::runtime_error("PARSE ERROR: UNEXPECTED EOF.")
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

PL_ATOM parseBool(const std::string& input, size_t& offset)
{
    EXPECT_CHAR(input.at(offset++), '#');
    switch(input.at(offset++))
    {
    case 't':
    case 'T':
        return TRUE;

    case 'f':
    case 'F':
        return FALSE;

    default:
        UNEXPECTED_TOKEN(input.at(offset-1), "t/T or f/F");
    }
}

PL_ATOM parseList(const std::string& input, size_t& offset)
{
    char c;
    char opener = input.at(offset++);
    char closer;
    if(opener == '(' || opener == '[')
    {
        if(opener == '(')
            closer = ')';
        else
            closer = ']';

        std::forward_list<PL_ATOM> parts;
        auto bb = parts.before_begin();
        bool needsWS = false;

        while(offset < input.size())
        {
            c = input.at(offset);
            if(c == closer)
            {
                ++offset;
                return WRAP(L_LIST, std::move(parts));
            }
            else if(c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                needsWS = false;
                ++offset;
            }
            else
            {
                if(needsWS)
                {
                    throw std::runtime_error(std::string("Unexpected: ")+c+", Expected some whitespace or "+closer);
                }
                else
                {
                    bb = parts.insert_after(bb, parseExpression(input, offset));
                    needsWS = true;
                }
            }
        }
        throw std::runtime_error(std::string("Unmatched ")+opener+".");
    }
    throw std::runtime_error(std::string("Unexpected: ")+input[offset-1]+", Expected ( or [");
}

PL_ATOM parseVector(const std::string& input, size_t& offset)
{
    char c;
    EXPECT_CHAR(input.at(offset++), '#');
    char opener = input.at(offset++);
    char closer;
    if(opener == '(' || opener == '[')
    {
        if(opener == '(')
            closer = ')';
        else
            closer = ']';

        std::vector<PL_ATOM> parts;
        bool needsWS = false;

        while(offset < input.size())
        {
            c = input.at(offset);
            if(c == closer)
            {
                ++offset;
                break;
            }
            else if(c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                needsWS = false;
            }
            else
            {
                if(needsWS)
                {
                    throw std::runtime_error(std::string("Unexpected: ")+c+", Expected some whitespace.");
                }
                else
                {
                    parts.push_back(parseExpression(input, offset));
                    needsWS = true;
                }
            }
            ++offset;
        }

        return WRAP(L_VECTOR, std::move(parts));
    }
    throw std::runtime_error(std::string("Unexpected: ")+input[offset-1]+", Expected ( or [");
}

PL_ATOM parseChar(const std::string& input, size_t& offset)
{
    EXPECT_CHAR(input.at(offset++), '#');
    EXPECT_CHAR(input.at(offset++), '\\');
    return WRAP(L_CHAR, input.at(offset++));
}

PL_ATOM parseString(const std::string& input, size_t& offset)
{
    std::string stringVal;
    char c = input.at(offset++);
    EXPECT_CHAR(c, '"');
    c = input.at(offset++);
    while(c != '"')
    {
        if(c == '\\')
        {
            switch(input.at(offset++))
            {
            case 'n':
                stringVal += '\n';
                break;
            case '\\':
                stringVal += '\\';
                break;
            case 'r':
                stringVal += '\r';
                break;
            case 't':
                stringVal += '\n';
                break;
            }
        }
        else
        {
            stringVal += c;
        }
        c = input.at(offset++);
    }
    return WRAP(L_STRING, stringVal);
}

PL_ATOM parseSymbol(const std::string& input, size_t& offset)
{
    std::string symbolName;
    char c;
    while( offset < input.size())
    {
        c = input.at(offset);
        if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '$' && c <= '&') ||
            (c >= '0' && c <= '9') || (c >= '<' && c <= '?') ||  c == '!' || c == '*'  ||
             c == '/' || c == ':'  ||  c == '^' || c == '_'  ||  c == '~' || c == '.'  ||
             c == '+' || c == '-')
         {
            symbolName += c;
         }
         else
         {
            break;
         }
         ++offset;
    }
    return WRAP(L_SYMBOL, symbolName);
}

PL_ATOM deepCopy(PL_ATOM expr)
{
    throw std::runtime_error("Deepcopy NYI");
}

void makeConstant(PL_ATOM expr)
{
    if(expr == nullptr)
        return;

    switch(expr->mType)
    {
    case LispType::LIST:
    {
        for(auto& element : AS(L_LIST, expr)->mAtoms)
        {
            makeConstant(element);
        }
        expr->mConstant = true;
    } break;

    case LispType::VECTOR:
    {
        for(auto& element : AS(L_VECTOR, expr)->mAtoms)
        {
            makeConstant(element);
        }
        expr->mConstant = true;
    } break;

    case LispType::BOOL:
    case LispType::CHAR:
    case LispType::STRING:
    case LispType::SYMBOL:
    case LispType::INT:
    case LispType::REAL:
        expr->mConstant = true;
        break;

    case LispType::RATIONAL:
    {
        PL_RATIONAL rat = AS(L_RATIONAL, expr);
        makeConstant(rat->mNumerator);
        makeConstant(rat->mDenominator);
    } break;

    case LispType::COMPLEX:
    {
        PL_COMPLEX comp = AS(L_COMPLEX, expr);
        makeConstant(comp->mReal);
        makeConstant(comp->mImaginary);
        expr->mConstant = true;
    } break;

    case LispType::LITERAL:
    {
        makeConstant(AS(L_LITERAL, expr)->mLiteral);
        expr->mConstant = true;
    } break;

    case LispType::FUNCTION:
    {
        expr->mConstant = true;
    } break;

    case LispType::BUILTIN_FUNCTION:
    {
        expr->mConstant = true;
    } break;
    }
}

}

int main(int argc, char* argv[])
{
    std::string inbuf;
    SymbolTableType global;
    SymbolTableType local;
    if(argc == 1)
    {
        std::string outbuf;
        size_t offset;

        std::cout << ">> ";
        std::getline(std::cin, inbuf);

        while(inbuf != "")
        {
            outbuf.clear();
            local.clear();
            offset = 0;

            try
            {
                PL_ATOM expr = evaluate(parseExpression(inbuf, offset), global, local);
                if(expr != NIL)
                {
                    tryToString(expr, outbuf);
                    std::cout << outbuf << std::endl;
                }
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }

            std::cout << ">> ";
            std::getline(std::cin, inbuf);
        }
    }
    else if(argc == 2)
    {
        std::ifstream input(argv[1]);
        std::string buf{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
        size_t offset = 0;
        evaluate(parseExpression(buf, offset), global, local);
    }
    return 0;
}
