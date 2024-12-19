#include <iostream>
#include"Student.h"

using namespace std;


class Node {
 public:
  Node(Student* stud); //create a node holding a student
  ~Node(); //destructor, deletes memory and sets next to null
  Node* getNext(); //gets the node in next
  Student* getStudent(); //gets the student associated with the node
  void setNext(Node* newNext); //allows more nodes to be attached next
 private:
  Node* next;
  Student* student;
};

