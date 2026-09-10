// ata.c
#include "io.h"

#define ATA_PRIMARY_DATA         0x1F0
#define ATA_PRIMARY_ERR          0x1F1
#define ATA_PRIMARY_SECCOUNT     0x1F2
#define ATA_PRIMARY_LBA_LO       0x1F3
#define ATA_PRIMARY_LBA_MID      0x1F4
#define ATA_PRIMARY_LBA_HIGH     0x1F5
#define ATA_PRIMARY_DRIVE_HEAD   0x1F6
#define ATA_PRIMARY_COMM_STAT    0x1F7

static void ata_wait_bsy(void) {
    while (inb(ATA_PRIMARY_COMM_STAT) & 0x80); // Bit 7 = BSY (Busy)
}

static void ata_wait_drq(void) {
    while (!(inb(ATA_PRIMARY_COMM_STAT) & 0x08)); // Bit 3 = DRQ (Data Request)
}

void ata_read_sector(uint32_t lba, uint16_t* buffer) {
    ata_wait_bsy();

    outb(ATA_PRIMARY_DRIVE_HEAD, 0xE0 | ((lba >> 24) & 0x0F)); // Master drive + LBA bits 24-27
    outb(ATA_PRIMARY_SECCOUNT, 1);                             // Liczba sektorów: 1
    outb(ATA_PRIMARY_LBA_LO, (uint8_t) lba);
    outb(ATA_PRIMARY_LBA_MID, (uint8_t)(lba >> 8));
    outb(ATA_PRIMARY_LBA_HIGH, (uint8_t)(lba >> 16));
    outb(ATA_PRIMARY_COMM_STAT, 0x20);                         // Komenda 0x20 = Read Sectors

    ata_wait_drq();

    // Odczyt 256 słów (16-bitowych) = 512 bajtów
    for (int i = 0; i < 256; i++) {
        buffer[i] = inw(ATA_PRIMARY_DATA);
    }
}
