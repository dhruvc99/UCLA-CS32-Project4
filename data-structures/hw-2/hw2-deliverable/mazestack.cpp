// mazestack.cpp

#include <stack>
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
    stack<Coord> coordStack;
    
    Coord sp(sr, sc);
    coordStack.push(sp);
    maze[sr][sc] = 'x'; // using lowercase x to mark a coord as visited
    
    while (coordStack.empty() == false)
    {
        Coord current = coordStack.top();
        coordStack.pop();
        if (current.r() == er && current.c() == ec)
            return true;
        
        if (maze[current.r() + 1][current.c()] == '.')
        {
            Coord south(current.r() + 1, current.c());
            coordStack.push(south);
            maze[south.r()][south.c()] = 'x';
        }
        
        if (maze[current.r()][current.c() - 1] == '.')
        {
            Coord west(current.r(), current.c() - 1);
            coordStack.push(west);
            maze[west.r()][west.c()] = 'x';
        }
        
        if (maze[current.r() - 1][current.c()] == '.')
        {
            Coord north(current.r() - 1, current.c());
            coordStack.push(north);
            maze[north.r()][north.c()] = 'x';
        }
        
        if (maze[current.r()][current.c() + 1] == '.')
        {
            Coord east(current.r(), current.c() + 1);
            coordStack.push(east);
            maze[east.r()][east.c()] = 'x';
        }
    }
    
    return false;
}
