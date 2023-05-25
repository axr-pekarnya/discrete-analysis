#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <fstream>

class TItem
{
    public:
        TItem() = default;

        std::string& GetKey();
        uint64_t GetValue() const;

        void SetKey(std::string& keyInput);
        void SetValue(uint64_t valueInput);
                
        friend std::istream& operator>>(std::istream& fin, TItem& elem)
        {
            fin >> elem.key >> elem.value;
            return fin;
        }

    private:
        std::string key;
        uint64_t value;
};

#endif
