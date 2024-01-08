module RAM (
    input wire [9:0] address,
    input wire [17:0] data,
    input wire WE,  // Write Enable
    input wire CE,  // Chip Enable
    output reg [17:0] q
);
  reg [17:0] ram[0:1023]; // Assuming a 1Kx18 RAM

  always @(posedge CE) begin
    if (WE) begin
      // Write operation
      ram[address] <= data;
    end else begin
      // Read operation
      q <= ram[address];
    end
  end
endmodule
