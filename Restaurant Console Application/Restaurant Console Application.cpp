#include "Functions.h"

int main() {

    Database dt;

#pragma region FileWrite
    if (CheckFileSize("menus.json") != 0) {
        json j = json::array();
        from_json_ingredient(j, dt.ingredients);
    }
    if (CheckFileSize("ingredient.json") != 0) {
        json jf = json::array();
        from_json_food(jf, dt.foods);
    }
    if (CheckFileSize("foods.json") != 0)
    {
        json jm = json::array();
        from_json_menu(jm, dt.Menus);
    }
    if (CheckFileSize("users.json") != 0) {
        json ju = json::array();
        from_json_user(ju, dt.users);
    }
    if (CheckFileSize("datas.json") != 0) {
        json ju = json::array();
        from_json_data(ju, dt.userdatas);
    }
    if (CheckFileSize("admindatas.json") != 0) {
        json ja = json::array();
        from_json_admin_data(ja, dt.admindatas);
    }
#pragma endregion

    label:
    system("cls");
    cout << "Welcome to our restaurant.." << endl;
    cout << "1.Admin" << endl << "2.User" << endl << "0.Quit" << endl;
    string choice;
    cin >> choice;
    if (choice != "1" && choice != "2" && choice != "0") {
        cout << "Wrong choice,try again" << endl;
        Sleep(1000);
        goto label;
    }
    else if (choice == "1") {
        system("cls");
    label1:
        string username;
        string password;
        cout << "Please,Log in..." << endl;
        cout << "Enter username :" << endl;
        cin >> username;
        cout << "Enter password :" << endl;
        cin >> password;
        if (LoginCheck(dt.admin, dt.adminpass, username, password)) {
            Loading();
            system("cls");
            if (AdminMenu(dt) == "0")
                goto label;
        }
        else {
            cout << "Wrong username or password,try again..." << endl;
            goto label1;
        }
    }
    else if (choice == "2") {
        if (ShowMenuOptionsUser(dt) == "0") {
            goto label;
        }
    }
    else if (choice == "0") {
        if (dt.Cart.size() > 0)
        {
            system("cls");
            cout << "Please make payment...";
            Sleep(3000);
            goto label;
        }
    }
}

