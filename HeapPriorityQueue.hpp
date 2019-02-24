//HeapPriorityQueue.hpp
#ifndef _HEAPPRIORITYQUEUE_HPP
#define _HEAPPRIORITYQUEUE_HPP


#include <vector>

#include "BagOfPuzzleStates.hpp"

// An implementation of a priority queue, using
// a min-heap as the underlying data structure.
//
// The priority should be based on each PuzzleState's getBadness() value.

class HeapPriorityQueue : public BagOfPuzzleStates
  {
  public:
    HeapPriorityQueue();
    PuzzleState *take_out();
    void put_in(PuzzleState *elem);
    bool is_empty();
    ~HeapPriorityQueue();


    
  private:


    bool is_root(int index);
    int parent(int index);
    int first_child(int index);
    int num_children(int index);
    bool is_leaf(int index);

    // The array representation of the heap.
    vector<PuzzleState *> heap;
  };

#endif
