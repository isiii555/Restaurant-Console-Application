#pragma once
#include "Database.h"
#include <cstring>
#include <string>

bool LoginCheck(string admin, string pass, string iadmin, string ipass) {
	if (admin == iadmin)
	{
		if (pass == ipass)
			return true;
		else
			return false;
	}
	return false;
}

void Loading() {
	cout << "Success,Loading";
	for (int i = 0; i < 3; i++)
	{
		cout << ".";
		Sleep(1000);
	}
	cout << endl;
}

void to_json_ingredient(json& js, vector<Ingredient*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		json j = json{ {"name", arr[i]->name}, {"count", arr[i]->count}, {"price", arr[i]->price} };
		js += j;
	}
	fstream f("ingredient.json", ios::out);
	f << js;
	f.close();
}

void from_json_ingredient(json& js, vector<Ingredient*>& arr) {
	fstream f("ingredient.json", ios::in);
	f >> js;
	f.close();
	for (int i = 0; i < js.size(); i++)
	{
		arr.push_back(new Ingredient());
		js.at(i).at("name").get_to(arr[i]->name);
		js.at(i).at("count").get_to(arr[i]->count);
		js.at(i).at("price").get_to(arr[i]->price);
	}
}

void to_json_food(json& js, vector<Food*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		json j = json{ {"name", arr[i]->name}, {"info", arr[i]->info}, {"price", arr[i]->price} };
		for (int c = 0; c < arr[i]->ingredients.size(); c++)
		{
			j["ingredients"] += { {"name", arr[i]->ingredients[c]->name}, { "count",arr[i]->ingredients[c]->count }, { "price",arr[i]->ingredients[c]->price }};
		}
		js += j;
	}
	fstream d("foods.json", ios::out);
	d << js;
	d.close();
}

void from_json_food(json& j, vector<Food*>& arr) {
	fstream f("foods.json", ios::in);
	f >> j;
	f.close();
	for (int i = 0; i < j.size(); i++)
	{
		arr.push_back(new Food());
		j.at(i).at("name").get_to(arr[i]->name);
		j.at(i).at("info").get_to(arr[i]->info);
		j.at(i).at("price").get_to(arr[i]->price);
		for (int c = 0; c < j[i]["ingredients"].size(); c++)
		{
			arr[i]->ingredients.push_back(new Ingredient());
			j.at(i).at("ingredients").at(c).at("name").get_to(arr[i]->ingredients[c]->name);
			j.at(i).at("ingredients").at(c).at("count").get_to(arr[i]->ingredients[c]->count);
			j.at(i).at("ingredients").at(c).at("price").get_to(arr[i]->ingredients[c]->price);
		}
	}
}

void to_json_menu(json& js, vector<Menu*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		json j = json{ {"name", arr[i]->name} };
		j["foods"] = json::array();
		for (int c = 0; c < arr[i]->foods.size(); c++) {
			json jj = {
				{"name", arr[i]->foods[c]->name},
				{ "info",arr[i]->foods[c]->info },
				{ "price",arr[i]->foods[c]->price },
				{ "ingredients", json::array() }
			};
			//json jj = j.at("foods").at("ingredients");
			for (int d = 0; d < arr[i]->foods[c]->ingredients.size(); d++)
			{
				jj["ingredients"] += {
					{"name", arr[i]->foods[c]->ingredients[d]->name},
					{ "count",arr[i]->foods[c]->ingredients[d]->count },
					{ "price",arr[i]->foods[c]->ingredients[d]->price }
				};
			}
			j["foods"] += jj;
		}
		js += j;
	}
	fstream f("menus.json", ios::out);
	f << js;
	f.close();
}

