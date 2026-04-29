# Port Scanner built with raw sockets
a raw sockets Port Scanner with multi-threading in Language C with CLI based workflow.
Returns following information:
- Port is open
- Port is closed
- Port was filtered

# Usability
execute binary in such manner:
./port_scanner_raw -i [ip_addr] -s [start of port range] -e [end of port range]

## Usage example
- root priviledges are require to use this scanner
./port_scanner_raw -i 192.168.1.1 -s 1 -e 65535

## Author 
Bogdan Ermakov
