# CSE3015 / CSE3215 DIGITAL LOGIC DESIGN TERM PROJECT

## General Info
You are expected to design and implement a processor which supports instruction set: (ADD, AND, NAND, NOR, ADDI, ANDI, LD, ST, CMP, JUMP, JE, JA, JB, JAE, JBE). Processor will have 10 bits address width and 18 bits data width. Processor will have 5 parts as follows:

1. **Register File:** Will hold register values and signal to write into any register. There will be 16 registers in the processor.
2. **Instruction Memory:** A read-only memory where instructions will be stored. If the current instruction is not one of the JRA, JUMP, JE, JA, JB, JAE, JBE; the next instruction will be fetched and executed consecutively from this memory.
3. **Data Memory:** A read-write memory that will store data. The program will be able to read data from data memory and also store data to this memory. Data Memory will have 10 bits address width and 18 bits data width.
4. **Control Unit:** Will produce proper signals to all datapath components.
5. **Arithmetic Logic Unit (ALU):** Will compute arithmetic operations ADD, AND, NAND, NOR, ADDI, ANDI. Operands will be fetched from register+register or register+ immediate value. Result will be stored to the Register File.

## Instruction Set
Detailed information about instructions is given below:

- **ADD, AND, NAND, NOR:**
  - ADD instruction will add two registers and store the result into another register. Structure of instruction is: `ADD DST, SRC1, SRC2`, where SRC1 and SRC2 are source registers, and DST is the destination register for the operation.

- **ADDI, ANDI:**
  - ADDI instruction will add a register value and an immediate value, and store the result into another register. Form of instruction is: `ADDI DST, SRC1, IMM`, where SRC1 is a register, DST is the destination register, and IMM is an immediate value.

- **JUMP:**
  - JUMP instruction will set the Program Counter (PC) to the given value in the instruction. `JUMP ADDR` where ADDR will be in PC relative mode. ADDR will be an offset, and it can be negative. For example:
    - `JUMP 3` will set PC to: next instruction's address + 3 (go forward 3 instructions).
    - `JUMP -5` will set PC to: next instruction's address – 5 (go back 5 instructions).

- **LD:**
  - LD instruction will load a value from Data Memory to any register. `LD DST, ADDR` where DST is a register to load and ADDR is an address in the max available bit size. Upper bits of ADDR will be zero-extended.

- **ST:**
  - ST instruction will store a value from a register to Data Memory. `ST SRC, ADDR` where SRC is a register to fetch data and ADDR is a Data Memory address to store content of the register. Upper bits of ADDR will be zero-extended.

- **CMP:**
  - Compare instruction will compare two operands, then will update the flag values of zero flag ZF and carry flag CF. Following conditional jump instruction will set the destination address if the condition holds. `CMP OP1, OP2` will compare registers OP1 and OP2. If they are equal, flag values will be ZF=1, CF=0. If the first operand's value is greater, flag values will be ZF=0, CF=0. If the first operand's value is less than the second operand, flag values will be ZF=0, CF=1.

As in the JUMP instruction, but conditional with the flag values, JE, JA, JB, JAE, JBE jumps to a new destination address.

- **JE:**
  - If flag values are (ZF=1, CF=0), PC will be set to ADDR (PC-relative).

- **JA:**
  - If flag values are (ZF=0, CF=0), PC will be set to ADDR (PC-relative).

- **JB:**
  - If flag values are (ZF=0, CF=1), PC will be set to ADDR (PC-relative).

- **JAE:**
  - If flag values are (CF=0), PC will be set to ADDR (PC-relative).

- **JBE:**
  - If flag values are (CF=1 or ZF=1), PC will be set to ADDR (PC-relative).

## Design Guide
Since you already have your instructions and instruction length (18 bits), your design process includes; instruction set architecture and control unit design. For instruction set architecture, you should decide on fields of your instruction like, what will be the size of the opcode field? How many bits to reserve for register addressing in instruction? What is the maximum possible size for the immediate part? Control unit design will include proper signal generation for all datapath. First, you must define a Finite State Machine for your processor (Micro-programmed control unit is not allowed!). For every instruction, you should decide how many states an instruction will need to execute? What will be the control signals for each state of an instruction?

For example, LD instruction will do the following operations consecutively:
1. Read PC value
2. Fetch instruction from Instruction Memory with address given in PC
3. Read Data Memory with the given address in instruction
4. Write content from Data Memory to the destination register.

LD instruction will require 4 states to complete. At each state, some signals should control components to do the right operations. For example, at state 1, PCread signal, which will allow PC to put its content on its output, should be activated. Remember that PC is an 18-bit register that holds the current instruction's address. At state 2, instruction fetch, instruction will be fetched from Instruction Memory. Therefore, instRead signal will be activated. At state 3, the extended address will be put on the address input of Data Memory, and dataMemRead signal will be activated. At state 4, we will write output from Data Memory to the register given in the instruction. So, regWrite signal will be activated. Remember that, your full Datapath will contain additional combinatorial components like a multiplexer, adder, ALU. Control signals have to be designed also for these parts of the processor. For example, if the current instruction is not setting PC value (not one of JUMP, BR), your next PC value will be PC+1. Since there are two possible next values for PC, there should be a multiplexer at the input of the PC register with two inputs: PC+1 and PC relative calculated address from instructions JUMP, BR. You should produce a signal for this multiplexer Pcselect signal. Your design must include the following signals also. (Remember that there can be additional signals and these signals are dependent on your design! - Mux signals or other additional signals).

- **ALUcontrol signal:** Should select the operation on the Arithmetic Logic Unit (ALU). For example, there are 4 arithmetic or logic operations on ALU (AND, OR, XOR, ADD). ALUcontrol must be at least 2 bits and for every operation, a 2-bit value has to be assigned.
- **MemWrite signal:** Must be 1 for the final state of ST instruction.
- **PCwrite:** At the final state of JUMP and Branch instructions, PC will be modified. PCwrite signal must be 1.
