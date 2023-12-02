pub inline fn done() noreturn {
    while (true) {
        asm volatile ("hlt");
    }
}
