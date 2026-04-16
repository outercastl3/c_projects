#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void scan_ports(const char *ip, int start_port, int end_port) {
	printf("Scanning ports from %d to %d from IP: %s\n", start_port,end_port,ip);

	for (int port = start_port; port <= end_port; port++) {
		printf("Chechking port %d\n", port);
		// work on logic here, sockets
	}
}
