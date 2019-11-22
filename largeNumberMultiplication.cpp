// Copyright Regan Willis 2019
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

vector <int> PadLeft(vector <int> bigger, vector <int> smaller) {
  size_t pad = 0;
  pad = bigger.size() - smaller.size();
  for (size_t i = 0; i < pad; ++i)
    smaller.insert(smaller.begin(), 0);
  return smaller;
}

vector <int> RemoveZeros(vector <int> vec) {
  string zeros, z;
  // if the vector is only zeros, return 1 zero
  if (equal(vec.begin() + 1, vec.end(), vec.begin()) && vec.at(0) == 0) {
    vec.clear();
    vec.push_back(0);
    return vec;
  }
  else {
    // remove leading zeros
    for (size_t i = 0; i < vec.size(); ++i)
      zeros += to_string(vec.at(i));
    zeros.erase(0, zeros.find_first_not_of('0'));
    vec.clear();
    for (size_t i = 0; i < zeros.size(); ++i)
      vec.push_back(stoi(z = zeros[i]));
    return vec;
  }
}

vector<int> Swap(vector<int> vec) {
  vector<int> ret;
  int index;
  for (size_t i = 0; i < vec.size(); ++i) {
    index = vec.size()-1-i;
    ret.push_back(vec.at(index));
  }
  return ret;
}

vector<int> Add(vector<int> vec1, vector<int> vec2) {
  vector<int> sum;
  vector<int> carry;
  int initialSum, temp;
  string helper, h2, h3;
  // pad with leading zeros
  if (vec1.size() > vec2.size())
    vec2 = PadLeft(vec1, vec2);
  else if (vec2.size() > vec1.size())
    vec1 = PadLeft(vec2, vec1);
  vec1 = Swap(vec1);
  vec2 = Swap(vec2);
  for (size_t i = 0; i < vec1.size(); ++i) {
    initialSum = vec1.at(i)+vec2.at(i);
    if (i > 0)
      initialSum = initialSum + carry.at(i-1);
    // if the sum is a two digit number we need to carry
    temp = 0;
    if (initialSum > 9) {
      helper = to_string(initialSum);
      temp = stoi(h2 = helper[0]);
      initialSum = stoi(h3 = helper[1]);
    }
    // add initial sum to sum vector
    sum.push_back(initialSum);
    carry.push_back(temp);
  }
  sum.push_back(temp);
  sum = Swap(sum);
  return sum;
}

vector <int> Subtract(vector<int> vec1, vector<int> vec2) {
  vector<int> difference;
  vec1 = RemoveZeros(vec1);
  vec2 = RemoveZeros(vec2);
  // if both vectors are zero we need to return zero
  if ((vec1.size() == 1) && (vec2.size() == 1) && (vec1.at(0) == 0) && (vec2.at(0) == 0))
    return vec1;
  // switch numbers so biggest is on top
  if (vec1.size() < vec2.size() || (vec1.size() == vec2.size() && (vec1.at(0) < vec2.at(0)))) {
    vector <int> temp;
    for (size_t i = 0; i < vec1.size(); ++i)
      temp.push_back(vec1.at(i));
    vec1.clear();
    for (size_t i = 0; i < vec2.size(); ++i)
      vec1.push_back(vec2.at(i));
    vec2.clear();
    for (size_t i = 0; i < temp.size(); ++i)
      vec2.push_back(temp.at(i));
  }
  // pad with leading zeros
  if (vec1.size() > vec2.size())
    vec2 = PadLeft(vec1, vec2);
  else if (vec2.size() > vec1.size())
    vec1 = PadLeft(vec2, vec1);
  vec1 = Swap(vec1);
  vec2 = Swap(vec2);
  // subtract vec2 from vec1
  for (size_t i = 0; i < vec1.size(); ++i) {
    // sometimes we need to borrow
    if (vec1.at(i) < vec2.at(i)) {
      vec1.at(i+1) = vec1.at(i+1) -1;
      vec1.at(i) = vec1.at(i) + 10;
    }
    difference.push_back(vec1.at(i)-vec2.at(i));
  }
  difference = Swap(difference);
  return difference;
}


