#!/usr/bin/env python

import dpkt
import socket
import re
import time

f = open('tcp-ecn-sample.pcap')
pcap = dpkt.pcap.Reader(f)
pktCounter = 0
noOfPacketsSent = 0
noOfPacketsReceived = 0

for ts, buf in pcap:
    eth = dpkt.ethernet.Ethernet(buf)
    ip = eth.data
    tcp = ip.data
    pktCounter+=1

    # Mac address
    src_mac = (eth.dst).encode("hex")
    dst_mac = (eth.src).encode("hex")
    smac = ':'.join([src_mac[i:i+2] for i in range(0, len(src_mac), 2)])
    dmac = ':'.join([dst_mac[i:i+2] for i in range(0, len(dst_mac), 2)])

    # Packet
    ip = eth.data
    tcp = ip.data
    src = socket.inet_ntoa(ip.src)
    srcport = tcp.sport
    dst = socket.inet_ntoa(ip.dst)
    dstport = tcp.dport

    # Definition of Time
    showTime = time.gmtime(ts)
    timeF = time.strftime("%Y/%m/%d %H:%M:%S", showTime)

    # Packet Size
    sizeP = len(buf)

    # Data filtering
    p = re.compile("<Line>(.*?)\</Line>", re.IGNORECASE|re.DOTALL)

    # Packet print
    print "Packet No.: %s" %(pktCounter) , "\nPacket Size: %s" %(sizeP) , "\nTime: %s" %(timeF)
    print "Source: (MAC: %s) \033[1;32m(IP:%s)\033[1;m (port:%s)" % (smac,src,srcport)
    print "Destination: (MAC: %s) \033[1;31m(IP:%s)\033[1;m (port:%s)" % (dmac,dst,dstport)
    print "\n" 

    if (src == "1.1.12.1"):
        noOfPacketsSent += 1
    elif (dst == "1.1.12.1"):
        noOfPacketsReceived += 1

print "-------------------------------SUMMARY----------------------------"

print "\nTotal Packets Sent:" , noOfPacketsSent
print "Total Packets Received:" , noOfPacketsReceived
print "Total Packets:" , pktCounter

for ts, buf in pcap:
    eth = dpkt.ethernet.Ethernet(buf)
    ip = eth.data
    tcp = ip.data

    if tcp.dport == 80 and len(tcp.data) > 0:
        http = dpkt.http.Request(tcp.data)
        print "\nURL: " , http.uri
        print "HTTP Method: " , http.method
        print "HTTP Version: " , http.version
        print "User-Agent: " , http.headers['user-agent']
        print "Host: " , http.headers['host']
        print "Authorization: " , http.headers['authorization']
        print "Connection: " , http.headers['connection']
        print "\n"

f.close()