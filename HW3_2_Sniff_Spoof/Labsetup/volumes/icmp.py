from scapy.all import*
a = IP()
a.dst = '123.4.2.0'
a.src= '4.2.0.0'
b = ICMP()
p = a/b
send(p)

a.show()