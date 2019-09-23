#pragma once
#include<string>
#include<vector>
#include<iostream>


using namespace std;


struct Pair {
	string op;
	string bin_code;
	Pair(string operation, string bin) {
		op = operation;
		bin_code = bin;
	}
	string get_code() {
		return bin_code;
	}
	string getOp() {
		return op;
	}
};

class SymbolTable {
public:
	vector<Pair> table;
	SymbolTable() {
		table.push_back(Pair("SP", "0"));
		table.push_back(Pair("LCL", "1"));
		table.push_back(Pair("ARG", "2"));
		table.push_back(Pair("THIS", "3"));
		table.push_back(Pair("THAT", "4"));
		table.push_back(Pair("SCREEN", "16384"));
		table.push_back(Pair("KBD", "24576"));
		for (int i = 0; i < 16; i++) {
			string strI = to_string(i);
			string newKey = "R" + strI;
			table.push_back(Pair(newKey, strI));
		}
	}
	void insert_Pair(string s);
	bool search_table(string s);
	string get_address(string s);
	void set_address(string op, string new_code);
	void pass_one(string filename);
	void print_table();
};



string Ctable(string toComp) {
	vector<Pair> ret;
	
	ret.push_back(Pair("0", "0101010"));
	ret.push_back(Pair("1", "0111111"));
	ret.push_back(Pair("-1", "0111010"));
	ret.push_back(Pair("D", "0001100"));
	ret.push_back(Pair("A", "0110000"));
	ret.push_back(Pair("!D", "0001101"));
	ret.push_back(Pair("!A", "0110001"));
	ret.push_back(Pair("-D", "0001111"));
	ret.push_back(Pair("-A", "0110011"));
	ret.push_back(Pair("D+1", "0011111"));
	ret.push_back(Pair("A+1", "0110111"));
	ret.push_back(Pair("D-1", "0001110"));
	ret.push_back(Pair("A-1", "0110010"));
	ret.push_back(Pair("D+A", "0000010"));
	ret.push_back(Pair("D-A", "0010011"));
	ret.push_back(Pair("A-D", "0000111"));
	ret.push_back(Pair("D&A", "0000000"));
	ret.push_back(Pair("D|A", "0010101"));
	ret.push_back(Pair("0", "1101010"));
	ret.push_back(Pair("1", "1111111"));
	ret.push_back(Pair("-1", "1111010"));
	ret.push_back(Pair("D", "1001100"));
	ret.push_back(Pair("M", "1110000"));
	ret.push_back(Pair("!D", "1001101"));
	ret.push_back(Pair("!M", "1110001"));
	ret.push_back(Pair("-D", "1001111"));
	ret.push_back(Pair("-M", "1110011"));
	ret.push_back(Pair("D+1", "1011111"));
	ret.push_back(Pair("M+1", "1110111"));
	ret.push_back(Pair("D-1", "1001110"));
	ret.push_back(Pair("M-1", "1110010"));
	ret.push_back(Pair("D+M", "1000010"));
	ret.push_back(Pair("D-M", "1010011"));
	ret.push_back(Pair("M-D", "1000111"));
	ret.push_back(Pair("D&M", "1000000"));
	ret.push_back(Pair("D|M", "1010101"));
	for (int i = 0; i < ret.size(); i++) {
		if (ret[i].getOp()==toComp) {
			return ret[i].get_code();
		}
	}
	
	return "value not found\n";
}
string Dtable(string tocomp) {
	vector<Pair> ret;
	ret.push_back(Pair("null", "000"));
	ret.push_back(Pair("M", "001"));
	ret.push_back(Pair("D", "010"));
	ret.push_back(Pair("MD", "011"));
	ret.push_back(Pair("A", "100"));
	ret.push_back(Pair("AM", "101"));
	ret.push_back(Pair("AD", "110"));
	ret.push_back(Pair("AMD", "111"));
	for (int i = 0; i < ret.size(); i++) {
		if (tocomp == ret[i].getOp()) {
			return ret[i].get_code();
		}
	}
	return "value not found\n";
}
string Jtable(string tocomp) {
	vector<Pair> ret;
	//cout << "jmp: "<<tocomp << endl;
	ret.push_back(Pair("null", "000"));
	ret.push_back(Pair("JGT", "001"));
	ret.push_back(Pair("JEQ", "010"));
	ret.push_back(Pair("JGE", "011"));
	ret.push_back(Pair("JLT", "100"));
	ret.push_back(Pair("JNE", "101"));
	ret.push_back(Pair("JLE", "110"));
	ret.push_back(Pair("JMP", "111"));
	for (int i = 0; i < ret.size(); i++) {
		if (tocomp == ret[i].getOp()) {
			return ret[i].get_code();
		}
	}
	return "value not found\n";
}


