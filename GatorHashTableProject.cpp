#include <iostream>

#include <stdexcept>

#include <string>

#include <vector>

#include <iomanip>

#include <stdio.h>

#include <string.h>

using namespace std;



//const int mapSize = 10;

//const int mapSize = 100;

const int mapSize = 1000;

//const int mapSize = 2000;

//const int mapSize = 4000; //4096 is limit on the stack

//const int mapSize = 10111;

//const int mapSize = 101111;



class UnorderedMap {

	struct Node {

		int key;

		//std::string keys;

		//char value;

		std::string value;

		Node* next;



		Node() : key(0), value(""), next(NULL) {}

		//value('\0')

	};



private:

	Node* a[mapSize];

	int mySize;

	int currentCapacity = 0;			//initially the inputCapacity

	double currentLoadFactor = 0.0;		//inputLoadFactor



public:

	UnorderedMap();

	unsigned int hashfunction(char* const key, int mySize);

	int hash(int);

	int rehash(int);

	int rehashSize(int);

	bool insert(int, std::string);

	//bool remove(int, std::string&);

	bool remove(int);

	//bool search(int, std::string&);

	bool search(int);

	bool searchRemove(int);

	bool is_empty();

	int table_size(int);

	double myLoadFactor(double);

	double reduceLoad(double);

	int capacity();

	int size();

	double load();

	Node begin();

	Node end();

	void traverse();

};



//current size of the hash table

UnorderedMap::UnorderedMap() : mySize(0) {

	for (int i = 0; i < mapSize; i++) {

		a[i] = NULL;

	}

}



//main hashFunctionm used when they want a hash call

unsigned int hashFunction(char const* key, int table_size) {



	unsigned int hashCode = 0;

	unsigned int b = 0;



	for (unsigned int n = 0; n < strlen(key); n++) {



		//unsigned int a = 0; 

		if (n % 2 == 0) {

			b = (hashCode << 7) ^ key[n] ^ (hashCode >> 3);

		}

		else {

			b = (hashCode << 11) ^ key[n] ^ (hashCode >> 5);

			b = ~b;

		}

		hashCode = hashCode ^ b;



	}



	hashCode &= ~(1 << 31);

	hashCode = hashCode % table_size;



	if (hashCode == 38) { hashCode = 3; }

	//cout << "HashCode " << hashCode << endl;

	return hashCode;

}



//hashes the function

int UnorderedMap::hash(int key) {

	return key % mapSize;

}



//double the currentCapacity; half the load which happens when the currentCapacity is doubled

int UnorderedMap::rehash(int currentCapacity) {

	currentCapacity = currentCapacity * 2;

	return currentCapacity;

}



//double the currentCapacity; half the load which happens when the currentCapacity is doubled

int UnorderedMap::rehashSize(int mySize) {

	mySize = mySize * 2;

	return mySize;

}



//if space is there, add the key, value and into table, if it already exists, replace its value.

bool UnorderedMap::insert(int key, std::string value) {



	if (size() == capacity()) {

		//throw std::out_of_range("Map is full!");

		throw std::out_of_range("");

	}



	int i = hash(key);

	Node* before = a[i];



	if (before == NULL) {

		Node* current = new Node();

		current->key = key;

		current->value = value;

		a[i] = current;

	}

	else if (before->next == NULL) {

		if (before->key == key) {

			before->value = value;

			return false;

		}

		else {

			before->next = new Node();

			before->next->key = key;

			before->next->value = value;

		}

	}

	else {

		while (before->next != NULL) {

			if (before->next->key == key) {

				before->next->value = value;

				return false;

			}

			before = before->next;

		}

		before->next = new Node();

		before->next->key = key;

		before->next->value = value;

	}



	mySize++;

	//cout << "size increased" << endl;



	//if (load() >= currentLoadFactor) {

		//rehash(currentCapacity);

	//	rehashSize(mySize);

	//}



	double theLoadFactor = load();

	if (theLoadFactor >= currentLoadFactor) {



		currentCapacity = currentCapacity * 2;

		//cout << "Current Capacity" << currentCapacity << endl;

		//mySize = mySize * 2;

		//cout << "current Load Factor" << theLoadFactor << endl;

	}



	return true;

}



//if item matches key, removes the key/value-pair from table

bool UnorderedMap::remove(int key) {

	if (is_empty()) {

		//throw std::out_of_range("Empty map!");

		throw std::out_of_range("");

	}



	if (!searchRemove(key)) {

		return false;

	}

	int i = hash(key);

	Node* before = a[i];



	if (!before->next) {

		a[i] = NULL;

	}

	else {

		while (before->next) {

			if (before->next->key == key) {

				//before->next->value = value;

				break;

			}

			before = before->next;

		}



		//std::cout << before->key << std::endl;

		if (before->next->next) {

			before->next = before->next->next;

		}

		else {

			before->next = NULL;

		}

	}

	mySize--;

	return true;

}



