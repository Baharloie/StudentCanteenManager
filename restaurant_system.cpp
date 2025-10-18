#include "restaurant_system.h"
#include <iostream>
#include <fstream>
using namespace std;

RestaurantSystem::RestaurantSystem()
{
    order_head = nullptr;
    order_counter = 1;
    load_data();
    load_menu();
}

void RestaurantSystem::load_menu()
{
    menu_items.push_back(MenuItem("Pizza", 8.99));
    menu_items.push_back(MenuItem("Burger", 5.49));
    menu_items.push_back(MenuItem("Pasta", 6.99));
    menu_items.push_back(MenuItem("Salad", 4.50));
    menu_items.push_back(MenuItem("Juice", 2.99));
    menu_items.push_back(MenuItem("Water", 1.00));
}

void RestaurantSystem::save_data()
{
    ofstream file("orders.txt");
    Order *temp = order_head;
    while (temp)
    {
        file << temp->order_number << "," << temp->student_name << "," << temp->student_surname << "," << temp->student_id << "," << temp->order_status;
        OrderItem *item = temp->order_items_head;
        while (item)
        {
            file << "," << item->item_name << "," << item->item_price;
            item = item->next;
        }
        file << "\n";
        temp = temp->next;
    }
    file.close();
}

void RestaurantSystem::load_data()
{
    ifstream file("orders.txt");
    if (!file.is_open())
        return;
    string line;
    while (getline(file, line))
    {
        vector<string> tokens;
        string token;
        for (char c : line)
        {
            if (c == ',')
            {
                tokens.push_back(token);
                token.clear();
            }
            else
                token += c;
        }
        tokens.push_back(token);
        if (tokens.size() < 5)
            continue;
        Order *new_order = new Order(stoi(tokens[0]), tokens[1], tokens[2], tokens[3]);
        new_order->order_status = tokens[4];
        for (size_t i = 5; i + 1 < tokens.size(); i += 2)
            new_order->add_item(tokens[i], stod(tokens[i + 1]));
        add_order_node(new_order);
        order_counter = max(order_counter, new_order->order_number + 1);
    }
    file.close();
}

void RestaurantSystem::add_order_node(Order *new_order)
{
    if (!order_head)
        order_head = new_order;
    else
    {
        Order *temp = order_head;
        while (temp->next)
            temp = temp->next;
        temp->next = new_order;
    }
}

void RestaurantSystem::display_menu()
{
    cout << "\n--- Restaurant Menu ---\n";
    for (size_t i = 0; i < menu_items.size(); ++i)
        cout << i + 1 << ". " << menu_items[i].item_name << " ($" << menu_items[i].item_price << ")\n";
}

void RestaurantSystem::create_new_order()
{
    string name, surname, id;
    cout << "Enter student name: ";
    cin >> name;
    cout << "Enter student surname: ";
    cin >> surname;
    cout << "Enter student ID: ";
    cin >> id;
    Order *new_order = new Order(order_counter++, name, surname, id);
    display_menu();
    int choice;
    while (true)
    {
        cout << "Enter item number to add (0 to finish): ";
        cin >> choice;
        if (choice == 0)
            break;
        if (choice > 0 && choice <= (int)menu_items.size())
            new_order->add_item(menu_items[choice - 1].item_name, menu_items[choice - 1].item_price);
    }
    add_order_node(new_order);
    save_data();
}

Order *RestaurantSystem::find_order(int num)
{
    Order *temp = order_head;
    while (temp && temp->order_number != num)
        temp = temp->next;
    return temp;
}

void RestaurantSystem::mark_order_delivered()
{
    int num;
    cout << "Enter order number: ";
    cin >> num;
    Order *order = find_order(num);
    if (!order)
        cout << "Order not found.\n";
    else
    {
        order->order_status = "Delivered";
        cout << "Order marked as delivered.\n";
        save_data();
    }
}

void RestaurantSystem::cancel_order()
{
    int num;
    cout << "Enter order number: ";
    cin >> num;
    Order *order = find_order(num);
    if (!order)
        cout << "Order not found.\n";
    else if (order->order_status == "Delivered")
        cout << "Cannot cancel a delivered order.\n";
    else
    {
        order->order_status = "Cancelled";
        cout << "Order cancelled.\n";
        save_data();
    }
}

void RestaurantSystem::change_order()
{
    int num;
    cout << "Enter order number: ";
    cin >> num;
    Order *order = find_order(num);
    if (!order)
        cout << "Order not found.\n";
    else if (order->order_status != "In Progress")
        cout << "Only active orders can be changed.\n";
    else
    {
        cout << "Current order items:\n";
        order->display_order_items();
        cout << "1. Add item\n2. Remove item\nChoose option: ";
        int opt;
        cin >> opt;
        if (opt == 1)
        {
            display_menu();
            int choice;
            cout << "Enter item number to add: ";
            cin >> choice;
            if (choice > 0 && choice <= (int)menu_items.size())
                order->add_item(menu_items[choice - 1].item_name, menu_items[choice - 1].item_price);
        }
        else if (opt == 2)
        {
            string name;
            cout << "Enter item name to remove: ";
            cin >> name;
            order->remove_item(name);
        }
        save_data();
    }
}

void RestaurantSystem::review_orders()
{
    Order *temp = order_head;
    if (!temp)
        cout << "No orders found.\n";
    while (temp)
    {
        cout << "\nOrder Number: " << temp->order_number << "\nName: " << temp->student_name << " " << temp->student_surname
             << "\nStudent ID: " << temp->student_id << "\nStatus: " << temp->order_status << "\nItems:\n";
        temp->display_order_items();
        temp = temp->next;
    }
}

void RestaurantSystem::main_menu()
{
    int choice;
    while (true)
    {
        cout << "\n--- Student Canteen Management ---\n1. View Menu\n2. New Order\n3. Mark Order Delivered\n4. Cancel Order\n5. Change Order\n6. Review Orders\n0. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 0)
            break;
        switch (choice)
        {
        case 1:
            display_menu();
            break;
        case 2:
            create_new_order();
            break;
        case 3:
            mark_order_delivered();
            break;
        case 4:
            cancel_order();
            break;
        case 5:
            change_order();
            break;
        case 6:
            review_orders();
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }
    save_data();
}
