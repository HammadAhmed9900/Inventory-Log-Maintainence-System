#include <iostream>
#include <fstream>
#include <cstdio>    // remove(), rename()
#include <cstdlib>   // atoi()
using namespace std;

const char DATA_FILE[] = "inventory.csv";
const char TEMP_FILE[] = "temp.csv";

// Returns true if the given C-string contains only digit characters
bool isNumericString(const char text[])
{
	if (text[0] == '\0')
		return false;

	for (int i = 0; text[i] != '\0'; ++i)
	{
		if (text[i] < '0' || text[i] > '9')
			return false;
	}
	return true;
}

// Prompts repeatedly until the user enters a purely numeric line
void readNumericField(const char prompt[], char buffer[], int bufferSize)
{
	while (true)
	{
		cout << prompt;
		cin.getline(buffer, bufferSize);
		if (isNumericString(buffer))
			break;
		cout << "Only no are allowed please enter numbers." << endl;
	}
}

void printMenu()
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
}

void printRow(const char id[], const char name[], const char qty[], const char price[])
{
	cout << id << "\t\t" << name << "\t\t" << qty << "\t\t" << price << endl;
}

void printSeparator()
{
	cout << "======================================================================" << endl;
}

void addItems()
{
	cout << "You chose to add a new item" << endl;
	ofstream Record(DATA_FILE, ios::app);

	int howMany;
	cout << "How many items you wanna add: ";
	cin >> howMany;
	cin.ignore();

	for (int counter = 1; counter <= howMany; ++counter)
	{
		char itemID[30], itemName[50], quantity[30], pricePerUnit[30];

		if (counter == 1)
			cout << "you chose to add " << howMany << " items." << endl;

		cout << "For item no: " << counter << endl;
		cout << "Write the item Id: ";
		cin.getline(itemID, 30);
		cout << "Write the item Name: ";
		cin.getline(itemName, 50);

		readNumericField("Write the quantity of item: ", quantity, 30);
		readNumericField("Write the price per unit of the item: ", pricePerUnit, 30);

		Record << itemID << "," << itemName << "," << quantity << "," << pricePerUnit << endl;
	}

	Record.close();
	cout << "New Record has been added." << endl;
}

void viewItems()
{
	cout << "View all items selected." << endl;
	ifstream fin(DATA_FILE);
	if (!fin)
	{
		cout << "No data is stored right now." << endl;
		return;
	}

	char itemID[30], itemName[50], quantity[20], pricePerUnit[30];

	printSeparator();
	cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;

	while (fin.getline(itemID, 30, ','))
	{
		fin.getline(itemName, 50, ',');
		fin.getline(quantity, 20, ',');
		fin.getline(pricePerUnit, 30, '\n');
		printRow(itemID, itemName, quantity, pricePerUnit);
	}

	printSeparator();
	fin.close();
}

void searchItem()
{
	cout << "Search item by Item Id selected." << endl;
	ifstream fin(DATA_FILE);
	if (!fin)
	{
		cout << "No data is stored right now." << endl;
		return;
	}

	char target[30];
	cout << "Enter the Item Id u wanna search: ";
	cin >> target;

	char itemID[30], itemName[50], quantity[20], pricePerUnit[30];
	bool found = false;

	while (fin.getline(itemID, 30, ','))
	{
		fin.getline(itemName, 50, ',');
		fin.getline(quantity, 20, ',');
		fin.getline(pricePerUnit, 30, '\n');

		if (atoi(target) == atoi(itemID))
		{
			cout << "\nRecord Found:\n";
			printSeparator();
			cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
			printRow(itemID, itemName, quantity, pricePerUnit);
			printSeparator();
			found = true;
			break;
		}
	}

	fin.close();
	if (!found)
		cout << "No item of this Item Id exist" << endl;
}

void updateItem()
{
	ifstream fin(DATA_FILE);
	ofstream fout(TEMP_FILE);
	if (!fin)
	{
		cout << "No data is stored right now." << endl;
		return;
	}

	char target[30];
	cout << "Enter the Item Id u wanna update: ";
	cin >> target;

	char itemID[30], itemName[50], quantity[20], pricePerUnit[30];
	bool updated = false;

	while (fin.getline(itemID, 30, ','))
	{
		fin.getline(itemName, 50, ',');
		fin.getline(quantity, 20, ',');
		fin.getline(pricePerUnit, 30, '\n');

		if (atoi(target) == atoi(itemID))
		{
			cout << "You chose to update:  " << endl;
			printSeparator();
			cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
			printRow(itemID, itemName, quantity, pricePerUnit);
			printSeparator();

			bool choiceMade = false;
			while (!choiceMade)
			{
				int choiceOfUpdate;
				cout << "What you wanna update: \n1.Quantity\n2.Price.\n";
				cin >> choiceOfUpdate;
				cin.ignore();

				if (choiceOfUpdate == 1)
				{
					cout << "You chose to update quantity." << endl;
					readNumericField("Enter the new Quantity: ", quantity, 20);
					updated = true;
					choiceMade = true;
				}
				else if (choiceOfUpdate == 2)
				{
					cout << "You chose to update price." << endl;
					readNumericField("Enter the new Price of item: ", pricePerUnit, 30);
					updated = true;
					choiceMade = true;
				}
				else
				{
					cout << "Invalid choice." << endl;
				}
			}

			cout << "After update: " << endl;
			printSeparator();
			cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
			printRow(itemID, itemName, quantity, pricePerUnit);
			printSeparator();
		}

		fout << itemID << "," << itemName << "," << quantity << "," << pricePerUnit << endl;
	}

	fin.close();
	fout.close();
	remove(DATA_FILE);
	rename(TEMP_FILE, DATA_FILE);

	if (updated)
		cout << "Item has been updated" << endl;
	else
		cout << "Item dont exist." << endl;
}

void deleteItem()
{
	ifstream fin(DATA_FILE);
	ofstream fout(TEMP_FILE);
	if (!fin)
	{
		cout << "No data is stored right now." << endl;
		return;
	}

	char target[30];
	cout << "Enter the Item Id u wanna delete: ";
	cin >> target;

	char itemID[30], itemName[50], quantity[20], pricePerUnit[30];
	bool deleted = false;

	while (fin.getline(itemID, 30, ','))
	{
		fin.getline(itemName, 50, ',');
		fin.getline(quantity, 20, ',');
		fin.getline(pricePerUnit, 30, '\n');

		if (atoi(target) == atoi(itemID))
		{
			printSeparator();
			cout << "Item Id:\tItem Name:\tQuantity:\tPrice Per Unit:" << endl;
			printRow(itemID, itemName, quantity, pricePerUnit);
			printSeparator();
			cout << "This record is deleted." << endl;
			deleted = true;
			continue;
		}

		fout << itemID << "," << itemName << "," << quantity << "," << pricePerUnit << endl;
	}

	fin.close();
	fout.close();
	remove(DATA_FILE);
	rename(TEMP_FILE, DATA_FILE);

	if (deleted)
		cout << "Item has been deleted" << endl;
	else
		cout << "Item dont exist." << endl;
}

int main()
{
	int choice;

	do
	{
		printMenu();
		cin >> choice;
		cout << endl << endl;

		switch (choice)
		{
		case 1:
			addItems();
			break;
		case 2:
			viewItems();
			break;
		case 3:
			searchItem();
			break;
		case 4:
			updateItem();
			break;
		case 5:
			deleteItem();
			break;
		case 6:
			cout << "You exited the program." << endl;
			break;
		default:
			cout << "You entered the wrong input" << endl;
			break;
		}

	} while (choice != 6);

	return 0;
}
