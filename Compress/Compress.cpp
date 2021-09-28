#include "Compress.hpp"



Compress::Compress(const char *filename)
:fname(filename)
{
    FILE *FileR = fopen(fname, "r");
    if(FileR == NULL)
    {
        cout << "fail to open " << filename << endl;
        fclose(FileR);
        return;
    }
    fclose(FileR);
    counting();
    Node *root = buildTree();
    code(root);
    write();
}

void Compress::counting()
{
    FILE *FileR = fopen(fname, "r");
    char ch;
    fscanf(FileR, "%c", &ch);
    while(true)
    {
        if(char_counts.find(ch) == char_counts.end())
        {
            char_counts.insert(pair<char, int>(ch, 1));
        }
        else
        {
            char_counts[ch]++;
        }
        if(fscanf(FileR, "%c", &ch) == EOF) break;
    }
    fclose(FileR);
    return;
}

Node * Compress::buildTree()
{
    int s = char_counts.size();
    struct Node **node_list = new struct Node*[s];

    map<char, int>::iterator it;
    int i = 0;
    for(it = char_counts.begin(); it != char_counts.end(); it++)
    {
        struct Node *new_node = new struct Node;
        new_node->key = it->first;
        new_node->cou = it->second;
        node_list[i] = new_node;
        i++;
    }

    for(int i = 0; i < s - 1; i++)
    {
        for(int j = 0; j < s - 1 - i; j++)
        {
            if(node_list[j]->cou > node_list[j + 1]->cou)
            {
                struct Node *temp = node_list[j];
                node_list[j] = node_list[j + 1];
                node_list[j + 1] = temp;
            }
        }
    }
    for(int i = 0; i < s - 1; i++)
    {
        struct Node *new_node = new struct Node;
        new_node->lnode = node_list[i];
        new_node->rnode = node_list[i + 1];
        new_node->cou = node_list[i]->cou + node_list[i + 1]->cou;

        for(int j = i + 1; j < s; j++)
        {
            if(j == s - 1 || new_node->cou <= node_list[j + 1]->cou)
            {
                node_list[j] = new_node;
                break;
            }
            else
            {
                node_list[j] = node_list[j + 1];
            }
        }
    }
    struct Node *root = node_list[s - 1];
    return root;
}

void Compress::code(Node *n)
{
    if(n->lnode != NULL)
    {
        n->lnode->code = n->code + "0";
        code(n->lnode);
    }
    if(n->rnode != NULL)
    {
        n->rnode->code = n->code + "1";
        code(n->rnode);
    }
    if(n->lnode == NULL && n->rnode == NULL)
    {
        code_table.insert(pair<char, string>(n->key, n->code));
    }
}

void Compress::write()
{
    // print file name
    int s = 0;
    while(fname[s] != '.')
    {
        s++;
    }
    char *fw = new char[s + 10];
    for(int i = 0; i < s; i++)
    {
        fw[i] = fname[i];
    }
    char str[11] = ".compress";
    for(int i = 0; i < 9; i++)
    {
        fw[s + i] = str[i];
    }
    fw[s + 9] = '\0';

    FILE *FileW = fopen(fw, "w+");
    fprintf(FileW, "%s ", fname);

    // print code table
    map<char, string>::iterator it;
    for(it = code_table.begin(); it != code_table.end(); it++)
    {
        fprintf(FileW, "%c", it->first);
        string code = it->second;
        for(int i = 0; i < code.size(); i++)
        {
            fprintf(FileW, "%c", code[i]);
        }
        fprintf(FileW, " ");
    }
    fprintf(FileW, "  ");


    string code;
    FILE *FileR = fopen(fname, "r");
    char ch;
    while(fscanf(FileR, "%c", &ch) != EOF)
    {
        code += code_table[ch];
        while(code.size() >= 31)
        {
            string f31 = "", r = ""; // first 31, remain
            for(int i = 0; i < code.size(); i++)
            {
                if(i < 31)
                {
                    f31 += code[i];
                }
                else
                {
                    r += code[i];
                }
            }
            code = r;

            int num = 0;
            for(int i = 0; i < 31; i++)
                num = num * 2 + (f31[i] - '0');
            char p[4]; // print
            for(int i = 0; i < 4; i++)
            {
                p[3 - i] = num % 216;
                num /= 216;
            }

            for(int i = 0; i < 4; i++)
            {
                fprintf(FileW, "%c", p[i] + 27);
            }
        }
    }

    //last code
    if(code.size() != 0)
    {
        int cs = code.size();//code size
        while(code.size() < 31)
            code += '0';
        int n = 0;
        for(int i = 0; i < 31; i++)
            n = n * 2 + (code[i] - '0');
        char p[4];
        for(int i = 0; i < 4; i++)
        {
            p[4 - i - 1] = n % 216;
            n /= 216;
        }

        for(int i = 0; i < 4; i++)
            fprintf(FileW, "%c", p[i] + 27);
        for(int i = 0; i < 31 - cs; i++)
            fprintf(FileW, "%c", 243);
    }

    fclose(FileR);
    fclose(FileW);
}



