#include <iostream>
#include <string.h>
#include "Compress.hpp"
#include "Decompress.hpp"

using namespace std;

int main()
{
    bool breakloop = false;
    int x;
    cout << "1: compress" << endl << "2: decompress" << endl << "3: exit" << endl << endl;
    while(cin >> x)
    {
        switch(x)
        {
            case 1:
            {
                cout << "\n\n-----compress file-----\n\n";
                string fileName;
                cout << "file name: ";
                cin >> fileName;
                int s = fileName.size();
                char *fn = new char[s + 1];
                for(int i = 0; i < s; i++)
                {
                    fn[i] = fileName[i];
                }
                fn[s] = '\0';
                Compress c(fn);


                break;
            }
            case 2:
            {
                cout << "\n\n-----decompress file-----\n\n";
                string fileName;
                cout << "file name: ";
                cin >> fileName;
                int s = fileName.size();
                char *fn = new char[s + 1];
                for(int i = 0; i < s; i++)
                {
                    fn[i] = fileName[i];
                }
                fn[s] = '\0';
                Decompress dec(fn);
                break;
            }
            case 3:
            {
                breakloop = true;
                break;
            }
            default:
            {
                cout << "wrong input" << endl;
            }
        }
        if(breakloop) break;
        cout << endl << "------------------------------" << endl;
        cout << endl << "1: compress" << endl << "2: decompress" << endl << "3: exit" << endl << endl;
    }

    return 0;
}
