from scapy.all import*
#references codeinlet.com
#Task 1.3
ip = IP()
ip.dst = '75.75.75.75' # nslookup sjsu.edu 
ip.ttl = 1
icmp = ICMP()
# send(ip/icmp)
while (ip.ttl <=30):
    reply= sr1(ip/icmp,verbose=0) #disable spammy info messages
    if (reply==None):
        ip.ttl+=1
        print(str(ip.ttl) + "\t * * *") # dis play ttl# * * *
        continue
    #otherwise print ttl , router
    print(str(ip.ttl)+'\t'+reply.src)

    if reply.src==ip.dst:
        break
    ip.ttl=ip.ttl+1