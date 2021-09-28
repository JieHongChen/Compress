#ifndef DECOMPRESS_HPP
#define DECOMPRESS_HPP
#include <map>
#include <iostream>
#include <string.h>
#include <stack>

using namespace std;

class Decompress
{
    public:
        Decompress(const char*);
        void dec();
        int base216ToDecimal(int*);
        string decimalToBinary(int);

    protected:

    private:
        const char *fnameR;
        map<string, char> code_table;

};

#endif // DECOMPRESS_HPP
