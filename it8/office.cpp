#include "STUDENT_new.h"

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <ctime>
#include <iomanip>
#include <map>
#include <iterator>
#include <fstream>

using namespace std;

bool arrive()
{
        if (rand() % 15 == 1) //probability student will arrive is 1/15 for each minute, expect 4 students per office hour session
                return true;
        else
                return false;
}

//sourced from GFG
int searchStudent(int num, multimap<int, int> multimap, int n)
{
        cout << "search for which student (enter num range): " << endl;
        int i;
        for (auto itr = multimap.begin(); itr != multimap.end(); ++itr)
        {
                if (itr->second == num)
                        return i;
                return -1;
        }
}

int time_need()
{
        return (1 + rand() % 15); //how much time student needs: 1-15 minutes;
}

int urgency()
{
        return (1 + rand() % 5); //how much time student needs: 1-15 minutes;
}

void check(priority_queue<int> &pq, int &time_begin, int &time, int *total_time, double &wait, queue<int> &arrive)
{
        if (time == (pq.top() + time_begin))
        { //checks if student can be popped off
                pq.pop();
                arrive.pop();
                cout << "pop! " << time << endl;
                if (pq.size() >= 1)
                {
                        wait += time - arrive.front();
                }
                time_begin = time;
        }

        if (pq.top() + time > *total_time)
        { // checks if teacher will need to stay past 60+ min
                *total_time = (time_begin + pq.top());
        }
}

double avg(double &sum, double &count)
{
        return (sum /= count);
}

int main()
{
        //setup stuff
        srand(time(NULL));
        double s_count = 0;
        double s_sum = 0;
        double t_sum = 0;
        double wait = 0;
        bool isTrue = true;

        //algortihm
        for (int i = 0; i < 100; i++)
        { // loop 100 times
                cout << setw(45) << "office session " << i + 1 << endl;
                priority_queue<int> pq;
                queue<int> t_arrive;
                int *total_time = new int;
                *total_time = 60;
                int time_begin = 0; //time when prof begins answering student's q

                for (int time = 0; time <= *total_time; time++)
                { //actual loop
                        int x;

                        if (arrive() && time <= 60)
                        { //will a student arrive at this minute?
                                if (pq.empty())
                                        time_begin = time;
                                t_arrive.push(time);
                                x = time_need(); //push student and allot random time
                                s_sum += x;
                                s_count++;
                                pq.push(x);
                                cout << "arrive: " << time << " need: " << x << endl;
                        }
                        if (!pq.empty())
                        { // if q is not empty then check if student can be popped
                                check(pq, time_begin, time, total_time, wait, t_arrive);
                        }
                        else if (pq.empty() && time == 60)
                        { // if 60 min have passed but q empty;
                                break;
                        }

                } //actual

                if (*total_time > 60)
                {
                        t_sum += (*total_time) - 60;
                }

                cout << "total wait " << wait << endl;
                cout << "total prof spent " << t_sum << endl;

        } //100 loop

        //info:
        cout << "Student spends avg " << avg(wait, s_count) << "min waiting" << endl;
        cout << "Student spends avg " << avg(s_sum, s_count) << "min with professor" << endl;
        cout << "Professor spends avg " << t_sum / 100.0 << " min longer than expected past 1 hr point" << endl;

        int temporary;
        cout << "Would you like to search for a student: " << endl;
        cin >> temporary;

        if (temporary > 0)
        {
                cout << searchStudent(temporary, multimap, 80);
        }

        //multimap stuff starts here
        multimap<int, int> multimap;

        for (int i = 0; i < s_count; i++) //s_count is basically the total amount of qs professor answers
        {
                Student s;
                multimap.insert(pair<int, int>(s.name, s.chapter)); //basically a student[name] is a key for 2 elements of chapter and freq
                s.printData(multimap);

        }

        cout << endl;


} //main
