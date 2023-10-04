# SIC-Asm-to-Obj

## File
1. split.cpp: The normalized format, characters transformed to uppercase.
2. pass1.cpp: Reads the output of the previous program and writes the output to two files, INTFILE and SYMTAB.
3. pass2.cpp: Reads the file INTFILE and SYMTAB which generated from previous program. The object file, should be printed to the stdout.
4. SAMPLE-input-1, SAMPLE-input-2, SAMPLE-input-3: These files are sample test file, should be replaced by your SIC assembly code.

| 1 | 2 | 3 |
| ------------- | ------------- | ------------- |
| 12345879  | 0123456789  | 0123456789  |
| 1-8 label  | 10-15 opcode  | 18- operand  |

## Run
```
 cat SAMPLE-input-1 | ./split | ./pass1
./pass2
```
