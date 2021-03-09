#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <ctime>
#include <map>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

class Student
{
public:
  //constructor
  Student() //everytime a student is created they are given random name and chapter and freq = 1 except for if they already exist in the multimap
  {
    name = 1 + rand() % 15;    //15 students in the class named 1-15
    chapter = 1 + rand() % 15; // 15 possible chapters to ask
  }

  void printData(multimap<int, int> multimap)
  {
    std::ofstream out("data.txt");
    int freq = 1;
    int temp1;
    int temp2;
    std::vector<int> chap;

    //fail condition
    if (out.fail())
    {
      exit(1);
      out << "fail" << std::endl;
    }

    //printing out
    for (auto itr = multimap.begin(); itr != multimap.end(); ++itr)
    {
      out << "Student info" << std::endl;
      temp1 = itr->first;        //holds current student name
      temp2 = itr->second;       //holds current student chapter

//check
      out << "1: " << temp1 << endl;
      out << "2: " << temp2 << endl;
      int bruh;
      bruh = (++itr)->first;
//check

      if ((++itr)->first == temp1) //if next key in map (aka student name) is the same as current student name
      {
        ++freq;
        if (itr->second != temp2)      //if student is same but asked a diff chapter
          chap.push_back(itr->second); //insert into vector
        continue;
      }

      out << "Student: " << itr->first << endl
          << "Freq: " << freq << endl;

    }

    for (auto e : chap)
    {
      out << "Chapters: " << e << std::endl; //needs this to loop thru vector
    }

    out << endl;

    chap.clear();

    out.close();
  }

  int name;    //student id essentially
  int chapter; //which chapter the student is asking a question from
};

#endif
