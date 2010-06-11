#ifndef LINUX_26_18_COMPAT_H
#define LINUX_26_18_COMPAT_H

#include <linux/version.h>

/* Compat work for 2.6.18 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18))

#define roundup(x, y)	((((x) + ((y) - 1)) / (y)) * (y))

struct hwrng
{
	const char *name;
	int (*init)(struct hwrng *rng);
	void (*cleanup)(struct hwrng *rng);
	int (*data_present)(struct hwrng *rng);
	int (*data_read)(struct hwrng *rng, u32 *data);
	unsigned long priv;

	/* internal. */
	struct list_head list;
};

static inline int
hwrng_register(struct hwrng *rng)
{
	return -ENOSYS;
}

static void
hwrng_unregister(struct hwrng *rng)
{
}

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)) */

#endif /* LINUX_26_18_COMPAT_H */
