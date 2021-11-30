#sniff n spoof
#Task 1.4
from scapy.all import *
import sys

# get packets on LAN
def spoofreply(packet): # Dissect 3 layers of packet (IP, ICMP, Data)
    # ls(packet[IP])
    # ls(packet[ICMP])
    # ls(packet[Raw])
    if(packet[ICMP].type!=8):
        return

    ip      = IP(src=packet[IP].dst,dst=packet[IP].src,ihl=packet[IP].ihl) #swap source with dest to spoof packet
    icmp    = ICMP(type=0,id=packet[ICMP].id,seq=packet[ICMP].seq)
    dat     = packet[Raw].load
    spoofd  = ip/icmp/dat

    send(spoofd,verbose=False)
    print("Spoof'd\t" + packet[IP].src +" with " + packet[IP].dst)
    
while(1):
    sniff(filter='icmp', prn=spoofreply)
