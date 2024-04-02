#pragma once
#include "Ingredient.h"

class Database {
public:
    double money = 1500;

    vector<Ingredient*> ingredients;
    vector<Food*> foods;
    vector<Menu*> Menus;
    vector<Food*> Cart;
    vector<User*> users;
    vector<Data*> userdatas;
    vector<AdminData*> admindatas;
    string admin = "admin";
    string adminpass = "admin123";

    void ShowIngredients(vector<Ingredient*>& val) {
        cout << "Ingredients" << endl;
        for (int i = 0; i < val.size(); i++)
        {
            cout << i + 1 << ". ";
            val[i]->ShowIngredient();
            if ((i + 1) % 2 == 0)
                cout << endl;
            else
                cout << "\t";
        }
    }

    bool CheckFood(Food* val) {
        bool cond = false;
        for (int i = 0; i < val->ingredients.size(); i++)
        {
            for (int j = 0;j < ingredients.size();j++) {
                if (val->ingredients[i]->name == ingredients[j]->name) {
                    if (val->ingredients[i]->count <= ingredients[j]->count)
                    {
                        cond = true;
                    }
                    else
                        cond = false;
                }
            }
        }
        if (cond)
            return true;
        else
            return false;
    }

    void ShowMenu(vector<Food*> val) {
        system("cls");
        vector<Food*> temp;
        for (int i = 0; i < val.size(); i++)
        {
            if (CheckFood(val[i]))
            {
                temp.push_back(val[i]);
            }
        }
        cout << "Current Menu" << endl;
        for (int i = 0; i < temp.size(); i++)
        {
            cout << i + 1 << ". ";
            cout << temp[i]->name;
            cout << "  ";
            cout << temp[i]->price << " AZN";
            if ((i + 1) % 2 == 0)
                cout << endl;
            else
                cout << "        ";
        }
        cout << "0.Back" << endl;
    }
};
