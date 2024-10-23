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
#include <queue>
#include <set>

using namespace std;
// Main Execution

//following the pseudo code implementation from the shortest path on piazza
map<int,int> dijkstra(map<int, vector<int>> graph, vector<int> vals, int node){
    //the tuple stores trios of cost, name, and the 
    //looked up how to make a priority queue a min heap on geeks for geeks and made it hold tuples
    priority_queue<tuple<int, int, int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> frontier;
    //marked stores the node and the cost to get there, realized we need the cost to find the smallest path
    map<int, int> marked;
    //path should store the node and who it is coming from
    map<int,int> path;
    //create the first tuple in frontier so we can just continuously go through the 
    //while loop until the shortest path to each is found
    frontier.push(make_tuple(0, node, node));
    path[0] = 0;

    while(!frontier.empty()){
        tuple <int,int,int> top = frontier.top();
        node = get<1>(top);
        frontier.pop();
        //continue if node is not in marked 
        if(marked.count(node) == 0){
            //vals[node] is the cost of getting into the current node            
            marked[node] = get<0>(top);
            for(int u: graph[node]){
                //need a conditional because we don't want to add to a value that has already unless it is a shorter path
                //graph[node][i] is the node connecting to current node
                //vals[graph[node][i]] is the cost of the node connecting to the current node 
                //frontier push tuple (u.cost + v.cost, v.name, u.name)
                if(marked.count(u) == 0){
                    frontier.push(make_tuple(vals[u] + marked[node], u, node));
                    path[u] = node;
                }
                else if((vals[u] + marked[node]) < marked[u]){
                    frontier.push(make_tuple(vals[u] + marked[node], u, node));       
                    path[u] = node;            
                }
                
            }
        }
    }
    
    return path;
}

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
    map<int, vector<int>> graphList;
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

        if(i/rows != 0){
            //i-rows bc this would be directly one above it in the map
            graphList[i].push_back(i-rows);
        }
        //connect node to the lower
        if(i/rows != rows - 1){
            graphList[i].push_back(i+rows);
        }
        //checks if this node should connect to the node to the left
        if(i % columns != 0){
            //adds the weight of the node to the left and the node to the left to the node
            graphList[i].push_back(i-1);
        }
        //connect node to the right
        if(i % columns != columns - 1){
            //columns - 1 bc this would be furthest right
            graphList[i].push_back(i+1);
        }
    }
    int row1,column1,row2,column2;
    cin >> row1 >> column1;
    //row1*rows +columns is where our beginning node should be
    map<int,int> path = dijkstra(graphList,mapVals, (row1*rows + column1));
    cin >> row2 >> column2;

    //could be row2*columns need to check
    int endNode = row2*rows + column2;

    //go until row2 column2 reaches the original node
    map<int,int> :: iterator i;
	//go through every piece of information going from artist down to song
	for(i = path.begin(); i != path.end(); i++){
        cout << i->first << ":" << i->second << endl;
	}

    int totalCost = 0;
    int currentNode = endNode;
    cout << currentNode/rows << " " << currentNode%columns << endl;
    //this is to get the path from start node to end node
    while(currentNode != (row1*rows + column1)){
        currentNode = path[currentNode];
        //cout << "added " << mapVals[currentNode] << endl;
        totalCost+= mapVals[currentNode];
        cout << currentNode/rows << " " << currentNode%columns << endl;
    }
    cout << totalCost << endl;

    //prints out the map in the value form
    /*for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            cout << mapVals[i*rows + j] << " ";
        }
        cout << endl;
    }*/
    //prints nodes and the edges they have connections to in the graph
    /*for (const auto& outerpair : graphList) {
        cout << outerpair.first << "| ";
        for (const auto& innerpair : outerpair.second) {
            cout << innerpair << " ";
        }
        cout << endl;
    }*/   
    return 0;
}



