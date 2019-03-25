#include <iostream>
#include "MyMap.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

int main(int argc, char* argv[]) {
    MyMap<int, int> example;
    example.Insert(5,0);
    example.Insert(10,0);
    example.Insert(15,0);
    example.Show();

    example.GetKeys().Show();
    example.GetValue().Show();
    example.GetColor().Show();

    /*MyMap<char, char> example;
    example.Insert('a','a');
    example.Insert('b','b');
    example.Insert('c','c');
    example.Show(example.GetRoot(),0);

    example.GetKeys().Show();
    example.GetValue().Show();
    example.GetColor().Show();*/

    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}