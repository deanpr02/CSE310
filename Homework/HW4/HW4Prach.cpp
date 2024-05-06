#include <iostream>
#include <string>

using namespace std; 

//record class which has name, gpa, academic level, and key attributes
//also has a pointer to the next record for chaining
class Record{
    public:
    string name;
    double GPA;
    string academicLevel;
    int key;
    Record* nextRecord;
    Record(string name, double GPA, string academicLevel, int key){
        this->name = name;
        this->GPA = GPA;
        this->academicLevel = academicLevel;
        this->key = key;
        this->nextRecord = NULL;
    }
};

//Our hash table class which contains a size m (1000) hashtable that implements chaining
//each slot acts as a linked list in chaining
class HashTable{
    public:
    Record** hashTable;
    HashTable(){
        this->hashTable = new Record*[1000]();
    }
    void insertRecord(string,double,string,int);
    void deleteRecord(int);
    Record* searchRecord(int);
};

//inserts a new record using the kmodm hash function
//if there is a collision it will be resolved using chaining
void HashTable::insertRecord(string name, double GPA, string academicLevel, int key){
    //hash function
    int slot = key % 1000;
    if(this->hashTable[slot] == NULL){
        this->hashTable[slot] = new Record(name,GPA,academicLevel,key);
        return;
    }
    Record* head = this->hashTable[slot];
    while(head->nextRecord != NULL ){
        head = head->nextRecord;
    }
    head->nextRecord = new Record(name,GPA,academicLevel,key);
}

//deletes a record corresponding to the input key
void HashTable::deleteRecord(int key){
    int slot = key % 1000;
    Record* head = this->hashTable[slot];
    if(head == NULL){
        cout<<"\nNo user with this key exists!\n";
        return;
    }
    //Searching for the correct key in hashtable linked list
    Record* prev = NULL;
    while(head->key != key){
        //If we reach NULL again that means this key does not exist in the table
        if(head->nextRecord == NULL){
            cout<<"\nThis record does not exist\n";
            return;
        }
        prev = head;
        //Check next record in list
        head = head->nextRecord;
    }
    //Record is found -> Delete the record
    if(prev == NULL){
        //If the record we want to delete is the first in the linked list and there are multiple there
        if(head->nextRecord != NULL){
            this->hashTable[slot] = head->nextRecord;
            return;
        }
        //If this is the only value in the linked list
        delete this->hashTable[slot];
        this->hashTable[slot] = NULL;
        return;
    }
    //previous is not equal to null
    prev->nextRecord = head->nextRecord;
    delete head;
    head = NULL;
}

//This function searches for a record and returns it if its found
Record* HashTable::searchRecord(int key){
    //hash function
    int slot = key % 1000;
    Record* head = this->hashTable[slot];
    //if the slot does not contain any records then we return NULL since it cant exist
    if(head == NULL){
        cout<< "\nNo record with this key exists\n";
        return NULL;
    }
    //Search through the entire linked list
    while(head != NULL){
        //if the key matches the record's key then return the record
        if(head->key == key){
            return head;
        }
        head = head->nextRecord;
    }
    //No remaining records, key does not exist
    cout<< "\nNo record with this key exists\n";
    return NULL;
}

//Main driver for program
int main(){
    HashTable table = HashTable();
    bool running = true;
    int selection;
    string name;
    string GPA;
    string academicLevel;
    string key;
    Record* temp;

    while(running){
        cout<<"\n1. Insert a record - (User enters the name, GPA, academic level, and key [between 0 - 65536])\n2. Search the table - (User enters a key for search -> key between [0-65536])\n3. Delete a record - (User enters a key of the record to be deleted)\n4. Exit\nEnter your choice: ";
        cin >> selection;
        switch(selection){
            
            //Insert a new record case
            case 1:
            cout<<"Enter the student's name: ";
            cin >> name;
            cout<<"Enter the student's GPA: ";
            cin >> GPA;
            cout << "Enter the student's academic level: ";
            cin >> academicLevel;
            cout << "Enter the student's key [0-65536]: ";
            cin >> key;
            table.insertRecord(name,stod(GPA),academicLevel,stoi(key));
            break;

            //Search for a record case
            case 2:
            cout << "Enter the key you want to search for: ";
            cin >> key;
            temp = table.searchRecord(stoi(key));
            if(temp == NULL){
                break;
            }
            cout << "\nStudent Name: " << temp->name << "\nStudent GPA: " << temp->GPA << "\nStudent Academic Level: " << temp->academicLevel << "\nKey: " << temp->key << "\n";
            break;

            //Delete a record case
            case 3:
            cout << "Enter the key to delete: ";
            cin >> key;
            table.deleteRecord(stoi(key));
            break;

            case 4:
            running = false;
            break;

            default:
            cout<<"Invalid input\n";
            break;

        }
    }


}