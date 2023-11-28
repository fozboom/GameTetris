#ifndef TETRIS_QUEUE_H
#define TETRIS_QUEUE_H
#include <iostream>
#include "Exceptions.h"

template<typename T>
class Queue {
private:
    struct Node
    {
        T data;
        Node *next;
        explicit Node(T data = 0, Node *next = nullptr) : data(data), next(next) {}
    };
    Node *head;
    Node *tail;
    int size;
public:
    // Конструктор
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор
    ~Queue()
    {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Добавление элемента в хвост
    void enqueue(T data)
    {
        Node *node = new Node(data, nullptr);
        if (tail)
        {
            tail->next = node;
        }
        else
        {
            head = node;
        }
        tail = node;
        size++;
    }

    // Удаление элемента из головы
    void dequeue()
    {
        if (isEmpty())
        {
            throw OutOfBoundsException("Очередь пуста, удалять нельзя");
        }
        Node* temp = head;
        head = head->next;
        size--;
        if (isEmpty())
        {
            tail = nullptr;
        }
    }

    // Получение элемента из начала очереди без удаления
    T front() const
    {
        if (head) return head->data;
        throw  OutOfBoundsException("Очередь пуста");
    }

    // Проверка очереди на пустоту
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Получение размера очереди
    int getSize() const
    {
        return size;
    }

    // Печать элементов очереди, начиная с головы
    void printQueue()
    {
        Node* current = head;
        while(current)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Копирование очереди
    Queue(const Queue<T>& other) : head(nullptr), tail(nullptr), size(0)
    {
        Node *cur = other.head;
        while (cur != nullptr)
        {
            enqueue(cur->data);
            cur = cur->next;
        }
    }

    // Перегрузка оператора присваивания
    Queue<T>& operator=(Queue<T> other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
        std::swap(size, other.size);
        return *this;
    }

    // Перегрузка оператора равенства
    bool operator==(const Queue<T>& other) const
    {
        if (size != other.size)
        {
            return false;
        }
        Node* cur1 = head;
        Node* cur2 = other.head;
        while (cur1 != nullptr && cur2 != nullptr)
        {
            if (cur1->data != cur2->data)
            {
                return false;
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        return true;
    }
};

#endif //TETRIS_QUEUE_H