#ifndef SCANNER_H
#define SCANNER_H
#include <pthread.h>
#include <stdint.h>
typedef struct {
	uint16_t port;
	int status;
} PortResult;

PortResult* scan_ports(const char *ip, uint16_t start_port, uint16_t end_port, int *out_count);

#endif
