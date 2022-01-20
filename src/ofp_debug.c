/*-
 * Copyright (c) 2015 ENEA Software AB
 * Copyright (c) 2015 Nokia
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <execinfo.h>
#include "ofpi_debug.h"

#define GSTACK_PATH     "/usr/bin/gstack"
//#define STDIN_FILENO    0
//#define STDOUT_FILENO   1
//#define STDERR_FILENO   2

struct ofp_flag_descript_s ofp_flag_descript[] = {
    {OFP_DEBUG_PRINT_RECV_NIC, "ODP to FP"},
    {OFP_DEBUG_PRINT_SEND_NIC, "FP to ODP"},
    {OFP_DEBUG_PRINT_RECV_KNI, "FP to SP"},
    {OFP_DEBUG_PRINT_SEND_KNI, "SP to ODP"}
};

int ofp_debug_flags = 0;
int ofp_debug_capture_ports = 0;
const char* DEFAULT_BBU_LOG_PATH   = "/opt/bbu/oam/log";
const char* DEFAULT_DEBUG_TXT_FILE_NAME = "ofp_packets.txt";
const char* DEFAULT_DEBUG_PCAP_FILE_NAME = "ofp_packets.pcap";

void ofp_set_debug_flags(int flags)
{
    ofp_debug_flags = flags;
}

int ofp_get_debug_flags(void)
{
    return ofp_debug_flags;
}

void ofp_set_debug_capture_ports(int ports)
{
    ofp_debug_capture_ports = ports;
}

int ofp_get_debug_capture_ports(void)
{
    return ofp_debug_capture_ports;
}

/* add -rdynamic to CFLAGS */
void ofp_backtrace_backtrace(void)
{
    void *array[256];
    int size;
    size = backtrace(array, sizeof(array)/sizeof(array[0]));
    backtrace_symbols_fd(array, size, STDOUT_FILENO);
}

int ofp_backtrace_gstack(void)
{
    pid_t kidpid;
    int pipefd[2];

    if (pipe(pipefd) != 0) {
        return -1;
    }

    kidpid = fork();

    if (kidpid == -1) {
        /* ERROR */
        return -1;
    } else if (kidpid == 0) {
        /* CHILD */
        char parent[16];

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(pipefd[1],STDOUT_FILENO);
        close(STDERR_FILENO);

        snprintf(parent, sizeof(parent), "%d", getppid());
        execle(GSTACK_PATH, "gstack", parent, NULL, NULL);
        exit(1);
    } else {
        /* PARENT */
        char btline[256];
        int kidstat;
        int bytesread;
        int done = 0;

        close(pipefd[1]);

        while (!done) {
            bytesread = read(pipefd[0], btline, sizeof(btline) - 1);

            if (bytesread > 0) {
                btline[bytesread] = 0;
                fprintf(stderr, "%s", btline);
            }
            else if ((bytesread == 0) ||
                     ((errno != EINTR) && (errno != EAGAIN))) {
                done = 1;
            }
        }
        close(pipefd[0]);
        waitpid(kidpid, &kidstat, 0);
        if (kidstat != 0)
            return -1;
    }
    return 0;
}

