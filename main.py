def on_bluetooth_connected():
    basic.show_icon(IconNames.HAPPY)
    bluetooth.start_uart_service()
bluetooth.on_bluetooth_connected(on_bluetooth_connected)

def on_bluetooth_disconnected():
    basic.show_icon(IconNames.SAD)
bluetooth.on_bluetooth_disconnected(on_bluetooth_disconnected)

def on_uart_data_received():
    global cmd
    cmd = bluetooth.uart_read_until(serial.delimiters(Delimiters.FULLSTOP))
    if cmd.includes("a"):
        basic.show_arrow(ArrowNames.NORTH)
    else:
        if cmd.includes("b"):
            basic.show_arrow(ArrowNames.SOUTH)
        else:
            basic.show_arrow(ArrowNames.EAST)
    bluetooth.uart_write_string(cmd)
bluetooth.on_uart_data_received(serial.delimiters(Delimiters.FULLSTOP),
    on_uart_data_received)

cmd = ""
basic.show_icon(IconNames.ASLEEP)