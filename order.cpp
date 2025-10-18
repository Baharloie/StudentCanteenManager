#include "order.h"
#include <iostream>
using namespace std;

OrderItem::OrderItem(string name, double price)
{
    item_name = name;
    item_price = price;
    next = nullptr;
}

Order::Order(int num, string name, string surname, string id)
{
    order_number = num;
    student_name = name;
    student_surname = surname;
    student_id = id;
    order_status = "In Progress";
    order_items_head = nullptr;
    next = nullptr;
}

void Order::add_item(string name, double price)
{
    OrderItem *new_item = new OrderItem(name, price);
    if (!order_items_head)
        order_items_head = new_item;
    else
    {
        OrderItem *temp = order_items_head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_item;
    }
}

void Order::remove_item(string name)
{
    OrderItem *temp = order_items_head;
    OrderItem *prev = nullptr;
    while (temp && temp->item_name != name)
    {
        prev = temp;
        temp = temp->next;
    }
    if (!temp)
        return;
    if (!prev)
        order_items_head = temp->next;
    else
        prev->next = temp->next;
    delete temp;
}

void Order::display_order_items()
{
    OrderItem *temp = order_items_head;
    while (temp)
    {
        cout << "  - " << temp->item_name << " ($" << temp->item_price << ")\n";
        temp = temp->next;
    }
}
