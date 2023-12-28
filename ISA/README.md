# Instruction Set Architecture (ISA)

```plaintext
         [17:14] [13:10] [9:6]  [5:2] [1:0]
-------------------------------------
ADD      0010     dest   reg0   reg1   00
AND      0010     dest   reg0   reg1   01
ADDI     0101     dest   reg0   imm6
ANDI     0110     dest   reg0   imm6
NOR      0111     dest   reg0   reg1   00
NAND     1000     dest   reg0   reg1   00
JUMP     1001     0000   address
LD       1010     dest   address
ST       1011     reg0   address
CMP      1100     0000   reg0   reg1   00
JE       1101     0000   address
JA       1110     0000   address
JB       1101     0000   address
JAE      1110     0000   address
JBE      1111     0000   address
