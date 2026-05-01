# Port Scanner
a simple port scanner based on sockets from the programming language C.
Uses CLI interface and tries to establish TCP connection with the range of portsgiven by the user, at the of execution returns results about the scan:
- Port is open
- Port if closed
- Connection request refused

## Usability 
The binary should be executed in such way
./scanner -i [ip_addr] -s [start of port range] -e [end of port range]

## Usage Example
./port_scanner -i 192.168.1.1 -s 1 -e 65535

## Author
Bogdan Ermakov
