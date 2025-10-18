#pragma once
#include <vector>
#include "order.h"
#include "menu_item.h"
using namespace std;

class RestaurantSystem
{
public:
    vector<MenuItem> menu_items;
    Order *order_head;
    int order_counter;

    RestaurantSystem();
    void load_menu();
    void save_data();
    void load_data();
    void add_order_node(Order *new_order);
    void display_menu();
    void create_new_order();
    Order *find_order(int num);
    void mark_order_delivered();
    void cancel_order();
    void change_order();
    void review_orders();
    void main_menu();
};
