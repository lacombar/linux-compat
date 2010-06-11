#ifndef LINUX_26_19_COMPAT_H
#define LINUX_26_19_COMPAT_H

#include <linux/version.h>

/* Compat work for 2.6.19 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19))

#include <linux/slab.h>

#define kmem_cache_destroy(cachep)	({ kmem_cache_destroy(cachep); 0; })

#else /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)) */

typedef _Bool			bool;
enum {
	false = 0,
	true = 1
};

#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)) */

#endif /* LINUX_26_19_COMPAT_H */
