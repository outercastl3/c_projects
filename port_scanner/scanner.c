#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int singularScan (uint16_t port, struct sockaddr_in addr) {

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
                perror("socket failed");
        	return errno;
	}

        addr.sin_port = htons(port);
        int conn = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	int err = errno;
	
	close(sock);

        return (conn == 0) ? 0 : err;
}

void scan_ports(const char *ip, uint16_t start_port, uint16_t end_port) {
        printf("Scanning ports from %u to %u from IP: %s\n", start_port,end_port,ip);
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;

        if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
                perror("inet_pton failed");
                return;
        }

        for (uint16_t port = start_port; port <= end_port; port++) {
                int result = singularScan(port,addr); 

                if (result == 0) {
                        printf("Port %u is open\n", port);
                } else if (result == ECONNREFUSED) {
			printf("Port %u is CLOSED\n", port);
                } else if (result == ETIMEDOUT) {         
			printf("Port %u is FILTERED (timeout)\n", port);
                } else {
			printf("Port %u error: %s\n", port, strerror(result));
		}
                };
        }

