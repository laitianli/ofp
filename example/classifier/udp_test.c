/*-
 * Copyright (c) 2014 ENEA Software AB
 * Copyright (c) 2014 Nokia
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <linux/ip.h>

int set_tos(int sock)
{
	unsigned char  service_type = 0xe0 | IPTOS_LOWDELAY | IPTOS_RELIABILITY;
	if(setsockopt(sock, SOL_IP/*IPPROTO_IP*/, IP_TOS, (void *)&service_type, sizeof(service_type)) < 0)
        perror("setsockopt(IP_TOS) failed:");
	
	int optval = 0;
	int optlen = sizeof(optval);
	if(getsockopt(sock, SOL_IP, IP_TOS, (void *)&optval, &optlen) < 0)
	        perror("getsockopt(IP_TOS) failed:");
	else
	        printf("OPTVAL=%x.\n", optval);
	return 0;
}

int main(int argv, char** argc)
{
	char *buffer = "[test_udp] hello classifieraaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.";
	struct sockaddr_in dest_addr = {0};
	int sd = -1;
	int i = 0;
	int count = 5;
	if(argv >= 2 && strlen(argc[1]) >0)
		count = atoi(argc[1]);
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sd == -1) {
		printf("Error: failed to create socket\n");
		exit(0);
	}
	set_tos(sd);
	
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(54321);
	inet_aton("192.168.80.128", &dest_addr.sin_addr.s_addr);
	while(i++ < count) {
		sendto(sd, buffer, strlen(buffer) + 1, 0,
			(const struct sockaddr *)&dest_addr, sizeof(dest_addr));
	}
	close (sd);
	return 0;
}
