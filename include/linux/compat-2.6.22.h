#ifndef LINUX_26_22_COMPAT_H
#define LINUX_26_22_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22))

/* <linux/netdevice.h> */
#ifdef _LINUX_NETDEVICE_H
#ifdef CONFIG_AX25
#error "Compat reuses the AX.25 pointer so that may not be enabled!"
#endif

#define ieee80211_ptr ax25_ptr
#endif

/* <linux/skbuff.h> */
#ifdef _LINUX_SKBUFF_H
static inline unsigned char *skb_mac_header(const struct sk_buff *skb)
{
	return skb->mac.raw;
}

static inline void skb_set_mac_header(struct sk_buff *skb, int offset)
{
	skb->mac.raw = skb->data + offset;
}

static inline void skb_reset_mac_header(struct sk_buff *skb)
{
	skb->mac.raw = skb->data;
}

static inline void skb_reset_network_header(struct sk_buff *skb)
{
	skb->nh.raw = skb->data;
}

static inline void skb_set_network_header(struct sk_buff *skb, int offset)
{
	skb->nh.raw = skb->data + offset;
}

static inline void skb_set_transport_header(struct sk_buff *skb, int offset)
{
	skb->h.raw = skb->data + offset;
}

static inline unsigned char *skb_transport_header(const struct sk_buff *skb)
{
	return skb->h.raw;
}

static inline unsigned char *skb_network_header(const struct sk_buff *skb)
{
	return skb->nh.raw;
}

static inline unsigned char *skb_tail_pointer(const struct sk_buff *skb)
{
	return skb->tail;
}

static inline void skb_copy_from_linear_data(const struct sk_buff *skb,
					     void *to,
					     const unsigned int len)
{
	memcpy(to, skb->data, len);
}

static inline void skb_copy_from_linear_data_offset(const struct sk_buff *skb,
						    const int offset, void *to,
						    const unsigned int len)
{
	memcpy(to, skb->data + offset, len);
}
#endif /* _LINUX_SKBUFF_H */

/* <linux/ip.h> */
#ifdef _LINUX_IP_H
static inline struct iphdr *ip_hdr(const struct sk_buff *skb)
{
	return (struct iphdr *)skb_network_header(skb);
}
#endif

/* <net/ip.h> */
#ifdef _IP_H
static inline unsigned int ip_hdrlen(const struct sk_buff *skb)
{
	return ip_hdr(skb)->ihl * 4;
}
#endif

/* <linux/tcp.h> */
#ifdef _LINUX_TCP_H
static inline struct tcphdr *tcp_hdr(const struct sk_buff *skb)
{
	return (struct tcphdr *)skb_transport_header(skb);
}

static inline unsigned int tcp_hdrlen(const struct sk_buff *skb)
{
	return tcp_hdr(skb)->doff * 4;
}

static inline unsigned int tcp_optlen(const struct sk_buff *skb)
{
	return (tcp_hdr(skb)->doff - 5) * 4;
}
#endif

/* <linux/compiler.h> */
#ifdef __LINUX_COMPILER_H
#if defined(__GNUC__)
#define __maybe_unused		__attribute__((unused))
#define uninitialized_var(x)	x = x
#endif

#ifndef __maybe_unused
#define __maybe_unused		/* unimplemented */
#endif

#ifndef uninitialized_var
#define uninitialized_var(x)	x
#endif
#endif /* __LINUX_COMPILER_H */

/* <net/netlink.h> */
#ifdef __NET_NETLINK_H
/* This will lead to very weird behaviour... */
#define NLA_BINARY NLA_STRING
#endif

/* <linux/list.h> */
#ifdef _LINUX_LIST_H
#define list_first_entry(ptr, type, member) \
        list_entry((ptr)->next, type, member)
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)) */

#endif /* LINUX_26_22_COMPAT_H */
