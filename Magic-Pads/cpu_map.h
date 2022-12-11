#ifndef CPU_MAP
#define CPU_MAP

#define enable_pin 11
#define enable_rPort PINB
#define enable_bit 7

#define pad_1_pin 2
#define pad_2_pin 3
#define pad_3_pin 4
#define pad_4_pin 5
#define pad_5_pin 6

#define pad_1_rPort PIND
#define pad_1_bit 1

#define pad_2_rPort PIND
#define pad_2_bit 0

#define pad_3_rPort PIND
#define pad_3_bit 4

#define pad_4_rPort PINC
#define pad_4_bit 4

#define pad_5_rPort PIND
#define pad_5_bit 7

#define setBit(RES, BIT) (RES |= (1 << BIT))                                // Set BIT in RES to HIGH
#define clrBit(RES, BIT) (RES &= ~(1 << BIT))                               // Set BIT in RES to LOW
#define tstBit(RES, BIT) (RES & (1 << BIT))                                 // Test BIT in RES and return 0 or 1
#define invBit(RES, BIT) (RES ^= (1 << BIT))                                // Invert BIT in RES (0 to 1 and 1 to 0)
#define writeBit(RES, BIT, VAL) (VAL) ? SetBit(RES, BIT) : ClrBit(RES, BIT) // Write VAL in BIT in RES (0 or 1)

#endif
