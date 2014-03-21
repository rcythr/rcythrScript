
#include <rcythrScript/rcythr.h>
#include <rcythrScript/constants.h>

#include <iostream>
#include <fstream>

using namespace rcythr;

int main(int argc, char* argv[])
{
    std::string inbuf;
    SymbolTableType global;
    SymbolTableType local;
    if(argc == 1)
    {
        size_t offset;

        std::cout << ">> ";
        std::getline(std::cin, inbuf);

        while(inbuf != "")
        {
            local.clear();
            offset = 0;

            try
            {
                PL_ATOM expr = evaluate(parseExpression(inbuf, offset), global, local);
                if(expr != NIL)
                {
                    std::cout << expr->str() << std::endl;
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
