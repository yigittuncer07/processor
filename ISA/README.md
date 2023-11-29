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
- **Binary Encoding:** `000001000010110100`

### ADDI DST, SRC1, IMM
- **Command:** ADDI R5, R13, 63
- **Binary Encoding:** `000101011101111111`

### JUMP ADDR
- **Command:** JMP 9
- **Binary Encoding:** `001000000001001000`

### LD DST, ADDR
- **Command:** LD R5, 9
- **Binary Encoding:** `001101010000001001`

### ST SRC, ADDR
- **Command:** ST R5, 9
- **Binary Encoding:** `010001010000001001`

### CMP OP1, OP2
- **Command:** CMP R5, R13
- **Binary Encoding:** `010101011101000000`

### JE ADDR
- **Command:** JE 9
- **Binary Encoding:** `011000000010010000`

### JA ADDR
- **Command:** JA 9
- **Binary Encoding:** `011100000010010000`

### JB ADDR
- **Command:** JB 9
- **Binary Encoding:** `100000000010010000`

### JAE ADDR
- **Command:** JAE 9
- **Binary Encoding:** `100100000010010000`

### JBE ADDR
- **Command:** JBE 9
- **Binary Encoding:** `101000000010010000`

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