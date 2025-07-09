
// According to the rfc, the Internet Protocol aims to provide
// a way to transmit blocks of data from a source to a destination
// WHERE source and destination are hosts identified by
// FIXED LENGTH ADRESSES
//
// The Internet Header Format is as such:
//  0                   1                   2                   3
//  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |Version|  IHL  |Type of Service|          Total Length         |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |         Identification        |Flags|      Fragment Offset    |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |  Time to Live |    Protocol   |         Header Checksum       |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                       Source Address                          |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                    Destination Address                        |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |                    Options                    |    Padding    |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#ifndef IPV4_H
#define IPV4_H

#include <stdint.h>
#include <stdbool.h>

// Section 3.2 defines Address Formats as:
// High Order Bits   Format                           Class
// ---------------   -------------------------------  -----
//       0            7 bits of net, 24 bits of host    a
//       10          14 bits of net, 16 bits of host    b
//       110         21 bits of net,  8 bits of host    c
//       111         escape to extended addressing mode
//
// That's some boring shit tbh
//
// We are just going to represent the IP Address
// as an array of 4 bytes as length is 4
typedef struct {
  uint8_t octets[4];
} IPV4Address;

// The Type Of Service as defined in the rfc:
// Bits 0-2:  Precedence.
// Bit    3:  0 = Normal Delay,      1 = Low Delay.
// Bits   4:  0 = Normal Throughput, 1 = High Throughput.
// Bits   5:  0 = Normal Relibility, 1 = High Relibility.
// Bit  6-7:  Reserved for Future Use.
//    0     1     2     3     4     5     6     7
// +-----+-----+-----+-----+-----+-----+-----+-----+
// |                 |     |     |     |     |     |
// |   PRECEDENCE    |  D  |  T  |  R  |  0  |  0  |
// |                 |     |     |     |     |     |
// +-----+-----+-----+-----+-----+-----+-----+-----+
//   Precedence
//     111 - Network Control
//     110 - Internetwork Control
//     101 - CRITIC/ECP
//     100 - Flash Override
//     011 - Flash
//     010 - Immediate
//     001 - Priority
//     000 - Routine
typedef struct {
  bool precedence[3];
  bool d;
  bool t;
  bool r;
  bool _reserved_future1;
  bool _reserved_future2;
} TypeOfService;

// As defined in the rfc again... :
//     Various Control Flags.
// Bit 0: reserved, must be zero
// Bit 1: (DF) 0 = May Fragment,  1 = Don't Fragment.
// Bit 2: (MF) 0 = Last Fragment, 1 = More Fragments.
//     0   1   2
//   +---+---+---+
//   |   | D | M |
//   | 0 | F | F |
//   +---+---+---+
// typedef struct {
//   bool _reserved0;
//   bool df;
//   bool mf; // not motherfucker (good to know)
// } Flags;
// Flags mixed with fragment_offset

// Options len is 40 at most
// so we store an array of 40 bytes
typedef struct {
  uint8_t length;
  uint8_t octets[40];
} Options;

// Implemented following the 3.1 Section of the rfc
typedef struct {
  uint8_t version_ihl;
  TypeOfService type_of_service;
  uint16_t total_length;
  uint16_t identification;
  // Flags -> 3 and fragment_offset: 13
  uint16_t fragment_offset_flags;
  uint8_t time_to_live;
  uint8_t protocol;
  uint16_t header_checksum;
  IPV4Address source_adress;
  IPV4Address destination_adress;
  Options options;
} IPV4Header;

#define HEADER_IHL(header) ((header)->version_ihl & 0b00001111)
#define HEADER_VER(header) ((header)->version_ihl >> 4)
#define HEADER_FLAGS(header) ((header)->fragment_offset_flags >> 13)
#define HEADER_FRAG_OFFSET(header) ((header)->fragment_offset_flags & 0b0001111111111111)

// this functions generates a valid
// ipv4 header for testing pursposes
void generate_ipv4_header(uint8_t *buf);

IPV4Header* ipv4_from_buffer(uint8_t* buffer, unsigned int buffer_len);

#endif
