// kernel.c
#include "vga.c"
#include "keyboard.c"
#include "ata.c"

void kernel_main(void) {
    vga_clear();
    vga_print("=== POBIERANIE SYSTEMU OPERACYJNEGO ===\n");
    vga_print("Wpisuj znaki na klawiaturze:\n> ");

    // Przykładowy odczyt 0 sektora z dysku
    uint16_t disk_buffer[256];
    ata_read_sector(0, disk_buffer);

    while (1) {
        char c = keyboard_getchar();
        if (c != 0) {
            vga_putchar(c);
        }
    }
}
