#ifndef LINUX_26_26_COMPAT_H
#define LINUX_26_26_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26))

#ifdef _LINUX_JIFFIES_H	/* <linux/jiffies.h> */
/*
 * These four macros compare jiffies and 'a' for convenience.
 */

/* time_is_before_jiffies(a) return true if a is before jiffies */
#define time_is_before_jiffies(a) time_after(jiffies, a)

/* time_is_after_jiffies(a) return true if a is after jiffies */
#define time_is_after_jiffies(a) time_before(jiffies, a)

/* time_is_before_eq_jiffies(a) return true if a is before or equal to jiffies*/
#define time_is_before_eq_jiffies(a) time_after_eq(jiffies, a)

/* time_is_after_eq_jiffies(a) return true if a is after or equal to jiffies*/
#define time_is_after_eq_jiffies(a) time_before_eq(jiffies, a)
#endif /* _LINUX_JIFFIES_H */

#ifdef _INPUT_H	/* <linux/input.h> */
#define SW_RFKILL_ALL           0x03  /* rfkill master switch, type "any"
					 set = radio enabled */
#endif

#ifdef _DEVICE_H_	/* <linux/device.h> */
extern int dev_set_name(struct device *dev, const char *name, ...)
			__attribute__((format(printf, 2, 3)));

extern struct device *device_create_drvdata(struct class *cls,
	struct device *parent,
	dev_t devt,
	void *drvdata,
	const char *fmt, ...)
__attribute__((format(printf, 5, 6)));

static inline const char *dev_name(struct device *dev)
{
	/* will be changed into kobject_name(&dev->kobj) in the near future */
	return dev->bus_id;
}
#endif

#ifdef _LINUX_KERNEL_H	/* <linux/kernel.h> */
/**
 * clamp - return a value clamped to a given range with strict typechecking
 * @val: current value
 * @min: minimum allowable value
 * @max: maximum allowable value
 *
 * This macro does strict typechecking of min/max to make sure they are of the
 * same type as val.  See the unnecessary pointer comparisons.
 */
#define clamp(val, min, max) ({			\
	typeof(val) __val = (val);		\
	typeof(min) __min = (min);		\
	typeof(max) __max = (max);		\
	(void) (&__val == &__min);		\
	(void) (&__val == &__max);		\
	__val = __val < __min ? __min: __val;	\
	__val > __max ? __max: __val; })

/**
 * clamp_t - return a value clamped to a given range using a given type
 * @type: the type of variable to use
 * @val: current value
 * @min: minimum allowable value
 * @max: maximum allowable value
 *
 * This macro does no typechecking and uses temporary variables of type
 * 'type' to make all the comparisons.
 */
#define clamp_t(type, val, min, max) ({		\
	type __val = (val);			\
	type __min = (min);			\
	type __max = (max);			\
	__val = __val < __min ? __min: __val;	\
	__val > __max ? __max: __val; })

/**
 * clamp_val - return a value clamped to a given range using val's type
 * @val: current value
 * @min: minimum allowable value
 * @max: maximum allowable value
 *
 * This macro does no typechecking and uses temporary variables of whatever
 * type the input argument 'val' is.  This is useful when val is an unsigned
 * type and min and max are literals that will otherwise be assigned a signed
 * integer type.
 */
#define clamp_val(val, min, max) ({             \
	typeof(val) __val = (val);              \
	typeof(val) __min = (min);              \
	typeof(val) __max = (max);              \
	__val = __val < __min ? __min: __val;   \
	__val > __max ? __max: __val; })
#endif /* _LINUX_KERNEL_H */

#ifdef _LINUX_LIST_H	/* <linux/list.h> */
/**
 * list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */
static inline int list_is_singular(const struct list_head *head)
{
	return !list_empty(head) && (head->next == head->prev);
}
#endif

#ifdef __NET_NET_NAMESPACE_H	/* <net/net_namespace.h> */
#ifdef CONFIG_NET_NS
static inline
int net_eq(const struct net *net1, const struct net *net2)
{
	return net1 == net2;
}
#else
static inline
int net_eq(const struct net *net1, const struct net *net2)
{
	return 1;
}
#endif
#endif /* __NET_NET_NAMESPACE_H */

#ifdef _SOCK_H	/* <net/sock.h> */
static inline
struct net *sock_net(const struct sock *sk)
{
#ifdef CONFIG_NET_NS
	return sk->sk_net;
#else
	return &init_net;
#endif
}
#endif

#ifdef _LINUX_NETDEVICE_H	/* <linux/netdevice.h> */
static inline
struct net *dev_net(const struct net_device *dev)
{
#ifdef CONFIG_NET_NS
	/*
	 * compat-wirelss backport note:
	 * For older kernels we may just need to always return init_net,
	 * not sure when we added dev->nd_net.
	 */
	return dev->nd_net;
#else
	return &init_net;
#endif
}

static inline
void dev_net_set(struct net_device *dev, struct net *net)
{
#ifdef CONFIG_NET_NS
	release_net(dev->nd_net);
	dev->nd_net = hold_net(net);
#endif
}
#endif

#ifdef LINUX_ASPM_H		/* <linux/pci-aspm.h> */
#define PCIE_LINK_STATE_L0S    1
#define PCIE_LINK_STATE_L1     2
#define PCIE_LINK_STATE_CLKPM  4

static inline void pci_disable_link_state(struct pci_dev *pdev, int state)
{
}
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)) */

#endif /* LINUX_26_26_COMPAT_H */
