/*

Credentials file

*/

#pragma once

// Only one of these settings must be defined
#define USE_ABP
//#define USE_OTAA

#ifdef USE_ABP

// UPDATE WITH YOUR TTN KEYS AND ADDR.
static const PROGMEM u1_t NWKSKEY[16] = { 0xA5, 0x3F, 0x81, 0x10, 0x66, 0x4F, 0x65, 0xED, 0x58, 0x02, 0x3E, 0xC6, 0xAA, 0x2F, 0x4B, 0xAC };
static const u1_t PROGMEM APPSKEY[16] = { 0xA1, 0x9A, 0xC6, 0x19, 0x4E, 0x5D, 0xA2, 0xE5, 0xDB, 0xA3, 0x94, 0x16, 0xB8, 0xD4, 0x57, 0x36 };
static const u4_t DEVADDR = 0x260B6A40 ; // <-- Change this address for every node!

#endif

#ifdef USE_OTAA

    // This EUI must be in little-endian format, so least-significant-byte
    // first. When copying an EUI from ttnctl output, this means to reverse
    // the bytes. For TTN issued EUIs the last bytes should be 0x00, 0x00,
    // 0x00.
    static const u1_t PROGMEM APPEUI[8]  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

    // This should also be in little endian format, see above. (least-significant-byte
    // first)
    static const u1_t PROGMEM DEVEUI[8]  = { 0xFF, 0xFE, 0x18, 0xD2, 0xDC, 0x98, 0x83, 0x30 };

    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    static const u1_t PROGMEM APPKEY[16] = { 0x26, 0x7B, 0x7C, 0x0A, 0x61, 0x8D, 0x0E, 0xFA, 0x6B, 0x18, 0xE9, 0x16, 0x6C, 0x46, 0x48, 0x63 };

#endif
