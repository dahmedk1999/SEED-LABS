from scapy.all import*
ip= IP()
ip.dst='10.9.0.6'
send(ip,5)