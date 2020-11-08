// AvlTreeImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "avlTree.h"
using namespace std;



int main()
{
	cout << R"(
    ___   ___      _____ ___ ___ ___ 
   /_\ \ / / |    |_   _| _ \ __| __|
  / _ \ V /| |__    | | |   / _|| _| 
 /_/ \_\_/ |____|   |_| |_|_\___|___|
 )";
	cout << "\n\n\n";

	int input = 0;
	avlTree myTree;
	do
	{
		cout << "Please choose an option\n";
		cout << "1. Insert Into Tree\n";
		cout << "2. Print Tree\n";
		cout << "3. Search Tree\n";
		cout << "4. Delete Node\n";
		cout << "-1. To quit\n\n";
		cout << ":";
		cin >> input;

		switch (input)
		{
			case 1:
			{
				string insert;
				cout << "Input your string to insert :";
				cin >> insert;
				myTree.InsertItem(insert);
				break;
			}
			case 2:
			{
				myTree.printTree();
				break;
			}
			case 3:
			{
				string insert;
				cout << "Input your string to insert :";
				cin >> insert;
				Node* theNode =  myTree.Search(insert);
				//Display node info
				if (theNode != nullptr)
				{
					cout << "Current\tLeft\tRight\t\n";
					cout << theNode->data << "\t";
					if (theNode->left != nullptr)
						cout << theNode->left->data << "\t";
					else
						cout << "NULL\t";

					if (theNode->right != nullptr)
						cout << theNode->right->data << "\t";
					else
						cout << "NULL\t";
					
					cout << "\n\n";
				}
				else
				{
					cout << "The item does not exist!\n\n";
				}
				break;

			}
			case 4:
			{
				string insert;
				cout << "Input your string to delete :";
				cin >> insert;
				myTree.DeleteItem(insert);
			}
		}
		

	} while (input != -1);






		









}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


