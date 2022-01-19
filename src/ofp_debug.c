/*-
 * Copyright (c) 2015 ENEA Software AB
 * Copyright (c) 2015 Nokia
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */
#include "ofpi_debug.h"

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
