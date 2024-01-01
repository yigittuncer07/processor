module ALU (
    input [17:0] INPUT_A,
    input [17:0] INPUT_B,
    input [1:0] ALU_OP,
    output reg [17:0] result
);

always @(*)
begin
    case (ALU_OP)
        2'b00: result = INPUT_A + INPUT_B; 
        2'b01: result = INPUT_A & INPUT_B;  
        2'b10: result = ~(INPUT_A | INPUT_B); 
        2'b11: result = ~(INPUT_A & INPUT_B); 
        default: result = 18'b0;  
    endcase
end

endmodule
