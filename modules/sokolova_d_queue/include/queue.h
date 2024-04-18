// Copyright 2024 Sokolova Daria

#ifndef MODULES_SOKOLOVA_D_QUEUE_INCLUDE_QUEUE_H_
#define MODULES_SOKOLOVA_D_QUEUE_INCLUDE_QUEUE_H_

#include <iostream>
#include <stdexcept>


template <class ValueType>
class  Queue {
 private:
    ValueType* buffer;
    size_t head;
    size_t tail;
    size_t count;
    size_t capacity;

 public:
    explicit Queue(size_t size = 10);
    ~Queue();
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);

    bool isEmpty() const;
    bool isFull() const;
    void enqueue(const ValueType& element);
    void dequeue();
    const ValueType& front() const;
    const ValueType& back() const;
    size_t size() const;
};

template <class ValueType>
Queue<ValueType>::Queue(size_t size)
    : buffer(new ValueType[size]), head(0),
    tail(0), count(0), capacity(size) {}

template <class ValueType>
Queue<ValueType>::~Queue() {
    delete[] buffer;
}

template <class ValueType>
Queue<ValueType>::Queue(const Queue& other)
    : buffer(new ValueType[other.capacity]),
    head(other.head),
    tail(other.tail),
    count(other.count),
    capacity(other.capacity) {
    for (size_t i = 0; i < count; ++i) {
        buffer[i] = other.buffer
            [(other.head + i) % other.capacity];
    }
}

template <class ValueType>
Queue<ValueType>& Queue<ValueType>::
operator=(const Queue& other) {
    if (this != &other) {
        delete[] buffer;

        buffer = new ValueType[other.capacity];
        head = other.head;
        tail = other.tail;
        count = other.count;
        capacity = other.capacity;

        for (size_t i = 0; i < count; ++i) {
            buffer[i] = other.buffer
                [(other.head + i) % other.capacity];
        }
    }
    return *this;
}

template <class ValueType>
bool Queue<ValueType>::isEmpty() const {
    return count == 0;
}

template <class ValueType>
bool Queue<ValueType>::isFull() const {
    return count == capacity;
}

template <class ValueType>
void Queue<ValueType>::enqueue(
    const ValueType& element) {
    if (isFull()) {
        throw std::runtime_error("Queue is full");
    }
    buffer[tail] = element;
    tail = (tail + 1) % capacity;
    ++count;
}

template <class ValueType>
void Queue<ValueType>::dequeue() {
    if (!isEmpty()) {
        head = (head + 1) % capacity;
        --count;
    } else {
        throw std::runtime_error("Queue is empty");
    }
}

template <class ValueType>
const ValueType& Queue<ValueType>::front() const {
    if (!isEmpty()) {
        return buffer[head];
    } else { throw std::runtime_error("Queue is empty");
    }
}

template <class ValueType>
const ValueType& Queue<ValueType>::back() const {
    if (!isEmpty()) {
        return buffer[(tail + capacity - 1) % capacity];
    } else {
        throw std::runtime_error("Queue is empty");
    }
}

template <class ValueType>
size_t Queue<ValueType>::size() const {
    return count;
}


#endif  // MODULES_SOKOLOVA_D_QUEUE_INCLUDE_QUEUE_H_
