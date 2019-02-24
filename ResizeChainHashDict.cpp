#ifndef _RESIZECHAINHASHDICT_CPP
#define _RESIZECHAINHASHDICT_CPP

//ResizeChainHashDict.cpp
#include "ResizeChainHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a resizable hash table with
// chaining

const int ResizeChainHashDict::primes[] = {53, 97, 193, 389, 769, 1543, 3079,
      6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869,
      3145739, 6291469, 12582917, 25165843, 50331653, 100663319,
      201326611, 402653189, 805306457, 1610612741, -1};
// List of good primes for hash table sizes from
// http://planetmath.org/goodhashtableprimes
// The -1 at the end is to guarantee an immediate crash if we run off
// the end of the array.

ResizeChainHashDict::ResizeChainHashDict() {
  size_index = 0;
  size = primes[size_index];
  table = new ChainNode*[size](); // Parentheses initialize to all NULL
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

ResizeChainHashDict::~ResizeChainHashDict() {
  for (int i=0; i<size; i++) {
    // Delete the chains from each table entry...
    ChainNode *head = table[i];
    while (head!=NULL) {
      ChainNode *temp = head;
      head = head->next;
      delete temp->key;  // Each PuzzleState is a key exactly once.
      // Don't delete temp->data here, to avoid double deletions.
      delete temp;
    }
  }
  // Delete the table itself
  delete [] table;

  cout << "Probe Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << probes_stats[i] << endl;
  delete [] probes_stats;
}

int ResizeChainHashDict::hash(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }

#ifdef MARKING_TRACE
std::cout << "Hashing " << keyID << " to " << h << std::endl;
#endif

  return h;
}

void ResizeChainHashDict::rehash() {

  std::cout << "*** REHASHING number=" << number << ", size changes from " << size;



  int oldSize = size;
  size_index +=1;
  size = primes[size_index];
  ChainNode **oldTable = table;
  table = new ChainNode*[size]();
  number = 0;
  for (int i=0; i<oldSize; i++) {
    if (oldTable[i] != NULL) {


      while(oldTable[i] != NULL) {
        add(oldTable[i]->key, oldTable[i]->data);
        ChainNode *oldValue = oldTable[i];
        oldTable[i] = oldTable[i]->next; 
        delete oldValue;
      }
   
    } else {
//do nothing
    }

  }
  delete[] oldTable;


  std::cout << " to " << size << " ***\n";

}

bool ResizeChainHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred

  // Be sure not to keep calling getUniqId() over and over again!


  string keyInD = key->getUniqId();
  int newHash = hash(keyInD);
    if (table[newHash] == NULL) {
      probes_stats[0]++;
      return false ;
    } else {
      ChainNode *entry = table[newHash];
      int i = 0;
      while(entry!= NULL && entry->keyID != keyInD) {
        entry = entry->next;
        i++;
      }
      if(i < 20) {
        probes_stats[i]++;
      }
      if (entry == NULL) {
        return false;
      } else {
        pred = entry->data;
        return true;
      }
    }
}

// You may assume that no duplicate PuzzleState is ever added.
void ResizeChainHashDict::add(PuzzleState *key, PuzzleState *pred) {

  // Rehash if adding one more element pushes load factor over 1/2
  if (2*(number+1) > size) rehash();  // DO NOT CHANGE THIS LINE


  string keyInD = key->getUniqId();
  int newHash = hash(keyInD);
  if (table[newHash] == NULL) {
    table[newHash] = new ChainNode();
    table[newHash]->key = key;
    table[newHash]->keyID = keyInD;
    table[newHash]->data = pred;
    number++;
  } else {
    ChainNode *entry = table[newHash];
    ChainNode *current = new ChainNode();
    current->key = key;
    current->keyID = keyInD;
    current->data = pred;
    current->next = entry;
    table[newHash] = current;
    number++;
  }
}

#endif 