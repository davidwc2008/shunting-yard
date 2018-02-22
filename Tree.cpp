//basically same comments from the Stack.cpp

#include "Tree.h"
#include <iostream>
#include <cstring> //for strcpy

char* Tree::top() {
  if (head == NULL) {
    return NULL;
  }
  return head->a;
}

char* Tree::pop() {
  if (head != NULL) {
    char* temp = new char[10];
    strcpy(temp, head->a);
    Node2* TOP = head;
    head = head->next;
    delete TOP;
    return temp;
  }
  return 0;
}

void Tree::push(char* a) {
  Node2* t = new Node2();
  t->next = head;
  strcpy(t->a, a);
  head = t;
}
