#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

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
	char opt;
	int s_flag = 0, e_flag = 0;


	while ((opt = getopt(argc, argv,"s:e:")) != -1) {
		switch (opt) {
			case 's':
				printf("here is your start %s\n", optarg);
				range_start = parse_port(optarg);
				s_flag = 1;
				break;
			case 'e': 	
				printf("here is your end %s\n", optarg);
				range_end = parse_port(optarg);
				e_flag = 1;
				break;
		}
	}
	printf("Your range start %u\n", (unsigned int)range_start);
	printf("Your range end %u\n", (unsigned int)range_end);
	if (!s_flag || !e_flag) {
		fprintf(stderr, "Both start flag -s and end flag -s should be provided/n");
		exit(EXIT_FAILURE);
	}
	return 0;
}			
