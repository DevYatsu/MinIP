# MinIP

My implementation of a Minimal Internet Protocol Suite in C.
[See this tweet for more informations](https://x.com/tetsuoai/status/1942891931744579745).

Each implementation follows the following Core Protocols RFCS:
- `arp.c`: [ARP (RFC 826)](https://tools.ietf.org/rfc/rfc826.txt)
- [ICMP (RFC 792)](https://tools.ietf.org/rfc/rfc792.txt)
- [TFTP (RFC 1350)](https://tools.ietf.org/rfc/rfc1350.txt)
- [DNS (RFC 1035)](https://tools.ietf.org/rfc/rfc1035.txt)
- [HTTP/1.1 (RFC 2616)](https://tools.ietf.org/rfc/rfc2616.txt)

For IPv4 and TCP RFCs:
IPv4 (RFC 791): https://tools.ietf.org/rfc/rfc791.txt)
TCP (RFC 793): https://tools.ietf.org/rfc/rfc793.txt)

For UDP RFC:
- [UDP (RFC 768)](https://tools.ietf.org/rfc/rfc768.txt)

Bonus - Related RFCs:
- [IP Routing (RFC 1122)](https://tools.ietf.org/rfc/rfc1122.txt)
- [Ethernet (RFC 894)](https://tools.ietf.org/rfc/rfc894.txt)

Bonus module: 
- [DHCP client (RFC 2131): discover, request, renew, release](https://tools.ietf.org/rfc/rfc2131.txt)
