#include <iostream>
#include <string>
using namespace std;
//This class represents the node class with name, population, and income attributes.
class City{
    public:
        string city_name;
        int city_population;
        int median_income;
        City* next;
        City(string city_name, int city_population, int median_income){
            this->city_name = city_name;
            this->city_population = city_population;
            this->median_income = median_income;
            this->next = NULL;
        }
};

//This class represents the linked list class with head and tail attributes.
class CityRecord{
    City* head;
    City* tail;
    public:
        CityRecord(){
            head = NULL;
            tail = NULL;
        }
        void addCity(string,int,int);
        void addCityAtHead(string,int,int);
        void addCityAtTail(string,int,int);
        void printRecord();
        void displayLargestPopulation();
};
void CityRecord::addCity(string name, int population, int income){
    City* new_city = new City(name,population,income);
    if(head == NULL){
        head = new_city;
        return;
    }
    City* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new_city;
}
//Print the entire city record linked list.
void CityRecord::printRecord(){
    if(head == NULL){
        cout<<"No city records.\n";
        return;
    }
    City* temp = head;
    while(temp != NULL){
        cout<<"Name: " << temp->city_name <<endl;
        cout<<"Population: "<< temp->city_population <<endl;
        cout<<"Income: $" << temp->median_income << "\n" <<endl;
        temp = temp->next;
    }
}
//Adds a city to the beginning of the city record linked list
void CityRecord::addCityAtHead(string name, int population, int income){
    City* new_city = new City(name,population,income);
    if(head == NULL){
        head = new_city;
        tail = new_city;
        return;
    }
    new_city->next = head;
    head = new_city;
}
//Adds a city at the end of the city record linked list
void CityRecord::addCityAtTail(string name, int population, int income){
    City* new_city = new City(name,population,income);
    if(head == NULL){
        head = new_city;
        tail = new_city;
        return;
    }
    tail->next = new_city;
    tail = tail->next;
}

void CityRecord::displayLargestPopulation(){
    City* temp = head;
    City* max = head;
    if(head == NULL){
        cout<<"No city records.\n";
        return;
    }
    while(temp != NULL){
        if(temp->city_population > max->city_population){
            max = temp;
        }
        temp = temp->next;
    }
    cout<<max->city_name<<", "<<max->city_population<<", $"<<max->median_income<<endl;
}




int main()
{
    CityRecord record = CityRecord();
    int selection = 0;
    string input_name;
    int input_population;
    int input_income;
    bool running = true;
    while(running){
        cout<<"\n1. Add city record at the tail."<<endl;
        cout<<"2. Add city at the head."<<endl;
        cout<<"3. Display the city with the largest population."<<endl;
        cout<<"4. Display all the city records."<<endl;
        cout<<"5. Exit\n"<<endl;        
        cin >> selection;
        switch(selection){
            case 1:
                cout<<"Please enter the name of the city: ";
                cin>>input_name;
                cout<<"Please enter the population of the city: ";
                cin>>input_population;
                cout<<"Please enter the median income of the city: ";
                cin>>input_income;
                record.addCityAtTail(input_name,input_population,input_income);
                break; 

            case 2:
                cout<<"Please enter the name of the city: ";
                cin>>input_name;
                cout<<"Please enter the population of the city: ";
                cin>>input_population;
                cout<<"Please enter the median income of the city: ";
                cin>>input_income;
                record.addCityAtHead(input_name,input_population,input_income);
                break;

            case 3:
                record.displayLargestPopulation();
                break;

            case 4:
                record.printRecord();
                break;
            
            case 5:
                running = false;
                break;
            
            default:
                cout<<"Please enter a valid number"<<endl;
        }

    }

};