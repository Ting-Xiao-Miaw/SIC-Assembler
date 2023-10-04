#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define LABLEN 9
#define OPCLEN 8
#define OPRLEN 18
#define SYMLEN 7

string Dec2Hex(int dec);
int Hex2Dec(string hex);

int main()
{
  ofstream INT("INTFILE");
  ofstream SYM("SYMTAB");
  string str;
  string sym = "";
  int begin = 0;
  int x = 0;
  while(getline(cin, str)) {

      // split
      string loc, label, opcode, operand;
      label = str.substr(0, LABLEN);
      bool start = false;
      bool end = false;
      bool byte = false;
      bool word = false;
      bool initial = false;
      if(str.length() > LABLEN)
        opcode = str.substr(LABLEN, OPCLEN);
      if(str.length() > LABLEN + OPCLEN)
        operand = str.substr(LABLEN + OPCLEN, OPRLEN);


      // INTFILE
      // check start and convert loc counter to string
      if(opcode.compare("START   ") == 0) {
	loc = operand;
        x = Hex2Dec(loc);
	begin = x;
	start = true;
      }
      else {
	loc = Dec2Hex(x);	
      }

      // check assembler directive
      if(opcode.compare("BYTE    ") == 0) {
	byte = true;
	initial = true;
      }
      else if(opcode.compare("WORD    ") == 0) {
	word = true;
	initial = true;
      }
      else if(opcode.compare("RESB    ") == 0) {
	byte = true;
      }
      else if(opcode.compare("RESW    ") == 0) {
        word = true;
      }
      else if(opcode.compare("END     ") == 0) {
	end = true;
      }

      // add loc counter
      if(start || end) {
	x += 0;
      }
      else if(byte && initial) {
	if(operand[0] == 'C')
	  x += operand.length() - 3;
	else if(operand[0] == 'X')
	  x += (operand.length() - 3) / 2;
      }
      else if(byte && !initial) {
	x += stoi(operand);
      }
      else if(word && !initial) {
        x += 3 * stoi(operand);
      }
      else
	x += 3;


      // loc add space and 0
      while(loc.length() < 6) {
        loc.insert(0, 1, '0');
      }

      // SYMTAB
      // check label
      if(label[0] != ' ') {
        string temp;
        temp = label.substr(0, SYMLEN);
        sym += temp;
        sym += loc;
        sym += "\n";
      }
      if(end) {
        string length = Dec2Hex(x - begin);
        while(length.length() < 6) {
          length.insert(0, 1, '0');
        }
        length.insert(0, 1, ' ');
        sym.insert(SYMLEN + 6, length);
      }

      // write to file
      loc += " ";
      INT << loc << label << opcode << operand << endl;
  }
  SYM << sym;
  SYM.close(); 
  INT.close();
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
