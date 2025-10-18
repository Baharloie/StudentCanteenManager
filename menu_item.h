#pragma once
#include <string>
using namespace std;

class MenuItem
{
public:
    string item_name;
    double item_price;
    MenuItem(string name, double price);
};
