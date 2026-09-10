// keyboard.c
#include "io.h"

// Tablica mapująca scancodes z zestawu PS/2 (Set 1) na ASCII
static const char scancode_ascii[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
     0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
     0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
   '*',   0, ' '
};

char keyboard_getchar(void) {
    // Port 0x64 to Status Register. Bajt ma ustawiony bit 0 (0x01), gdy dane są gotowe.
    while (!(inb(0x64) & 0x01)) {
        // Czekaj na wciśnięcie
    }

    uint8_t scancode = inb(0x60); // Port 0x60 to Data Register

    // Bit 7 oznacz puszczenie klawisza (Key Release). Ignorujemy go na start.
    if (scancode & 0x80) {
        return 0; 
    }

    if (scancode < sizeof(scancode_ascii)) {
        return scancode_ascii[scancode];
    }

    return 0;
}
