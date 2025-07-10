#include "ip.h"
#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint8_t rand_byte() { return rand() % 256; }
uint16_t compute_checksum(uint8_t *buffer) {
  uint8_t ihl_u16 = (buffer[0] & 0b1111) * 2;
  // cast uint8* to uint16*
  uint16_t *buf = (uint16_t *)buffer;

  unsigned int sum = 0;

  for (uint8_t i = 0; i < ihl_u16; i++) {
    sum += buf[i];
    if (sum > 0xFFFF)
      // habdle overflow
      sum = (sum & 0xFFFF) + 1;
  }

  // return complement of sum
  return ~((uint16_t)sum);
}
uint8_t *generate_random_ipv4_buffer() {
  srand(time(NULL));
  // rfc tells:
  // The maximal internet header is 60
  //     octets, and a typical internet header is 20 octets, allowing a
  //     margin for headers of higher level protocols.

  // to get a lenght between 20 and 60
  unsigned int length = rand() % 21 + 40;
  uint8_t *buffer = calloc(length, sizeof(uint8_t));

  // for ipv4
  uint8_t version = 4;
  // ihl on 4 bits so between 0 and 15
  // but the rfc specifies the min Header length is 20
  // so ihl is between 5 and 15 (so 20 and 60 bytes in total)
  uint8_t ihl = rand() % 11 + 5;
  uint8_t header_len = ihl * 4;
  buffer[0] = (version << 4) + ihl;
  // last two bytes of TOS are unused
  // max value is 2^6 = 64
  buffer[1] = rand() % 64;
  // total_length in number of bytes
  buffer[2] = header_len + rand() % 16;
  buffer[3] = rand_byte();
  // identification
  buffer[4] = rand_byte();
  buffer[5] = rand_byte();
  // flags and fragment_offset
  // flags first byte must be 0
  buffer[6] = rand() % 128;
  buffer[7] = rand_byte();
  // time to live
  buffer[8] = rand_byte();
  // protocol: rfc790
  // we are gonna generate only first 25 (except 0 which is reserved)
  // ICMP is 1
  buffer[9] = rand() % 24 + 1;
  // The checksum algorithm is:
  //   The checksum field is the 16 bit one's complement of the one's
  //   complement sum of all 16 bit words in the header.  For purposes of
  //   computing the checksum, the value of the checksum field is zero.
  // so we set it to 0
  buffer[10] = 0;
  buffer[11] = 0;
  // IP adresses
  for (uint8_t i = 12; i < 16; i++)
    buffer[i] = rand_byte();
  for (uint8_t i = 16; i < 20; i++)
    buffer[i] = rand_byte();
  // Options
  buffer[20] = rand_byte();

  // need to recompute checksum first
  if (header_len == 20) {
    uint16_t checksum = compute_checksum(buffer);
    buffer[10] = (checksum >> 8);
    buffer[11] = (checksum & 0xFF) >> 8;
    return buffer;
  }

  // option_len octet counts option-type
  // option-length and option-data octets
  buffer[21] = header_len - 19;

  for (uint8_t i = 21; i < header_len; i++)
    buffer[i] = rand_byte();

  uint16_t checksum = compute_checksum(buffer);
  buffer[10] = (checksum >> 8);
  buffer[11] = (checksum & 0xFF) >> 8;

  return buffer;
}

IPV4Header *ipv4_from_buffer(uint8_t *buffer, unsigned int buffer_len) {
  if (buffer_len < 20) {
    return NULL;
  }

  IPV4Header *header = (IPV4Header *)buffer;

  // rfc specifies that 1 word == 4 bytes
  // so we retrieve total number of bytes
  uint8_t ihl = HEADER_IHL(header) * 4;

  if (buffer_len < ihl) {
    return NULL;
  }

  return header;
}
