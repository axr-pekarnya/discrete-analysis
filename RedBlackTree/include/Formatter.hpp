#ifndef FORMATTER_HPP
#define FORMATTER_HPP

#include <string>
#include <fstream>

const char NULL_COLOUR = 'n';
const char BLACK_COLOUR = 'b';
const char RED_COLOUR = 'r';

class TFormatter
{
    friend class TFileManager;

    private:
        char colour;
        uint64_t value;
        std::string key;

        TFormatter();
        TFormatter(char colourInput, uint64_t valueInput, std::string& keyInput);

        friend std::istream& operator>>(std::istream& fin, TFormatter& elem)
        {
            fin >> elem.colour >> elem.value >> elem.key;
            return fin;
        }

        friend std::ostream& operator<<(std::ostream& fout, const TFormatter& elem)
        {
            fout << elem.colour << ' ' << elem.value << ' ' << elem.key << '\n';
            return fout;
        }
};

#endif
