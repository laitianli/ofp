/* Copyright (c) 2016, ENEA Software AB
 * Copyright (c) 2016, Nokia
 * All rights reserved.
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */
#ifndef __NETWRAP_ERRNO_H__
#define __NETWRAP_ERRNO_H__

#include <errno.h>
#include "ofp_errno.h"

#define NETWRAP_ERRNO(x) ((x >= 0 && x <= OFP_ELAST) ?  netwrap_errno[x] : x)

static const int netwrap_errno[OFP_ELAST + 1] = {
0,
EPERM,            /* OFP_EPERM        1 */
ENOENT,        /* OFP_ENOENT        2 */
ESRCH,            /* OFP_ESRCH        3 */
EINTR,            /* OFP_EINTR        4 */
EIO,            /* OFP_EIO        5 */
ENXIO,            /* OFP_ENXIO        6 */
E2BIG,            /* OFP_E2BIG        7 */
ENOEXEC,        /* OFP_ENOEXEC        8 */
EBADF,            /* OFP_EBADF        9 */

ECHILD,        /* OFP_ECHILD        10 */
EDEADLK,        /* OFP_EDEADLK        11 */
ENOMEM,        /* OFP_ENOMEM        12 */
EACCES,        /* OFP_EACCES        13 */
EFAULT,        /* OFP_EFAULT        14 */
ENOTBLK,        /* OFP_ENOTBLK        15 */
EBUSY,            /* OFP_EBUSY        16 */
EEXIST,        /* OFP_EEXIST        17 */
EXDEV,            /* OFP_EXDEV        18 */
ENODEV,        /* OFP_ENODEV        19 */

ENOTDIR,        /* OFP_ENOTDIR        20 */
EISDIR,        /* OFP_EISDIR        21 */
EINVAL,        /* OFP_EINVAL        22 */
ENFILE,        /* OFP_ENFILE        23 */
EMFILE,        /* OFP_EMFILE        24 */
ENOTTY,        /* OFP_ENOTTY        25 */
ETXTBSY,        /* OFP_ETXTBSY        26 */
EFBIG,            /* OFP_EFBIG        27 */
ENOSPC,        /* OFP_ENOSPC        28 */
ESPIPE,        /* OFP_ESPIPE        29 */


EROFS,            /* OFP_EROFS        30 */
EMLINK,        /* OFP_EMLINK        31 */
EPIPE,            /* OFP_EPIPE        32 */
/* math software */
EDOM,            /* OFP_EDOM        33 */
ERANGE,        /* OFP_ERANGE        34 */
/* non-blocking and interrupt i/o */
EAGAIN,        /* OFP_EAGAIN        35 */

EINPROGRESS,        /* OFP_EINPROGRESS    36 */
EALREADY,        /* OFP_EALREADY        37 */

/* ipc/network software -- argument errors */
ENOTSOCK,        /* OFP_ENOTSOCK        38 */
EDESTADDRREQ,        /* OFP_EDESTADDRREQ    39 */

EMSGSIZE,        /* OFP_EMSGSIZE        40 */
EPROTOTYPE,        /* OFP_EPROTOTYPE    41 */
ENOPROTOOPT,        /* OFP_ENOPROTOOPT    42 */
EPROTONOSUPPORT,    /* OFP_EPROTONOSUPPORT    43 */
ESOCKTNOSUPPORT,    /* OFP_ESOCKTNOSUPPORT    44 */
EOPNOTSUPP,        /* OFP_EOPNOTSUPP    45 */
EPFNOSUPPORT,        /* OFP_EPFNOSUPPORT    46 */
EAFNOSUPPORT,        /* OFP_EAFNOSUPPORT    47 */
EADDRINUSE,        /* OFP_EADDRINUSE    48 */
EADDRNOTAVAIL,        /* OFP_EADDRNOTAVAIL    49 */


/* ipc/network software -- operational errors */
ENETDOWN,        /* OFP_ENETDOWN        50 */
ENETUNREACH,        /* OFP_ENETUNREACH    51 */
ENETRESET,        /* OFP_ENETRESET    52 */
ECONNABORTED,        /* OFP_ECONNABORTED    53 */
ECONNRESET,        /* OFP_ECONNRESET    54 */
ENOBUFS,        /* OFP_ENOBUFS        55 */
EISCONN,        /* OFP_EISCONN        56 */
ENOTCONN,        /* OFP_ENOTCONN        57 */
ESHUTDOWN,        /* OFP_ESHUTDOWN    58 */
ETOOMANYREFS,        /* OFP_ETOOMANYREFS    59 */


ETIMEDOUT,        /* OFP_ETIMEDOUT    60 */
ECONNREFUSED,        /* OFP_ECONNREFUSED    61 */
ELOOP,            /* OFP_ELOOP        62 */
ENAMETOOLONG,        /* OFP_ENAMETOOLONG    63 */
EHOSTDOWN,        /* OFP_EHOSTDOWN    64 */
EHOSTUNREACH,        /* EHOSTUNREACH        65 */
ENOTEMPTY,        /* OFP_ENOTEMPTY    66 */

/* quotas & mush */
EINVAL,        /* OFP_EPROCLIM        67 */
EUSERS,        /* OFP_EUSERS        68 */
EDQUOT,        /* OFP_EDQUOT        69 */


/* Network File System */
ESTALE,        /* OFP_ESTALE        70 */
EREMOTE,        /* OFP_EREMOTE        71 */
EINVAL,        /* OFP_EBADRPC        72 */
EINVAL,        /* OFP_ERPCMISMATCH    73 */
EINVAL,        /* OFP_EPROGUNAVAIL    74 */
EINVAL,        /* OFP_EPROGMISMATCH    75 */
EINVAL,        /* OFP_EPROCUNAVAIL    76 */
ENOLCK,        /* OFP_ENOLCK        77 */
ENOSYS,        /* OFP_ENOSYS        78 */
EINVAL,        /* OFP_EFTYPE        79 */


EINVAL,        /* OFP_EAUTH        80 */
EINVAL,        /* OFP_ENEEDAUTH    81 */
EIDRM,            /* OFP_EIDRM        82 */
ENOMSG,        /* OFP_ENOMSG        83 */
EOVERFLOW,        /* OFP_EOVERFLOW    84 */
ECANCELED,        /* OFP_ECANCELED    85 */
EILSEQ,        /* OFP_EILSEQ        86 */
EINVAL,        /* OFP_ENOATTR        87 */
EINVAL,        /* OFP_EDOOFUS        88 */
EBADMSG,        /* OFP_EBADMSG        89 */

EMULTIHOP,        /* OFP_EMULTIHOP    90 */
ENOLINK,        /* OFP_ENOLINK        91 */
EPROTO,        /* OFP_EPROTO        92 */
EINVAL,        /* OFP_ENOTCAPABLE    93 */
EINVAL            /* OFP_ECAPMODE        94 */
};

#endif /*__NETWRAP_ERRNO_H__*/
