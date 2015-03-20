#include <iostream>
#include <stack>
#include <string>
using namespace std;

string code = "";
unsigned int codepointer = 0; //position in code
unsigned char cell[30000] = {0}; //all the cells set to 0
unsigned short pointer = 0; //current cell
stack<unsigned int> loops; //store positions of loop starting points
stack<unsigned int> unloop; //don't loop through these

void mleft() //move one cell to the left, or do nothing if first one, left() apparently exists already
{
	if(pointer > 0)
	{
		pointer--;
	}
	else
	{
		pointer = 29999;
	}
}
void mright() //move one cell to the right, or do nothing if the last one, right() apparently exists already
{
	if(pointer < 29999)
	{
		pointer++;
	}
	else
	{
		pointer=0;
	}
}
void add() //add one to current cell
{
	cell[pointer]++;
}
void sub() //subtract one from current cell
{
	cell[pointer]--;
}
void in() //push standard input into current cell, will probably break somehow :D
{
	cin >> cell[pointer];
}
void out() //output current cell
{
	cout << cell[pointer];
}
void loop() //woo! stack based state loops!
{
	if(cell[pointer])
	{
		loops.push(codepointer);
	}
	else
	{
		unloop.push(code[codepointer]);
		while(unloop.size())
		{
			codepointer++;
			switch(code[codepointer])
			{
			case '[':
				{
					unloop.push(code[codepointer]);
					break;
				}
			case ']':
				{
					unloop.pop();
					break;
				}
			}
		}
	}
}
void endloop() //loop if current cell is not 0
{
	if(cell[pointer])
	{
		codepointer = loops.top()-1;
	}
	loops.pop();
}
void o(){} //do nothing, to handle characters outside brainfuck range

void main(int argc, char** argv)
{
	if(argc>1) code = argv[1]; //command line code input

	typedef void (*fptr)(); //because you can't normally make an array of function pointers :(
	fptr funcs[256];
	for(int i=0;i<256;i++) funcs[i]=o; //init all to empty function

	funcs['+'] = add;		funcs['-'] = sub; //assign functions to characters
	funcs['['] = loop;		funcs[']'] = endloop;
	funcs['<'] = mleft;		funcs['>'] = mright;
	funcs[','] = in;		funcs['.'] = out;

	while(codepointer < code.size()) //do until end of string
	{
		funcs[code[codepointer]](); //execute function for current character
		codepointer++; //move to next character
	}
}