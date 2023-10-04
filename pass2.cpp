#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <cmath>
#include <cctype>
#define LOC_BEGIN 2
#define LOC_LEN 4
#define OP_BEGIN 16
#define OP_LEN 8
#define OPER_BEGIN 24
using namespace std;

// OPTABLE
map<string, string> OPTAB = {
  {"ADD", "18"},
  {"AND", "40"},
  {"COMP", "28"},
  {"DIV", "24"},
  {"J", "3C"},
  {"JEQ", "30"},
  {"JGT", "34"},
  {"JLT", "38"},
  {"JSUB", "48"},
  {"LDA", "00"},
  {"LDCH", "50"},
  {"LDL", "08"},
  {"LDX", "04"},
  {"MUL", "20"},
  {"OR", "44"},
  {"RD", "D8"},
  {"RSUB", "4C"},
  {"STA", "0C"},
  {"STB", "78"},
  {"STCH", "54"},
  {"STL", "14"},
  {"STSW", "E8"},
  {"STX", "10"},
  {"SUB", "1C"},
  {"TD", "E0"},
  {"TIX", "2C"},
  {"WD", "DC"}
};


string get_loc(string str);

string get_op(string str);

string get_oper(string str);

string Dec2Hex(int dec);

int Hex2Dec(string hex);

int main()
{
  // load SYMTAB
  ifstream SYM;
  SYM.open("SYMTAB");

  // store SYMTAB into vector
  vector<string> SYMTEMP;
  string line;
  while(getline(SYM, line)) {
    SYMTEMP.push_back(line);
  }
  SYM.close();

  // turn vector to map(SYMTABLE)
  map<string, string> SYMTAB;
  string sep = " ";
  for(int i = 1; i < SYMTEMP.size(); i++) {
    int end = SYMTEMP[i].find(sep);
    int begin = 0;
    string op;
    string value;
    while(end != string::npos) {
      if(end - begin != 0) {
	op = SYMTEMP[i].substr(begin, end - begin);
      }
      begin = end + sep.size();
      end = SYMTEMP[i].find(sep, begin);
    }
    if(begin != SYMTEMP[i].length())
    value = SYMTEMP[i].substr(begin, end - begin);
    SYMTAB[op] = value;
  }

  // print first line
  SYMTEMP[0].erase(13, 1);
  SYMTEMP[0].erase(6, 1);
  cout << "H" << SYMTEMP[0] << endl;

  // load INTFILE
  ifstream OP;
  OP.open("INTFILE");

  // store INTFILE into vector
  vector<string> OPTEMP;
  while(getline(OP, line)) {
    OPTEMP.push_back(line);
  }

  string text = "T";
  string loc = get_loc(OPTEMP[0]);
  while(loc.size() < 6)
    loc.insert(0, "0");
  text += loc;
  int length = 0;
  int base = Hex2Dec(get_loc(OPTEMP[0]));
  bool directive = false;

  for(int i = 1; i < OPTEMP.size(); i++) {
    string loc = get_loc(OPTEMP[i]);
    string op = get_op(OPTEMP[i]);

    if(directive) {
      base = Hex2Dec(loc);
      text = "T";
      while(loc.size() < 6)
        loc.insert(0, "0");
      text += loc;
      directive = false;
    }

    length = Hex2Dec(loc) - base;

    if(length >= 28) {
      string len = Dec2Hex(length);
      text.insert(7, len);

      cout << text << endl;
      base = Hex2Dec(loc);
      text = "T";
      while(loc.size() < 6)
        loc.insert(0, "0");
      text += loc;
    }

    if(op.compare("END") == 0) {
      if(text.length() > 7) {
	string len = Dec2Hex(length);
	if(len.length() < 2)
          len.insert(0, "0");
	text.insert(7, len);
	cout << text << endl;
      }
    }
    else if(op.compare("RESW") == 0 || op.compare("RESB") == 0) {
      if(text.length() > 7) {
	string len = Dec2Hex(length);
	if(len.length() < 2)
	  len.insert(0, "0");
	text.insert(7, len);
	cout << text << endl;
      }
      directive = true;
    }
    else if(op.compare("RSUB") == 0) {
      text += "4C0000";
    }
    else if(op.compare("BYTE") == 0) {
      string temp = get_oper(OPTEMP[i]);
      if(temp[0] == 'C') {
	temp = temp.substr(temp.find("'") + 1);
	temp.erase(temp.size() - 1);
	for(int i = 0; i < temp.size(); i++) {
          text += Dec2Hex(int(temp[i]));
	}
      }
      else if(temp[0] == 'X') {
	temp = temp.substr(temp.find("'") + 1);
	temp.erase(temp.size() - 1);
	text += temp;
      }
    }
    else if(op.compare("WORD") == 0) {
      string temp = get_oper(OPTEMP[i]);
      int value = stoi(temp);
      temp = Dec2Hex(value);
      while(temp.size() < 6)
	temp.insert(0, "0");
      text += temp;
    }
    else {
      text += OPTAB[op];
      string temp = get_oper(OPTEMP[i]);
      if(temp.find(",X") != string::npos) {
	temp = temp.substr(0, temp.find(",X"));
	temp = SYMTAB[temp];
        int location = Hex2Dec(temp);
	location += 4096 * 8;
	temp = Dec2Hex(location);
      }
      else {
	temp = SYMTAB[temp];
	temp = temp.substr(2, 4);
      }
      text += temp;
    } 
  }

  cout << "E" << SYMTEMP[0].substr(6, 6) << endl;
  

  return 0;
}


string get_loc(string str)
{
  str = str.substr(LOC_BEGIN, LOC_LEN);
  return str;
}

string get_op(string str)
{
  str = str.substr(OP_BEGIN, OP_LEN);
  str = str.substr(0, str.find(' '));
  return str;
}

string get_oper(string str)
{
  str = str.substr(OPER_BEGIN, str.length() - OPER_BEGIN);
  return str;
}

string Dec2Hex(int dec)
{
  string hex = "";
  int remain;
  while(dec != 0) {
    remain = dec % 16;
    if(remain < 10)
      remain = remain + 48;
    else
      remain = remain + 55;
    hex.insert(0, 1, remain);
    dec /= 16;
  }
  return hex;
}

int Hex2Dec(string hex)
{
  int dec = 0;
    for(int i = 0; i < hex.length(); i++) {
        if(hex[i] >= 48 && hex[i] <= 57)
        {
          dec += (hex[i] - 48) * pow(16, hex.length() - i - 1);
        }
        else if(hex[i] >= 65 && hex[i] <= 70) {
          dec += (hex[i] - 55) * pow(16, hex.length( ) - i - 1);
        }
        else if(hex[i] >= 97 && hex[i] <= 102) {
          dec += (hex[i] - 87) * pow(16, hex.length() - i - 1);
        }
    }
    return dec;
}

