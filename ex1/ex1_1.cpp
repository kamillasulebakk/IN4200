#include <iostream>

int main(int argc, char const *argv[]) {
  using namespace std;
  float sum = 0;
  for (int i=0; i<1000; i+=2)
    sum = sum + 1/pow(2,i);
  cout << sum << endl;  
  return 0;
}
