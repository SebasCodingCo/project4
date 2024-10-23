/*Sebastian Salas-Vaca
Project4-Dijkstras
In this project we use dijkstras alogrithm to find the best path from one coordinate of
the map to another. I chose to use an adjacency list as the main benefits of adjacency matrices
are nulified on top of the fact that adjacency lists are more space efficient.
*/
// dijsktras.cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
//for the pseudo code implementation from piazza
#include <tuple>

using namespace std;
// Main Execution

int main(int argc, char *argv[]) {
    int numOfTiles;
    cin >> numOfTiles;

    //takes in the tiles and values of the tiles 
    unordered_map<char, int> tiles;

    for(int i = 0; i < numOfTiles; i++){
        char tile;
        int value;
        cin >> tile >> value;
        tiles[tile] = value;
    }

    //take in the size of the map and everything in the map
    int rows, columns;
    cin >> rows >> columns;

    //int might have to be changed in this unordered map depending on how we want to store each node
    // first int is the current value, second is the value it wants to go to
    map<int, multimap<int, int>> graphList;
    //create the vector with a number of nodes = rows *columns
    vector<int> mapVals;
    for(int i = 0; i < columns*rows; i++){
        char tile;
        cin >> tile;
        mapVals.push_back(tiles.at(tile));
    }

    //create the graph with all the nodes pointing to the left right up and down if possible
    for(int i = 0; i < columns*rows; i++){
        //connect each tile to the other tiles and connect them to their value
        //connect the node to the upper
        cout << "Inserting connections for node " << i << ": ";

        if(i/rows != 0){
            cout << "Up: " << i - columns << " ";
            //i-rows bc this would be directly one above it in the map
            graphList[i].insert({mapVals[i-rows], i-rows});
        }
        //connect node to the lower
        if(i/rows != rows - 1){
            graphList[i].insert({mapVals[i+rows],i+rows});
            cout << "Down: " << i + columns << " ";
        }
        //checks if this node should connect to the node to the left
        if(i % columns != 0){
            //adds the weight of the node to the left and the node to the left to the node
            graphList[i].insert({mapVals[i-1],i-1});
            cout << "Left: " << i - 1 << " ";
        }
        //connect node to the right
        if(i % columns != columns - 1){
            //columns - 1 bc this would be furthest right
            cout << "Right: " << i + 1 << " ";
            graphList[i].insert({mapVals[i+1], i+1});
        }
        cout << endl;
    }

    //prints out the map in the value form
    /*for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            cout << mapVals[i*rows + j] << " ";
        }
        cout << endl;
    }*/
    
    for (const auto& outerpair : graphList) {
        cout << outerpair.first << "| ";
        for (const auto& innerpair : outerpair.second) {
            cout << innerpair.first << ":" << innerpair.second << " ";
        }
        cout << endl;
    }   

    //just to do the test get rid of this or edit it
    int row,column;
    cin >> row >> column;
    cin >> row >> column;
    return 0;
}

