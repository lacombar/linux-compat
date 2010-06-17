#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24))

#ifndef __NET_NET_NAMESPACE_H
#define __NET_NET_NAMESPACE_H

#include <linux/list.h>
#include <linux/workqueue.h>

#include <asm/atomic.h>

struct proc_dir_entry;
struct net_device;
struct net {
	atomic_t		count;		/* To decided when the network
						 *  namespace should be freed.
						 */
	atomic_t		use_count;	/* To track references we
						 * destroy on demand
						 */
	struct list_head	list;		/* list of network namespaces */
	struct work_struct	work;		/* work struct for freeing */

	struct proc_dir_entry 	*proc_net;
	struct proc_dir_entry 	*proc_net_stat;
	struct proc_dir_entry 	*proc_net_root;

	struct net_device       *loopback_dev;          /* The loopback */

	struct list_head 	dev_base_head;
	struct hlist_head 	*dev_name_head;
	struct hlist_head	*dev_index_head;
};

#ifdef CONFIG_NET
/* Init's network namespace */
extern struct net init_net;
#define INIT_NET_NS(net_ns) .net_ns = &init_net,
#else
#define INIT_NET_NS(net_ns)
#endif

#endif /* __NET_NET_NAMESPACE_H */

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)) */
