#pragma once
#include <iostream>
#include <vector>
#include <cstring>
#include <Windows.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
using json = nlohmann::json;
using namespace std;

#pragma region IngredientClass

class Ingredient {

public:

    string name = "";
    double count = 0;
    double price = 0;

    Ingredient() {
        name = "";
        count = 0;
        price = 0;
    }

    Ingredient(string name, double count, double price) {
        this->name = name;
        this->count = count;
        this->price = price;
    }

    Ingredient(double count) {
        this->count = count;
    }

    virtual void ShowIngredient() {
        cout << name << " " << price << " AZN " << " - " << count << " eded" << "    ";
    }

};

#pragma endregion

#pragma region FoodClass

class Food {

public:

    string name = "";
    string info = "";
    double price = 0;

    vector<Ingredient*> ingredients;

    Food() {
        name = "";
        price = 0;
        info = "";
    }

    Food(string n, double c, string info) {
        this->info = info;
        name = n;
        price = c;
    }

    Food(string n, double c) {
        name = n;
        price = c;
    }

    void ShowFood() {
        system("cls");
        cout << "Food name : " << name
            << "\nFood info : " << info
            << "\nFood price : " << price << " AZN" << endl;
        cout << "\nIngredients" << endl;
        for (int i = 0; i < ingredients.size(); i++)
        {
            cout << i + 1 << ".";
            ingredients[i]->ShowIngredient();
            cout << endl;
        }
        cout << "\n0.Back";
    }

    virtual ~Food() {}
};

#pragma endregion

class Menu {

public:

    string name = " ";
    vector<Food*> foods;

    Menu() {
        name = " ";
    }

    Menu(string name) {
        this->name = name;
    }
};

class User {
public:
    string username;
    string password;


    User() {

        username = "default";
        password = "default";

    }

    User(string user, string pass) {

        username = user;
        password = pass;

    }

};

class Data {

public:
    string username;
    string time;
    vector<Food*> foods;

    Data() {

        username = "default";
        time = "default";

    }

    Data(string username, char* time) {
        this->username = username;
        this->time = time;
    }


};

class AdminData {
public:
    int money = 0;
    int profit = 0;
    int cost = 0;
    string temp = "";
    string date = "";
    string buydate = "";

    AdminData() = default;

    AdminData(int m, double c, char* time, string t) {
        money = m;
        cost = c;
        buydate = time;
        temp = t;
    }

    AdminData(int m, int pr, char* time) {
        money = m;
        profit = pr;
        date = time;
    }

};

