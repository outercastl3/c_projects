#ifndef SCANNER_LOGIC_H
#define SCANNER_LOGIC_H

#include <pthread.h>
#include <stdint.h>
#include <netinet/in.h>

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

PortResult* scan_ports(const char *ip, uint16_t start_port, uint16_t end_port, int *out_count);

#endif
