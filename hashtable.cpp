#include "hashtable.h"
#include <iostream>

using namespace std;

#define A 54059 
#define B 76963 
#define C 86969 

/**
Hash function for the CS104 hash table.
*/
unsigned hash_str(const char* s)
{
   unsigned h = 31;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h % C; 
}

/**
Creates a hash table of the given input size. Creates the array and vectors used for the hash table.
*/
HashTable::HashTable(int size) {
	this->size = size;
	data = new std::string*[size]();
}

/**
Does nothing
*/
HashTable::~HashTable() {
	for(int i = 0; i < size; i++) {
		if (data[i] != nullptr) delete data[i];
	}
	delete[] data;
}

/**
Insert should do nothing if the name already exists in the hash table.
*/
void HashTable::insert(string str) {
	unsigned hash = hash_str(str.c_str());
	hash = hash % size;

	for(int i = 0; i < size; i++) {
		
		if(data[hash] == nullptr) {
			string* temp = new string(str);
			data[hash] = temp;
			break;
		}else if(*data[hash] == str) break;
		else {
			//cout << str << " collided with: " << *data[hash] << endl;
		}
		hash++;
		hash = hash % size;
	}
}

/**
Find should return true if the name exists in the hash table.
*/
bool HashTable::find(string key) {
	unsigned hash = hash_str(key.c_str());
	hash = hash % size;

	for(int i = 0; i < size; i++) {
		if(data[hash] == nullptr) return false;
		if(*data[hash] == key) return true;
		hash++;
		hash = hash % size;
	}
	return false;
}

/**
Remove should do nothing if the name does not exist in the hash table.
*/
void HashTable::remove(string str) {
	unsigned hash = hash_str(str.c_str());
	hash = hash % size;

	//TODO
	int i;
	size_t pos;
	for(i = 0; i < size; i++)
	{
	//this means that the key does not exist in the table
		if(data[hash] == nullptr) return;
		//go until find the key
		if(*data[hash] == str)
		{
			//because found the key to remove, can break
			pos = hash;
			break;
		}
		hash++;
		hash = hash % size;
	}

	if (i == size)
	{
		return;
	}

	delete data[hash];
	data[hash] = nullptr;
	hash++;
	hash = hash % size;
	
	//for loop running max of size times means it stops when loop back around
	while (data[hash] != nullptr && hash != pos){
	// for(int i = 0; i < size; i++)
	// {
	// 	if (data[hash] == nullptr)
	// 	{
	// 		break;
	// 	}
		string key = *data[hash];
		delete data[hash];
		data[hash] = nullptr;
		insert(key);
		hash++;
		hash = hash % size;
	}
}

void HashTable::print() {
	for(int i = 0; i < size; i++) {
		cout << i << ": " << (data[i] == nullptr ? " " : *data[i]) << endl;
	}
}
