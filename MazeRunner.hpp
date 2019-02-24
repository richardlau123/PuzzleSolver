#ifndef _MAZERUNNER_HPP
#define _MAZERUNNER_HPP

#include <iostream>
#include <string>
using namespace std;

/*
  MazeRunner.hpp

  Explores a 2D rectangular maze.
*/

class MazeRunner : public PuzzleState {
 public:
  MazeRunner(int, int, string, int, int);
    // The constructor takes the number of rows and columns in the maze,
    // then a string of length row*col showing the maze, in row-major order,
    // where a space indicates open space, $ indicates a target, and
    // other characters indicate obstacles.
    // The last two parameters are the starting row and column.
  MazeRunner(const MazeRunner&); // Deep copy constructor
  ~MazeRunner();

  // returns true if this PuzzleState is a solution for the puzzle
  bool isSolution();

  // returns a vector of possible next positions for the puzzle.
  vector<PuzzleState*> getSuccessors();

 
  //
  // returns an integer representing a guess of how far we are
  // from a solution.  Bigger means farther from solution.
  int getBadness();


  
  // Returns a unique string for any state
  string getUniqId();

  // print the puzzle state
  void print (ostream& out);

 private:
  const int rows; // number of rows
  const int cols; // number of columns
  char *maze; // array of size rows*cols to hold the maze
  int my_row; // current row position of explorer
  int my_col; // current col position of explorer
  int target_row; // location of a $ in the maze
  int target_col;
  void move_down(); // explore downward (increase row)
  void move_up(); // explore upward (decrease row)
  void move_right(); // explore rightward (increase col)
  void move_left(); // explore leftward (decrease col)
};

#endif
