#!/usr/bin/env python3
from scapy.all import *

ifaceC=['br-61846b5b5ea4', 'enp0s3']
def print_pkt(pkt):
    pkt.show()
print("Starting Packet Sniffing")
pkt = sniff(iface=ifaceC, filter="dst net 128.230.0.0/16", prn=print_pkt,count=5)
