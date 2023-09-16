//Abdul Aziz
// BCSF19A026

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;


int z = -1;
string inarr[100]{};
string curr_token{};
bool terminal(string s);
int get(string st);

int main()
{
	string ppt[30][21]{};
	ifstream fin;
	fin.open ("code.txt");
	if (fin)
	{
		int i = 0;
        while (fin && i < 100)
		fin>>inarr[i++];
		fin.close();
	}
	else
	{
		"File not found";
	}
	curr_token = inarr[++z];
	fin.open("table.txt");
	if (fin)
	{
		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 21; j++)
				fin >> ppt[i][j];
		fin.close();
	}
	else
	{
		cout << "File not found\n";
	}
	string newrule{};
	stack<string> s;
	s.push("$");
	s.push("Function");
	// curr_token=inarr[++index];
	while (!s.empty())
	{
		string top = s.top();
		s.pop();
		if (!terminal(top))
		{
			newrule = ppt[get(top)][get(curr_token)];
			if (newrule == "pop")
			{
				cout << "popped error\n";
				continue;
			}
			else if (newrule == "scan")
			{
				cout << "scanning error\n";
				s.push(top);
				curr_token = inarr[++z];
			}
			else if (newrule == "e")
				continue;
			else
			{
				cout <<"Mating\n";
				s.push(newrule);
			}
		}
	}

	return 0;
}
bool terminal(string s)
{
	if (s == "pop")
		return true;
	if (s == curr_token)
	{
		curr_token = inarr[++z];
		return true;
	}
	else
		return false;
}
int get(string st)
{
	

	if (st == "Function" || st == "id")
		return 0;
	else if (st == "ArgList" || st== ";")
		return 1;
	else if (st == "ArgList'" || st == "if")
		return 2;
	else if (st == "Arg" || st == "}")
		return 3;
	else if (st == "Stmt" || st == "int")
		return 4;
	else if (st == "Stmt'" || st == "float")
		return 5;
	else if (st == "Stmt\"" || st == "else")
		return 6;
	else if (st == "Decalartion" || st == "{")
		return 7;
	else if (st == "Type" || st == "<")
		return 8;
	else if (st == "WhileStmt" || st == ">")
		return 9;
	else if (st == "IfStmt" || st == "=")
		return 10;

	else if (st == "IfStmt'" || st == "number")
		return 11;
	else if (st == "ElsePart" || st == "*")
		return 12;
	else if (st == "CompoundStmt" || st == "/")
		return 13;
	else if (st == "CompoundStmt'" || st == "+")
		return 14;
	else if (st == "StmtList" || st == "-")
		return 15;
	else if (st == "StmtList\"" || st == "$")
		return 16;
	else if (st == "StmtList'''" || st == "(")
		return 17;
	else if (st == "BoolExpr" || st == ")")
		return 18;
	else if (st == "Compare" || st == ",")
		return 19;
	else if (st == "Compare'" || st == "while")
		return 20;
	else if (st == "Compare\"")
		return 21;
	else if (st == "Expr")
		return 22;
	else if (st == "Mag")
		return 23;
	else if (st == "Mag'")
		return 24;
	else if (st == "Mag\"")
		return 25;
	else if (st == "Term")
		return 27;
	else if (st == "Term'")
		return 28;
	else if (st == "Factor")
		return 29;
	else
	 return -1;
}