module program_counter (
    input [9:0] ADDRESS,
    input JMP_SGNL,
    input PC_ENABLE,
    input clock,
    input CLEAR,
    output reg [9:0] result
);

  reg [9:0] register_out;
  reg [9:0] mux_out;

  // Register
  always @(posedge clock or posedge CLEAR) begin
    if (CLEAR) begin
      register_out <= 10'b0;
    end else if (PC_ENABLE) begin
      register_out <= ADDRESS;
    end
  end

  // Mux
  always @* begin
    mux_out = JMP_SGNL ? 10'b1 : ADDRESS;
  end

  // Adder
  always @* begin
    result = register_out + mux_out;
  end

endmodule

