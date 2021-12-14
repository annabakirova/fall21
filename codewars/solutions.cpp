#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

std::string DNAStrand(const std::string& dna)
{
  std::string result = "";
  for (unsigned int i = 0; i < dna.size(); ++i) {
    switch (dna.at(i)) {
        case 'T': result.push_back('A'); break;
        case 'A': result.push_back('T'); break;
        case 'C': result.push_back('G'); break;
        case 'G': result.push_back('C'); break;
    }
  }
  return result;
}

std::string no_space(std::string x)
{
    while(x.find(' ') != std::string::npos) {
      x.erase(x.find(' '), 1);
    }
  return x;
}

bool isAscOrder(std::vector<int> arr)
{
  for (int i = 1; i < arr.size(); ++i) {
    if (arr.at(i) <= arr.at(i - 1)) { return false; }
  }
  return true;
}

bool is_isogram(std::string str) {
  bool occurences[26];
  for (int i = 0; i < 26; ++i) {
    occurences[i] = false;
  }
  int letter;
  for (unsigned int i = 0; i < str.size(); ++i) {
    letter = static_cast<int>(str.at(i));
    letter = (letter >= 97) ? (letter - 97) : (letter - 65);
    if (occurences[letter]) {
      return false;
    }
    occurences[letter] = true;
  }
  return true;
}

std::string bool_to_word(bool value)
{
  if (value) {return "Yes"; }
  return "No";
}

bool XO(const std::string& str)
{
  int count = 0;
  for (unsigned long i = 0; i < str.size(); ++i) {
    if (str.at(i) == 'x' || str.at(i) == 'X') { count++; }
    else if (str.at(i) == 'o' || str.at(i) == 'O') { count--; }
  }
  return count == 0;
}

static long findMissing(std::vector<long> list){
  long diff = 0;
  if (list.at(1) - list.at(0) > list.at(2) - list.at(1)) {
    diff = list.at(2) - list.at(1);
    return (list.at(0) + diff);
  } else {
    diff = list.at(1) - list.at(0);
  }
  
  long sum = 0L;
  for (unsigned int i = 0; i < list.size(); ++i) {
    sum += list.at(0) + static_cast<long>(i) * diff;
    sum -= list.at(i);
  }
  return list.at(list.size() - 1) + sum;
}

unsigned int countBits(unsigned long long n){
  int count = 0;
  while (n > 0) {
    if (n & 1 == 1) { count++; }
    n >>= 1;
  }
  return count;
}

bool is_square(int n)
{
  if (n < 0) { return false; }
  int i = 0;
  for (i = 0; i * i < n; ++i) {
    ;
  }
  return (n - i * i == 0);
}

bool narcissistic( int value ){
  int digits = 0;
  int copy = value;
  while (copy > 0) {
    copy /= 10;
    digits++;
  }
  copy = value;
  int sum = 0;
  for (int i = 0; i < digits; ++i) {
    sum += pow(copy % 10, digits);
    copy /= 10;
  }
  return sum == value;
}

#include <vector>

long sumTwoSmallestNumbers(std::vector<int> numbers)
{
  long min1 = 9223372036854775807; //min1 < min2
  long min2 = 9223372036854775807;
  for (unsigned long i = 0; i < numbers.size(); ++i) {
    if (numbers.at(i) < min2) {
      min2 = numbers.at(i);
    }
    if (min2 < min1) {
      long t = min2;
      min2 = min1;
      min1 = t;
    }
  }
    return min1 + min2;
}

std::vector<int> tribonacci(std::vector<int> signature, int n)
{
  std::vector<int> result;
  int max = n >= 3 ? 3 : n;
  for (int i = 0; i < max; ++i) {
    result.push_back(signature.at(i));
  }
  for (int i = 3; i < n; ++i) {
    result.push_back(result.at(i - 1) + result.at(i - 2) + result.at(i - 3));
  }
  return result;
}

std::string get_middle(std::string input) 
{
  if (input.size() % 2 == 0) {
    return input.substr(input.size() / 2 - 1, 2);
  } else {
    return input.substr(input.size() / 2, 1);
  }
}

int twice_as_old(int dad, int son) {
  return abs(dad - (son << 1));
}

int opposite(int number) 
{
  return -number;
}

std::string even_or_odd(int number) 
{
  return (number % 2 == 0) ? "Even" : "Odd";
}

int summation(int num){
 return (num + 1) * num / 2;
}

int centuryFromYear(int year) 
{
  int remainder = (year % 100 == 0) ? 0 : 1;
  return year / 100 + remainder;
}

int basicOp(char op, int val1, int val2) {
  switch (op) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
  }
}