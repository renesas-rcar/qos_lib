/*
 * Copyright (c) 2016 Renesas Electronics Corporation
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef __QOS_H__
#define __QOS_H__

#include <linux/types.h>
#include <asm/ioctl.h>

#define QOS_DEVICE_NAME		"qos"
#define QOS_VERSION		"2.00"

enum {
	QOS_TYPE_FIX = 0,
	QOS_TYPE_BE = 1,
	QOS_TYPE_TRAFFIC_MONITOR = 2,
	QOS_TYPE_MAX
};

struct qos_ioc_get_status_param {
	__u8 statqen;
	__u8 exe_membank;
};

struct qos_ioc_set_all_qos_param {
	__u8 *fix_qos;
	__u8 *be_qos;
};


struct qos_ioc_set_ip_qos_param {
	__u8 qos_type;
	__u16 master_id;
	__u64 qos;
};

struct qos_ioc_get_ip_qos_param {
	__u8 qos_type;
	__u16 master_id;
	__u8 membank;
	__u64 qos;
};

#define QOS_IOCTL_BASE			'q'
#define QOS_IO(nr)			_IO(QOS_IOCTL_BASE, nr)
#define QOS_IOR(nr, type)		_IOR(QOS_IOCTL_BASE, nr, type)
#define QOS_IOW(nr, type)		_IOW(QOS_IOCTL_BASE, nr, type)
#define QOS_IOWR(nr, type)		_IOWR(QOS_IOCTL_BASE, nr, type)

#define QOS_IOCTL_SET_ALL_QOS	\
		QOS_IOW(0x01, struct qos_ioc_set_all_qos_param)
#define QOS_IOCTL_SWITCH_MEMBANK	\
		QOS_IO(0x03)

#define QOS_IOCTL_MAX_NR		0x04

#endif /* __QOS_H__ */
