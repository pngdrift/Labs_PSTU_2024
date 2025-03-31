// 11. *char(строка символов), очередь

#include <cstring>
#include <iostream>

struct QueueCharrItem
{
    char *data;
    QueueCharrItem *next;
};

struct CharrQueue
{
    QueueCharrItem *front = nullptr;
    QueueCharrItem *back = nullptr;
    int size = 0;

    void push(char *data)
    {
        QueueCharrItem *elem = new QueueCharrItem();
        elem->data = data;
        elem->next = nullptr;
        if (size == 0)
        {
            front = back = elem;
        }
        else
        {
            back->next = elem;
            back = elem;
        }
        ++size;
    }

    char *pop()
    {
        char *result = front->data;
        QueueCharrItem *tmp = front;
        if (size == 1)
        {
            back = nullptr;
        }
        front = front->next;
        delete tmp;
        --size;
        return result;
    }
};

CharrQueue *createQueue(int size)
{
    CharrQueue *queue = new CharrQueue;
    char *data;
    for (int i = 0; i < size; ++i)
    {
        data = new char[100];
        std::cout << i + 1 << " element: ";
        std::cin >> data;
        queue->push(data);
    }
    return queue;
}

void showQueue(CharrQueue *queue)
{
    std::cout << "Queue:\n";
    for (QueueCharrItem *elem = queue->front; elem != nullptr; elem = elem->next)
    {
        std::cout << elem->data << "\n";
    }
}

int findElem(char *e, CharrQueue *queue)
{
    int index = 0;
    for (QueueCharrItem *elem = queue->front; elem != nullptr; elem = elem->next)
    {
        if (std::strcmp(elem->data, e) == 0)
        {
            return index;
        }
        ++index;
    }
    return -1;
}

void addInQueue(CharrQueue *queue, int index, char *elem)
{
    QueueCharrItem *newElem = new QueueCharrItem;
    newElem->data = elem;
    newElem->next = nullptr;
    if (index == 0)
    {
        newElem->next = queue->front;
        queue->front = newElem;
    }
    else
    {
        QueueCharrItem *prev = queue->front;
        for (int i = 0; i < index - 1; ++i)
        {
            prev = prev->next;
        }
        newElem->next = prev->next;
        prev->next = newElem;
    }
    ++queue->size;
}

void deleteInQueue(CharrQueue *queue, int index)
{
    QueueCharrItem *tmp;
    if (index == 0)
    {
        tmp = queue->front;
        queue->front = queue->front->next;
    }
    else
    {
        QueueCharrItem *prev = queue->front;
        for (int i = 0; i < index - 1; ++i)
        {
            prev = prev->next;
        }
        tmp = prev->next;
        prev->next = tmp->next;
    }
    delete tmp;
    --queue->size;
}

int main()
{
    int size;
    std::cout << "Queue size: ";
    std::cin >> size;
    CharrQueue *queue = createQueue(size);
    showQueue(queue);

    std::cout << "Enter new element to add and its index: ";
    char *elem = new char[100];
    int index;
    std::cin >> elem >> index;
    addInQueue(queue, index, elem);
    showQueue(queue);

    std::cout << "Enter element index to remove: ";
    std::cin >> index;
    deleteInQueue(queue, index);
    showQueue(queue);

    std::cout << "Enter element to Find: ";
    elem = new char[100];
    std::cin >> elem;

    int result = findElem(elem, queue);
    std::cout << "Result: " << result << '\n';
    return 0;
}
