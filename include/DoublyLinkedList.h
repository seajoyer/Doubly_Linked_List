#pragma once

#include <iostream>
#include <vector>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void push_front(const T& value);
    void push_back(const T& value);
    void insert(size_t position, const T& value);
    void insert(size_t position, const std::vector<T>& values);
    void insert(size_t position, const DoublyLinkedList<T>& other);
    void remove(size_t position);
    T pop_front();
    T pop_back();

    void concatenate(const DoublyLinkedList<T>& other);
    bool compare(const DoublyLinkedList<T>& other) const;
    size_t find(const T& value) const;

    void save_to_file(const std::string& filename) const;
    void load_from_file(const std::string& filename);

    size_t get_size() const { return size; }
    bool is_empty() const { return size == 0; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<U>& list);
    template <typename U>
    friend std::istream& operator>>(std::istream& is, DoublyLinkedList<U>& list);
};

#include "../src/DoublyLinkedList.hpp"
