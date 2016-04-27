/*
 * Copyright (c) 2016 Renesas Electronics Corporation
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#ifndef __QOS_H__
#define __QOS_H__

int qos_lib_init(unsigned long *handle);
int qos_lib_quit(unsigned long handle);
int qos_lib_setall_from_csv(unsigned long handle, char *read_file);
int qos_lib_switch(unsigned long handle);

#endif /* __QOS_H__ */
