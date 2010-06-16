#ifndef LINUX_26_20_COMPAT_H
#define LINUX_26_20_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20))

/* <linux/workqueue.h> */
#ifdef _LINUX_WORKQUEUE_H
/* `struct work_struct' and `struct delayed_work' are field compatible */
#define delayed_work work_struct
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20)) */

#endif /* LINUX_26_20_COMPAT_H */
