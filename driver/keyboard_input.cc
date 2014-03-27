
#include <iostream>

#include "keyboard_input.h"

int count_parens(const std::string& str)
{
    int result = 0;
    for(size_t i=0; i < str.size(); ++i)
    {
        if(str[i] == '(')
            result += 1;
        else if(str[i] == ')')
            result -= 1;
    }
    return result;
}

std::string get_rscript_line()
{
    std::string result;
    std::string current;
    int open_count = 0;

    printf(">> ");
    std::getline(std::cin, current);
    result += current;
    open_count += count_parens(current);
    while(open_count != 0)
    {
        current.clear();
        printf(".. ");
        
        std::getline(std::cin, current);
        result += current;
        open_count += count_parens(current);
    }
    return result;
}