void from_json_menu(json& j, vector<Menu*>& arr) {
	fstream f("menus.json", ios::in);
	f >> j;
	f.close();
	for (int i = 0; i < j.size(); i++)
	{
		arr.push_back(new Menu());
		j.at(i).at("name").get_to(arr[i]->name);
		for (int c = 0; c < j[i]["foods"].size(); c++)
		{
			arr[i]->foods.push_back(new Food());
			j.at(i).at("foods").at(c).at("name").get_to(arr[i]->foods[c]->name);
			j.at(i).at("foods").at(c).at("info").get_to(arr[i]->foods[c]->info);
			j.at(i).at("foods").at(c).at("price").get_to(arr[i]->foods[c]->price);
			for (int d = 0; d < j[i].at("foods").at(c).at("ingredients").size(); d++)
			{
				arr[i]->foods[c]->ingredients.push_back(new Ingredient());
				j.at(i).at("foods").at(c).at("ingredients").at(d).at("name").get_to(arr[i]->foods[c]->ingredients[d]->name);
				j.at(i).at("foods").at(c).at("ingredients").at(d).at("count").get_to(arr[i]->foods[c]->ingredients[d]->count);
				j.at(i).at("foods").at(c).at("ingredients").at(d).at("price").get_to(arr[i]->foods[c]->ingredients[d]->price);
			}
		}
	}
}

void to_json_user(json& js, vector<User*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		json j = json{ {"username", arr[i]->username}, {"password", arr[i]->password} };
		js += j;
	}
	fstream f("users.json", ios::out);
	f << js;
	f.close();
}

void from_json_user(json& js, vector<User*>& arr) {
	fstream f("users.json", ios::in);
	f >> js;
	f.close();
	for (int i = 0; i < js.size(); i++)
	{
		arr.push_back(new User());
		js.at(i).at("username").get_to(arr[i]->username);
		js.at(i).at("password").get_to(arr[i]->password);
	}
}

void to_json_data(json& js, vector<Data*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		json j = json{ {"username", arr[i]->username}, {"time", arr[i]->time} };
		j["foods"] = json::array();
		for (int c = 0; c < arr[i]->foods.size(); c++)
		{
			j["foods"] += {
				{"name", arr[i]->foods[c]->name},
				{ "price", arr[i]->foods[c]->price }
			};
		}
		js += j;
	}
	fstream f("datas.json", ios::out);
	f << js;
	f.close();
}

void from_json_data(json& js, vector<Data*>& arr) {
	fstream f("datas.json", ios::in);
	f >> js;
	f.close();
	for (int i = 0; i < js.size(); i++)
	{
		arr.push_back(new Data());
		js.at(i).at("username").get_to(arr[arr.size() - 1]->username);
		js.at(i).at("time").get_to(arr[arr.size() - 1]->time);
		for (int c = 0; c < js[i]["foods"].size(); c++)
		{
			arr[arr.size() - 1]->foods.push_back(new Food);
			js[i]["foods"].at(c).at("name").get_to(arr[arr.size() - 1]->foods[arr[arr.size() - 1]->foods.size() - 1]->name);
			js[i]["foods"].at(c).at("price").get_to(arr[arr.size() - 1]->foods[arr[arr.size() - 1]->foods.size() - 1]->price);
		}
	}
}

void to_json_admin_data(json& js, vector<AdminData*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		json j = { {"balance",arr[i]->money},
			{"date",arr[i]->date},
			{"cost",arr[i]->cost},
			{"profit",arr[i]->profit} };
		js += j;
	}
	fstream f("admindatas.json", ios::out);
	f << js;
	f.close();
}

void from_json_admin_data(json& js, vector<AdminData*>& arr) {
	fstream f("admindatas.json", ios::in);
	f >> js;
	f.close();
	for (int i = 0; i < js.size(); i++)
	{
		arr.push_back(new AdminData());
		js[i]["balance"].get_to(arr[i]->money);
		js[i]["cost"].get_to(arr[i]->cost);
		js[i]["date"].get_to(arr[i]->date);
		js[i]["profit"].get_to(arr[i]->profit);
	}
}

string Lower(string val) {
	string temp = "";
	for (int i = 0; i < val.size(); i++)
	{
		temp.append(1, char(tolower(val[i])));
	}
	return temp;
}

