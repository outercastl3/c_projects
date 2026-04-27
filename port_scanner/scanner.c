#include <pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define NUM_THREADS 4

typedef struct {
	uint16_t port;
	int status;
} PortResult;

typedef struct {
	struct sockaddr_in addr;
	uint16_t start_port;
	uint16_t end_port;
	PortResult *results;
} ThreadArgs;

int singularScan (uint16_t port, struct sockaddr_in addr) {

        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
                perror("socket failed");
        	return errno;
	}
	struct timeval tv = { .tv_sec = 1, .tv_usec = 0 };
	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
	
        addr.sin_port = htons(port);
        int conn = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	int err = errno;
	
	close(sock);

        return (conn == 0) ? 0 : err;
}

void *threadFunction(void *arg) {
        ThreadArgs *a = (ThreadArgs *)arg;

        for (int port = a->start_port; port <= a->end_port; port++) {
                int idx = port - a->start_port;
                a->results[idx].port = (uint16_t)port;
                a->results[idx].status = singularScan(port, a->addr);
        }

        return NULL;
}

PortResult* scan_ports(const char *ip, uint16_t start_port, uint16_t end_port, int *out_count) {
        printf("Scanning ports from %u to %u from IP: %s\n", start_port,end_port,ip);
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;

        if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
                perror("inet_pton failed");
                return NULL;
        }
	
	int range = (int)end_port - (int)start_port + 1;
	PortResult *results = malloc(sizeof(PortResult) * range);
	if (!results) {
		perror("malloc failed");
		return NULL;
	}
	pthread_t threads[NUM_THREADS];
	ThreadArgs args[NUM_THREADS];

	int chunk = range / NUM_THREADS;

	for (int i = 0; i < NUM_THREADS; i++) {
		args[i].addr = addr;
		args[i].start_port = start_port + i * chunk;

		args[i].end_port = (i == NUM_THREADS - 1) ? end_port : args[i].start_port + chunk - 1;
		args[i].results = results + (args[i].start_port - start_port);

		pthread_create(&threads[i], NULL, threadFunction, &args[i]);
	}

	for (int i = 0; i < NUM_THREADS; i ++) {
		pthread_join(threads[i], NULL);
	}

	*out_count = range;
	return results;
}
