// CS Afternoon
// BCSF19A026
// Abdul Aziz
#define _CRT_SECURE_NO_WARNINGS
#ifndef BUFFER_H
#define BUFFER_H
#include <iostream>
#include <cstring>
using namespace std;

class Node
{
public:
    char *data;
    Node *next;
    Node(const char *buff = {})
    {
        data = new char[strlen(buff) + 1]{};
        strcpy(data, buff);
        data[strlen(buff)] = '\0';
        next = NULL;
    }
};
class BuffList
{
    Node *first;
    Node *last;

public:
    BuffList(Node * = NULL, Node * = NULL);
    BuffList(const BuffList &);
    const BuffList &operator=(const BuffList &);
    void pushLast(const char *);
    Node *getFirst() const;
    bool empty() const;
    void popFirst();
    int getCount() const;
    void display()const;
    ~BuffList();
};
#endif // ! BUFFH
