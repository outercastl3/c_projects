#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void scan_ports(const char *ip, uint16_t start_port, uint16_t end_port) {
	printf("Scanning ports from %u to %u from IP: %s\n", start_port,end_port,ip);
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	
	if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
		perror("inet_pton failed");
		return;
	}

	for (int port = start_port; port <= end_port; port++) {
		int sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			perror("socket failed");
			continue;
		}		

		addr.sin_port = htons(port);
		
		int conn = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
		if (conn == 0) {
			printf("Port %u is open\n", port);
		} else {

			int err = errno;

			if (err == ECONNREFUSED) {
				printf("Port %u is CLOSED\n", port);
			} else if (err == ETIMEDOUT) {
				printf("Port %u is FILTERED (timeout)\n", port);
			} else {
				printf("Port %u error: %s\n", port, strerror(err));
			}
		}
		close(sock);
	}
}

