module RegisterFile(
  input [3:0] READ_REG_1,
  input [3:0] READ_REG_2,
  input [3:0] WRITE_REG,
  input [17:0] WRITE_DATA,
  input REG_WRITE_ENABLE,
  input CPU_CLOCK,
  input CLEAR,
  output reg [17:0] READ_DATA_1,
  output reg [17:0] READ_DATA_2
);

  reg [17:0] registers [0:15]; 

  always @(posedge CPU_CLOCK) begin
    if (CLEAR) begin
      for (int i = 0; i < 16; i = i + 1) begin
        registers[i] <= 18'b0;
      end
    end else begin
      if (REG_WRITE_ENABLE) begin
        registers[WRITE_REG] <= WRITE_DATA;
      end
    end
  end

  assign READ_DATA_1 = registers[READ_REG_1];

  assign READ_DATA_2 = registers[READ_REG_2];

endmodule
