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
int binarySearch(vector<Interval> &Intervals, int index);

//**********
//Main
int main(int argc, char* argv[]) {
  vector<int> payoffs;
  vector<int> prev_vec;
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

   payoffs.push_back(intervals[0].pay);
   prev_vec.push_back(-1);

   //O(nlogn)
   int ind;
   for (int i = 1; i< intervals.size(); i++) {
       int curr_prof = intervals[i].pay;
       //O(logn)
       ind = binarySearch(intervals, i);
       if (ind!= -1) {
           curr_prof += payoffs[ind];
       }

       if (curr_prof > payoffs[i-1]) {
         payoffs.push_back(curr_prof);
         prev_vec.push_back(ind);

       } else {
         payoffs.push_back(payoffs[i-1]);
         prev_vec.push_back(-1000);

       }
   }

   //worst case: O(n)
   vector<int> sol_vec;
   for(int i = intervals.size() - 1; i >= 0; i--) {

     if (prev_vec[i] == -1000) {
       continue;
     }
     else {
       sol_vec.push_back(i);
       if (prev_vec[i] == -1) {
         break;

       }
       i = prev_vec[i];
       i++;
     }
   }

   cout << "Max Payoff: " << payoffs[intervals.size() - 1] <<endl;

   //worst case O(nlogn)
   sort(sol_vec.begin(), sol_vec.end());

   //O(n)
   for(int i = 0; i < sol_vec.size(); i++) {
       cout << intervals[sol_vec[i]].start << " " << intervals[sol_vec[i]].end << " " << intervals[sol_vec[i]].pay <<endl;
   }

   return 0;
}

int binarySearch(vector<Interval> &Intervals, int index) {
    int right = 0;
    int left = index - 1;

    while (right <= left) {
        int middle = (right+left)/2;
        if (Intervals[middle].end <= Intervals[index].start) {
            if (Intervals[middle + 1].end <= Intervals[index].start)
                right = middle + 1;
            else {
                return middle;
            }
        }
        else {
            left =middle-1;
        }
    }
    return -1; //change to -INF
}
