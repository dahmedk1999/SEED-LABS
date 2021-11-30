from scapy.all import*
#Task 1.2
a = IP()
a.dst = '123.14.22.30'
a.src= '1.2.3.4'
b = ICMP()
p = a/b
send(p)

a.show()