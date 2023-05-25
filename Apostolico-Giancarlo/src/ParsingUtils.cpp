#include "ParsingUtils.hpp"

std::vector<uint32_t> ParsePattern() 
{
    std::vector<uint32_t> result;
    std::string buffer;
    char symbol = ' ';

    while (true) 
    {
        symbol = getchar();

        if (buffer.length() && symbol == ' ') 
        {
            result.push_back(std::stoul(buffer));
            buffer.clear();
        }
        else if (symbol == '\n')
        {
            if(buffer.length())
            {
                result.push_back(std::stoul(buffer));
                buffer.clear();
            }

            break;
        }
        else if (symbol >= '0' && symbol <= '9') {
            buffer.push_back(symbol);
        }
    }

    return result;
}

std::vector<uint32_t> ParseText(std::vector<pii>& positions) 
{
    std::vector<uint32_t> result;
        
    std::string buffer;
    char symbol = ' ';
  
    unsigned int numOfLine = 1;
    unsigned int posInLine = 0;

    while (true) 
    {
        symbol = getchar();

        if (buffer.length() && symbol == ' ') 
        {
            posInLine++;
            positions.emplace_back(numOfLine, posInLine);
            result.push_back(std::stoul(buffer));
            buffer.clear();
        }
        else if (symbol == '\n')
        {
            if(buffer.length())
            {
                posInLine++;
                positions.emplace_back(numOfLine, posInLine);
                result.push_back(std::stoul(buffer));
                buffer.clear();
            }

            posInLine = 0;
            numOfLine++;
        }
        else if (symbol == EOF)
        {
            if(buffer.length() != 0)
            {
                posInLine++;
                positions.emplace_back(numOfLine, posInLine);
                result.push_back(std::stoul(buffer));
            }

        break;
        }

        else if (symbol >= '0' && symbol <= '9') {
            buffer.push_back(symbol);
        }
    }

    return result;
}

