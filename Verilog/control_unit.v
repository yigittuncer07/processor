module ControlUnit (
    input [17:0] INPUT,
    input ZF,
    input CF,
    input CPU_CLOCK,
    output [15:0] ADDRESS,
    output [5:0] IMM,
    output [3:0] REG0,
    output [3:0] REG1,
    output [3:0] REG_DEST,
    output [3:0] OPCODE,
    output PC_ENABLE,
    output MEM_READ,
    output MEM_WRITE,
    output COMP_SIGNAL,
    output JUMP_SIGNAL,
    output REG_WRITE,
    output ALU_CONTROL,
    output [1:0] ALU_OP,
    output IS_IMMEDIATE
);

  wire fetch0, fetch1, add_and, addI, andI, nr, nnd, jmp, ld, st, comp, je, ja, jb, jae, jbe;

  // Counter logic
  reg [3:0] counter;
  reg load_counter;
  reg clear_counter;
  
  always @(posedge CPU_CLOCK or posedge load_counter) begin
    if (load_counter) begin
      counter <= INPUT[15:12];
    end else if (clear_counter) begin
      counter <= 4'b0000;
    end else begin
      counter <= counter + 4'b0001;
    end
  end


  Decoder decoder (
    .counter_output(counter),
    .fetch0(fetch0),
    .fetch1(fetch1),
    .add_and(add_and),
    .addI(addI),
    .andI(andI),
    .nr(nr),//Had to put nor as nr so it doesnt bug
    .nnd(nnd),//Had to put nand as ndn so it doesnt bug
    .jmp(jmp),
    .ld(ld),
    .st(st),
    .comp(comp),
    .je(je),
    .ja(ja),
    .jb(jb),
    .jae(jae),
    .jbe(jbe)
  );

  // Output assignments
  assign ADDRESS = INPUT[9:0];
  assign IMM = {6'b0, INPUT[5:0]};
  assign REG0 = INPUT[9:6];
  assign REG1 = INPUT[5:2];
  assign REG_DEST = INPUT[13:10];
  assign PC_ENABLE = |(add_and | addI | andI | nr | nnd | jmp | ld | st | comp | je | ja | jb | jae | jbe);
  assign ALU_OP = (add_and && (INPUT[17] == 0)) ? 2'b00 :
                 (add_and && (INPUT[17] == 1)) ? 2'b01 :
                 (nr) ? 2'b10 :
                 (nnd) ? 2'b11 :
                 2'b00; // Default value
  assign IS_IMMEDIATE = (addI | andI);
  assign ALU_CONTROL = (add_and || addI || andI || nr || nnd) ? 1'b1 : 1'b0;
  assign MEM_READ = ld;
  assign MEM_WRITE = st;
  assign COMP_SIGNAL = comp;
  assign JUMP_SIGNAL = je | ja | jb | jae | jbe;
  assign REG_WRITE = (ld || st || ALU_CONTROL) ? 1'b1 : 1'b0;
  assign ALU_CONTROL = (add_and) ? 2'b01 : 2'b00; 
  


endmodule