// brute force pen and paper algorithm
vector<int> PenAndPaper(vector<int> nOne, vector<int> nTwo) {
  vector <int> solution, carry, ret;
  vector<vector<int>> sum;
  int prod, temp;
  string helper, h2, h3;
  nOne = Swap(nOne);
  nTwo = Swap(nTwo);
  for (size_t i = 0; i < nTwo.size(); ++i) {
    for (size_t j = 0; j < nOne.size(); ++j) {
      // multiply and add the carry
      if (nOne.at(j) == 0 && nTwo.at(i) == 0)
        prod = 0;
      else
        prod = nOne.at(j)*nTwo.at(i);
      if (j > 0)
        prod = prod + carry.at(j-1);
      // if the product is a two digit number we need to carry
      temp = 0;
      if (prod > 9) {
        helper = to_string(prod);
        temp = stoi(h2 = helper[0]);
        prod = stoi(h3 = helper[1]);
      }
      // add solution to vector of solutions
      solution.push_back(prod);
      carry.push_back(temp);
    }
    solution.push_back(temp);
    solution = Swap(solution);
    // pad right with zeros
    for (size_t k = 0; k < i; ++k)
      solution.push_back(0);
    // add solutions to sum
    sum.push_back(solution);
    // clear solution and carry vectors
    solution.clear();
    carry.clear();
  }
  // add all the solutions together
  for (size_t i = 1; i < sum.size(); ++i) {
      sum.at(0) = (Add(sum.at(0), sum.at(i)));
  }
  for (size_t i = 0; i < sum.at(0).size(); ++i)
    ret.push_back(sum.at(0).at(i));
  return ret;
}

// karatsuba algorithm
vector <int> Karatsuba(vector<int> a, vector<int> b) {
  // base case
  if (a.size() <= 5 && b.size() <= 5)
    return PenAndPaper(a, b);
  else {
    size_t m = floor(max(a.size(), b.size())/2);
    // pad with zeros
    if (a.size() > b.size())
      b = PadLeft(a, b);
    else if (b.size() > a.size())
      a = PadLeft(b, a);
    // split vectors on m
    vector <int> a0, a1, b0, b1, c0, c1, c2, c1recur;
    for (size_t i = 0; i < a.size(); ++i) {
      if (a.size() % 2 != 0) {
        if (i > m)
          a0.push_back(a.at(i));
        else
          a1.push_back(a.at(i));
      }
      else {
        if (i >= m)
          a0.push_back(a.at(i));
        else
          a1.push_back(a.at(i));
      }
      
    }
    for (size_t i = 0; i < b.size(); ++i) {
      if (a.size() % 2 != 0) {
        if (i > m)
          b0.push_back(b.at(i));
        else
          b1.push_back(b.at(i));
      }
      else {
        if (i >= m)
          b0.push_back(b.at(i));
        else
          b1.push_back(b.at(i));
      }
    }
    // recursive calls with split vectors
    c2 = Karatsuba(a1, b1);
    c0 = Karatsuba(a0, b0);
    c1recur = Karatsuba(Add(a1, a0), Add(b1, b0));
    c1 = Subtract(c1recur, Add(c2, c0));
    // add 10^2m and 10^m for the return
    for (size_t i = 0; i < 2*m; ++i)
      c2.push_back(0);
    for (size_t i = 0; i < m; ++i)
      c1.push_back(0);
    // add c2, c1, c0 and return
    return Add(Add(c2, c1), c0);
  }
}

int main() {
  string input, tmp;
  vector<string> vecInput;
  size_t vecOneSize = 0;
  vector<int> nOne;
  vector<int> nTwo;
  // get user input
  cin >> input;
  for (size_t i = 0; i < input.length(); ++i) {
    tmp = input[i];
    vecInput.push_back(tmp);
  }
  // deliminate input
  for (size_t i = 0; i < vecInput.size(); ++i) {
    if (vecInput.at(i) == "*")
      break;
    ++vecOneSize;
  }
  size_t vecTwoSize = vecInput.size() - vecOneSize - 1;
  // populate vectors with input
  for (size_t i = 0; i < vecOneSize; ++i)
    nOne.push_back(stoi(vecInput.at(i)));
  for (size_t i = 0; i < vecTwoSize; ++i)
    nTwo.push_back(stoi(vecInput.at(i+vecOneSize+1)));
  // pen and paper algorithm
  vector<int> B = PenAndPaper(nOne, nTwo);
  B = RemoveZeros(B);
  cout << "B: ";
  for (size_t i = 0; i < B.size(); ++i)
    cout << B.at(i);
  cout << endl;
  // karatsuba algorithm
  vector <int> K = Karatsuba(nOne, nTwo);
  K = RemoveZeros(K);
  cout << "K: ";
  for (size_t i = 0; i < K.size(); ++i)
    cout << K.at(i);
  cout << endl;

  return 0;
}
