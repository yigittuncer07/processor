module Comparator(
  input [17:0] operand1,
  input [17:0] operand2,
  output reg ZF_register,
  output reg CF_register
);

  assign ZF = (operand1 == operand2);
  assign CF = (operand1 > operand2);

  always @(posedge clk or posedge rst) begin
    if (rst) begin
      ZF_register <= 1'b0; // Reset the ZF register to 0
      CF_register <= 1'b0; // Reset the CF register to 0
    end else begin
      ZF_register <= ZF;    // Store ZF in the ZF register
      CF_register <= CF;    // Store CF in the CF register
    end
  end

endmodule