string CheckIngredient(Database& dt, string name, double count, double price) {
	for (int i = 0; i < dt.ingredients.size(); i++)
	{
		if (Lower(dt.ingredients[i]->name) == Lower(name)) {
			if (dt.money - (count * price) >= 0)
			{
				dt.ingredients[i]->count += count;
				dt.ingredients[i]->price = price;
				system("cls");
				cout << "Succesfully added";
				dt.money = dt.money - (price * count);
				int cost = price * count;
#pragma warning(disable:4996)
				time_t now = time(0);
				char* dc = ctime(&now);
				dt.admindatas.push_back(new AdminData(dt.money, cost, dc, ""));
				Sleep(1000);
				return "1";
			}
			else {
				return "0";
			}
		}
	}
	if (dt.money - (price * count) >= 0)
	{
		dt.ingredients.push_back(new Ingredient(name, count, price));
		system("cls");
		cout << "Succesfully added";
		dt.money = dt.money - (price * count);
		int cost = price * count;
#pragma warning(disable:4996)
		time_t now = time(0);
		char* dc = ctime(&now);
		dt.admindatas.push_back(new AdminData(dt.money, cost, dc, ""));
		Sleep(1000);
		return "2";
	}
	return "0";
}

string CheckFood(Database& dt, string name, string info, double price) {
	for (int i = 0; i < dt.foods.size(); i++)
	{
		if (Lower(dt.foods[i]->name) == Lower(name)) {
			return "0";
		}
	}
	dt.foods.push_back(new Food(name, price, info));
labelfooding:
	int choice = 0;
	system("cls");
	dt.ShowIngredients(dt.ingredients);
	cout << "Add ingredient to your food :" << endl;
	cout << "0.Back" << endl;
	cin >> choice;
	if ((choice - 1) >= dt.ingredients.size() && choice != 0)
	{
		cout << "Wrong choice,try again" << endl;
		Sleep(1000);
		system("cls");
		goto labelfooding;
	}
	else if (choice == 0) {
		if (dt.foods[dt.foods.size() - 1]->ingredients.size() == 0) {
			dt.foods.erase(dt.foods.end() - 1);
		}
		return "2";
	}
	else
	{
		for (int i = 0; i < dt.foods[dt.foods.size() - 1]->ingredients.size(); i++)
		{
			if (dt.foods[dt.foods.size() - 1]->ingredients[i]->name == dt.ingredients[choice - 1]->name) {
				system("cls");
				cout << "This ingredient is already in this food" << endl;
				Sleep(1000);
				goto labelfooding;
			}
		}
		Ingredient* temp = new Ingredient(dt.ingredients[choice - 1]->name, dt.ingredients[choice - 1]->count, dt.ingredients[choice - 1]->price);
		dt.foods[dt.foods.size() - 1]->ingredients.push_back(temp);
		int count;
		cout << "Enter the count of ingredient : " << endl;
		cin >> count;
		dt.foods[dt.foods.size() - 1]->ingredients[(dt.foods[dt.foods.size() - 1]->ingredients.size()) - 1]->count = count;
	}
	system("cls");
	cout << "Succesfully added";
	Sleep(1000);
	goto labelfooding;
	return "1";
}

string UserMenu(Database& dt, vector<Food*> val) {

labeluser1:
	dt.ShowMenu(val);
	vector<Food*> temp;
	for (int i = 0; i < val.size(); i++)
	{
		if (dt.CheckFood(val[i]))
		{
			temp.push_back(val[i]);
		}
	}
	val = temp;
	int choice1 = 0;
	cout << "Enter the number of food which you want to buy : " << endl;
	cin >> choice1;
	if (choice1 - 1 >= val.size() && choice1 != 0) {
		cout << "Wrong number,try again" << endl;
		goto labeluser1;
	}
	else if (choice1 == 0) {
		return "0";
	}
	else {
		dt.Cart.push_back(val[choice1 - 1]);
		system("cls");
		cout << "Food succesfully added to your cart" << endl;
		Sleep(1000);
		goto labeluser1;
	}

}

