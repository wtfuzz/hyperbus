# Timing contrains for Hyperbus on Intel FPGAs

proc hyperbus_constrain_pins { name clk_pin clk90_pin data_pins } {
    puts "Adding timing constraints on hyperbus pins $name"
    puts "Clock pin: $clk_pin"
    puts "Data pins: $data_pins"

    # 200MHz clock with no phase shift
    create_clock -name "${name}_clk" -period 5.000 "$clk_pin"

    # 200MHz clock with 90 degree phase shift (1.250ns delay)
    create_clock -name "${name}_clk90" -period 5.000 "$clk90_pin" -waveform {1.250 3.750}

    set_input_delay -add_delay -clock "${name}_clk90" -max 1.00 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "${name}_clk90" -min -0.25 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "${name}_clk90" -clock_fall -max 1.00 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "${name}_clk90" -clock_fall -min -0.25 [get_ports "$data_pins"]

    set_output_delay -add_delay -clock "${name}_clk" -max 1.00 [get_ports "$data_pins"]
    set_output_delay -add_delay -clock "${name}_clk" -min -1.00 [get_ports "$data_pins"]
    set_output_delay -add_delay -clock "${name}_clk" -clock_fall -max 1.00 [get_ports "$data_pins"]
    set_output_delay -add_delay -clock "${name}_clk" -clock_fall -min -1.00 [get_ports "$data_pins"]

    set_false_path -rise_from [get_clocks "${name}_clk"] -fall_to [get_clocks "${name}_clk90"] -setup
    set_false_path -fall_from [get_clocks "${name}_clk"] -rise_to [get_clocks "${name}_clk90"] -setup

    set_false_path -rise_from [get_clocks "${name}_clk"] -fall_to [get_clocks "${name}_clk90"] -hold
    set_false_path -fall_from [get_clocks "${name}_clk"] -rise_to [get_clocks "${name}_clk90"] -hold
}