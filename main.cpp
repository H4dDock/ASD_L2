#include <iostream>
#include "MyMap.h"

using namespace std;

int main() {
    MyMap<int, int> example;
    example.Insert(5,0);
    example.Insert(7,0);
    example.Insert(6,0);
    example.Insert(1,0);
    example.Remove(1);
    example.Show(example.GetRoot(),0);
    //example.clear(example.GetRoot());
    //example.Show(example.GetRoot(),0);

    example.GetKeys().Show();
    example.GetValue().Show();

    return 0;
}