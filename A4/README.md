# Lab Assignment 3
### by Vipul B17069 and Swapnil B17104

## Problem 1
- Compile using ```make```. This will generate 3 executables - ```script```, ```server``` and ```client```.
- If you just want to test manually on 2 VMs run ```./server``` on your server VM and run ```./client YOUR_SERVER_IP``` on your client VM.
- Both can run simultaneously on both the VMs. Just take care of the server IP you put as the command line argument.
- Send ```exit``` from client to exit the program anytime.
- To run automated script tests on client, run ```./script YOUR_SERVER_IP``` on your client VM. This script will perform these tasks-
    - Generate random input strings in ```input/``` directory.
    - Generate corresponding outputs in ```expected_output/``` directory.
    - Run the test case using client program by sending requests to server and generate the output in ```output/``` directory.
    - Compare the test cases in ```output/``` and ```expected_output/``` directory to see if the cases pass or fail.


## Problem 2

## Problem 3
a) DNS - DNS or a Domain Name Server is a server that acts like a phonebook for the clients on the internet. Everytime we put in a domain name in a browser, the request actually goes to a DNS Server, which then provides the IP Address corresponding to that particular domain name.
DHCP - DHCP or Dynamic Host Configuration Protocol is a network management protocol used on IP Networks. A DHCP server dynamically assigns IP Addresses to nodes on a network. It allows the nodes to request IP Addresses from the router or the ISP, reducing the need for manual IP Addresses.

b) TCP - TCP or Transmission Control Protocol is a connection-oriented protocol, i.e. conection is first established before transmitting data. It is reliable data delivery protocol. Packets arrive in order at the server. Retransmission of lost packets occurs. Used in HTTP, HTTPS, FTP, SMTP etc.
UDP - UDP or User Datagram Protocol is a datagram oriented protocol. Unlike TCP, there is no need to establish a connection in this case and also maintaining and terminating it. It is preffered for broadcast or multicast transmissions. It is unreliable data delivery protocol. No ordering of packets is required. No retrasmission of lost packets occurs. Used in DNS, DHCP, VoIP etc.

c) The OSI Layer model was developed in the year 1984 and used in most modern day networks. In this 7 layer model, each layer has a separate function to perform and all these layers work together to transmit data from one node to another over a network. These layers are Physical, Data Link, Network, Transport, Session, Presentation and Application Layers.

d) 
vipul@vipul:~/CS307-SystemPracticum/A4/1$ ifconfig
enp0s3    Link encap:Ethernet  HWaddr 08:00:27:60:ea:c1  
          inet addr:192.168.1.7  Bcast:192.168.1.255  Mask:255.255.255.0
          inet6 addr: fe80::dfc6:3a18:df69:8b58/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:87885 errors:0 dropped:5 overruns:0 frame:0
          TX packets:13605 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:30317696 (30.3 MB)  TX bytes:8611453 (8.6 MB)

IP Address from ifconfig - 192.168.1.7
IP Address from ip2location - 117.207.52.35

The reason for this difference is that there are finite number of IPs in the world. Thus, there is need for routers to which my computer is connected to. The IP address 192.168.1.7 is assigned to my computer by the router and the IP Address 117.207.52.35 is assigned to me by my ISP - BSNL. This same IP Address maybe assigned to many people across North India as the location showed on ip2location is Ambala, Haryana.

e) 0.0.0.0 is used to designate an unknown or invalid node on a network. It has different uses in different contexts. For example, to send a request from a node to DHCP to get an IP Address assigned, a packet is send to 0.0.0.0 along with the MAC Address of the node.

255.255.255.255 is the broadcast address which is a network address used to transmit to all devices connected on the network. 

f) 
vipul@vipul:~/CS307-SystemPracticum/A4/1$ traceroute harvard.edutraceroute to harvard.edu (23.185.0.1), 30 hops max, 60 byte packets
 1  192.168.1.1 (192.168.1.1)  1.948 ms  1.920 ms  1.876 ms
 2  117.207.52.1 (117.207.52.1)  1.847 ms * *
 3  * * *
 4  218.248.107.134 (218.248.107.134)  2.848 ms * *
 5  * 117.216.207.202 (117.216.207.202)  9.703 ms *
 6  117.216.207.203 (117.216.207.203)  12.683 ms  12.500 ms *
 7  * * 115.110.78.173 (115.110.78.173)  12.446 ms
 8  * 172.23.183.161 (172.23.183.161)  30.739 ms *
 9  * * 172.28.132.245 (172.28.132.245)  32.192 ms


192.168.1.1 - Router IP Address
117.207.52.1 - ISP IP Address BSNL - Ambala
218.248.107.134 - ISP Node BSNL - Delhi
117.216.207.203 - ISP Node BSNL - Bengaluru
115.110.78.173 - Inter-country Network Node by TATA Communications - Delhi
172.23.183.161 - Private IP Address LAN
172.28.132.245 - Private IP Address LAN
23.185.0.1 - Public Proxy Server harvard.edu - California, USA

