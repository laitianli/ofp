#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <odp_api.h>
#include "ofpi.h"
#include <odp_api.h>
#include "ofpi_log.h"
#include "ofpi_cli.h"
#include "ofpi_util.h"

const char* log_level_string[ODP_LOG_LEVEL_MAX] = 
{
    "error",
    "unimplemented",
    "abort",
    "debug",
    "print"
};
static const char* log_level_to_string(int level) 
{
    switch (level) {
    case ODP_LOG_ERR:
    case ODP_LOG_UNIMPLEMENTED:
    case ODP_LOG_ABORT:
    case ODP_LOG_DBG:
    case ODP_LOG_PRINT:
        return log_level_string[level];
    default:
        return "unknow";
    }
}

void f_odp_log_help(struct cli_conn *conn, const char *s)
{
    (void)s;
    ofp_sendf(conn->fd, "odp dump\r\n");
    ofp_sendf(conn->fd, "odp help\r\n");
    ofp_sendf(conn->fd, "odp reset\r\n");
    ofp_sendf(conn->fd, "odp log <level>\r\n");
    sendcrlf(conn);
}

/* odp dump */
void f_odp_log_dump(struct cli_conn *conn, const char *s)
{
    (void)s;
    int i = 0;
    int len = 0;
    int log_level = odp_get_log();
    char buf[1024] = {0};
    len = snprintf(buf, sizeof(buf), "odp log level: \r\n");
    for (i = 0; i < ODP_LOG_LEVEL_MAX; i++) {
        len += snprintf(buf + len, sizeof(buf) - len, "\t%d - %s\r\n", 
            i, log_level_to_string(i));
    }
    len += snprintf(buf + len, sizeof(buf) - len, "->odp log curr level: %d - %s\r\n",
            log_level, log_level_to_string(log_level));
    ofp_sendf(conn->fd, "%s", buf);
    sendcrlf(conn);
}
/* odp log <level> */
void f_odp_log(struct cli_conn *conn, const char *s)
{
    (void)s;
    int log_level = 0;
    log_level = strtol(s, NULL, 0);
    if (log_level < ODP_LOG_ERR)
        log_level = ODP_LOG_ERR;
    if (log_level >= ODP_LOG_LEVEL_MAX)
        log_level = ODP_LOG_LEVEL_MAX - 1;
    odp_set_log(log_level);
    ofp_sendf(conn->fd, "set odp log level: %d (%s) success.\r\n", log_level, 
            log_level_to_string(log_level));
    sendcrlf(conn);
}

/* odp log reset */
void f_odp_log_reset(struct cli_conn *conn, const char *s)
{
    (void)s;
    int log_level = 0;
    odp_reset_log();
    log_level = odp_get_log();
    ofp_sendf(conn->fd, "reset odp log level to %d (%s) success.\r\n", log_level, 
            log_level_to_string(log_level));
    sendcrlf(conn);
}


