
#include <rscript/rscript.h>
#include <rscript/constants.h>

#include "keyboard_input.h"

#include <iostream>
#include <fstream>

using namespace rscript;

int main(int argc, char* argv[])
{
    std::string inbuf;
    SymbolTable symbols;
    if(argc == 1)
    {
        size_t offset;

        inbuf = get_rscript_line();

        while(inbuf != "")
        {
            offset = 0;

            try
            {
                PL_ATOM expr = evaluate(parseExpression(inbuf, offset), symbols);
                if(expr != NIL)
                {
                    std::cout << expr->str() << std::endl;
                }
            }
            catch(std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
    
            inbuf = get_rscript_line();
        }
    }
    else if(argc == 2)
    {
        std::ifstream input(argv[1]);
        std::string buf{std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
        size_t offset = 0;
        evaluate(parseExpression(buf, offset), symbols);
    }
    return 0;
}
