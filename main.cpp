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
	fptr funcs[94] = {o,o,o,o,o,o,o,o,o,o, //0-9
				   o,o,o,o,o,o,o,o,o,o, //10-19
				   o,o,o,o,o,o,o,o,o,o, //20-29
				   o,o,o,o,o,o,o,o,o,o, //30-39
				   o,o,o, add, in, sub, out,o,o,o, //40-49, add:'+'(43), in:','(44), sub:'-'(45), out:'.'(46)
				   o,o,o,o,o,o,o,o,o,o, //50-59
				   mleft,o, mright,o,o,o,o,o,o,o, //60-69, left:'<'(60), right:'>'(62)
				   o,o,o,o,o,o,o,o,o,o, //70-79
				   o,o,o,o,o,o,o,o,o,o, //80-89
				   o,loop,o,endloop}; //90-93 loop:'['(91), endloop:']'(93), bloody messy
	while(codepointer < code.size()) //do until end of string
	{
		funcs[code[codepointer]](); //execute function for current character
		codepointer++; //move to next character
	}
}