#pragma once

template<typename T>
class Queue{
private:
    struct Node
    {
        T* data;
        Node* link;
    };

    Node* head;
    Node* tail;
public:
    Queue();
    void Enqueue(T*);
    void Dequeue();
    bool IsEmpty();
    void EmptyQueue();
    T* GetHead();

    ~Queue();
};


template<typename T>
Queue<T>::~Queue() { delete head, tail; }

template<typename T>
Queue<T>::Queue()
{
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void Queue<T>::Enqueue(T* data)
{
    Node* temp = new Node();
    temp->data = data;
    temp->link = nullptr;

    if (head == nullptr && tail == nullptr)
    {
        head = tail = temp;
        return;
    }

    tail->link = temp;
    tail = temp;
}

template<typename T>
void Queue<T>::Dequeue()
{
    Node* temp = head;

    if (head == nullptr)
    {
        return;
    }

    if (head == tail)
    {
        head = tail = nullptr;
    }
    else
    {
        head = head->link;
    }

    delete temp;
}

template<typename T>
bool Queue<T>::IsEmpty()
{
    if (head == nullptr || tail == nullptr)
        return true;
    else
        return false;
}

template<typename T>
void Queue<T>::EmptyQueue()
{
    if (head == nullptr && tail == nullptr)
    {
        return;
    }

    Node* temp = nullptr;
    while (head != nullptr)
    {
        temp = head;
        head = head->link;
        delete temp;
        temp = nullptr;
    }

    tail = nullptr;
}

template<typename T>
T* Queue<T>::GetHead()
{
    if (head != nullptr)
    {
        return head->data;
    }
    return nullptr;
}