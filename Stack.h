//first stack header file

#pragma once

#include <iostream>

//creating the nodes for the linkedlist
struct Node {
  char a;
  Node* next = NULL;
};

class Stack { //LIFO (Last in first out)
 public:
  char top(); //this gets the top of the stack
  char pop(); //pops a node off the stack
  void push(char a); //push something to the stack

 private:
  Node* head = NULL;
  
};
