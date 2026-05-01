#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "scanner_logic.h"

uint16_t parse_port(const char *arg) {
	char *endptr;
	long port = strtol(arg, &endptr, 10);

	if (*endptr != '\0') {
		fprintf(stderr, "Invalid port: %s\n", arg);
		exit(EXIT_FAILURE);
	}
	
	if (port < 0 || port > 65535) {
		printf("Port out of the range: %ld\n", port);
		exit(EXIT_FAILURE);
	}
	return (uint16_t)port; 
}

int main(int argc, char* argv[]) {
	uint16_t range_start = 0;
	uint16_t range_end = 0;
	char *ip = NULL;
	int opt;
	int s_flag = 0, e_flag = 0, i_flag = 0;


	while ((opt = getopt(argc, argv,"s:e:i:")) != -1) {
		switch (opt) {
			case 's':
				range_start = parse_port(optarg);
				s_flag = 1;
				break;
			case 'e': 	
				range_end = parse_port(optarg);
				e_flag = 1;
				break;
			case 'i':
				ip = optarg;
				i_flag = 1;
				break;
		}
	}
	
	if (!s_flag || !e_flag || !i_flag) {
		fprintf(stderr, "Usage: %s -s <start> -e <end> -i <ip>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (range_start > range_end) {
		uint16_t tmp = range_start;
		range_start = range_end;
		range_end = tmp;
	}

	int count = 0;
	PortResult *results = scan_ports(ip, range_start, range_end, &count);
	if (results) {
		for (int i = 0; i < count; i++) {
			uint16_t port = results[i].port;
			int status = results[i].status;

			if (status == 0) {
				printf("Port %u is open\n", port);
			} else if (status == ECONNREFUSED) {
				printf("Port %u is closed\n", port);
			} else if (status == ETIMEDOUT) {
				printf("Port %u is filtered\n", port);
			} else {
				printf("Port %u error: %s\n", port, strerror(status));
			}
		}
		free(results);
	}
}
