#ifndef LINUX_26_30_COMPAT_H
#define LINUX_26_30_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30))

/* <linux/tracepoint.h> */
#ifdef _LINUX_TRACEPOINT_H
#ifndef TP_PROTO
#define TP_PROTO(args...)	TPPROTO(args)
#endif
#ifndef TP_ARGS
#define TP_ARGS(args...)	TPARGS(args)
#endif
#endif

/* <linux/interrupt.h> */
#ifdef _LINUX_INTERRUPT_H
#define IRQ_WAKE_THREAD	(2)
#endif

/* <linux/pm.h> */
#ifdef _LINUX_PM_H
/* How to reorder dpm_list after device_move() */
enum dpm_order {
	DPM_ORDER_NONE,
	DPM_ORDER_DEV_AFTER_PARENT,
	DPM_ORDER_PARENT_BEFORE_DEV,
	DPM_ORDER_DEV_LAST,
};
#endif

/* <linux/device.h> */
#ifdef _DEVICE_H_
static inline void dev_set_uevent_suppress(struct device *dev, int val)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,21))
	dev->uevent_suppress = val;
#endif
}
#endif

/*
 * Print a one-time message (analogous to WARN_ONCE() et al):
 */
#define printk_once(x...) ({			\
	static bool __print_once;		\
						\
	if (!__print_once) {			\
		__print_once = true;		\
		printk(x);			\
	}					\
})

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30)) */

#endif /* LINUX_26_30_COMPAT_H */
