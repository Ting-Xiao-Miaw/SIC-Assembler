#include <iostream>
#include <string>
#include <cctype>
using namespace std;

#define LABLEN 9
#define OPCLEN 8
#define OPRLEN 18

int main()
{
  string str;
  while(getline(cin, str)) {
    if(str[0] != '.') {

      // split
      string label, opcode, operand;
      size_t found;
      int count;
      label = str.substr(0, LABLEN);
      if(str.length() > LABLEN)
        opcode = str.substr(LABLEN, OPCLEN);
      if(str.length() > LABLEN + OPCLEN)
        operand = str.substr(LABLEN + OPCLEN, OPRLEN);

      // operand
      count = 0;
      while(operand[0] == ' ') {
        if(count == OPRLEN)
          break;
        operand.erase(operand.begin());
        operand += ' ';
        count++;
      }
      found = operand.find(' ');
      if(found != string::npos)
        operand.erase(found);
      if(operand[1] == '\'' && (operand[0] == 'c' || operand[0] == 'C')) {
        operand[0] = toupper(operand[0]);
      }
      else {
	for(int i = 0; i < operand.size(); i++) {
	  if(islower(operand[i]))
	    operand[i] = toupper(operand[i]);
	}
      }

      // opcode
      count = 0;
      while(opcode[0] == ' ') {
        if(count == OPCLEN)
          break;
        opcode.erase(opcode.begin());
        opcode += ' ';
        count++;
      }
      if(operand.empty()) {
        found = opcode.find(' ');
        if(found != string::npos)
        opcode.erase(found);
      }
      for(int i = 0; i < opcode.size(); i++) {
        if(islower(opcode[i]))
          opcode[i] = toupper(opcode[i]);
      }

      // label
      count = 0;
      while(label[0] == ' ') {
	if(count == LABLEN)
	  break;
	label.erase(label.begin());
	label += ' ';
	count++;
      }
      if(operand.empty() && opcode.empty()) {
        found = label.find(' ');
        if(found != string::npos)
        label.erase(found);
      }
      for(int i = 0; i < label.size(); i++) {
        if(islower(label[i]))
          label[i] = toupper(label[i]);
      }
      
      // print
      cout << label << opcode << operand << endl;
    }
  }
}
