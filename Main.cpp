/*
David Chen
2018 C++
Shunting Yard Program
*/

#include <iostream>
#include <cstring>
#include "Stack.h"
#include "Tree.h"

using namespace std;

struct TREENODE {
  char * a;
  TREENODE* left = NULL;
  TREENODE* right = NULL;
};

//Function prototypes for shunting
char* POSTFIX (char *infix);
int precedence (char a);

//Function prototypes for expression tree
TREENODE* getTree(Tree &postfix);
void prefix(TREENODE* node);
void postfix2(TREENODE* node);
void infix(TREENODE* node);
void deleteTree(TREENODE* node);

int main() {
  //char array declarations
  char input_post[80] = {' '};
  char input_pre[80] = {' '};
  char input_in[80] = {' '};
  char input[80] = {' '};

  char again = 'y';
  
  while (again == 'y') {
    cout << "Welcome to the Shunting Yard Program. Enter a mathematical expression (infix notation, no equals sign, and using spaces between each token).  It can contain the four basic arithmetic expressions, powers, integer numbers, and parentheses." << endl;
    cin.getline(input,80);
    strcpy(input_in, input);

    cout << "This is your mathematical expression in infix notation (original): " << input_in << endl;

    //convert infix to postfix
    char* postfix = POSTFIX(input);

    //create a new stack for the tree
    Tree stack_t;
    
    int i = 0;
    while (postfix[i]) {
      if (postfix[i] == ' ') {
	i++;
      }
      if ((postfix[i] == '0') || (postfix[i] == '1') || (postfix[i] == '2') || (postfix[i] == '3') || (postfix[i] == '4') || (postfix[i] == '5') || (postfix[i] == '6') || (postfix[i] == '7') || (postfix[i] == '8') || (postfix[i] == '9')) {
	char temp[10];
	int j = 0;
	while ((postfix[i] == '0') || (postfix[i] == '1') || (postfix[i] == '2') || (postfix[i] == '3') || (postfix[i] == '4') || (postfix[i] == '5') || (postfix[i] == '6') || (postfix[i] == '7') || (postfix[i] == '8') || (postfix[i] == '9')) {
	  temp[j++] = postfix[i++];
	}
	temp[j++] = '\0';
	stack_t.push(temp);
      } else {
	char temp2[2] = {postfix[i++], '\0'};
	stack_t.push(temp2);
    }
    }
  delete[] postfix;
  TREENODE* root = getTree(stack_t);

  //print the prefix, postfix, and infix forms from the expression tree
  
  cout << endl << "Prefix from tree: ";
  prefix(root);
  cout << endl << "Postfix from tree: ";
  postfix2(root);
  cout << endl << "Infix from tree: ";
  infix(root);

  deleteTree(root);
  
  }
  return 0;
}

