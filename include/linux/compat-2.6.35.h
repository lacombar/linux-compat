#ifndef LINUX_26_35_COMPAT_H
#define LINUX_26_35_COMPAT_H

#include <linux/version.h>

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))

/* <linux/kernel.h> */
#ifdef _LINUX_KERNEL_H
#define USHRT_MAX      ((u16)(~0U))
#define SHRT_MAX       ((s16)(USHRT_MAX>>1))
#endif

/* <linux/mmc/sdio.h> */
#ifdef MMC_SDIO_H
#define  SDIO_BUS_ECSI		0x20	/* Enable continuous SPI interrupt */
#define  SDIO_BUS_SCSI		0x40	/* Support continuous SPI interrupt */
#endif

/* <linux/netdevice.h> */
#ifdef _LINUX_NETDEVICE_H
#define netdev_hw_addr dev_mc_list
#endif

/* <net/sock.h> */
#ifdef _SOCK_H
static inline wait_queue_head_t *sk_sleep(struct sock *sk)
{
	return sk->sk_sleep;
}
#endif

/* <linux/mmc/sdio_func.h> */
#ifdef _SOCK_H
#define sdio_writeb_readb(func, write_byte, addr, err_ret) sdio_readb(func, addr, err_ret)
#endif

int hex_to_bin(char ch);

extern loff_t noop_llseek(struct file *file, loff_t offset, int origin);

#endif /* (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35)) */

#endif /* LINUX_26_35_COMPAT_H */
