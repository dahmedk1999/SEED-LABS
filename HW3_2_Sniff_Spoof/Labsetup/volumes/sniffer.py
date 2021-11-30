#!/usr/bin/env python3
#Task 1.1
#sudo python3 sniffer.py
from scapy.all import *

ifaceC=['br-eee96822962c', 'enp0s3'] # Machine specific, find using ifconfig

def print_pkt(pkt):
    pkt.show()
print("Starting Packet Sniffing")
pkt = sniff(iface=ifaceC, filter='icmp', prn=print_pkt) # ICMP Filter
# pkt = sniff(iface=ifaceC, filter='src host 10.9.0.5 and dst port 23', prn=print_pkt) # TCP Host and Port filter
# pkt = sniff(iface=ifaceC, filter="dst net 128.230.0.0/16", prn=print_pkt,count=5) # Subnet Filter