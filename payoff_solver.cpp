#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

struct Job {
    int start, finish, profit;
};

// A utility function that is used for sorting events
// according to finish time
bool myfunction(Job s1, Job s2) {
    return (s1.finish < s2.finish);
}

int binarySearch(Job jobs[], int index )  //, vector<Job> &sol_vec)
{
    // Initialize 'lo' and 'hi' for Binary Search
    int lo = 0, hi = index - 1;

    // Perform binary Search iteratively
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        if (jobs[mid].finish <= jobs[index].start)
        {
            if (jobs[mid + 1].finish <= jobs[index].start)
                lo = mid + 1;
            else {
                //cout << jobs[mid].start << " " << jobs[mid].finish << jobs[mid].profit <<endl;
                //sol_vec.push_back(jobs[mid]);
                return mid;
            }
        }
        else
            hi = mid - 1;
    }

    return -1; //change to -INF
}

// The main function that returns the maximum possible
// profit from given array of jobs
int findMaxProfit(Job arr[], int n)
{

    vector<Job> sol_vec;

    sort(arr, arr+n, myfunction);

    int *table = new int[n];
    table[0] = arr[0].profit;

    for (int i=1; i<n; i++) {


        // Find profit including the current job
        int inclProf = arr[i].profit;


        vector<Job> prev_sol(sol_vec);
        sol_vec.clear();

        sol_vec.push_back(arr[i]);

        int l = binarySearch(arr, i  );   //, sol_vec);
        if (l != -1) {
            inclProf += table[l];
            sol_vec.push_back(arr[l]);



        }
        if (inclProf > table[i-1]) {

        } else{
          sol_vec = prev_sol;

        }

        // Store maximum of including and excluding
        table[i] = max(inclProf, table[i-1]);


    }

    for(int i = 0; i < sol_vec.size(); i++)
      cout << sol_vec[i].start << " "<< sol_vec[i].finish << " " << sol_vec[i].profit <<endl;

    // Store result and free dynamic memory allocated for table[]
    int result = table[n-1];

    // cout << "sol_vec is: " <<endl;
    // for (int i = 0; i < sol_vec.size(); i++) {
    //   cout << sol_vec[i].start;
    // }


    delete[] table;

    return result;
}

// Driver program
int main()
{
    Job arr[] = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
    int n = sizeof(arr)/sizeof(arr[0]);


    cout << "Optimal profit is " << findMaxProfit(arr, n)<<endl;
    return 0;




}
