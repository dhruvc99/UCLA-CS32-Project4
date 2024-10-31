// maze.cpp
// Dhruv Chakraborty, UID: 204-962-098
// UCLA CS32, HW3: part 3

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec) return true; // since start coord same as end coord

	maze[sr][sc] = 'x'; // use lowercase x to mark start as visited
	
	// checking the four directions and recursively calling pathExists again:
	// NORTH:
	if (maze[sr - 1][sc] == '.')
	{
		if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec)) // call pathExists with starting point changed to NORTH
			return true;
	}
	// EAST:
	if (maze[sr][sc + 1] == '.')
	{
		if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec)) // call pathExists with starting point changed to EAST
			return true;
	}
	// SOUTH:
	if (maze[sr + 1][sc] == '.')
	{
		if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec)) // call pathExists with starting point changed to SOUTH
			return true;
	}
	// WEST:
	if (maze[sr][sc - 1] == '.')
	{
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec)) // call pathExists with starting point changed to WEST
			return true;
	}

	return false;
}