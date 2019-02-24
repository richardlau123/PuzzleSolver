//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

HeapPriorityQueue::HeapPriorityQueue() {
  // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // no clean-up to do, since the heap is not dynamically allocated
}

void HeapPriorityQueue::put_in(PuzzleState *elem) {
 
  int current_badness = elem->getBadness();
  int hole = heap.size();
  heap.push_back(elem);
  while (hole > 0 && current_badness < (heap[(hole-1)/2])->getBadness()) {
    heap[hole]= heap[(hole-1)/2];
    hole = (hole-1)/2;
  }  
  int newPos = hole;
  heap[newPos] = elem;
}

PuzzleState * HeapPriorityQueue::take_out() {
    assert(!is_empty());
  PuzzleState * returnVal = heap[0];
  int size = heap.size() -1;
  int hole = 0;
  int target = 0;
  while (2*hole+1 < heap.size() -1){
    int left = 2*hole + 1;
    int right = left + 1;
    if (right < size && ((heap[right]->getBadness()) < (heap[left]->getBadness()))) {
      target = right;
    }
    else {target = left;
    }

    if (heap[target]->getBadness() < heap[size]->getBadness()){
      heap[hole] = heap[target];;
      hole = target;
    }
    else break;
  }
  heap[hole] = heap[size];
  heap.pop_back();
  return returnVal;





bool HeapPriorityQueue::is_empty() {
  return (heap.size() == 0);
}

int HeapPriorityQueue::parent(int index) {
  return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
  return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
  return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
  return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
  int fchild = first_child(index);
  return max(0, min(2, (int)heap.size() - fchild));
}

#endif
