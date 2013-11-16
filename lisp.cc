#include "lisp.h"
#include "builtins.h"
#include <iostream>

using namespace rcythr;

namespace rcythr
{

bool isSpace(char val) { return val == ' '; }
bool isWhitespace(char val) { return val == ' ' || val == '\t' || val == '\r' || val == '\n'; }
bool isNumber(char val) { return val >= '0' && val <= '9'; }
bool isLetter(char val) { return (val >= 'a' && val <= 'z') || (val >= 'A' && val <= 'Z'); }
bool isAlpha(char val) { return isLetter(val) || isNumber(val); }
bool isSymbol(char val)
{
    switch(val)
    {
    case '!': case '#': case '$': case '%':
    case '&': case '*': case '+': case ',':
    case '-': case '.': case '/': case ':':
    case '<': case '=': case '>': case '?':
    case '@': case '\\': case '^': case '_':
    case '|': case '~': case '\'':
        return true;
    }
    return false;
}
bool isAlphaSymbol(char val) { return isAlpha(val) || isSymbol(val); }

void printIndent(size_t indent)
{
    for(size_t i=0; i < indent; ++i)
        printf("\t");
}

void printExpression(PL_ATOM expr, size_t indent)
{
    switch(expr->mType)
    {
        case LispType::LITERAL:
        {
            PL_LITERAL literal = AS(L_LITERAL, expr);
            printIndent(indent);
            printf("'(\n");
            printExpression(literal->mLiteral);
            printIndent(indent);
            printf(")\n");
        } break;

        case LispType::BOOL:
        {
            printIndent(indent);
            printf((AS(L_BOOL, expr)->mValue) ? "BOOL: true\n" : "BOOL: false\n");
        } break;

        case LispType::SYMBOL:
        {
            printIndent(indent);
            printf("SYMBOL: %s\n", AS(L_SYMBOL, expr)->mName.c_str());
        } break;

        case LispType::LIST:
        {
            printIndent(indent);
            printf("(\n");
            for(auto& atom : AS(L_LIST, expr)->mAtoms)
                printExpression(atom, indent+1);
            printIndent(indent);
            printf(")\n");
        } break;

        case LispType::VECTOR:
        {
            printIndent(indent);
            printf("#(\n");
            for(auto& atom : AS(L_VECTOR, expr)->mAtoms)
                printExpression(atom, indent+1);
            printf(")\n");
        } break;

        case LispType::INT:
        {
            printIndent(indent);
            printf("INT: %d\n", AS(L_INT, expr)->mValue);
        } break;

        case LispType::REAL:
        {
            printIndent(indent);
            printf("REAL: %f\n", AS(L_REAL, expr)->mValue);
        } break;

        case LispType::RATIONAL:
        {
            printIndent(indent);
            PL_RATIONAL rational = AS(L_RATIONAL, expr);
            printf("RATIONAL: %d/%d\n", rational->mNumerator->mValue, rational->mDenominator->mValue);
        } break;

        case LispType::COMPLEX:
        {
            printIndent(indent);
            PL_COMPLEX complex = AS(L_COMPLEX, expr);
            printf("COMPLEX: ");

            if(complex->mReal->mType == LispType::INT)
                printf("%d+", AS(L_INT, complex->mReal)->mValue);
            else if(complex->mReal->mType == LispType::REAL)
                printf("%f+", AS(L_REAL, complex->mReal)->mValue);
            else
                printf("0+");

            if(complex->mImaginary->mType == LispType::INT)
                printf("%di\n", AS(L_INT, complex->mImaginary)->mValue);
            else if(complex->mImaginary->mType == LispType::REAL)
                printf("%fi\n", AS(L_REAL, complex->mImaginary)->mValue);
            else
                printf("0i\n");
        } break;

        case LispType::CHAR:
        {
            printIndent(indent);
            printf("CHAR: %c\n", AS(L_CHAR, expr)->mValue);
        } break;

        case LispType::STRING:
        {
            printIndent(indent);
            printf("STRING: %s\n", AS(L_STRING, expr)->mValue.c_str());
        } break;

        case LispType::FUNCTION:
        {
            printIndent(indent);
            printf("<PROCEDURE %p>\n", expr.get());
        } break;

        case LispType::BUILTIN_FUNCTION:
        {
            printIndent(indent);
            printf("<BUILTIN PROCEDURE %p>\n", expr.get());
        } break;
    }
}

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
                    return forms_itr->second(lst, localSymbolTable, globalSymbolTable);
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
            } break;

            default:
                break;
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

}

int main(int argc, char* argv[])
{
    std::string buf;
    std::cout << ">> ";
    std::getline(std::cin, buf);
    SymbolTableType global;
    SymbolTableType local;
    while(buf != "quit")
    {
        local.clear();

        auto itr = begin(buf);
        auto enditr = end(buf);

        try
        {
            printExpression(evaluate(parseExpression(itr, enditr), global, local));
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        std::cout << ">> ";
        std::getline(std::cin, buf);
    }
    return 0;
}
