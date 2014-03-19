
#include <rcythrScript/rcythr.h>
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
