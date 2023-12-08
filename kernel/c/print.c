#include <print.h>

void (*limine_print)(char const *buf, size_t len) = NULL;

static char const CONVERSION_TABLE[] = "0123456789abcdef";

void putc(char c) {
    if (limine_print != NULL)
        limine_print(&c, 1);
#if defined(__x86_64__) || defined(__i386__)
    __asm__ __volatile__("outb %0, %1"
        :: "a"(c), "Nd"(0xe9)
        : "memory");
#endif
}

void print_blind(const char *msg) {
    for (size_t i = 0; msg[i]; i++) {
        putc(msg[i]);
    }
}

void _puts(const char *msg) {
    print_blind(msg);
    putc('\n');
}

static void e_printhex(size_t num) {
    int i;
    char buf[17];

    if (!num) {
        print_blind("0x0");
        return;
    }

    buf[16] = 0;

    for (i = 15; num; i--) {
        buf[i] = CONVERSION_TABLE[num % 16];
        num /= 16;
    }

    i++;
    print_blind("0x");
    print_blind(&buf[i]);
}

static void _printdec(size_t num) {
    int i;
    char buf[21] = { 0 };

    if (!num) {
        putc('0');
        return;
    }

    for (i = 19; num; i--) {
        buf[i] = (num % 10) + 0x30;
        num = num / 10;
    }

    i++;
    print_blind(buf + i);
}

void _printf(const char *format, ...) {
    va_list argp;
    va_start(argp, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 'x') {
                e_printhex(va_arg(argp, size_t));
            } else if (*format == 'd') {
                _printdec(va_arg(argp, size_t));
            } else if (*format == 's') {
                print_blind(va_arg(argp, char *));
            } else if (*format == 'c') {
                putc(va_arg(argp, char));
            }
        } else {
            putc(*format);
        }
        format++;
    }

    putc('\n');
    va_end(argp);
}