//creating the postfix version by shunting yard algorithm
char* POSTFIX(char* infix) {
  Stack s;
  char* postfix = new char[strlen(infix) + 1];
  //infix and postfix counters respectively
  int in_c = 0;
  int post_c = 0;

  while (infix[in_c]) {
    if (infix[in_c] == ' ') {
      in_c++;
    }

    if ((infix[in_c] == '0') || (infix[in_c] == '1') || (infix[in_c] == '2') || (infix[in_c] == '3') || (infix[in_c] == '4') || (infix[in_c] == '5') || (infix[in_c] == '6') || (infix[in_c] == '7') || (infix[in_c] == '8') || (infix[in_c] == '9')) {
	while ((infix[in_c] == '0') || (infix[in_c] == '1') || (infix[in_c] == '2') || (infix[in_c] == '3') || (infix[in_c] == '4') || (infix[in_c] == '5') || (infix[in_c] == '6') || (infix[in_c] == '7') || (infix[in_c] == '8') || (infix[in_c] == '9')) {
	  postfix[post_c++] = infix[in_c++];
	}
	postfix[post_c++] = ' ';
      }
    else if ((infix[in_c] == '+') || (infix[in_c] == '-') || (infix[in_c] == '*') || (infix[in_c] == '/') || (infix[in_c] == '^')) {
      while (((s.top() == '+') || (s.top() == '-') || (s.top() == '*') || (s.top() == '/') || (s.top() == '^')) &&
	     ((infix[in_c] != '^' && precedence(infix[in_c]) <= precedence(s.top())) || (infix[in_c] == '^' && precedence(infix[in_c]) < precedence(s.top())))) {
	postfix[post_c++] = s.pop();
	postfix[post_c++] = ' ';
      }
      s.push(infix[in_c++]);
    }
    else if (infix[in_c] == '(') {
      s.push(infix[in_c++]);
    }
    else if (infix[in_c] == ')') {
      while (s.top() != '(') {
	postfix[post_c++] = s.pop();
	postfix[post_c++] = ' ';
	if (s.top() == 0) {
	  break;
	}
      }
      s.pop();
      in_c++;
    }
  } //first while loop

  while (s.top()) {
    postfix[post_c++] = s.pop();
    postfix[post_c++] = ' ';
  }
  postfix[post_c - 1] = 0;

  return postfix;
}

//this function determines the precedence of each operator
int precedence (char a) {
  if (a == '+' || a == '-') {
    return 0;
  } else if (a == '*' || a == '/') {
    return 1;
  } else if (a == '^') {
    return 2;
  } else {
    return -1;
  }
}

//creating the expression tree
TREENODE* getTree(Tree &postfix) {
  if ((*postfix.top() == '+') || (*postfix.top() == '-') || (*postfix.top() == '*') || (*postfix.top() == '/') || (*postfix.top() == '^')) {
    TREENODE* d = new TREENODE();
    d->a = postfix.pop();
    d->right = getTree(postfix);
    d->left = getTree(postfix);
    return d;
  } else {
    TREENODE* d = new TREENODE();
    d->a = postfix.pop();
    return d;
  }
}

//getting the prefix form from the experssion tree
void prefix(TREENODE* node) {
  if ((*(node->a) == '+') || (*(node->a) == '-') || (*(node->a) == '*') || (*(node->a) == '/') || (*(node->a) == '^')) {
    cout << node->a << ' ';
    //recursive calls
    prefix(node->left);
    prefix(node->right);
  } else {
    cout << node->a << ' ';
  }
}

//getting the postfix form from the expression tree
void postfix2(TREENODE* node) {
  if ((*(node->a) == '+') || (*(node->a) == '-') || (*(node->a) == '*') || (*(node->a) == '/') || (*(node->a) == '^')) {
    //recursive calls
    postfix2(node->left);
    postfix2(node->right);
    cout << node->a << ' ';
  } else {
    cout << node->a << ' ';
  }
}

//getting the infix form from expression tree (not just the input)
void infix(TREENODE* node) {
  if ((*(node->a) == '+') || (*(node->a) == '-') || (*(node->a) == '*') || (*(node->a) == '/') || (*(node->a) == '^')) {
    if ((*(node->left->a) == '+') || (*(node->left->a) == '-') || (*(node->left->a) == '*') || (*(node->left->a) == '/') || (*(node->left->a) == '^')) {
      cout << "(";
      //recursive call
      infix(node->left);
      cout << ")";
    } else {
      //recursive call
      infix(node->left);
    }
    cout << node->a;

    if ((*(node->right->a) == '+') || (*(node->right->a) == '-') || (*(node->right->a) == '*') || (*(node->right->a) == '/') || (*(node->right->a) == '^')) {
      cout << "(";
      //recursive call
      infix(node->right);
      cout << ")";
    } else {
      //recursive call
      infix(node->right);
    }
  } else { // first if
    cout << node->a; 
  }
}

//destroying the tree
void deleteTree(TREENODE* node) {
  if (node) {
    //recursive calls
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}
