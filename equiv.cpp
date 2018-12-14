// CSCI 2530
// Assignment: 4
// Author:     Shelby Brown
// File:       equiv.cpp
// Tab stops:  ***

/* This assignment is to create a tool that manages an equivalence relation that can be changed in a specific way by the program while the program runs. The assignment will involve two files, equiv.h and equiv.cpp. For this assignment, the equivalence relation is always over a set of integers {1, 2, 3, …, n} for some positive integer n.
Step 	                     Result
ER R = newER(7) 	     R = {1} {2} {3} {4} {5} {6} {7}
merge(R, 1, 5) 	             R = {1, 5} {2} {3} {4} {6} {7}
merge(R, 2, 7) 	             R = {1, 5} {2, 7} {3} {4} {6}
equivalent(R, 1, 5) 	     yields true
equivalent(R, 1, 7) 	     yields false
merge(R, 5, 7) 	             R = {1, 2, 5, 7} {3} {4} {6}
equivalent(R, 2, 5) 	     yields true
equivalent(R, 2, 3)yields false 	yields false
merge(R, 2, 3) 	             R = {1, 2, 3, 5, 7} {4} {6}
equivalent(R, 3, 7) 	     yields true
equivalent(R, 4, 7) 	     yields false
merge(R, 4, 6)     	     R = {1, 2, 3, 5, 7} {4, 6}
merge(R, 2, 3)  	     R = {1, 2, 3, 5, 7} {4, 6} 
*/

#include <cstdio>
#include "equiv.h"
using namespace std;

//newER(n) returns an array of n+1 integers. Allocate the array in the heap. This array will be used to store the bosses. If R has type ER then R[x] is x's boss.

ER newER(int n)
{
  int*A = new int [n + 1];
  
  for(int i = 1; i <= n; i++)
  {
    A[i] = 0;
  }

  return A;
}

//showER(R, n) prints the entire contents of array R (of size n) in a readable form for debugging. Be sure that showER shows both k and k's boss, for each k. 

void showER(const ER R, const int n)
{
  printf("i\ti's boss\n");
  for(int i = 1; i <= n; i++)
  {
    printf("%i\t%i\n", i, R[i]);
  }
}

//leader(R, x) returns the leader of x in equivalence relation R. To compute x's leader, just follow the bosses up to the leader.
 
int leader (ER R, int x)
{
  int r = x;
  while(R[r] != 0)
  {
    r = R[r];
  }
return r;
	
	
}

//merge(R, x, y) merges the equivalence classes of x and y in R as follows. First, it finds the leaders x′ and y′ of x and y.

void merge(ER R, const int x, const int y)
{
  int LeaderOne = leader(R, x);
  int LeaderTwo = leader(R, y);
  if (LeaderOne != LeaderTwo)
  {
    R[LeaderOne] = LeaderTwo;
  }
}

//equivalent(R, x, y) returns true if x and y are currently in the same equivalence class in equivalence relation R. They are in the same equivalence class if they have the same leader.

bool equivalent(ER R, const int x, const int y)
{
  return leader(R, x) == leader(R, y);
}

//destroyER(R) deallocates R.

void destroyER(ER R)
{
  delete [] R;
}
