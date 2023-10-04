# SIC-Asm-to-Obj

## File
1. split.cpp: The normalized format, characters transformed to uppercase
        +----------------------------------------+
        |          1         2         3         |
        | 1234567890123456789012345678901234567  |
        | ======== ======  ==================    |
        |   1-8    10-15     18-                 |
        |  label   opcode    operand             |
        +----------------------------------------+
   Attempt | #1 | #2 | #3 | #4 | #5 | #6 | #7 | #8 | #9 | #10 | #11
--- | --- | --- | --- |--- |--- |--- |--- |--- |--- |--- |---
Seconds | 301 | 283 | 290 | 286 | 289 | 285 | 287 | 287 | 272 | 276 | 269
3. pass1.cpp: Reads the output of the previous program and writes the output to two files, INTFILE and SYMTAB.
4. pass2.cpp: Reads the file INTFILE and SYMTAB which generated from previous program. The object file, should be printed to the stdout.
