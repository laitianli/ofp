#include <stdio.h>
#include <string.h>
#include <odp_api.h>
#include "ofpi.h"
#include <odp_api.h>
#include "ofpi_log.h"
#include "ofpi_cli.h"
#include "ofpi_util.h"

#define UNIT_SIZE 512
#define POS_ARRAY_SIZE 20
#define DATA_BUF_SIZE (UNIT_SIZE * POS_ARRAY_SIZE)

void f_dpdk_log_help(struct cli_conn *conn, const char *s)
{
    (void)s;
    ofp_sendf(conn->fd, "dpdk help               -  show dpdk help info.\r\n");
    ofp_sendf(conn->fd, "dpdk                    -  dump dpdk log info.\r\n");
    ofp_sendf(conn->fd, "dpdk reset              -  reset dpdk log to origin level.\r\n");
    ofp_sendf(conn->fd, "dpdk log all <level>    -  set dpdk all submodule log to <level>, 0 will close log.\r\n");
    ofp_sendf(conn->fd, "dpdk log <logtype> <level>    -  set dpdk <logtype> submodule log to <level>, 0 will close log.\r\n");
    sendcrlf(conn);
}
/* dpdk */
void f_dpdk_log_dump(struct cli_conn *conn, const char *s)
{
    (void)s;
    int i = 0;
    int ret = 0;
    char data_buf[DATA_BUF_SIZE + POS_ARRAY_SIZE + 1] = {0};
    char* pos[POS_ARRAY_SIZE] = {NULL};
    ret = odp_dpdk_dump_log_types(data_buf, sizeof(data_buf) - 1, 
                                    pos, POS_ARRAY_SIZE, UNIT_SIZE);
    if(ret <= 0) {
        ofp_sendf(conn->fd, "[Error] odp_dpdk_dump_log_types return val = %d\n", ret);     
        goto end;
    }
    while (pos[i]) {
        ofp_sendf(conn->fd, "%s\r\n", pos[i]);
        i++;
    }
end:    
    sendcrlf(conn);
}
/* dpdk log <logtype>/all <level> */
void f_dpdk_log(struct cli_conn *conn, const char *s)
{
	const char *logtype = NULL;
	int logtype_len = 0;
	const char *level = NULL;
    char *str = strdup(s);
    char* tmp_str = str;
    if (!str) {
        printf("[Error] input error!\n");
        return ;
    }
	logtype = str;
	while ((*str != ' ') && (*str != 0)) {
		str++;
    }
    if (*str) {
        logtype_len = str - logtype;
        *str = '\0';
        str++;
    }    

	if (*str != 0) {
		while (*str == ' ')
			str++;
		if (*str != 0)
			level  = str;
	}
    
    int ret = odp_dpdk_set_log(logtype, logtype_len, strtol(level, NULL, 0));
    if (strtol(level, NULL, 0) == 0 && !strncmp(logtype, "all", logtype_len)) {
        ofp_sendf(conn->fd, "disable dpdk log %s\r\n", ret == 1 ? "success.":"failed!");
    }
    else {
        ofp_sendf(conn->fd, "set logtype: %s , level: %d %s\r\n", 
                        logtype, strtol(level, NULL, 0), ret == 1 ? "success.":"failed!");
    }
    sendcrlf(conn);
    free(tmp_str);
}

/* dpdk log reset */
void f_dpdk_log_reset(struct cli_conn *conn, const char *s)
{
    (void)s;
    int ret = 0;
    ret = odp_dpdk_reset_log();
    ofp_sendf(conn->fd, "reset dpdk log %s\r\n", ret == 1 ? "success.":"failed!");
    sendcrlf(conn);
}



