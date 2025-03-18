// 11. *char(строка символов), двухсвязный список

#include <cstring>
#include <iostream>

struct Node
{
    char *data;
    Node *next;
    Node *prev;
};

struct CharrList
{
    Node *head;
    Node *tail;

    void pushFront(char *value)
    {
        Node *newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        newNode->prev = nullptr;

        if (head != nullptr)
        {
            head->prev = newNode;
        }
        head = newNode;

        if (tail == nullptr)
        {
            tail = newNode;
        }
    }

    void pushBack(char *value)
    {
        Node *newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail != nullptr)
        {
            tail->next = newNode;
        }
        tail = newNode;

        if (head == nullptr)
        {
            head = newNode;
        }
    }

    void popFront()
    {
        if (head == nullptr)
        {
            return;
        }
        Node *temp = head;
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        delete temp;
    }

    void popBack()
    {
        if (tail == nullptr)
        {
            return;
        }
        Node *temp = tail;
        tail = tail->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete temp;
    }

    int size()
    {
        int count = 0;
        Node *current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }

    void addAt(int index, char *elem)
    {
        if (index == 0)
        {
            pushFront(elem);
        }
        else if (index == size())
        {
            pushBack(elem);
        }
        else
        {
            Node *newNode = new Node();
            newNode->data = elem;

            Node *current = head;
            for (int i = 0; i < index - 1; i++)
            {
                current = current->next;
            }

            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
        }
    }

    void deleteAt(int index)
    {
        if (index == 0)
        {
            popFront();
        }
        else if (index == size() - 1)
        {
            popBack();
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
    }
};

CharrList *createList(int size)
{
    CharrList *result = new CharrList();
    std::cout << "elemetns: ";
    for (int i = 0; i < size; i++)
    {
        char *elem = new char[100];
        std::cin >> elem;
        result->pushBack(elem);
    }
    return result;
}

void printList(CharrList *list)
{
    std::cout << "List: ";
    Node *current = list->head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int findElem(char *elem, CharrList *list)
{
    int i = 1;
    for (Node *item = list->head; item != nullptr; item = item->next)
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
    CharrList *list = createList(size);
    printList(list);

    std::cout << "Enter new element to add and its index: ";
    char *elem = new char[100];
    int index;
    std::cin >> elem >> index;
    list->addAt(index, elem);
    printList(list);

    std::cout << "Enter element index to remove: ";
    std::cin >> index;
    list->deleteAt(index);
    printList(list);

    std::cout << "Enter element to Find: ";
    elem = new char[100];
    std::cin >> elem;

    int result = findElem(elem, list);

    std::cout << "Result position: " << result << '\n';
    return 0;
}
