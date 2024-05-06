#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

//Network class which is in control of reading in our files that contain the graph.
class Network{
    public:
    string networkFile;
    ifstream inFile;
    vector<string> edges;
    int numVertices;
    int numEdges;
    void readFromFile(string);
};

#endif