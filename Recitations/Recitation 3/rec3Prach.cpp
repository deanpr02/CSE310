#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;


class Ticket
{
    public:
    string ticket_name;
    int level_of_urgency;
    int priority_score;
    Ticket(string ticket_name, string level_of_urgency)
    {
        this->ticket_name = ticket_name;
        this->level_of_urgency = stoi(level_of_urgency);
        this->priority_score = 0;
    }
};

class TicketSystem
{
    public:
    vector<Ticket> ticket_heap;
    void add_ticket(string, string);
    void heapify();
    void resolve_ticket();
    void list_all_tickets();
};

//This method will add a ticket to the heap
void TicketSystem::add_ticket(string ticket_name, string level_of_urgency)
{
    Ticket new_ticket = Ticket(ticket_name,level_of_urgency);
    clock_t time = clock()/CLOCKS_PER_SEC;
    int t = int(time);
    int priority_score = ceil((pow(new_ticket.level_of_urgency,3))/t);
    new_ticket.priority_score = priority_score;
    this->ticket_heap.push_back(new_ticket);
    this->heapify();
}

//Heapify ensures the system follows the heap properties
void TicketSystem::heapify()
{
    int size = this->ticket_heap.size();
    int n = (size-2) / 2;
    int left_child;
    int right_child;
    while(n >= 0)
    {
        left_child = 2*n+1;
        right_child = 2*n+2;
        //Checks to see if the left child is the largest
        if(left_child < size)
        {
            if(this->ticket_heap[left_child].priority_score > this->ticket_heap[n].priority_score)
            {
                Ticket temp = ticket_heap[left_child];
                ticket_heap[left_child] = ticket_heap[n];
                ticket_heap[n] = temp;
            }
        }
        //Checks to see if the right child is the largest
        if(right_child < size)
        {
            if(this->ticket_heap[right_child].priority_score > this->ticket_heap[n].priority_score)
            {
                Ticket temp = ticket_heap[right_child];
                ticket_heap[right_child] = ticket_heap[n];
                ticket_heap[n] = temp;
            }
        }
        n--;
    }
}

//This pops the top priority ticket from the heap
void TicketSystem::resolve_ticket()
{
    Ticket resolved_ticket = this->ticket_heap[0];
    this->ticket_heap.erase(this->ticket_heap.begin());
    this->heapify();
    cout<<"The ticket with the title "<<resolved_ticket.ticket_name<< " is now resolved"<<endl;
}

//Prints out all of the tickets in the heap
void TicketSystem::list_all_tickets()
{
    int size = this->ticket_heap.size();
    for(int i = 0; i < size; i++)
    {
        cout<<"Ticket Name: " << this->ticket_heap[i].ticket_name <<endl;
        cout<<"Level of Urgency: " << this->ticket_heap[i].level_of_urgency <<endl;
        cout<<"Priority Score: " << this->ticket_heap[i].priority_score <<endl;
        cout<<"\n";
    }
}




int compute_TPS_score(Ticket ticket, double time)
{
    cout<<time;
    return 1;
    //return ceil(pow(ticket.level_of_urgency,3)/time);
}

int main()
{
    TicketSystem system = TicketSystem();
    bool running = true;
    int selection;
    string ticket_name;
    string level_of_urgency;
    while(running)
    {
        cout<<"1. Create a ticket\n2. Resolve a ticket\n3. List all tickets\n4. Exit\n";
        cin>>selection;
        switch(selection)
        {
        case 1:
            cout<<"\nPlease enter the name of the ticket: ";
            cin>>ticket_name;
            cout<<"Please enter the level of urgency for the ticket (1-7): \n";
            cin>>level_of_urgency;
            system.add_ticket(ticket_name,level_of_urgency);
            break;
        case 2:
            system.resolve_ticket();
            break;
        case 3:
            system.list_all_tickets();
            break;
        case 4:
            running = false;
            break;
    }
    
    
}
}