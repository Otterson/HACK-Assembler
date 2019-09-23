#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<algorithm>
#include "Table.h"

using namespace std;

int commandType(string line) {
	if (line[0] == '@') {
		return 65; //A
	}
	else if (line[0] == '(') {
		return 76; //L
	}
	else if (line[0] != ' ') {
		return 67; //C
	}
	return -1;
}

string decToBinary(int n)
{

	vector<int> binaryNum(16, 0);
	string to_return;

	int i = 0;
	while (n > 0) {
		binaryNum[i] = n % 2;
		n = n / 2;
		i++;
	}

	for (int j = 15; j >= 0; j--) {
		to_return = to_return + to_string(binaryNum[j]);
	}
	return to_return;
}

bool is_number(string s)
{
	s = s.substr(0, s.length()-1);	
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void SymbolTable::pass_one(string filename) {
	ifstream file;
	file.open(filename);
	string s;

	int line_number = 0;
	while (getline(file, s)) {

		if (s.at(0) == '@') {
			int index = s.find(" ");
			s = s.substr(1, index-1);
			if(s.length()>=3){ s.pop_back(); }
			
			cout << "S: "<<s<<endl<< "s.length(): " << s.length() << endl;
			
			if (!is_number(s)) {
				if (search_table(s) == false) {
					insert_Pair(s);
				}
			}
			line_number++;
		}
		else if (s.at(0) == '(') {
			s = s.substr(1, s.find(')')-1);
			cout << "S: " << s << endl<<"(s).length: "<<s.length()<<endl;
			if (search_table(s) == true) {
				set_address(s, to_string(line_number-1));
			}
			else {
				insert_Pair(s);
				set_address(s, to_string(line_number-1));
			}
			
		}
		else if (s.at(0) != '/' && s.empty() == false && s.at(0) != ' ') {
			line_number++;
		}

	}

}

void process(string line, SymbolTable& table) {
	string to_ret;
	vector<Pair> symbols;
	bool label = false;
	if (line.length() != 1) {
		//cout << line << endl;
		switch (commandType(line)) {
		case 65:
		{
			string a = "";
			a = line.substr(1, line.find(' '));
			a.pop_back();
			
			if (!is_number(a)) {
				if (table.search_table(a) == true) {
					//cout << "a: " << a << endl;
					a = table.get_address(a);
				}
				
			}
			int bin = stoi(a);
			string binary = decToBinary(bin);
			to_ret = binary;
			//cout << to_ret << endl;
			break;
		}
		case 76:
		{
			label = true;
		}
		case 67:
		{
			string dest;
			int store;
			bool jmp = false;

			for (int i = 0; i < line.length(); i++) { //check for jump
				if (line[i] == *";") {

					jmp = true;
					break;
				}
			}
			if (jmp == false) {
				for (int i = 0; i < line.length(); i++) { //find dest
					if (line[i] != '=') {
						dest = dest + line[i];
					}
					else {
						store = i + 1;
						break;
					}
				}
				//cout << "dest: " << dest << endl;
				dest = Dtable(dest);
			}
			else { dest = "000"; store = 0; }
			string comp = "";
			string jump_Op = "000";

			for (int j = store; j < line.length() - 1; j++) {
				if (line[j] != ' ' && line[j] != ';') {
					comp = comp + line[j];

				}
				else {
					store = j + 1;
					break;
				}
			}
			//cout << "comp: " << comp << endl;
			comp = Ctable(comp);

			jump_Op = "";
			for (int j = store; j < line.length() - 1; j++) {
				if (line[j] != ' ') {
					jump_Op = jump_Op + line[j];
				}
				else {
					break;
				}
			}
			jump_Op = Jtable(jump_Op);

			if (jmp == false) { jump_Op = "000"; }

			to_ret = "111" + comp + dest + jump_Op;
			if (label == false) {
				//cout << "OP code: " << to_ret << endl;
			}

			break;

		}
		}
	}
	//cout << endl;
	ofstream file;
	file.open("Prog.hack", std::ios_base::app);
	if (label == false) {
		file << to_ret << endl;
	}

}
bool SymbolTable::search_table(string s) {
	for (int i = 0; i < table.size(); i++) {
		if (table[i].op.c_str() == s) {
			return true;
		}
	}
	return false;
}
void SymbolTable::set_address(string key, string new_code) {
	for (int i = 0; i < table.size(); i++) {
		if (table[i].getOp() == key) {
			table[i].bin_code = new_code;
		}
	}
	return;
}
void SymbolTable::insert_Pair(string s) {
	table.push_back(Pair(s, to_string(table.size()-8)));
}
string SymbolTable::get_address(string s) {
	for (int i = 0; i < table.size(); i++) {
		if (table[i].op == s) {
			return table[i].bin_code;
		}
	}
	return "error";
}

void SymbolTable::print_table() {
	for (int i = 0; i < table.size(); i++) {
		cout << table[i].op << ", " << table[i].bin_code << endl;
	}
}

int main() {
	string filename = "PongL.asm";
	ifstream file;
	file.open(filename);
	string s;
	SymbolTable table = SymbolTable();
	cout << "Symbol Table: " << endl;
	table.print_table();
	table.pass_one(filename);
	cout << endl << "Symbol Table, Pass 1:" << endl;
	table.print_table();
	string to_proc;
	remove("Prog.hack");
	while (getline(file, to_proc)) {
		if (!to_proc.empty()) {
			if (to_proc[0] != '/') {
				process(to_proc, table);
			}
		}
		
	}
	return 0;
}


