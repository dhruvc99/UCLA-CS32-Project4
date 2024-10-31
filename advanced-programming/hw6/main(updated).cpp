#include<vector>
#include<iostream>
#include"colortree.h"
using namespace std;
int main()
{
    
	vector<vector<int> > map =
        { { 0, 1, 2, 3},
          { 0, 0, 1, 0},
          { 0, 0, 0, 0},
          { 0, 0, 0, 0}};
    
    // find path from node0 to node2
    int shortest1 = dijkstra(map, 0, 2);

    // find path from node2 to node0
    int shortest2 = dijkstra(map, 2, 0);
	
    cout << "Shortest path from 0 to 2 is " << shortest1 << endl;
    cout << "Shortest path from 2 to 0 is " << shortest2 << endl;
    
    return 0;
} 
