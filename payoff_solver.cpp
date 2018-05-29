#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

//***********
//Structs
struct Interval {
    int start, end, pay;
};

struct comparator{
    inline bool operator() (const Interval& inter1, const Interval& inter2) {
        return (inter1.end < inter2.end);
    }
};

//************
//Methods
int binarySearch(vector<Interval> Intervals, int index);

//**********
//MAIN
int main(int argc, char* argv[]) {

    vector<Interval> intervals;
    string temp;
    int max_pay = 0;

  //O(n)
  for(string line; getline(cin, line) && line.compare("");) {
      stringstream ss(line);
      ss >> temp;
      int start = stoi(temp);
      ss >> temp;
      int end = stoi(temp);
      ss >> temp;
      int pay = stoi(temp);

      Interval inter;
      inter.start = start;
      inter.end = end;
      inter.pay = pay;

      intervals.push_back(inter);
  }

  //O(nlogn)
   sort(intervals.begin(), intervals.end(), comparator());

   int n = intervals.size();

   int *table = new int[n];
   int *back = new int[n];
   table[0] = intervals[0].pay;
   back[0] = -1;


   //O(nlogn)
   for (int i=1; i<n; i++) {
       int inclProf = intervals[i].pay;
       //O(logn)
       int l = binarySearch(intervals, i);
       if (l != -1) {
           inclProf += table[l];

       }

       if (inclProf > table[i-1]) {
         table[i] = inclProf;
         back[i] = l;

       } else {
         table[i] = table[i-1];
         back[i] = -2;
       }
   }

   //worst case: O(n)
   vector<int> sol_vec;
   for(int i = n-1; i >= 0; i--) {
     if (back[i] == -2) {
       continue;
     }
     else {
       sol_vec.push_back(i);
       if (back[i] == -1) {

         break;

       }
       i = back[i];
       i++;
     }
   }

   cout << "Max Payoff: " << table[n-1] <<endl;

   //worst case O(nlogn)
   sort(sol_vec.begin(), sol_vec.end());

   //O(n)
   for(int i = 0; i < sol_vec.size(); i++) {
       cout << intervals[sol_vec[i]].start << " " << intervals[sol_vec[i]].end << " " << intervals[sol_vec[i]].pay <<endl;
   }



   delete[] table;
   delete[] back;

   return 0;
}

int binarySearch(vector<Interval> Intervals, int index) {
    int lo = 0, hi = index - 1;

    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if (Intervals[mid].end <= Intervals[index].start)
        {
            if (Intervals[mid + 1].end <= Intervals[index].start)
                lo = mid + 1;
            else {

                return mid;
            }
        }
        else
            hi = mid - 1;
    }

    return -1; //change to -INF
}
