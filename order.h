#pragma once
#include <string>
using namespace std;

class OrderItem
{
public:
    string item_name;
    double item_price;
    OrderItem *next;
    OrderItem(string name, double price);
};

class Order
{
public:
    int order_number;
    string student_name;
    string student_surname;
    string student_id;
    string order_status;
    OrderItem *order_items_head;
    Order *next;

    Order(int num, string name, string surname, string id);
    void add_item(string name, double price);
    void remove_item(string name);
    void display_order_items();
};
