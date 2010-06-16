#ifndef LINUX_26_18_COMPAT_H
#define LINUX_26_18_COMPAT_H

#include <linux/version.h>

/* Compat work for 2.6.18 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18))

/* <linux/kernel.h> */
#ifdef _LINUX_KERNEL_H
#define roundup(x, y)	((((x) + ((y) - 1)) / (y)) * (y))
#endif

/* <linux/skbuff.h> */
#ifdef _LINUX_SKBUFF_H
static inline struct sk_buff *
netdev_alloc_skb(struct net_device *dev, unsigned int length)
{
	struct sk_buff *skb;

	skb = alloc_skb(length + NET_SKB_PAD, GFP_ATOMIC);
	if (likely(skb)) {
		skb_reserve(skb, NET_SKB_PAD);
		skb->dev = dev;
	}
	return skb;
}
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)) */

#endif /* LINUX_26_18_COMPAT_H */
