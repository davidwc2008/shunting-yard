#include "Stack.h"

//getting the top node
char Stack::top() {
  if (head == NULL) {
    return '\0';
  }
  return head->a;
}

//popping the node off (linked list procedures)
char Stack::pop() {
  if (head != NULL) {
    char b = head->a;
    Node* TOP = head;
    head = head->next;
    delete TOP;
    return b;    
  }
  return 0;
}

//pushing a node to the top (linked list procedures)
void Stack::push(char a) {
  Node* c = new Node();
  c->next = head;
  c->a = a;
  head = c;
}
