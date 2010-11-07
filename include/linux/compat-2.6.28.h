#ifndef LINUX_26_28_COMPAT_H
#define LINUX_26_28_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28))

/* <linux/if_ether.h> */
#ifdef _LINUX_IF_ETHER_H
#ifndef ETH_P_PAE
#define ETH_P_PAE 0x888E      /* Port Access Entity (IEEE 802.1X) */
#endif
#endif

/* <asm-generic/bug.h> */
#ifdef _ASM_GENERIC_BUG_H 
#ifndef WARN_ONCE
#define WARN_ONCE(condition, format...) ({                      \
	static int __warned;                                    \
	int __ret_warn_once = !!(condition);                    \
								\
	if (unlikely(__ret_warn_once))                          \
		if (WARN(!__warned, format))                    \
			__warned = 1;                           \
	unlikely(__ret_warn_once);                              \
})
#endif
#endif

/* <pcmcia/ds.h> */
#ifdef _LINUX_DS_H
#if defined(CONFIG_PCMCIA) || defined(CONFIG_PCMCIA_MODULE)

#ifdef pcmcia_parse_tuple
#undef pcmcia_parse_tuple
#define pcmcia_parse_tuple(tuple, parse) pccard_parse_tuple(tuple, parse)
#endif

/* loop CIS entries for valid configuration */
int pcmcia_loop_config(struct pcmcia_device *p_dev,
		       int	(*conf_check)	(struct pcmcia_device *p_dev,
						 cistpl_cftable_entry_t *cfg,
						 cistpl_cftable_entry_t *dflt,
						 unsigned int vcc,
						 void *priv_data),
		       void *priv_data);

#endif /* CONFIG_PCMCIA */
#endif

/* <linux/usb.h> */
#ifdef __LINUX_USB_H
/* USB anchors were added as of 2.6.23 */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,23))

#if defined(CONFIG_USB) || defined(CONFIG_USB_MODULE)
#if 0
extern void usb_poison_urb(struct urb *urb);
#endif
extern void usb_unpoison_urb(struct urb *urb);

#if 0
extern void usb_poison_anchored_urbs(struct usb_anchor *anchor);
#endif

extern int usb_anchor_empty(struct usb_anchor *anchor);
#endif /* CONFIG_USB */
#endif
#endif /* __LINUX_USB_H */

/* <linux/pci.h> */
#ifdef LINUX_PCI_H
void __iomem *pci_ioremap_bar(struct pci_dev *pdev, int bar);
#endif

/* <linux/skbuff.h> */
#ifdef _LINUX_SKBUFF_H
/**
 *	skb_queue_is_last - check if skb is the last entry in the queue
 *	@list: queue head
 *	@skb: buffer
 *
 *	Returns true if @skb is the last buffer on the list.
 */
static inline bool skb_queue_is_last(const struct sk_buff_head *list,
				     const struct sk_buff *skb)
{
	return (skb->next == (struct sk_buff *) list);
}

/**
 *	skb_queue_next - return the next packet in the queue
 *	@list: queue head
 *	@skb: current buffer
 *
 *	Return the next packet in @list after @skb.  It is only valid to
 *	call this if skb_queue_is_last() evaluates to false.
 */
static inline struct sk_buff *skb_queue_next(const struct sk_buff_head *list,
                                             const struct sk_buff *skb)
{
	/* This BUG_ON may seem severe, but if we just return then we
	 * are going to dereference garbage.
	 */
	BUG_ON(skb_queue_is_last(list, skb));
	return skb->next;
}

/**
 *	__skb_queue_head_init - initialize non-spinlock portions of sk_buff_head
 *	@list: queue to initialize
 *
 *	This initializes only the list and queue length aspects of
 *	an sk_buff_head object.  This allows to initialize the list
 *	aspects of an sk_buff_head without reinitializing things like
 *	the spinlock.  It can also be used for on-stack sk_buff_head
 *	objects where the spinlock is known to not be used.
 */
static inline void __skb_queue_head_init(struct sk_buff_head *list)
{
	list->prev = list->next = (struct sk_buff *)list;
	list->qlen = 0;
}

static inline void __skb_queue_splice(const struct sk_buff_head *list,
				      struct sk_buff *prev,
				      struct sk_buff *next)
{
	struct sk_buff *first = list->next;
	struct sk_buff *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

/**
 *	skb_queue_splice - join two skb lists, this is designed for stacks
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 */
static inline void skb_queue_splice(const struct sk_buff_head *list,
				    struct sk_buff_head *head)
{
	if (!skb_queue_empty(list)) {
		__skb_queue_splice(list, (struct sk_buff *) head, head->next);
		head->qlen += list->qlen;
	}
}

/**
 *	skb_queue_splice - join two skb lists and reinitialise the emptied list
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 *
 *	The list at @list is reinitialised
 */
static inline void skb_queue_splice_init(struct sk_buff_head *list,
					 struct sk_buff_head *head)
{
	if (!skb_queue_empty(list)) {
		__skb_queue_splice(list, (struct sk_buff *) head, head->next);
		head->qlen += list->qlen;
		__skb_queue_head_init(list);
	}
}

/**
 *	skb_queue_splice_tail - join two skb lists and reinitialise the emptied list
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 *
 *	Each of the lists is a queue.
 *	The list at @list is reinitialised
 */
static inline void skb_queue_splice_tail_init(struct sk_buff_head *list,
					      struct sk_buff_head *head)
{
	if (!skb_queue_empty(list)) {
		__skb_queue_splice(list, head->prev, (struct sk_buff *) head);
		head->qlen += list->qlen;
		__skb_queue_head_init(list);
	}
} /* From include/linux/skbuff.h */

/**
 *	skb_queue_splice_tail - join two skb lists, each list being a queue
 *	@list: the new list to add
 *	@head: the place to add it in the first list
 */
static inline void skb_queue_splice_tail(const struct sk_buff_head *list,
					 struct sk_buff_head *head)
{
	if (!skb_queue_empty(list)) {
		__skb_queue_splice(list, head->prev, (struct sk_buff *) head);
		head->qlen += list->qlen;
	}
}

extern void skb_add_rx_frag(struct sk_buff *skb, int i, struct page *page,
			    int off, int size);
#endif /* _LINUX_SKBUFF_H */

/* <linux/timer.h> */
#ifdef _LINUX_TIMER_H
/* openSuse includes round_jiffies_up in it's kernel 2.6.27.
 * This is needed to prevent conflicts with the openSuse definition.
 */
#define round_jiffies_up backport_round_jiffies_up

unsigned long round_jiffies_up(unsigned long j);
#endif

/* <linux/wait.h> */
#ifdef _LINUX_WAIT_H	
#define wake_up_interruptible_poll(x, m)			\
	__wake_up(x, TASK_INTERRUPTIBLE, 1, (void *) (m))
#endif

/* linux/tty.h */
#ifdef _LINUX_TTY_H	
extern int n_tty_ioctl_helper(struct tty_struct *tty, struct file *file,
		       unsigned int cmd, unsigned long arg);
#endif

/* <linux/ieee80211.h> */
#ifdef LINUX_IEEE80211_H
#define IEEE80211_HT_CAP_DSSSCCK40		0x1000
#endif

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,28)) */

#endif /* LINUX_26_28_COMPAT_H */
