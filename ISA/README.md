# Command and Register Encoding

## Command Encoding
- **Commands (4 bits):**
  - `0000` -> add
  - `0001` -> addi
  - `0010` -> jump
  - `0011` -> ld
  - `0100` -> st
  - `0101` -> cmp
  - `0110` -> je
  - `0111` -> ja
  - `1000` -> jb
  - `1001` -> jae
  - `1010` -> jbe

## Register Encoding
- **Registers (4 bits):**
  - R1 -> `0000`
  - R2 -> `0001`
  - R3 -> `0010`
  - ...
  - R15 -> `1111`

## Examples
### ADD DST, SRC1, SRC2
- **Command:** ADD R4, R2, R13
- **Binary Encoding:** `0000 0100 0010 1101 00`

### ADDI DST, SRC1, IMM
- **Command:** ADDI R5, R13, 63
- **Binary Encoding:** `0001 0101 1101 1111 11`

### JUMP ADDR
- **Command:** JMP 9
- **Binary Encoding:** `0010 0000 0001 0010 00`

### LD DST, ADDR
- **Command:** LD R5, 9
- **Binary Encoding:** `0011 0101 0000 0010 01`

### ST SRC, ADDR
- **Command:** ST R5, 9
- **Binary Encoding:** `0100 0101 0000 0010 01`

### CMP OP1, OP2
- **Command:** CMP R5, R13
- **Binary Encoding:** `0101 0101 1101 0000 00`

### JE ADDR
- **Command:** JE 9
- **Binary Encoding:** `0110 0000 0010 0100 00`

### JA ADDR
- **Command:** JA 9
- **Binary Encoding:** `0111 0000 0010 0100 00`

### JB ADDR
- **Command:** JB 9
- **Binary Encoding:** `1000 0000 0010 0100 00`

### JAE ADDR
- **Command:** JAE 9
- **Binary Encoding:** `1001 0000 0010 0100 00`

### JBE ADDR
- **Command:** JBE 9
- **Binary Encoding:** `1010 0000 0010 0100 00`

## Input File
```plaintext
ADD R4, R2, R13
LD R5, 9
JE 9
```

## Output File
```plaintext
010B4 0D409 18090
```