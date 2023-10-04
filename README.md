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
2. pass1.cpp: Reads the output of the previous program and writes the output to two files, INTFILE and SYMTAB.
3. pass2.cpp: Reads the file INTFILE and SYMTAB which generated from previous program. The object file, should be printed to the stdout.
