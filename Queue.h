#ifndef TETRIS_QUEUE_H
#define TETRIS_QUEUE_H
#include <iostream>
#include "Exceptions.h"

// Определяем шаблонный класс Queue (очередь)
template<typename T>
class Queue {
private:
    // Внутренний класс Node (узел), представляет собой элемент очереди
    struct Node
    {
        T data;         // Данные узла
        Node *next;     // Указатель на следующий узел в очереди
        explicit Node(T data = 0, Node *next = nullptr) : data(data), next(next) {}  // Конструктор узла
    };

    Node *head;   // Указатель на голову (начало) очереди
    Node *tail;   // Указатель на хвост (конец) очереди
    int size;     // Размер очереди

public:
    // Конструктор очереди
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор очереди, освобождает память занятую узлами
    ~Queue()
    {
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Метод добавления элемента в конец очереди
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

    // Метод удаления элемента из начала очереди
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

    // Метод для получения элемента из начала очереди без его удаления
    T front() const
    {
        if (head) return head->data;
        throw  OutOfBoundsException("Очередь пуста");
    }

    // Метод проверки очереди на пустоту
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Метод возвращает размер очереди
    int getSize() const
    {
        return size;
    }

    // Метод печатает элементы очереди, начиная с головы
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

    // Конструктор копирования
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

    // Перегрузка оператора сравнения на равенство
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