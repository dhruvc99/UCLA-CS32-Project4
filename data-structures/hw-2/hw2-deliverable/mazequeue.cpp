// mazequeue.cpp

#include <queue>
#include <string>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    
    Coord sp(sr, sc);
    coordQueue.push(sp);
    maze[sr][sc] = 'x'; // using lowercase x to mark a coord as visited
    
    while (coordQueue.empty() == false)
    {
        Coord current = coordQueue.front();
        coordQueue.pop();
        if (current.r() == er && current.c() == ec)
            return true;
        
        if (maze[current.r() + 1][current.c()] == '.')
        {
            Coord south(current.r() + 1, current.c());
            coordQueue.push(south);
            maze[south.r()][south.c()] = 'x';
        }
        
        if (maze[current.r()][current.c() - 1] == '.')
        {
            Coord west(current.r(), current.c() - 1);
            coordQueue.push(west);
            maze[west.r()][west.c()] = 'x';
        }
        
        if (maze[current.r() - 1][current.c()] == '.')
        {
            Coord north(current.r() - 1, current.c());
            coordQueue.push(north);
            maze[north.r()][north.c()] = 'x';
        }
        
        if (maze[current.r()][current.c() + 1] == '.')
        {
            Coord east(current.r(), current.c() + 1);
            coordQueue.push(east);
            maze[east.r()][east.c()] = 'x';
        }
    }
    
    return false;
}
