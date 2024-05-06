#include <iostream>
#include "utilities.h"
#include "graph.h"

using namespace std;

//Main run file to control the program flow
int main(){
    //Local variables for our loop
    Network net = Network();
    Graph graph;
    bool running = true;
    string file_input;
    string style;
    string flag;
    string start_inp = "";
    string end_inp = ""; 
    bool D_check = false;
    bool UD_check = false;
    int selection;

    //main loop
    while(running){
        cout<<"\nDean Prach - Homework 5 - CSE 310"<<endl;
        cout<<"1. Read the graph from the file (enter the file name, D or UD, and the flag)"<<endl;
        cout<<"2. Print Adjacency List"<<endl;
        cout<<"3. Single Source, enter the starting node number"<<endl;
        cout<<"4. Single Pair, enter the starting node number and ending node numbers"<<endl;
        cout<<"5. Print Path, enter the starting node and ending node numbers"<<endl;
        cout<<"6. Print Length of Path, enter the starting node and ending node numbers"<<endl;
        cout<<"7. Print All Paths, enter the starting node number"<<endl;
        cout<<"8. Stop"<<endl;

        cin>>selection;
        switch(selection){
            //Read the graph: user will be prompted to enter a file name, then either D or UD for directed or undirected
            //and lastly for the flag which will be a 1 or a 2
            case 1:
                cout<<"\nPlease enter the file name (<file_name>.txt): ";
                cin.ignore();
                getline(cin,file_input);
                cout<<"Please enter either directed or undirected (D or UD): ";
                getline(cin,style);
                cout<<"Please enter the flag (1 or 2): ";
                getline(cin,flag);
                net.readFromFile(file_input);
                graph = Graph(net.numVertices,net.numEdges);
                graph.initializeLists(net.edges);
                if(style == "D" && flag == "1"){
                    graph.addDirectedEdges_F();
                    D_check = true;
                }
                else if(style == "D" && flag == "2"){
                    graph.addDirectedEdges_B();
                    D_check = true;
                }
                else if(style == "UD" && flag == "1"){
                    graph.addUndirectedEdges_F();
                    UD_check = true;
                }
                else if(style == "UD" && flag == "2"){
                    graph.addUndirectedEdges_B();
                    UD_check = true;
                }
                else{
                    cout<<"\nInvalid Input\n";
                }
                break;

            //Makes sure that we have read from a file, if we have then print out adjacency list
            case 2:
                if(D_check || UD_check){
                    graph.printAdjList();
                }
                else{
                    cout<< "\nYou have not read from a file yet\n";
                }
            break;

            //This case will be for a single source djikstras search which will get all of the shortest paths to each vertex
            //from a single src node
            case 3:
                if(D_check || UD_check){
                    cout<<"Enter the starting node number: ";
                    cin>>start_inp;
                    graph.djikstras(graph.vertices[graph.findVertex(stoi(start_inp))]);
                }
                else{
                    cout<<"\nNot valid reading\n";
                }
            break;

            //This will be a dijkstras shortest path from a single src to a single dest
            case 4:
                if(D_check || UD_check){
                    cout<<"Enter the starting node number: ";
                    cin>>start_inp;
                    cout<<"Enter the ending node number: ";
                    cin>>end_inp;
                    graph.djikstras_singledest(graph.vertices[graph.findVertex(stoi(start_inp))],graph.vertices[graph.findVertex(stoi(end_inp))]);
                }
                else{
                    cout<<"\nNot valid reading\n";
                }
            break;

            //print a single path given a src vertex and a dest vertex
            case 5:
            if(D_check || UD_check){
                cout<<"Enter the starting node number: ";
                cin>>start_inp;
                cout<<"Enter the ending node number: ";
                cin>>end_inp;
                cout<<"\nThe path from " << start_inp << " to " << end_inp << " is: \n";
                graph.printSinglePath(graph.vertices[graph.findVertex(stoi(end_inp))]);
            }
            break;

            //Prints the length of the path and the total weight of the path
            case 6:
            if(D_check || UD_check){
                cout<<"Enter the starting node number: ";
                cin>>start_inp;
                cout<<"Enter the ending node number: ";
                cin>>end_inp;
                graph.printLength(graph.vertices[graph.findVertex(stoi(start_inp))],graph.vertices[graph.findVertex(stoi(end_inp))]);
            }
            break;

        //Prints out all of the paths that were generated
        //single src was selected all shortest paths to every vertex will be printed
            case 7: 
                if(D_check || UD_check){
                cout<<"Enter the starting node number: ";
                cin>>start_inp;
                graph.printAllShortestPaths();
                }
            break;

            //Stops the program
            case 8:
            running = false;
            break;
        }
    }
    
}
