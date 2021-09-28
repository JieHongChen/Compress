#ifndef COMPRESS_HPP
#define COMPRESS_HPP
#include <iostream>
#include <map>
#include <string.h>

using namespace std;

struct Node
{
    char key;
    int cou;
    string code = "";
    Node *lnode = NULL; // left node
    Node *rnode = NULL; // right node
};

class Compress
{
    public:
        Compress(const char*);
        void counting();
        Node* buildTree();
        void code(Node*);
        void write();

    protected:

    private:
        const char *fname; // file name
        map<char, int> char_counts;
        map<char, string> code_table;

};

#endif // COMPRESS_HPP
