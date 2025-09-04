//
// Created by tysser on 5/27/25.
//
#include <iostream>
#include <fstream>
using namespace std;

int sum (int a, int a1 = 2, int a2, int a3, int a4)
{
  return a + a1 + a2 + a3 + a4;
}
int main()
{
  // constexpr int c = 5;
  // int s = 1, b = c;
  // for (int j = 1; j <= c; j++)
  // {
  //   for (int i = 1; i <= c; i++)
  //   {
  //     if (i != s && i != b) cout << 1 << "  ";
  //     else cout << " " << "  ";
  //   }
  //   cout << endl;
  //   s++;
  //   b--;
  // }



  cout << sum (9, 8,7,6);

}
