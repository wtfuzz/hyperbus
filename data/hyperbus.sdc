# Timing contrains for Hyperbus on Intel FPGAs

proc hyperbus_constrain_pins { name clk_pin data_pins } {
    puts "Adding timing constraints on hyperbus pins $name"
    puts "Clock pin: $clk_pin"
    puts "Data pins: $data_pins"

    # 200MHz clock with no phase shift
    create_clock -name "virt_${name}_clk" -period 5.000

    # 200MHz clock with 90 degree phase shift (1.250ns delay)
    create_clock -name "${name}_clk" -period 5.000 "$clk_pin" -waveform {1.250 3.750}

    set_input_delay -add_delay -clock "virt_${name}_clk" -max 1.00 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "virt_${name}_clk" -min -0.25 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "virt_${name}_clk" -clock_fall -max 1.00 [get_ports "$data_pins"]
    set_input_delay -add_delay -clock "virt_${name}_clk" -clock_fall -min -0.25 [get_ports "$data_pins"]
}