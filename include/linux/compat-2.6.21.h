#ifndef LINUX_26_21_COMPAT_H
#define LINUX_26_21_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,21))

/* <linux/sysctl.h> */
#ifdef _LINUX_SYSCTL_H
#define register_sysctl_table(table)				\
	({							\
		register_sysctl_table((table), 0);		\
	})
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,21)) */

#endif /* LINUX_26_21_COMPAT_H */
