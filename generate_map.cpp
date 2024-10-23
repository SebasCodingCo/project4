#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    //this gets random random seed
    srand(time(0));
    int size;
    cin >> size;

    //write out to this file named by the size of the map
    string file = to_string(size);
    ofstream fout;
    fout.open(file);
    
    //the possible tiles
    vector <char> tiles = {'f','g','G','h','m','r'};

    for(int i = 0; i < size; i++){
        fout << tiles[rand()%6];
        for(int j = 1; j < size; j++){
            fout << " " << tiles[rand()%6];
        }
        fout << endl;
    }
}
