# Timing contrains for Hyperbus on Intel FPGAs

proc hyperbus_constrain_pins { name clk clk90 data_pins } {
    puts "Adding timing constraints on hyperbus pins $name"
    puts "Clock: $clk"
    puts "90 degree clock: $clk90"
    puts "Data pins: $data_pins"

    # 200MHz clock with no phase shift
    #create_clock -name "${name}_clk" -period 5.000 "$clk_pin"

    # 200MHz clock with 90 degree phase shift (1.250ns delay)
    #create_clock -name "${name}_clk90" -period 5.000 "$clk90_pin" -waveform {1.250 3.750}

    set_input_delay -add_delay -clock "${clk}" -max 0.25 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "${clk}" -min -0.25 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "${clk}" -clock_fall -max 0.25 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "${clk}" -clock_fall -min -0.25 [get_ports "$data_pins"]
    
    #set_output_delay -add_delay -clock "${clk90}" -max 1.00 [get_ports "$data_pins"]
    #set_output_delay -add_delay -clock "${clk90}" -min -1.00 [get_ports "$data_pins"]
    #set_output_delay -add_delay -clock "${clk90}" -clock_fall -max 1.00 [get_ports "$data_pins"]
    #set_output_delay -add_delay -clock "${clk90}" -clock_fall -min -1.00 [get_ports "$data_pins"]

    set_false_path -setup -rise_from [get_clocks "${clk}"] -fall_to [get_clocks "${clk90}"]
    set_false_path -setup -fall_from [get_clocks "${clk}"] -rise_to [get_clocks "${clk90}"]

    set_false_path -hold -rise_from [get_clocks "${clk}"] -fall_to [get_clocks "${clk90}"]
    set_false_path -hold -fall_from [get_clocks "${clk}"] -rise_to [get_clocks "${clk90}"]
}