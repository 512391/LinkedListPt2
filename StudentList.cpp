#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "Node.h"

/*
  Author: Jay Williamson
  Date: 10/24/2024
  This program maintains a list of students which can be added to or deleted from
  you can also print the students and type QUIT to exit
 */

using namespace std;

//Makes and returns a new students
Student* makeStudent()
{
  //variables for the student
  char firstName[10] = {};
  char lastName[10] = {};
  float GPA = 0;
  int id = 0;

  //gets the students info
          cout << "Enter Student First Name\n";
          cin >> firstName;
	  cout << "Enter Student Last Name\n";
          cin >> lastName;
          cout << "Enter GPA\n";
          cin >> GPA;
          cout << "Enter ID\n";
          cin >> id;

	  //creates the new students
          Student* newStudent = new Student();

	  //copies all of the info into the student
          strcpy(newStudent->firstName, firstName);
	  strcpy(newStudent->lastName, lastName);
	  
          newStudent->GPA = GPA;
          newStudent->id = id;
	  
	  return newStudent;
}

//this prints all of the students in the list
void printNames(Node* head)
{
  //checks if there is a list at all
  if(head == nullptr)
    {
      cout << "list empty \n";
      return;
    }

  //gets the student once to reuse
  Student* currentStudent = head->getStudent();

  //outputs the stuff
  cout << "ID: " << currentStudent->id << "\n";
  cout << setprecision(2);
  cout << "GPA: " << currentStudent->GPA << "\n";
  cout << "First Name: " << currentStudent->firstName << "\n";
  cout << "Last name: " << currentStudent->lastName << "\n";

  //checks if it should get the next student if there is one
  if(head->getNext() != nullptr)
    {
      //if there is one it prints the next persons stuff
      printNames(head->getNext());
    }
  else
    {
      //outherwise it just exits the recursion
      cout << endl;
      return;
    }
}

//this deletes a node based on an id number
Node* deleteName(Node* newHead, Node* head, Node* previous, int toDelete)
{
  //checks if ther is a list at all
  if(newHead == nullptr)
    {
      //gets out if there is no list
      cout << "There is no list to delete from \n";
      return newHead;
    }

  //this accesses the next node to use
  Node* next = head->getNext();

  //this checks if the node it the one to delete
  if(head->getStudent()->id == toDelete)
    {
      //this checks whether it is in the middle of the list
      if(previous != nullptr && next != nullptr)
        {
	  //this corrects the list
          previous->setNext(next);
	  //this deleted the node it is on
          delete head;
	  //continues the search
          deleteName(newHead, next, previous, toDelete);
        }//this checks if it is the end of the list
      else if(previous != nullptr)
        {
	  //sets the previous one to the new end of the list
          previous->setNext(nullptr);
	  //deletes current node
          delete head;
	  //returns out
          return newHead;
        }
      else//this case is for the beginning
        {
	  //deletes the current node
          delete head;
	  //checks if it is the beginning and end
          if(next == nullptr)
            {
	      //if it is the only element it returns a nullptr as there is no list
              return nullptr;
            }
	  //otherwise it continues searching with the next element as the new head
          deleteName(next, next, nullptr, toDelete);
        }
    }//if it is not the one to delete and there are more elements it continues searching
  else if(head->getNext() != nullptr)
    {
      deleteName(newHead, next, head, toDelete);
    }
  else//if it is the end of the list and it is not the one to delete it returns the new head in case the first element was deleted
    {
      return newHead;
    }
}

//this adds a node to the linked list
Node* addNode(Node* previous, Node* head, Node* toAdd, Node* returnHead)
{
  //if it is at the end of the list it sets the toAdd to the end of the list
  if(head->getNext() == nullptr)
    {
      //sets the toAdd tot he end of the list
      if(toAdd->getStudent()->id > head->getStudent()->id) //if it is not at the end of the list it keeps traversing to the end
	{
	  head->setNext(toAdd);
	}
      else
	{
	  if(previous == nullptr)
	    {
	      toAdd->setNext(head);
	      return toAdd;
	    }
	  else
	    {
	      previous->setNext(toAdd);
	      toAdd->setNext(head);
	    }
	}
      return returnHead;
    }
  else if(toAdd->getStudent()->id > head->getStudent()->id) //if it is not at the end of the list it keeps traversing to the end
    {
      addNode(head, head->getNext(), toAdd, returnHead);
    }
  else
    {
      if(previous == nullptr)
	{
	  toAdd->setNext(head);
	  return toAdd;
	}
      else
	{
	  previous->setNext(toAdd);
	  toAdd->setNext(head);
	  return returnHead;
	}
    }
}

float getAverageGPA(Node* current, int amountOfNodes, float amount)
{
  amountOfNodes++;
  amount += current->getStudent()->GPA;
  if(current->getNext() == nullptr)
    {
      return amount/amountOfNodes;
    }
  else
    {
      getAverageGPA(current->getNext(), amountOfNodes, amount);
    }
}

int main()
{
  //the head of the linked list that holds all of the students
  Node* head = nullptr;

  //the input
  char input[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};
  const char emptyInput[7] = {' ', ' ', ' ', ' ', ' ', ' ', ' '};

  //gets initial input
  cout << "Enter one of the following inputs, PRINT. ADD, DELETE, AVG, or QUIT \n";
  cin >> input;

//checks if it should quit and end
  while(strncmp(input, "QUIT", 4) != 0)
    {
      //Checks if it is adding a student
      if(strncmp(input, "ADD", 3) == 0)
	{
	  Student* st = makeStudent();

	  //adds the student that was made to the linkedList
	  if(head == nullptr)
	    {
	      head = new Node(st);
	    }
	  else
	    {
	      head = addNode(nullptr, head, new Node(st), head);
	    }
	}//Checks if it should print the students
      else if(strncmp(input, "PRINT", 5) == 0)
	{
	  printNames(head);
	}//Checks if it should delete a student
      else if(strncmp(input, "DELETE", 6) == 0)
	{
	  int id = 0;
	  //gets an id to check for
	  cout << "Enter an ID to delete \n";
	  cin >> id;

	  head = deleteName(head, head, nullptr, id);
	}
      else if(strncmp(input, "AVG", 3) == 0)
        {
	  cout << getAverageGPA(head, 0, 0) << endl;
	}

      //clears the input array
      for(int i = 0; i < 7; i++)
	{
	  input[i] = emptyInput[i]; 
	}

      //gets next input
      cout << "Enter one of the following inputs, PRINT. ADD, DELETE, AVG, or QUIT \n";
      cin >> input;
    }
  
  cout << "bye bye";

  return 0;
}
