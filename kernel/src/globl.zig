pub export fn hcf() noreturn {
    while (true) {
        asm volatile ("hlt");
    }
}
