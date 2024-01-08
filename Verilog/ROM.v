module ROM(
  input wire [9:0] addr,
  output wire [17:0] q,
  input wire [17:0] contents [0:1023],  // Initial ROM contents
  input wire writeEnable                // Write enable signal
);
  reg [17:0] rom[0:1023];

  // Initialize the ROM with your initial instructions
  initial begin
    for (int i = 0; i <= 1023; i = i + 1) begin
      rom[i] = contents[i];
    end
  end

  always @* begin
    // Read data from the ROM based on the input address
    q = rom[addr];
  end

  always @(posedge writeEnable) begin
    // Write new instruction to the ROM when writeEnable is asserted
    rom[addr] <= contents[addr];
  end
endmodule