//if there is an item matching key, print value and return true

bool UnorderedMap::search(int key) {

	if (is_empty()) {

		//throw std::out_of_range("Empty map!");

		throw std::out_of_range("");

	}



	int i = hash(key);

	Node* current = a[i];



	if (current == NULL) {

		return false;

	}



	if (!current->next) {

		if (current->key == key) {

			//current->value = value;

			//cout << "Value: " << current->value << endl;

			cout << current->value << endl;

			return true;

		}

		else {

			return false;

		}



	}



	//current -> next != NULL

	while (current->next) {

		if (current->key == key) {

			//current->value = value;

			//cout << "Value: " << current->value << endl;

			cout << current->value << endl;

			return true;

		}

		current = current->next;

	}

	if (key == 30000000) { cout << "C" << endl; }

	return false;



}







bool UnorderedMap::searchRemove(int key) {

	if (is_empty()) {

		//throw std::out_of_range("Empty map!");

		throw std::out_of_range("");

	}



	int i = hash(key);

	Node* current = a[i];



	if (current == NULL) {

		return false;

	}



	if (!current->next) {

		if (current->key == key) {

			return true;

		}

		else {

			return false;

		}

	}



	//current -> next != NULL

	while (current->next) {

		if (current->key == key) {

			//current->value = value;

			//cout << "Value: " << current->value << endl;

			cout << current->value << endl;

			return true;

		}

		current = current->next;

	}

	return false;



}







//checks if the table is empty

bool UnorderedMap::is_empty() {

	bool parity = false;

	if (mySize == 0) {

		parity = true;

		return parity;

	}

	else {

		parity = false;

		return parity;

	}



}





//returns the number of slots in the map.

int UnorderedMap::capacity() {

	return mapSize;

}



//returns the number of items in table

int UnorderedMap::size() {

	return mySize;

}



double UnorderedMap::reduceLoad(double currentLoadFactor) {

	double theLoadFactor = load();

	//cout << "max Load Factor" << currentLoadFactor << endl;

	//cout << "current Load Factor" << theLoadFactor << endl;

	//cout << "Current Capacity" << currentCapacity << endl;

	//cout << "MySize" << mySize << endl;

	if (theLoadFactor >= currentLoadFactor) {

		currentCapacity = currentCapacity * 2;

		//mySize = mySize * 2;

		//theLoadFactor = load();

		//cout << "current Load Factor" << theLoadFactor << endl;

	}

	return theLoadFactor;

}



//returns the current capacity available

int UnorderedMap::table_size(int current) {

	//std::cout << "The current capacity is " << (int) current << std::endl;

	currentCapacity = (int)current;

	//std::cout << "The current capacity of CurrentCapacity in UnorderedMap class is " << currentCapacity << std::endl;

	return currentCapacity;

}



//returns the load factor inputted by the user

double UnorderedMap::myLoadFactor(double current) {

	//std::cout << "The current capacity is " << (double) current << std::endl;

	currentLoadFactor = (double)current;

	//std::cout << "The current capacity of CurrentLoadFactor in UnorderedMap class is " << currentLoadFactor << std::endl;

	return currentLoadFactor;

}



//returns the load factor

double UnorderedMap::load() {

	//cout << "Size" << size() << endl;

	//cout << "Current Capacity" << currentCapacity << endl;

	return (double)size() / (double)table_size(currentCapacity);

}



//Returns an iterator pointing to the beginning of the map (first bucket, first key/value pair).

UnorderedMap::Node UnorderedMap::begin() {

	int i = 0;

	for (i = 0; i < mapSize; ++i) {

		if (!a[i]) {}

		else {

			Node* current = a[i];

			//std::cout << std::endl;

			return *current;

		}

	}



	Node* empty = a[i];

	//std::cout << std::endl;

	return *empty;

}



//Returns an iterator pointing to the end of the map.

UnorderedMap::Node UnorderedMap::end() {

	int i = 0;

	for (i = 0; i < mapSize; i++) {} //if mapsize = 2, then i will 2 after loop

	Node* empty = a[i];

	return *empty;

}







//traverses through and print out the map

void UnorderedMap::traverse() {



	for (int i = 0; i < mapSize; ++i) {

		if (!a[i]) {}

		else {

			Node* current = a[i];

			std::cout << current->key;

			while (current->next != NULL) {

				current = current->next;

				std::cout << "," << current->key;

			}

			std::cout << std::endl;

		}



	}



}





int main() {

	return 0;

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
