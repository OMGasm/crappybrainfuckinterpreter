#include <iostream>
#include <stack>
using namespace std;
unsigned char c[30000] = {0};
stack<unsigned long long> loops;
unsigned long long cp = 0;
unsigned short p = 0;
void left(){p > 0 ? p-- : 0;}
void right(){p < 30000 ? p++ : 0;}
void add(){c[p]++;}
void sub(){c[p]--;}
void in(){cin >> c[p];}
void out(){cout << c[p];}
void loop(){loops.push(cp);}
void endloop(){c[p] > 0 ? cp = loops.top() : loops.pop();}

void main(int argc, char** argv)
{
	void* x[94];
}