pub extern "C" fn e9_print(msg: [*c]const u8) callconv(.C) void;

pub export fn _print(msg: [*c]const u8) callconv(.C) void {
    e9_print(msg);
}
