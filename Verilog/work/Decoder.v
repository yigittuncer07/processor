module Decoder(
  input [3:0] opcode,
  output wire fetch0,
  output wire fetch1,
  output wire add_and,
  output wire addI,
  output wire andI,
  output wire nr,
  output wire nnd,
  output wire jmp,
  output wire ld,
  output wire st,
  output wire comp,
  output wire je,
  output wire ja,
  output wire jb,
  output wire jae,
  output wire jbe
);

  assign fetch0 = (opcode == 4'b0000);
  assign fetch1 = (opcode == 4'b0001);
  assign add_and = (opcode == 4'b0010);
  assign addI = (opcode == 4'b0011);
  assign andI = (opcode == 4'b0100);
  assign nr = (opcode == 4'b0101);
  assign nnd = (opcode == 4'b0110);
  assign jmp = (opcode == 4'b0111);
  assign ld = (opcode == 4'b1000);
  assign st = (opcode == 4'b1001);
  assign comp = (opcode == 4'b1010);
  assign je = (opcode == 4'b1011);
  assign ja = (opcode == 4'b1100);
  assign jb = (opcode == 4'b1101);
  assign jae = (opcode == 4'b1110);
  assign jbe = (opcode == 4'b1111);

endmodule
