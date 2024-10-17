#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "../include/DoublyLinkedList.h"

TEST_CASE("DoublyLinkedList operations", "[doubly_linked_list]") {
    DoublyLinkedList<int> list;

    SECTION("Push and pop operations") {
        list.push_back(1);
        list.push_back(2);
        list.push_front(0);

        REQUIRE(list.get_size() == 3);
        REQUIRE(list.pop_front() == 0);
        REQUIRE(list.pop_back() == 2);
        REQUIRE(list.get_size() == 1);
    }

    SECTION("Insertion operations") {
        list.push_back(1);
        list.push_back(3);
        list.insert(1, 2);

        REQUIRE(list.get_size() == 3);
        REQUIRE(list.pop_front() == 1);
        REQUIRE(list.pop_front() == 2);
        REQUIRE(list.pop_front() == 3);
    }

    SECTION("Insert vector of elements") {
        std::vector<int> values = {4, 5, 6};
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.insert(1, values);

        REQUIRE(list.get_size() == 6);
        REQUIRE(list.pop_front() == 1);
        REQUIRE(list.pop_front() == 4);
        REQUIRE(list.pop_front() == 5);
        REQUIRE(list.pop_front() == 6);
        REQUIRE(list.pop_front() == 2);
        REQUIRE(list.pop_front() == 3);
    }

    SECTION("Concatenation") {
        DoublyLinkedList<int> list1, list2;
        list1.push_back(1);
        list1.push_back(2);
        list2.push_back(3);
        list2.push_back(4);

        list1.concatenate(list2);

        REQUIRE(list1.get_size() == 4);
        REQUIRE(list1.pop_front() == 1);
        REQUIRE(list1.pop_front() == 2);
        REQUIRE(list1.pop_front() == 3);
        REQUIRE(list1.pop_front() == 4);
    }

    SECTION("Comparison") {
        DoublyLinkedList<int> list1, list2;
        list1.push_back(1);
        list1.push_back(2);
        list2.push_back(1);
        list2.push_back(2);

        REQUIRE(list1.compare(list2) == true);

        list2.push_back(3);
        REQUIRE(list1.compare(list2) == false);
    }

    SECTION("Find operation") {
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        REQUIRE(list.find(2) == 1);
        REQUIRE(list.find(4) == list.get_size());
    }

    SECTION("File I/O") {
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.save_to_file("test_list.bin");

        DoublyLinkedList<int> loaded_list;
        loaded_list.load_from_file("test_list.bin");

        REQUIRE(list.compare(loaded_list) == true);
    }

    SECTION("Stream I/O") {
        std::stringstream ss;
        ss << "1 2 3 4 5";
        ss >> list;

        REQUIRE(list.get_size() == 5);
        REQUIRE(list.pop_front() == 1);
        REQUIRE(list.pop_back() == 5);

        std::stringstream output;
        output << list;
        REQUIRE(output.str() == "2 3 4 ");
    }
}
