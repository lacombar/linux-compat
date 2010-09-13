#ifndef LINUX_26_17_COMPAT_H
#define LINUX_26_17_COMPAT_H

#include <linux/version.h>

/* Compat work for 2.6.17 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,17))

/* <linux/skbuff.h> */
#ifdef _LINUX_SKBUFF_H
#define NET_SKB_PAD	16
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,17)) */

#endif /* LINUX_26_17_COMPAT_H */
