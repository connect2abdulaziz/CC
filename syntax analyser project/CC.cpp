#include <iostream>
#include <fstream>
using namespace std;

enum COL
{
    A = 128,
    R,
    T
};
int main()
{
    char buff[4096]{};
    int bi = 0;
    int state = 0;
    int li = 0;
    char lex[1024]{};
    char ch;
    int TT[5][131]{};
    ifstream fin;
    fin.open("TT.txt");
    if (fin)
    {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 131; j++)
                fin >> TT[i][j];
        fin.close();
    }
    else
    {
        cout << "ERROR\n";
    }
    fin.open("prog.txt");
    if (!fin)
        cout << "ERROR\n";
    else
    {
        while (fin)
        {
            fin >> buff[bi++];
        }
        buff[bi] = '\0';
        bi = 0;
        fin.close();
    }
    cout << endl
         << endl;
    while ((ch = buff[bi]) != '\0')
    {

        if (!TT[state][128])
        {
            state = TT[state][ch];
            if (state == -1)
            {
                state = 0;
                li = 0;
                lex[li] = '\0';
            }
            else
            {
                lex[li] = ch;
                li++;
            }
        }
        else
        {
            lex[li] = '\0';
            cout << lex << endl
                 << endl
                 << endl
                 << endl;
            if (TT[state][129])
                bi--;
            state = 0;
            li = 0;
        }
        bi++;
    }

    return 0;
}