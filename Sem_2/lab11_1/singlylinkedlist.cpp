// 11. *char(строка символов), односвязный список

#include <cstring>
#include <iostream>

struct CharrListItem
{
    char *data;
    CharrListItem *next;
};

CharrListItem *makeList(int size)
{
    if (size <= 0)
    {
        return nullptr;
    }
    CharrListItem *head = new CharrListItem();
    std::cout << "elements:\n";
    head->data = new char[100];
    std::cin >> head->data;
    CharrListItem *prev = head;
    for (int i = 1; i < size; ++i)
    {
        CharrListItem *elem = new CharrListItem();
        elem->next = nullptr;
        elem->data = new char[100];
        std::cin >> elem->data;
        prev->next = elem;
        prev = elem;
    }
    return head;
}

void printList(CharrListItem *first)
{
    for (CharrListItem *item = first; item != nullptr; item = item->next)
    {
        std::cout << item->data << "\n";
    }
}

CharrListItem *removeAt(CharrListItem *first, int pos)
{
    if (pos == 0)
    {
        CharrListItem *tmp = first;
        first = first->next;
        delete tmp;
    }
    else
    {
        int i = 1;
        for (CharrListItem *item = first; item != nullptr; item = item->next)
        {
            if (i == pos)
            {
                CharrListItem *tmp = item->next;
                item->next = tmp->next;
                delete tmp;
                break;
            }
            ++i;
        }
    }
    return first;
}

CharrListItem *addAt(CharrListItem *first, char *data, int pos)
{
    if (pos == 0)
    {
        CharrListItem *elem = new CharrListItem();
        elem->data = data;
        elem->next = first;
        first = elem;
    }
    else
    {
        int i = 1;
        for (CharrListItem *item = first; item != nullptr; item = item->next)
        {
            if (i == pos)
            {
                CharrListItem *elem = new CharrListItem();
                elem->data = data;
                elem->next = item->next;
                item->next = elem;
                break;
            }
            ++i;
        }
    }
    return first;
}

int findElem(char *elem, CharrListItem *first)
{
    int i = 1;
    for (CharrListItem *item = first; item != nullptr; item = item->next)
    {
        if (strcmp(item->data, elem) == 0)
        {
            return i;
        }
        ++i;
    }
    return -1;
}

int main()
{
    std::cout << "List size: ";
    int size;
    std::cin >> size;
    CharrListItem *start = makeList(size);

    std::cout << "\nResult list:\n";
    printList(start);

    std::cout << "Enter new element to add and its position: ";
    char *data = new char[100];
    int pos;
    std::cin >> data >> pos;
    start = addAt(start, data, pos);

    std::cout << "\nNew list after add:\n";

    printList(start);

    std::cout << "Enter element position to remove: ";
    std::cin >> pos;
    start = removeAt(start, pos);

    std::cout << "\nNew list after remove:\n";
    printList(start);

    std::cout << "Enter element to Find: ";
    char *elem = new char[100];
    std::cin >> elem;

    int result = findElem(elem, start);

    std::cout << "\nResult position: " << result;

    return 0;
}
