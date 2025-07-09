#include "ip.h"
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

IPV4Header* ipv4_from_buffer(uint8_t* buffer, unsigned int buffer_len) {
  if (buffer_len < 20) {
    return NULL;
  }
  
  IPV4Header* header = (IPV4Header *)buffer;

  // rfc specifies that 1 word == 4 bytes
  // so we retrieve total number of bytes
  uint8_t ihl = HEADER_IHL(header) * 4;
  
  if (buffer_len < ihl) {
    return NULL;
  }

  return header;
}
