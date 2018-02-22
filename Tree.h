//basically the second stack for expression tree

#pragma once

#include <iostream>

struct Node2 {
  char a[10];
  Node2* next = NULL;
};

class Tree {
 public:
  char* top();
  char* pop();
  void push(char* a);

 private:
  Node2* head = NULL;
};

