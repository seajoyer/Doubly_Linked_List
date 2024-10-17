#pragma once

#include "../include/DoublyLinkedList.h"
#include <stdexcept>

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!is_empty()) {
        pop_front();
    }
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++size;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);
    if (is_empty()) {
        head = tail = new_node;
    } else {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    ++size;
}

template <typename T>
void DoublyLinkedList<T>::insert(size_t position, const T& value) {
    if (position > size) {
        throw std::out_of_range("Invalid position");
    }
    if (position == 0) {
        push_front(value);
    } else if (position == size) {
        push_back(value);
    } else {
        Node* current = head;
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        Node* new_node = new Node(value);
        new_node->prev = current->prev;
        new_node->next = current;
        current->prev->next = new_node;
        current->prev = new_node;
        ++size;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(size_t position, const std::vector<T>& values) {
    for (const auto& value : values) {
        insert(position++, value);
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(size_t position, const DoublyLinkedList<T>& other) {
    Node* current = other.head;
    while (current) {
        insert(position++, current->data);
        current = current->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::remove(size_t position) {
    if (position >= size) {
        throw std::out_of_range("Invalid position");
    }
    if (position == 0) {
        pop_front();
    } else if (position == size - 1) {
        pop_back();
    } else {
        Node* current = head;
        for (size_t i = 0; i < position; ++i) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --size;
    }
}

template <typename T>
T DoublyLinkedList<T>::pop_front() {
    if (is_empty()) {
        throw std::runtime_error("List is empty");
    }
    Node* temp = head;
    T value = temp->data;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    --size;
    return value;
}

template <typename T>
T DoublyLinkedList<T>::pop_back() {
    if (is_empty()) {
        throw std::runtime_error("List is empty");
    }
    Node* temp = tail;
    T value = temp->data;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    --size;
    return value;
}

template <typename T>
void DoublyLinkedList<T>::concatenate(const DoublyLinkedList<T>& other) {
    Node* current = other.head;
    while (current) {
        push_back(current->data);
        current = current->next;
    }
}

template <typename T>
bool DoublyLinkedList<T>::compare(const DoublyLinkedList<T>& other) const {
    if (size != other.size) {
        return false;
    }
    Node* current1 = head;
    Node* current2 = other.head;
    while (current1) {
        if (current1->data != current2->data) {
            return false;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return true;
}

template <typename T>
size_t DoublyLinkedList<T>::find(const T& value) const {
    Node* current = head;
    size_t position = 0;
    while (current) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        ++position;
    }
    return size;  // Return size if not found
}

template <typename T>
void DoublyLinkedList<T>::save_to_file(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing");
    }
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    Node* current = head;
    while (current) {
        file.write(reinterpret_cast<const char*>(&current->data), sizeof(T));
        current = current->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::load_from_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for reading");
    }
    size_t loaded_size;
    file.read(reinterpret_cast<char*>(&loaded_size), sizeof(loaded_size));
    while (!is_empty()) {
        pop_front();
    }
    for (size_t i = 0; i < loaded_size; ++i) {
        T value;
        file.read(reinterpret_cast<char*>(&value), sizeof(T));
        push_back(value);
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
    typename DoublyLinkedList<T>::Node* current = list.head;
    while (current) {
        os << current->data << " ";
        current = current->next;
    }
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, DoublyLinkedList<T>& list) {
    T value;
    while (is >> value) {
        list.push_back(value);
    }
    return is;
}
