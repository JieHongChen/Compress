#include "Decompress.hpp"

Decompress::Decompress(const char *filename)
:fnameR(filename)
{
    FILE *FileR = fopen(fnameR, "r");
    if(FileR == NULL)
    {
        cout << "fail to open " << fnameR << endl;
        fclose(FileR);
        return;
    }
    fclose(FileR);
    dec();
}

void Decompress::dec()
{
    FILE *FileR = fopen(fnameR, "r");
    char ch;
    char *fnameW = new char[100];
    fscanf(FileR, "%s", fnameW);
    fscanf(FileR, "%c", &ch);

    char key;
    string code;
    bool breakloop = false;
    while(true)
    {
        fscanf(FileR, "%c", &ch);
        key = ch;
        code = "";
        while(true)
        {
            fscanf(FileR, "%c", &ch);
            if(ch == ' ')
            {
                if(code.size() == 0)
                {
                    breakloop = true;
                }
                else
                {
                    code_table.insert(pair<string, char>(code, key));
                }
                break;
            }
            else
            {
                code += ch;
            }
        }
        if(breakloop)
        {
            break;
        }
    }

    FILE *FileW = fopen(fnameW, "w+");
    code = "";
    breakloop = false;
    fscanf(FileR, "%c", &ch);//first code
    while(true)
    {
        int n = 0, x = 0;
        for(int i = 0; i < 4; i++)
        {
            n = n * 216 + (((int)ch - 27 + 256) % 256);
            if(fscanf(FileR, "%c", &ch) == EOF)//next code
                breakloop = true;
            if(((int)ch - 27 + 256) % 256 == 216)
            {
                do
                {
                    x++;
                }while(fscanf(FileR, "%c", &ch) != EOF);
            }
        }
        stack<char> binary;
        for(int i = 0; i < 31; i++)
        {
            binary.push((n % 2) + '0');
            n /= 2;
        }
        for(int i = 0; i < 31 - x; i++)
        {
            code += binary.top();
            if(code_table.find(code) != code_table.end())
            {
                fprintf(FileW, "%c", code_table[code]);
                code = "";
            }
            binary.pop();
        }
        if(breakloop || x) break;
    }

    fclose(FileW);
    fclose(FileR);
}

