#ifndef LINUX_26_19_COMPAT_H
#define LINUX_26_19_COMPAT_H

#include <linux/version.h>

/* Compat work for 2.6.19 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19))

/* <linux/slab.h> */
#ifdef _LINUX_SLAB_H
#define kmem_cache_destroy(cachep)	({ kmem_cache_destroy(cachep); 0; })
#endif

#else /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)) */

typedef _Bool			bool;

/* <linux/stddef.h> */
#ifdef _LINUX_STDDEF_H
enum {
	false = 0,
	true = 1
};
#endif

#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,19)) */

#endif /* LINUX_26_19_COMPAT_H */
