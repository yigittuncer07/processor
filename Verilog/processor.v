`include "ALU.v"
`include "counter.v"
`include "control_unit.v"
`include "RAM.v"
`include "ROM.v"
`include "register_file.v"
`include "Comparator.v"

module Processor(
  input wire CPU_CLOCK,
  input wire CLEAR,
);

  
  wire [17:0] DATA0, DATA1, ALU_OUT, ADDRESS, IMM, REG0, REG1;
  wire [4:0] REG_DEST;
  wire [3:0] OPCODE;
  wire PC_ENABLE, MEM_READ, MEM_WRITE, COMP_SIGNAL, JUMP_SIGNAL, REG_WRITE, ALU_CONTROL, IS_IMMEDIATE;
  wire [1:0] ALU_OP;
  wire ZF, CF, JMP_SIGNAL;

  // Instantiate Control Unit
  ControlUnit control_unit (
    .INPUT(RAM_DATA),
    .ZF(ZF),
    .CF(CF),
    .CPU_CLOCK(CPU_CLOCK),
    .ADDRESS(ADDRESS),
    .IMM(IMM),
    .REG0(REG0),
    .REG1(REG1),
    .REG_DEST(REG_DEST),
    .OPCODE(OPCODE),
    .PC_ENABLE(PC_ENABLE),
    .MEM_READ(MEM_READ),
    .MEM_WRITE(MEM_WRITE),
    .COMP_SIGNAL(COMP_SIGNAL),
    .JUMP_SIGNAL(JUMP_SIGNAL),
    .REG_WRITE(REG_WRITE),
    .ALU_CONTROL(ALU_CONTROL),
    .ALU_OP(ALU_OP),
    .IS_IMMEDIATE(IS_IMMEDIATE)
  );

  ALU alu (
    .DATA0(DATA0),
    .DATA1(DATA1),
    .ALU_OP(ALU_OP),
    .ALU_OUT(ALU_OUT),
    .ZF(ZF),
    .CF(CF)
  );

  RegisterFile reg_file (
    .READ_REG_1(REG0),
    .READ_REG_2(REG1),
    .WRITE_REG(REG_DEST),
    .WRITE_DATA(ALU_OUT),
    .REG_WRITE_ENABLE(REG_WRITE),
    .CPU_CLOCK(CPU_CLOCK),
    .CLEAR(CLEAR),
    .READ_DATA_1(DATA0),
    .READ_DATA_2(DATA1)
  );

  Comparator comparator (
    .operand1(DATA0),
    .operand2(DATA1),
    .ZF_register(ZF),
    .CF_register(CF)
  );

  // Instantiate Program Counter
  counter pc (
    .ADDRESS(ADDRESS),
    .JMP_SGNL(JUMP_SIGNAL),
    .PC_ENABLE(PC_ENABLE),
    .clock(CPU_CLOCK),
    .CLEAR(CLEAR),
    .result(ADDRESS)
  );

  ROM instructionMemory (
  .addr(ADDRESS),
  .q(ROM_DATA),
  .contents({
    18'hC15F, 18'hC542, 18'hC44A, 18'h24434, 18'h8C41, 18'h8840, 18'h24BFF, 18'h24A00,
    18'h21200, 18'h280D0, 18'h2C001
  }),
  .writeEnable(WRITE_ENABLE)
  );

  RAM dataMemory (
  .address(DATA_ADDRESS),   // Connect to the address bus
  .data(DATA_IN),           // Connect to the data input bus
  .WE(WRITE_ENABLE),        // Connect to the write enable signal
  .CE(CHIP_ENABLE),         // Connect to the chip enable signal
  .q(DATA_OUT)              // Connect the output to your processor's data output
  );

endmodule
