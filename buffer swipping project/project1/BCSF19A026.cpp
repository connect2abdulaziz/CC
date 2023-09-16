// CS Afternoon
// BCSF19A026
// Abdul Aziz

#include <iostream>
#include <string>
#include <fstream>
#include "BuffList.cpp"//linklist file 
using namespace std;




//Global Variables
//************************************************************************************
//***********************************************************************************
#define BUFF_SIZE 4096    // you can change it to required size of buffer
int state = 0;            // current state of lexeme
BuffList bufferList;      // to stored buffer for performing dynamic buffering
BuffList lexemeTokenList; // to store lexeme tokens
int lexemeSize = 0;       // size of lexeme
int startingIndex = 0;    // starting position of lexeme
//************************************************************************************
//************************************************************************************


//function prototypes
bool generateLexeme(char *);
int main()
{
    char buffer[BUFF_SIZE + 1]{}; // buffer to take input from file
    ifstream fin;                 // file opening var fin
    string fileName;
    cout << "Enter name of input file something like (input.txt): "; // to take input file name from user
    getline(cin, fileName);
    fin.open(fileName, ios::in);
    if (!fin)
    {
        cout << "Oops! Something wrong happened during file opening\nOR " << fileName << " not found\n";
        exit(-1);
    }
    else
    {
        fin.seekg(ios::beg, ios::end); // to get size of the file
        int fileSize = fin.tellg();    // fileSize  stored in the fileSize variable
        fin.seekg(ios::beg);           // to back to starting position of the file
        while (fin)
        {
            int curSize = fin.tellg();          // current position of the file
            if (curSize + BUFF_SIZE < fileSize) // if there is enough file available
            {
                fin.read(buffer, BUFF_SIZE); // read char of buff size or end of buffer
                buffer[BUFF_SIZE] = '\0';
            }
            else
            {
                fin.read(buffer, (fileSize - curSize) + 1); // to read from file tell end of file
                buffer[fileSize - curSize] = '\0';
            }
            bool lexemeComplete = generateLexeme(buffer); // to read from buffer tell end of buffer and generate lexeme
            if (!lexemeComplete)
                bufferList.pushLast(buffer); // push last buffer
        }
        fin.close(); // close file
        cout << "*************************************\n";
        cout << "Here are the lexeme tokens generated: " << endl;
        cout << "*************************************\n";
        lexemeTokenList.display();
    }
    return 0;
}



//function implementation
bool generateLexeme(char *buff)
{
    int endingIndex = 0; // ending position of lexeme
    char ch;
    int bi = 0;               // buffer index
    while ((ch = buff[bi++])) // when there is a character in the buffer still unread
    {
        switch (state)
        {
        case 0:
        {
            if (isalpha(ch) || ch == '_') // this is just for identifier
            {
                endingIndex++;
                lexemeSize++;
                state = 1;
            }
            else
            {
                startingIndex = endingIndex = bi;
                lexemeSize = 0;
                state = 0;
            }
        }
        break;
        case 1:
        {
            if (isalnum(ch) || ch == '_')
            {
                endingIndex++;
                lexemeSize++;
            }
            else
                state = 2;
        }
        break;
        case 2:
        {
            // Displaying Lexeme
            // size of lexeme
            int lexemeIndex = 0;                       // Index of lexeme
            char *lexeme = new char[lexemeSize + 1]{}; // lexeme generating
            while (!bufferList.empty())
            {
                Node *temp = bufferList.getFirst();
                for (int i = startingIndex; temp->data[i] && i < BUFF_SIZE; i++)
                {
                    lexeme[lexemeIndex++] = temp->data[i];
                }
                bufferList.popFirst();
                startingIndex = 0;
                temp = NULL;
            }
            while (startingIndex < endingIndex)
                lexeme[lexemeIndex++] = buff[startingIndex++];
            lexeme[lexemeIndex] = '\0';
            state = 0;
            bi--;
            startingIndex = endingIndex = bi;
            lexemeTokenList.pushLast(lexeme);
            if (lexeme)
                delete[] lexeme;
            lexeme = NULL;
            lexemeSize = 0;
        }
        break;
        }
    }
    if (state == 0)
        return true;
    else
        return false;
}