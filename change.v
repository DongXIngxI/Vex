

//   下面路径更换为自己生成的.bin文件的路径
  initial begin
    $readmemb("\\wsl.localhost/Ubuntu/home/anata/VexRiscv/mycpu.v_toplevel_axi_ram_ram_symbol0.bin",ram_symbol0);
    $readmemb("\\wsl.localhost/Ubuntu/home/anata/VexRiscv/mycpu.v_toplevel_axi_ram_ram_symbol1.bin",ram_symbol1);
    $readmemb("\\wsl.localhost/Ubuntu/home/anata/VexRiscv/mycpu.v_toplevel_axi_ram_ram_symbol2.bin",ram_symbol2);
    $readmemb("\\wsl.localhost/Ubuntu/home/anata/VexRiscv/mycpu.v_toplevel_axi_ram_ram_symbol3.bin",ram_symbol3);
  end

// 掩码写入，不然布局布线会出问题
always @(posedge io_axiClk) begin
    // 使用掩码进行按位写入
    if (stage0_fire && stage0_payload_fragment_write) begin
        if (io_axi_w_payload_strb[0]) begin
            ram_symbol0[_zz_io_axi_r_payload_data] <= 
                (ram_symbol0[_zz_io_axi_r_payload_data] & ~8'hFF) | 
                (_zz_io_axi_r_payload_data_1[7 : 0] & 8'hFF);
        end
        if (io_axi_w_payload_strb[1]) begin
            ram_symbol1[_zz_io_axi_r_payload_data] <= 
                (ram_symbol1[_zz_io_axi_r_payload_data] & ~8'hFF) | 
                (_zz_io_axi_r_payload_data_1[15 : 8] & 8'hFF);
        end
        if (io_axi_w_payload_strb[2]) begin
            ram_symbol2[_zz_io_axi_r_payload_data] <= 
                (ram_symbol2[_zz_io_axi_r_payload_data] & ~8'hFF) | 
                (_zz_io_axi_r_payload_data_1[23 : 16] & 8'hFF);
        end
        if (io_axi_w_payload_strb[3]) begin
            ram_symbol3[_zz_io_axi_r_payload_data] <= 
                (ram_symbol3[_zz_io_axi_r_payload_data] & ~8'hFF) | 
                (_zz_io_axi_r_payload_data_1[31 : 24] & 8'hFF);
        end
    end
end