#include "utilities.h"

void Network::readFromFile(string file){
    //Set network file name
    this->networkFile = file;

    //Initializing local variables
    string numVertices_s;
    string numEdges_s;
    string edge_line;

    //Opening the file for reading
    inFile.open(file);

    //Read our vertex/edge count
    getline(inFile,numVertices_s,' ');
    if(numVertices_s.compare(" ")){
        getline(inFile, numVertices_s, ' ');
    }
    getline(inFile,numEdges_s);
    this->numVertices = stoi(numVertices_s);
    this->numEdges = stoi(numEdges_s);

    //Read in all of the edge information
    for(int i = 0; i < this->numEdges; i++){
        getline(inFile,edge_line,'\n');
        if(edge_line[0] == ' '){
            edge_line = edge_line.substr(1,edge_line.length());
        }
        this->edges.push_back(edge_line);
    }

    //Close our file
    inFile.close();

}