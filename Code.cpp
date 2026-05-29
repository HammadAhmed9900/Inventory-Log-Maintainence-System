#include<iostream>
#include<fstream>
#include <cstdio>    // For remove() and rename()
#include <cstdlib>   // For atoi()
using namespace std;
int main()
{
	int choice;
	do
	{
		cout << "==================================================" << endl;
		cout << "        Inventory Log Maintainence System" << endl;
		cout << "==================================================" << endl;
		cout << "1.Add New Item" << endl;
		cout << "2.View All items" << endl;
		cout << "3.Search item by itemId." << endl;
		cout << "4.Update Quantity or price of an item" << endl;
		cout << "5.Delete an Item" << endl;
		cout << "6.Exit the program" << endl;
		cout << "What action you wanna perform: ";
		cin >> choice;
		cout << endl;
		cout << endl;
		if (choice == 1)
		{
			cout << "You chose to add a new item" << endl;
			ofstream Record("inventory.csv", ios::app);
			int howMany;
			cout << "How many items you wanna add: ";
			cin >> howMany;
			cin.ignore();
			for (int ItemCounter = 1; ItemCounter <= howMany; ++ItemCounter)
			{
				char itemID[30], itemName[50];
				char quantity[30], pricePerUnit[30];
				if (ItemCounter == 1)
					cout << "you chose to add " << howMany << " items." << endl;
				cout << "For item no: " << ItemCounter << endl;
				cout << "Write the item Id: ";
				cin.getline(itemID, 30);
				cout << "Write the item Name: ";
				cin.getline(itemName, 50);
			not_Digit:
				cout << "Write the quantity of item: ";
				cin.getline(quantity, 30);
				bool onlyDigits = false;
				for (int DigitsCounter = 0; quantity[DigitsCounter] != '\0'; ++DigitsCounter)
				{
					if (quantity[DigitsCounter] >= '0' && quantity[DigitsCounter] <= '9')
					{
						onlyDigits = true;
					}
					else
					{
						onlyDigits = false;
					}
					if (!onlyDigits)
					{
						cout << "Only no are allowed please enter numbers." << endl;
						goto not_Digit;
					}
				}
			not_Digit2:
				cout << "Write the price per unit of the item: ";
				cin.getline(pricePerUnit, 30);
				bool onlyDigits2 = false;
				for (int DigitsCounter2 = 0; pricePerUnit[DigitsCounter2] != '\0'; ++DigitsCounter2)
				{
					if (pricePerUnit[DigitsCounter2] >= '0' && pricePerUnit[DigitsCounter2] <= '9')
					{
						onlyDigits2 = true;
					}
					else
					{
						onlyDigits2 = false;
					}
					if (!onlyDigits2)
					{
						cout << "Only no are allowed please enter numbers." << endl;
						goto not_Digit2;
					}
				}
				Record << itemID << "," << itemName << "," << quantity << "," << pricePerUnit << endl;
			}
			Record.close();
			cout << "New Record has been added." << endl;
		}
		else if (choice == 2)
		{
			cout << "View all items selected." << endl;
			ifstream fin("inventory.csv");
			if (!fin)
			{
				cout << "No data is stored right now." << endl;
				continue;
			}
			char itemID[30], itemName[50];
			char quantity[20];
			char pricePerUnit[30];
			cout << "======================================================================" << endl;
			cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
			while (fin.getline(itemID, 30, ','))
			{
				fin.getline(itemName, 50, ',');
				fin.getline(quantity, 20, ',');
				fin.getline(pricePerUnit, 30, '\n');
				cout << itemID << "\t\t" << itemName << "\t\t" << quantity << "\t\t" << pricePerUnit << endl;
			}
			cout << "======================================================================" << endl;
			fin.close();
		}
		else if (choice == 3)
		{
			cout << "Search item by Item Id selected." << endl;
			ifstream fin("inventory.csv");
			if (!fin)
			{
				cout << "No data is stored right now." << endl;
				continue;
			}
			char target[30];
			cout << "Enter the Item Id u wanna search: ";
			cin >> target;
			char itemID[30], itemName[50];
			char quantity[20];
			char pricePerUnit[30];
			bool found = false;
			while (fin.getline(itemID, 30, ','))
			{
				fin.getline(itemName, 50, ',');
				fin.getline(quantity, 20, ',');
				fin.getline(pricePerUnit, 30, '\n');
				if (atoi(target) == atoi(itemID))
				{
					cout << "\nRecord Found:\n";
					cout << "======================================================================" << endl;
					cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
					cout << itemID << "\t\t" << itemName << "\t\t" << quantity << "\t\t" << pricePerUnit << endl;
					cout << "======================================================================" << endl;
					found = true;
					break;
				}
			}
			fin.close();
			if (!found)
				cout << "No item of this Item Id exist" << endl;
		}
		else if (choice == 4)
		{
			ifstream fin("inventory.csv");
			ofstream fout("temp.csv");
			if (!fin)
			{
				cout << "No data is stored right now." << endl;
				continue;
			}
			char target[30];
			cout << "Enter the Item Id u wanna update: ";
			cin >> target;
			char itemID[30], itemName[50];
			char quantity[20];
			char pricePerUnit[30];
			bool updated = false;
			while (fin.getline(itemID, 30, ','))
			{
				fin.getline(itemName, 50, ',');
				fin.getline(quantity, 20, ',');
				fin.getline(pricePerUnit, 30, '\n');
				if (atoi(target) == atoi(itemID))
				{
					cout << "You chose to update:  " << endl;
					cout << "======================================================================" << endl;
					cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
					cout << itemID << "\t\t" << itemName << "\t\t" << quantity << "\t\t" << pricePerUnit << endl;
					cout << "======================================================================" << endl;
				update_input:
					int choiceOfUpdate;
					cout << "What you wanna update: \n1.Quantity\n2.Price.\n";
					cin >> choiceOfUpdate;
					cin.ignore();
					if (choiceOfUpdate == 1)
					{
						cout << "You chose to update quantity." << endl;
					not_Digit3:
						cout << "Enter the new Quantity: ";
						cin.getline(quantity, 20);
						bool onlyDigits = false;
						for (int DigitsCounter = 0; quantity[DigitsCounter] != '\0'; ++DigitsCounter)
						{
							if (quantity[DigitsCounter] >= '0' && quantity[DigitsCounter] <= '9')
							{
								onlyDigits = true;
							}
							else
							{
								onlyDigits = false;
							}
							if (!onlyDigits)
							{
								cout << "Only no are allowed please enter numbers." << endl;
								goto not_Digit3;
							}
						}
						updated = true;
					}
					else if (choiceOfUpdate == 2)
					{
						cout << "You chose to update price." << endl;
					not_Digit4:
						cout << "Enter the new Price of item: ";
						cin.getline(pricePerUnit, 30);
						bool onlyDigits2 = false;
						for (int DigitsCounter2 = 0; pricePerUnit[DigitsCounter2] != '\0'; ++DigitsCounter2)
						{
							if (pricePerUnit[DigitsCounter2] >= '0' && pricePerUnit[DigitsCounter2] <= '9')
							{
								onlyDigits2 = true;
							}
							else
							{
								onlyDigits2 = false;
							}
							if (!onlyDigits2)
							{
								cout << "Only no are allowed please enter numbers." << endl;
								goto not_Digit4;
							}
						}
						updated = true;
					}
					else
					{
						cout << "Invalid choice." << endl;
						goto update_input;
					}
					cout << "After update: " << endl;
					cout << "======================================================================" << endl;
					cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
					cout << itemID << "\t\t" << itemName << "\t\t" << quantity << "\t\t" << pricePerUnit << endl;
					cout << "======================================================================" << endl;
				}
				fout << itemID << "," << itemName << "," << quantity << "," << pricePerUnit << endl;
			}
			fin.close();
			fout.close();
			remove("inventory.csv");
			rename("temp.csv", "inventory.csv");
			if (updated)
			{
				cout << "Item has been updated" << endl;
			}
			else
			{
				cout << "Item dont exist." << endl;
			}
		}
		else if (choice == 5)
		{
			ifstream fin("inventory.csv");
			ofstream fout("temp.csv");
			if (!fin)
			{
				cout << "No data is stored right now." << endl;
				continue;
			}
			char target[30];
			cout << "Enter the Item Id u wanna delete: ";
			cin >> target;
			char itemID[30], itemName[50];
			char quantity[20];
			char pricePerUnit[30];
			bool deleted = false;
			while (fin.getline(itemID, 30, ','))
			{
				fin.getline(itemName, 50, ',');
				fin.getline(quantity, 20, ',');
				fin.getline(pricePerUnit, 30, '\n');
				if (atoi(target) == atoi(itemID))
				{
					cout << "======================================================================" << endl;
					cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
					cout << itemID << "\t\t" << itemName << "\t\t" << quantity << "\t\t" << pricePerUnit << endl;
					cout << "======================================================================" << endl;
					cout << "This record is deleted." << endl;
					deleted = true;
					continue;
				}
				fout << itemID << "," << itemName << "," << quantity << "," << pricePerUnit << endl;
			}
			fin.close();
			fout.close();
			remove("inventory.csv");
			rename("temp.csv", "inventory.csv");
			if (deleted)
			{
				cout << "Item has been deleted" << endl;
			}
			else
			{
				cout << "Item dont exist." << endl;
			}
		}
		else if (choice == 6)
		{
			cout << "You exited the program." << endl;
		}
		else
		{
			cout << "You entered the wrong input" << endl;
		}
	} while (choice != 6);

	return 0;
}