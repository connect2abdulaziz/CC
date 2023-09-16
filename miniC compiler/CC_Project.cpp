// CS Afternoon
// BCSF19A026
// Abdul Aziz

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

void displayFileOfToken(ifstream &);
enum COL
{
    A = 128,
    R,
    T
};
enum TokenType
{
    reserve_words = 1,
    identifier,
    numeric_literal,
    punctuation,
    Operator,
    comments
};
string Reserve_word[14] = {
    "CONST", "FLOAT", "INT", "BREAK", "CONTINUE",
    "ELSE", "FOR", "SWITCH", "VOID", "CASE",
    "CHAR", "DO", "IF", "WHILE"};
bool checkKeyword(const char *lex)
{
    string str = lex;
    for (int i = 0; i < 14; i++)
        if (str == Reserve_word[i])
            return true;
    return false;
}
int main()
{

    const int BUFFER_SIZE = 4096;  // Size of buffer
    const int ROW = 59;            // rows of transition table
    const int COL = 131;           // columns of transition table
    char buff1[BUFFER_SIZE + 1]{}; // buffer1
    char buff2[BUFFER_SIZE + 1]{}; // buffer2
    int bi = 0;                    // buffer current index
    int state = 0;                 // state of transition table
    int liSize = 0;                // number of char in lex buffer
    int b1Start = 0;               // start of lexeme in buffer 1
    int b2Start = 0;               // start of lexeme in buffer 2
    int b1End = 0;                 // end of lexeme in buffer1
    int b2End = 0;                 // end of lexeme in buffer

    char ch;
    int TT[ROW][COL]{}; // transition table
    ifstream fin;       // input stream variable fin
    string fileName;
    cout << "Enter Transition Table File name (i.e TT.txt): ";
    getline(cin, fileName);
    fin.open(fileName, ios::in); // file to read the transition table
    if (fin)
    {
        // taking input from file for transition table
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                fin >> TT[i][j];
        fin.close();
    }
    else
    {
        cout << "Oops! Something wrong happened during file opening\nOR " << fileName << " not found\n";
        exit(-1);
    }
    ofstream fout;
    fout.open("Token.txt", ios::out);
    if (!fout)
    {
        cout << "Oops! Something wrong happened during file opening\nOR Token.txt not Generated\n";
        exit(-1);
    }
    else
    {
        cout << "Enter the program file name i.e (input.txt): ";
        getline(cin, fileName);
        fin.open(fileName, ios::in);
        if (!fin)
        {
            cout << "Oops! Something wrong happened during file opening\nOR " << fileName << " not found\n";
            exit(-1);
        }
        else
        {
            while (fin)
            {
                while (fin && bi < BUFFER_SIZE)
                {
                    fin.get(buff1[bi++]);
                }
                buff1[bi] = '\0';
                bi = 0;
                while ((ch = buff1[bi++]) != '\0')
                {
                    state = TT[state][int(ch)];
                    if (!TT[state][A])
                    {
                        if (state == -1)
                        {
                            state = 0;
                            liSize = 0;
                            b1Start = b1End = bi;
                            b2Start = b2End = 0;
                        }
                        else
                        {

                            b1End++;
                            liSize++;
                            if (liSize > BUFFER_SIZE)
                            {
                                cout << "Oops! the lexeme size can't be greater than buffer size\n";
                                state = 0;
                                liSize = 0;
                                b1Start = b1End = bi;
                                b2Start = b2End = 0;
                            }
                        }
                    }
                    else
                    {
                        b1End++;
                        liSize++;
                        if (TT[state][R])
                        {
                            liSize--;
                            b1End--;
                            // if (bi == 1)
                            //     b2End--;
                            bi--;
                        }
                        char *lex = new char[liSize + 1]{};
                        liSize = 0;
                        while (b2Start < b2End)
                            lex[liSize++] = buff2[b2Start++];
                        while (b1Start < b1End)
                            lex[liSize++] = buff1[b1Start++];
                        lex[liSize] = '\0';
                        switch (TT[state][T])
                        {
                        case reserve_words:
                        {
                            if (checkKeyword(lex))
                            {
                                fout << "<Reserve Words, " << lex << "> \n";
                            }
                        }
                        break;
                        case identifier:
                        {
                            fout << "<identifier, " << lex << ">\n";
                        }
                        break;
                        case punctuation:
                        {
                            fout << "<identifier, " << lex << ">\n";
                        }
                        break;
                        case numeric_literal:
                        {
                            fout << "<Numeric literal, " << lex << ">\n";
                        }
                        break;
                        case Operator:
                        {
                            fout << "<Operator, " << lex << ">\n";
                        }
                        break;
                        case comments:
                        {
                            fout << "<Comment, " << lex << ">\n";
                        }
                        };
                        delete[] lex;
                        lex = NULL;
                        b1Start = b1End = bi;
                        b2Start = b2End = 0;
                        state = 0;
                        liSize = 0;
                    }
                }
                if (state > 0 && b1Start != b1End)
                {
                    strcpy(buff2, buff1);
                    buff2[bi - 1] = '\0';
                    b2Start = b1Start;
                    b2End = b1End;
                }
                else
                {
                    b2Start = b2End = 0;
                }
                b1Start = b1End = bi = 0;
            }
            fin.close();
        }
        fout.close();
        // display File Of Token
        displayFileOfToken(fin);
    }
    return 0;
}
void displayFileOfToken(ifstream &fin)
{
    char ch;
    fin.open("Token.txt");
    if (!fin)
        cout << "ERROR! while opening token file" << endl;
    else
    {
        cout << "\t\t*****************************\n";
        cout << "\t\t*       TOKEN FILE          *\n";
        cout << "\t\t*****************************\n";
        do
        {
            fin.get(ch);
            cout << ch;
        } while (fin);
    }
}
