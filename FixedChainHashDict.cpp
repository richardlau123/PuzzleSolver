#ifndef _FIXEDCHAINHASHDICT_CPP
#define _FIXEDCHAINHASHDICT_CPP

//FixedChainHashDict.cpp
#include "FixedChainHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a fixed-size hash table with
// chaining

FixedChainHashDict::FixedChainHashDict(int table_size) {
  size = table_size;
  table = new ChainNode*[size](); // Parentheses initialize to all NULL
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
}

FixedChainHashDict::~FixedChainHashDict() {
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

int FixedChainHashDict::hash(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }

#ifdef MARKING_TRACE
std::cout << "Hashing " << keyID << " to " << h << std::endl;
#endif

  return h;
}

bool FixedChainHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred


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


void FixedChainHashDict::add(PuzzleState *key, PuzzleState *pred) {
  string keyInD = key->getUniqId();
  int newHash = hash(keyInD);
  if (table[newHash] == NULL) {
    table[newHash] = new ChainNode();
    table[newHash]->key = key;
    table[newHash]->keyID = keyInD;
    table[newHash]->data = pred;
  } 
  else {
    ChainNode *entry = table[newHash];
    ChainNode *current = new ChainNode();
    current->key = key;
    current->keyID = keyInD;
    current->data = pred;
    current->next = entry;
    table[newHash]= current;
  }

}

#endif 
