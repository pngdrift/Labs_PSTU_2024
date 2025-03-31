// 11. *char(строка символов), стек

#include <cstring>
#include <iostream>

struct StackCharrElem
{
    char *data;
    StackCharrElem *next;
};

struct CharrStack
{
    int size = 0;
    StackCharrElem *top = nullptr;

    void push(char *data)
    {
        StackCharrElem *elem = new StackCharrElem();
        elem->data = data;
        elem->next = top;
        top = elem;
        ++size;
    }

    char *pop()
    {
        char *result = top->data;
        StackCharrElem *temp = top;
        top = top->next;
        --size;
        delete temp;
        return result;
    }
};

CharrStack *createStack(int size)
{
    CharrStack *stack = new CharrStack();
    char *data;
    for (int i = 0; i < size; ++i)
    {
        data = new char[100];
        std::cout << i + 1 << " element: ";
        std::cin >> data;
        stack->push(data);
    }
    return stack;
}

void showStack(CharrStack *stack)
{
    std::cout << "Stack:\n";
    for (StackCharrElem *elem = stack->top; elem != nullptr; elem = elem->next)
    {
        std::cout << elem->data << "\n";
    }
}

int findElem(char *e, CharrStack *stack)
{
    int i = 0;
    for (StackCharrElem *elem = stack->top; elem != nullptr; elem = elem->next)
    {
        if (std::strcmp(elem->data, e) == 0)
        {
            return i;
        }
        ++i;
    }
    return -1;
}

void addInStack(CharrStack *stack, int index, char *elem)
{
    CharrStack *tmpStack = new CharrStack();
    for (int i = 0; i < index; ++i)
    {
        tmpStack->push(stack->pop());
    }
    stack->push(elem);
    int size = tmpStack->size;
    for (int i = 0; i < size; ++i)
    {
        stack->push(tmpStack->pop());
    }
    delete tmpStack;
}

void deleteInStack(CharrStack *stack, int index)
{
    CharrStack *tmpStack = new CharrStack();
    for (int i = 0; i < index; ++i)
    {
        tmpStack->push(stack->pop());
    }
    stack->pop();
    int size = tmpStack->size;
    for (int i = 0; i < size; ++i)
    {
        stack->push(tmpStack->pop());
    }
    delete tmpStack;
}

int main()
{
    int size;
    std::cout << "Stack size: ";
    std::cin >> size;
    CharrStack *stack = createStack(size);
    showStack(stack);

    std::cout << "Enter new element to add and its index: ";
    char *elem = new char[100];
    int index;
    std::cin >> elem >> index;
    addInStack(stack, index, elem);
    showStack(stack);

    std::cout << "Enter element index to remove: ";
    std::cin >> index;
    deleteInStack(stack, index);
    showStack(stack);

    std::cout << "Enter element to Find: ";
    elem = new char[100];
    std::cin >> elem;

    int result = findElem(elem, stack);
    std::cout << "Result: " << result << '\n';
    return 0;
}
