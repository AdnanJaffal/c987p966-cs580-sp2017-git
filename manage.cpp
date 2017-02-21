/*
 * manage.cpp
 *
 *  Created on: Apr 25, 2016
 *      Author: Adnan Jaffal
 */

#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <vector>
#include "product.hpp"
#include "productbatch.hpp"
using namespace std;

Product* add_product () {
	Product* product = new Product(-1, "", NONPERISHABLE, 0);
	int id, category;
	unsigned int storage;
	string name;

	cout << endl << "Enter product ID: " << endl;
	cin >> id;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter product name: " << endl;
	getline (cin, name);
	cout << "Enter category (1=Perishable, 2=Nonperishable): " << endl;
	cin >> category;
	cout << "Enter the storage life in days: " << endl;
	cin >> storage;

	if (name != "") {
		if (category == 1) {
			product = new Product(id, name, PERISHABLE, storage);
		} else {
			product = new Product(id, name, NONPERISHABLE, storage);
		}

		cout << endl << "Product added!" << endl;
	} else {
		cout << endl << "Product not added." << endl;
	}

	return product;
}

void receive_batch(const vector<Product*> &products) {
	int choice;
	unsigned int day;
	unsigned long amount;
	cout << endl << "A batch can only be added for a product that exists."
			<< " If the product is not yet in the product list, return to the "
			<< "main menu, add the product, then return to add the batch." << endl;

	cout << endl << "List of products:" << endl;
	for (unsigned int y = 0 ; y < products.size() ; y++) {
		cout << "  " << y+1 << ". " << products[y]->product_name() << endl;
	}

	cout << endl << "Enter the number of the product to receive for: " << endl;
	cin >> choice;

	if (choice < products.size()) {
		cout << "Enter the amount to receive: " << endl;
		cin >> amount;
		cout << "Enter day received: " << endl;
		cin >> day;

		if (amount > 0) {
			products[choice-1]->receive(amount, day);
			cout << endl << "Batch received!" << endl;
		} else {
			cout << endl << "Batch not received" << endl;
		}
	}

	return;
}

void ship_batch (const vector<Product*> products) {
	int choice;
	unsigned long amount;

	cout << "It is only possible to ship from an existing batch of an existing product."
			<< " Selecting a product or batch that doesn’t exist will return to "
			<< "the main menu." << endl;

	cout << endl << "List of products:" << endl;
	for (unsigned int y = 0 ; y < products.size() ; y++) {
		cout << "  " << y+1 << ". " << products[y]->product_name() << endl;
	}

	cout << endl << "Enter the number of the product to ship for: " << endl;
	cin >> choice;

	choice -= 1;

	if (choice < products.size()) {
		unsigned int batches = products[choice]->num_batches();
		int choiceB;
		if (batches > 0) {
			ProductBatch* batch;
			cout << endl << "List of batches:" << endl;
			for (unsigned int x = 0 ; x < batches ; x++) {
				batch = products[choice]->batch(x);
				cout << "  " << x+1 << ". Number in stock: " << batch->num_in_stock() << ", Received on "
						<< batch->received_on() << ", Expires on " << batch->expires_on()
						<< endl;
			}

			cout << endl << "Enter the number of the batch to ship for: " << endl;
			cin >> choiceB;

			choiceB -= 1;

			batch = products[choice]->batch(choiceB);

			if (choiceB < batches) {
				cout << endl << "Enter the amount to ship: " << endl;
				cin >> amount;

				products[choice]->ship_from_batch(amount, choiceB);
				cout << "Items shipped." << endl;
			} else {
				cout << endl << "That is not a valid choice." << endl;
			}
		} else {
			cout << endl << "There are no batches for that product." << endl;
		}
	} else {
		cout << endl << "That is not a valid choice." << endl;
	}

	return;
}

void print_product (const Product *product) {
	unsigned int batches = product->num_batches();

	cout << endl << "List of products:" << endl;
	cout << "  ID: " << product->product_id() << ", Name: " << product->product_name()
			<< ", Category: " << product->category() << ", Storage life: "
			<< product->storage_life() << endl;
	cout << "  " << batches << " batches: " << endl;

	if (batches > 0) {
		ProductBatch* batch;
		for (unsigned int x = 0 ; x < batches ; x++) {
			batch = product->batch(x);
			cout << "    Number in stock: " << batch->num_in_stock() << ", Received on "
					<< batch->received_on() << ", Expires on " << batch->expires_on()
					<< endl;
		}
	}

	return;
}

int menu () {
	int choice;

	cout << endl << "Available options:" << endl;
	cout << "\t1. Add new product" << endl;
	cout << "\t2. Receive batch" << endl;
	cout << "\t3. Ship batch" << endl;
	cout << "\t4. Show all products" << endl;
	cout << "\t5. Quit" << endl;
	cout << "Enter the number of your choice: " << endl;
	cin >> choice;

	return choice;
}
int main () {
	Product* temp;
	vector<Product*> products;
	int choice = menu();

	while (choice != 5) {

		switch (choice) {
			case 1: {
				temp = add_product();

				if (temp->product_id() != -1) {
					products.push_back(temp);
				}
				break;
			}
			case 2: {
				receive_batch(products);
				break;
			}
			case 3: {
				ship_batch(products);
				break;
			}
			case 4: {
				for (unsigned int x = 0 ; x < products.size() ; x++) {
					print_product(products[x]);
				}
				break;
			}
			case 5: {
				break;
			}
			default:
				cout << "Invalid choice." << endl;
		}

		choice = menu();
	}

	system("PAUSE");
	return 0;
}


