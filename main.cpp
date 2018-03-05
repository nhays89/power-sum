/*
Author: Nicholas Hays
Date: 3/5/2018
Program: HackerRank - Recursion - The Power Sum
*/

#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<unordered_map>

unsigned int tot;
std::unordered_map<int, int> map;

/*
builds arr by expanding each unique nth power up to x.
i.e
x = 50
n = 2

arr[0] = 2  = 2^1
arr[1] = 4  = 2^2
arr[2] = 8  = 2^3
arr[3] = 16 = 2^4
arr[4] = 32 = 2^5

*/
void build_arr(int n, int x, std::vector<int> &arr) {
  int max_exp = pow(x, 1. / n);
  for (int i = 1; i <= max_exp; i++) { 
    int res = (int)pow(i, n);
     arr.push_back(res);
  }
}


/*

Generates a map.
key = x
value = index in arr.

Provides quick access to determine the index in arr for a given
x value.

@arr - the array of unique sums.
*/

void gen_map(int x, std::vector<int> &arr) {
  int i = 0;
  while (i < arr.size()) {
    while (x >= arr[i]) {
      map[x--] = i;
    }
    i++;
  }
  while (x >= 0) {
    map[x--] = INT32_MAX;
  }
}

/*

Req: Implement using recursion. 
Iterates through the arr to find all possible combinations of numbers in the arr that sum to x.

i.e
caller -> find(0, 10, [9, 4, 1]);

i = 0, x = 10  sum = ""
i = 1, x = 1   sum = "9"
i = 2, x = 0   sum = "9 + 1"

@i - current index
@x - current x value.
@arr - container for all unique sums (desc order)
&stk - builds the current combination of numbers 
*/
void find(int i, int x, std::vector<int> &arr) {
 
  if (x < 0) return;
  if (x == 0) {
    tot++;
  }
  else {
    int r, t;
    while (i < arr.size()) {
      r = x - arr[i];
      t = map[r] > i + 1 ? map[r] : i + 1;
      find(t, r, arr);
      i++;
    }
  }
}

/*
Entry point to program.
*/
int main() {
  int x, n;
  std::vector<int> arr;
  std::cin >> x;
  std::cin >> n;
  build_arr(n, x, arr);
  std::reverse(arr.begin(), arr.end());
  gen_map(x, arr);
  find(0, x, arr);
  std::cout << tot << std::endl;
}
