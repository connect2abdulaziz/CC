// CS Afternoon
// BCSF19A026
// Abdul Aziz
#include "BuffList.h"
BuffList::BuffList(Node *start, Node *end)
{
    first = start;
    last = end;
}
BuffList::BuffList(const BuffList &rhs)
{
    Node *cur = rhs.first;
    while (cur)
    {
        pushLast(cur->data);
        cur = cur->next;
    }
}
const BuffList &BuffList::operator=(const BuffList &rhs)
{
    if (this == &rhs)
        return *this;
    if (first)
        this->~BuffList();
    Node *cur = rhs.first;
    while (cur)
    {
        pushLast(cur->data);
        cur = cur->next;
    }
    return *this;
}
void BuffList::pushLast(const char *Buffer)
{
    if (empty())
    {
        first = new Node(Buffer);
        last = first;
    }
    else
    {
        last->next = new Node(Buffer);
        last = last->next;
    }
}
Node *BuffList::getFirst() const
{
    if (first)
    {
        return first;
    }
    else
        exit(-1);
}
bool BuffList::empty() const
{
    if (first == NULL)
        return true;
    else
        return false;
}
void BuffList::popFirst()
{
    if (!empty())
    {
        if (first->next == NULL)
        {
            if (first->data)
                delete[] first->data;
            first->data = NULL;
            delete[] first;
            first = NULL;
            last = NULL;
        }
        else
        {
            Node *head = first;
            if (first->data)
                delete[] first->data;
            first->data = NULL;
            first = head->next;
            delete[] head;
            head = NULL;
        }
    }
    else
    {
        cout << "BuffList is empty\n";
    }
}
int BuffList::getCount() const
{
    int count = 0;
    Node *head = first;
    while (head)
    {
        head = head->next;
        count++;
    }
    return count;
}
void BuffList::display() const
{
    Node *cur = first;
    while (cur)
    {
        cout << "<identifier," << cur->data << ">\n";
        cur = cur->next;
    }
}
BuffList ::~BuffList()
{
    Node *head = first;
    while (head)
    {
        first = head->next;
        if (head->data)
        {
            delete[] head->data;
            head->data = NULL;
        }
        delete[] head;
        head = first;
    }
}
