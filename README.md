# RSiCS Client Broker (RSicsCB)

A system for conntecting clients using RSiCS for simple direct Peer to Peer communication. 

RSiCS Client Brokers can be used to establish a direct p2p connection with two clients. One client connects to a RSicsCB, exposing its IP and port. After that, another client can connect before a specified expiry. The RSicsCB can then send the connection information to the two clients and they can start direct p2p communication. 

  
RSicsCB is built on RSiCS (hence the name). This means it uses the RStP. Check out [RSiCS](https://github.com/rubensystems/rsics) for more information. 


