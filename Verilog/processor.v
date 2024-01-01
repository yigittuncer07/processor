`include "ALU.v"


module processor (
    // Your module ports
    input wire [17:0] INPUT_A,
    input wire [17:0] INPUT_B,
    input wire [1:0] ALU_OP,
    output wire [17:0] ALU_OUT
);


ALU_module ALU (
    .inputA(INPUT_A),
    .inputB(INPUT_B),
    .ALU_OP(ALU_OP),
    .result(ALU_OUT)
);


endmodule