bool SignIn(string username, string password, vector<User*>& arr) {
	for (int i = 0; i < arr.size(); i++)
	{
		if (username == arr[i]->username) {
			if (password == arr[i]->password)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool SignUp(string username, string password, vector<User*>& arr) {
	if (arr.size() != 0) {
		for (int i = 0; i < arr.size(); i++)
		{
			if (username == arr[i]->username)
			{
				return false;
			}
			else
			{
				arr.push_back(new User(username, password));
				json js = json::array();
				to_json_user(js, arr);
				return true;
			}
		}
	}
	else {
		arr.push_back(new User(username, password));
		json js = json::array();
		to_json_user(js, arr);
		return true;
	}
}

string ShowMenuOptionsUser(Database& dt) {

labelfunc:
	string username;
	string password;
	string choice3;
	system("cls");
	cout << "1.Sign In\n2.Sign Up\n0.Back" << endl;
	cin >> choice3;
	if (choice3 != "1" && choice3 != "2" && choice3 != "0") {
		cout << "Wrong choice,try again..." << endl;
	}
	else if (choice3 == "0") {
		return "0";
	}
	else if (choice3 == "1") {
		system("cls");
		cout << "Enter username : " << endl;
		cin >> username;
		cout << "Enter password : " << endl;
		cin >> password;
		if (!SignIn(username, password, dt.users)) {
			cout << "Wrong username or password,try again" << endl;
			Sleep(2000);
			goto labelfunc;
		}
		Loading();
	}
	else if (choice3 == "2") {
		system("cls");
		cout << "Enter username : " << endl;
		cin >> username;
		cout << "Enter password : " << endl;
		cin >> password;
		if (!SignUp(username, password, dt.users)) {
			cout << "This username already exists on database,try again" << endl;
			Sleep(2000);
			goto labelfunc;
		}
		Loading();
		goto labelfunc;

	}
labelfunc2:
	system("cls");
	cout << "Menus" << endl;
	for (int i = 0; i < dt.Menus.size(); i++)
	{
		cout << i + 1 << "." << dt.Menus[i]->name << endl;
	}
	cout << dt.Menus.size() + 1 << ".Current Basket" << endl
		<< dt.Menus.size() + 2 << ".History" << endl
		<< "0.Back(Quit)" << endl;
	int choice = 0;
	cin >> choice;
	if (choice - 1 > dt.Menus.size() && choice != dt.Menus.size() + 1 && choice != dt.Menus.size() + 2 && choice != 0)
	{
		cout << "Wrong choice,try again" << endl;
		goto labelfunc2;
	}
	else if (choice == 0)
	{
		return "0";
	}
	else if (choice - 1 == dt.Menus.size()) {
	labelcart:
		system("cls");
		int sum = 0;
		cout << "Your cart : \n";
		for (int i = 0; i < dt.Cart.size(); i++)
		{
			cout << i + 1 << "."
				<< "Food Name : " << dt.Cart[i]->name
				<< "\nFood Price : " << dt.Cart[i]->price << " AZN" << endl;
			sum += dt.Cart[i]->price;
		}
		cout << "\n-------------------------------" << endl;
		cout << "\tSUBTOTAL" << endl;
		cout << "\t" << sum << " AZN";
		string choice;
		cout << "\n1.Payment" << endl;
		cout << "2.Edit cart" << endl;
		cout << "0.Back" << endl;
		cin >> choice;
		if (choice != "1" && choice != "2" && choice != "0") {
			goto labelcart;
		}
		else if (choice == "0") {
			goto labelfunc2;
		}
		else if (choice == "1") {
		labelpayment:
			int sumuser;
			cout << "Please make payment" << endl;
			cin >> sumuser;
			if (sumuser == sum) {
				system("cls");
				dt.money += sum;
				cout << "Success..Thank you!";
#pragma warning(disable:4996)
				time_t now = time(0);
				char* dc = ctime(&now);
				dt.userdatas.push_back(new Data(username, dc));
				for (int i = dt.Cart.size() - 1; i >= 0; i--)
				{
					for (int j = 0; j < dt.Cart[i]->ingredients.size(); j++)
					{
						for (int c = 0; c < dt.ingredients.size(); c++)
						{
							if (dt.Cart[i]->ingredients[j]->name == dt.ingredients[c]->name) {
								dt.ingredients[c]->count -= dt.Cart[i]->ingredients[j]->count;
								json js = json::array();
								to_json_ingredient(js, dt.ingredients);
								break;
							}
						}
					}
					dt.userdatas[dt.userdatas.size() - 1]->foods.push_back(new Food(dt.Cart[i]->name, dt.Cart[i]->price, dt.Cart[i]->info));
					dt.admindatas.push_back(new AdminData(dt.money, dt.Cart[i]->price, dc));
					dt.Cart.erase(dt.Cart.begin() + i);
				}
				json js = json::array();
				to_json_data(js, dt.userdatas);
				json ja = json::array();
				to_json_admin_data(ja, dt.admindatas);
				Sleep(1000);
				goto labelfunc2;
			}
			else if (sumuser > sum)
			{
				system("cls");
				dt.money += sum;
				cout << "Change due :" << endl;
				cout << sum - sumuser << "AZN";
				time_t now = time(0);
				char* dc = ctime(&now);
				dt.userdatas.push_back(new Data(username, dc));
				for (int i = dt.Cart.size() - 1; i >= 0; i++)
				{
					for (int j = 0; j < dt.Cart[i]->ingredients.size(); j++)
					{
						for (int c = 0; c < dt.ingredients.size(); c++)
						{
							if (dt.Cart[i]->ingredients[i]->name == dt.ingredients[c]->name) {
								dt.ingredients[c]->count -= dt.Cart[i]->ingredients[i]->count;
								json js = json::array();
								to_json_ingredient(js, dt.ingredients);
							}
						}
					}
					dt.userdatas[dt.userdatas.size() - 1]->foods.push_back(new Food(dt.Cart[i]->name, dt.Cart[i]->price, dt.Cart[i]->info));
					dt.Cart.erase(dt.Cart.begin() + i);
				}
				json js = json::array();
				to_json_data(js, dt.userdatas);
				json ja = json::array();
				to_json_admin_data(ja, dt.admindatas);
				goto labelfunc2;
			}
			else
			{
				system("cls");
				cout << "The payment was not completed" << endl;
				Sleep(1000);
				goto labelcart;
			}
		}
		else
		{
		labelerase:
			system("cls");
			cout << "Your cart : \n";
			for (int i = 0; i < dt.Cart.size(); i++)
			{
				cout << i + 1 << "."
					<< "Food Name : " << dt.Cart[i]->name
					<< "\nFood Price : " << dt.Cart[i]->price << " AZN" << endl;
			}
			cout << "\n0.Back" << endl;
			int cart = 0;
			cout << "Enter the number of food which you want to remove from cart.." << endl;
			cin >> cart;
			if (cart >= dt.Cart.size() && cart < 0) {
				goto labelerase;
			}
			else if (cart == 0) {
				goto labelcart;
			}
			else {
				dt.Cart.erase(dt.Cart.begin() + (cart - 1));
				cout << "Food successfully removed from cart.." << endl;
				Sleep(2000);
				goto labelerase;
			}
		}
	}
	else if (choice - 2 == dt.Menus.size()) {
	labelarchive:
		system("cls");
		cout << "History" << endl;
		string choice39;
		int j = 1;
		for (int i = 0; i < dt.userdatas.size(); i++)
		{
			if (username == dt.userdatas[i]->username) {
				cout << j << ".Order" << endl;
				cout << "Date : " << dt.userdatas[i]->time;
				for (int c = 0; c < dt.userdatas[i]->foods.size(); c++)
				{
					cout << c + 1 << ". " << "Food name : " << dt.userdatas[i]->foods[c]->name << endl;
					cout << "Food price : " << dt.userdatas[i]->foods[c]->price << " AZN" << endl;
				}
				j++;
				cout << "------------------------------" << endl;
			}
		}
		cout << "0.Back" << endl;
		cin >> choice39;
		if (choice39 != "0") {
			cout << "You can't select anything on this page" << endl;
			Sleep(2000);
			goto labelarchive;
		}
		else
			goto labelfunc2;
	}
	else {
		if (UserMenu(dt, dt.Menus[choice - 1]->foods) == "0") {
			goto labelfunc2;
		}
		return "1";

	}
}

string ShowMenuOptionsAdmin2(Database& dt) {
labelfunc:
	system("cls");
	cout << "Menus" << endl;
	for (int i = 0; i < dt.Menus.size(); i++)
	{
		cout << i + 1 << "." << dt.Menus[i]->name << endl;
	}
	cout << "0.Back" << endl;
	int choice;
	cin >> choice;
	if (choice - 1 >= dt.Menus.size() && choice != 0)
	{
		cout << "Wrong choice,try again" << endl;
		goto labelfunc;
	}
	else if (choice == 0)
	{
		return "0";
	}
	else {
	labelfoodelse:
		string choice1;
		dt.ShowMenu(dt.Menus[choice - 1]->foods);
		cin >> choice1;
		if (choice1 == "0")
		{
			goto labelfunc;
		}
		else {
			system("cls");
			cout << "You cant buy anything in admin panel" << endl;
			Sleep(2000);
			goto labelfoodelse;
		}
	}

}

string ShowMenuOptionsAdmin3(Database& dt) {
label3:
	system("cls");
	dt.ShowIngredients(dt.ingredients);
	string choice;
	double count;
	double price;
	cout << "\nEnter the name of ingredient which you want to add : " << endl;
	cout << "0.Back" << endl;
	cin >> choice;
	if (choice == "0")
	{
		return "0";
	}
labelcount:
	cout << "Enter count of ingredient" << endl;
	cin >> count;
	cout << "Enter price of ingredient" << endl;
	cin >> price;
	if (CheckIngredient(dt, choice, count, price) == "0") {
		system("cls");
		cout << "There are not enough funds in the cash register,please reduce count or price." << endl;
		cout << "Money in our cash register : " << dt.money << " AZN" << endl;
		cout << "Your order : " << int(price * count) << " AZN" << endl;
		Sleep(2000);
		system("cls");
		goto labelcount;
	}
	else {
		json js = json::array();
		to_json_ingredient(js, dt.ingredients);
		json ja = json::array();
		to_json_admin_data(ja, dt.admindatas);
		goto label3;
	}
}

string ShowMenuOptionsAdmin4(Database& dt) {
label4:
	string choice1 = "";
	string info = "";
	double price = 0;
	system("cls");
	cout << "Current Foods in base" << endl;
	for (int i = 0; i < dt.foods.size(); i++)
	{
		cout << i + 1 << ". ";
		cout << dt.foods[i]->name;
		if ((i + 1) % 2 == 0)
			cout << endl;
		else
			cout << "        ";
	}
	cout << "0.Back ";
	cout << "\nEnter the name of food which you want to add : " << endl;
	while (choice1 == "")
	{
		getline(cin, choice1);
	}
	if (choice1 == "0")
	{
		return "0";
	}
	cout << "Enter the info of food : " << endl;
	while (info == "")
	{
		getline(cin, info);
	}
	cout << "Enter the price of food : " << endl;
	cin >> price;
	string cond = CheckFood(dt, choice1, info, price);
	if (cond == "0") {
		system("cls");
		cout << "This food is already available at the base" << endl;
		Sleep(2000);
		system("cls");
		goto label4;
	}
	else if (cond == "1") {
		goto label4;
	}
	else
	{
		json js = json::array();
		to_json_food(js, dt.foods);
		goto label4;
	}

}

string ShowMenuOptionsAdmin5(Database& dt) {
label4:
	system("cls");
	cout << "Current Foods in base" << endl;
	for (int i = 0; i < dt.foods.size(); i++)
	{
		cout << i + 1 << ". ";
		cout << dt.foods[i]->name;
		if ((i + 1) % 2 == 0)
			cout << endl;
		else
			cout << "        ";
	}
	cout << "0.Back ";
	cout << "\nEnter the number of food which you want to change : " << endl;
	int choice1 = 0;
	cin >> choice1;
	if (choice1 - 1 >= dt.foods.size() && choice1 != 0) {
		cout << "Wrong number,try again..." << endl;
		goto label4;
	}
	else if (choice1 == 0)
	{
		return "0";
	}
	else {
	label31:
		int choice2;
		dt.foods[choice1 - 1]->ShowFood();
		cout << "\nEnter the number of ingredient which you want to change count : " << endl;
		cin >> choice2;
		if (choice2 - 1 >= dt.foods[choice1 - 1]->ingredients.size() && choice2 != 0)
		{
			cout << "Wrong number,try again..." << endl;
			goto label31;
		}
		else if (choice2 == 0) {
			goto label4;
		}
		else {
			system("cls");
			int count;
			cout << "Enter a count : ";
			cin >> count;
			dt.foods[choice1 - 1]->ingredients[choice2 - 1]->count = count;
			system("cls");
			cout << "Successfully changed" << endl;
			json js = json::array();
			to_json_food(js, dt.foods);
			Sleep(1000);
			goto label31;
		}
	}
}

string ShowMenuOptionsAdmin6(Database& dt) {
labelmenu:
	system("cls");
	cout << "Menus" << endl;
	for (int i = 0; i < dt.Menus.size(); i++)
	{
		cout << i + 1 << ". " << dt.Menus[i]->name << endl;
	}
	string choice = "";
	cout << "Enter the name of menu which you want to create : " << endl;
	cout << "0.Back" << endl;
	while (choice == "") {
		getline(cin, choice);
	}
	if (choice == "0") {
		return "0";
	}
	else {
		for (int i = 0; i < dt.Menus.size(); i++)
		{
			if (choice == dt.Menus[i]->name) {
				system("cls");
				cout << "There is already a menu with this name" << endl;
				Sleep(1000);
				goto labelmenu;
			}
		}
		dt.Menus.push_back(new Menu(choice));
		json js = json::array();
		to_json_menu(js, dt.Menus);
		goto labelmenu;
	}
}

string ShowMenuOptionsAdmin7(Database& dt) {
labelfunc:
	system("cls");
	cout << "Menus" << endl;
	for (int i = 0; i < dt.Menus.size(); i++)
	{
		cout << i + 1 << "." << dt.Menus[i]->name << endl;
	}
	cout << "0.Back" << endl;
	int choice;
	cin >> choice;
	if (choice - 1 <= dt.Menus.size() && choice < 0)
	{
		cout << "Wrong choice,try again" << endl;
		goto labelfunc;
	}
	else if (choice == 0)
	{
		return "0";
	}
	else {
	labelfoodadd:
		system("cls");
		dt.ShowMenu(dt.Menus[choice - 1]->foods);
		cout << "\n-----------------------------\n";
		for (int i = 0; i < dt.foods.size(); i++)
		{
			cout << i + 1 << "." << dt.foods[i]->name << endl;
		}
		int choice1 = 0;
		cout << "Enter the number of food which you want to add " << dt.Menus[choice - 1]->name << endl;
		cin >> choice1;
		if (choice1 - 1 >= dt.foods.size() && choice1 != 0) {
			cout << "Wrong choice,try again" << endl;
			goto labelfoodadd;
		}
		else if (choice1 == 0) {
			goto labelfunc;
		}
		else {
			for (int i = 0; i < dt.Menus[choice - 1]->foods.size(); i++)
			{
				if (dt.foods[choice1 - 1]->name == dt.Menus[choice - 1]->foods[i]->name) {
					system("cls");
					cout << "This food is already in menu" << endl;
					Sleep(1000);
					goto labelfoodadd;
				}
			}
			dt.Menus[choice - 1]->foods.push_back(dt.foods[choice1 - 1]);
			system("cls");
			cout << "Succesfully added" << endl;
			json js = json::array();
			to_json_menu(js, dt.Menus);
			Sleep(2000);
			goto labelfoodadd;
		}
	}
}

string ShowMenuOptionsAdmin8(Database& dt)
{
labelfunc:
	system("cls");
	cout << "Menus" << endl;
	for (int i = 0; i < dt.Menus.size(); i++)
	{
		cout << i + 1 << "." << dt.Menus[i]->name << endl;
	}
	cout << "0.Back" << endl;
	int choice;
	cin >> choice;
	if (choice - 1 >= dt.Menus.size() && choice != 0)
	{
		cout << "Wrong choice,try again" << endl;
		goto labelfunc;
	}
	else if (choice == 0)
	{
		return "0";
	}
	else {
		int choice1 = 0;
	labelfood1:
		dt.ShowMenu(dt.Menus[choice - 1]->foods);
		cout << "\n---------------------" << endl;
		cout << "\nEnter the number of food which you want to remove : " << endl;
		cin >> choice1;
		if (choice1 - 1 >= dt.Menus[choice - 1]->foods.size() && choice1 != 0)
		{
			cout << "Wrong number,try again...";
			Sleep(1000);
			goto labelfood1;
		}
		else if (choice1 == 0)
		{
			goto labelfunc;
		}
		else {

			dt.Menus[choice - 1]->foods.erase(dt.Menus[choice - 1]->foods.begin() + (choice1 - 1));
			system("cls");
			cout << "Succesfully removed";
			Sleep(1000);
			goto labelfood1;
		}
		return "1";
	}
}

string ShowMenuOptionsAdmin9(Database& dt) {
labelhistory:
	system("cls");
	int money = 0;
	int profit = 0;
	int cost = 0;
	string date;
	string choice1;
	for (int i = 0; i < dt.admindatas.size(); i++)
	{
		money = dt.admindatas[i]->money;
		profit += dt.admindatas[i]->profit;
		cost += dt.admindatas[i]->cost;
		date = dt.admindatas[i]->date;
	}
	cout << "Last Purchase : " << date;
	cout << "Balance : " << money << endl;
	cout << "Cost : " << cost << endl;
	cout << "Sales : " << profit << endl;
	cout << "0.Back" << endl;
	cin >> choice1;
	if (choice1 != "0") {
		cout << "You cant select anything on this page" << endl;
		Sleep(2000);
		goto labelhistory;
	}
	else
		return "0";
}

string AdminMenu(Database& dt) {
	string choice;
label:
	system("cls");
	cout << "1.Show Ingredients" << endl;
	cout << "2.Show Menu" << endl;
	cout << "3.Add Ingredients" << endl;
	cout << "4.Add Food" << endl;
	cout << "5.View foods(Change ingredients)" << endl;
	cout << "6.Add Menu" << endl;
	cout << "7.Add Food To Menu" << endl;
	cout << "8.Remove Food From Menu" << endl;
	cout << "9.Statistics" << endl;
	cout << "0.Back" << endl;
	cin >> choice;
	if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8" && choice != "9" && choice != "0") {
		cout << "Wrong choice,try again" << endl;
		goto label;
	}
	else if (choice == "1") {
	labelchoice1:
		Loading();
		system("cls");
		dt.ShowIngredients(dt.ingredients);
		string choice;
		cout << "0.Back" << endl;
		cin >> choice;
		if (choice != "0")
		{
			goto labelchoice1;
		}
		else
			goto label;
		return "1";
	}
	else if (choice == "2") {
		Loading();
		if (ShowMenuOptionsAdmin2(dt) == "0")
		{
			goto label;
		}
		return "2";
	}
	else if (choice == "3") {
		Loading();
		if (ShowMenuOptionsAdmin3(dt) == "0") {
			goto label;
		}
		return "3";
	}
	else if (choice == "4") {
		Loading();
		if (ShowMenuOptionsAdmin4(dt) == "0") {
			goto label;
		}
		return "5";
	}
	else if (choice == "5") {
		Loading();
		if (ShowMenuOptionsAdmin5(dt) == "0") {
			goto label;
		}
		return "5";
	}
	else if (choice == "6") {
		Loading();
		if (ShowMenuOptionsAdmin6(dt) == "0") {
			goto label;
		}
		return "6";
	}
	else if (choice == "7") {
		Loading();
		if (ShowMenuOptionsAdmin7(dt) == "0")
		{
			goto label;
		}
		return "7";
	}
	else if (choice == "8") {
		Loading();
		if (ShowMenuOptionsAdmin8(dt) == "0")
		{
			goto label;
		}
		return "8";
	}
	else if (choice == "9") {
		Loading();
		if (ShowMenuOptionsAdmin9(dt) == "0")
		{
			goto label;
		}
		return "9";
	}
	else
		return "0";
}

int CheckFileSize(string filename) {
	fstream fi(filename, ios::app);
	fi.seekg(0, ios::end);
	int lengthfi = fi.tellg();
	fi.close();
	return lengthfi;
}