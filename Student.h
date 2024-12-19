#include<iostream>
/*
Author: jay williamson
date:12/19/24
this is the .h that holds the student info
  */
  class Student
  {
    public:
//all the students information
    char firstName[20];
    char lastName[20];
    float GPA;
    int id;
    int lastNameLength;
    int firstNameLength;
//random seed for hashing distribution
    int randomSeed;
    Student();
  };
