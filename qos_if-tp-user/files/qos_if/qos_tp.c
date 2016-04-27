/*
 * Copyright (c) 2016 Renesas Electronics Corporation
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include "qos_tp.h"

static void exec_interactive(void);
static void exec_noninteractive(int argc, char *argv[]);

static int exec_help(int argc, char *argv[]);
static int exec_status(int argc, char *argv[]);
static int exec_set_all(int argc, char *argv[]);
static int exec_set_ip(int argc, char *argv[]);
static int exec_switch_membank(int argc, char *argv[]);
static int exec_start(int argc, char *argv[]);
static int exec_stop(int argc, char *argv[]);
static int exec_get_ip(int argc, char *argv[]);
static int exec_exit(int argc, char *argv[]);

static void get_input(char *buf, unsigned int size);
static int cmd_convert(char *cmd);

struct cmd_info {
	char *cmd_str;
	int cmd_type;
};
struct cmd_info c_info[] = {
	{"help", CMD_HELP},
	{"setall", CMD_SET_ALL},
	{"switch", CMD_SWITCH_MEMBANK},
	{"exit", CMD_EXIT},
};

typedef int (*cmd_t)(int argc, char *argv[]);

static const cmd_t cmd_funcs[] = {
	[CMD_HELP] = exec_help,
	[CMD_SET_ALL] = exec_set_all,
	[CMD_SWITCH_MEMBANK] = exec_switch_membank,
	[CMD_EXIT] = exec_exit
};

static unsigned long qos_handle;
static int cmd_loop = 1;

int main(int argc, char *argv[])
{
	int ret = 0;

	ret = qos_lib_init(&qos_handle);
	if (ret) {
		printf("qos open error\n");
		return ret;
	}

	if (argc == 1)
		exec_interactive();
	else if (argc > 1)
		exec_noninteractive(argc - 1, argv + 1);
	else
		printf("unexpected parameter error. exit...");

	ret = qos_lib_quit(qos_handle);
	if (ret != 0) {
		printf("qos close error\n");
		return ret;
	}

	return 0;
}

static void exec_interactive(void)
{
	unsigned char cmd[256] = {};
	int argc = 0;
	char *argv[256] = {};
	int cmd_type;
	int ret = 0;

	while (cmd_loop) {
		argc = 0;

		printf(">> ");

		get_input(cmd, 256);

		argv[argc] = strtok(cmd, " ");
		while (argv[argc] != NULL) {
			argc++;
			argv[argc] = strtok(NULL, " ");
		}

		if (argc < 1) {
			printf("invalid command!\n");
			continue;
		}

		cmd_type = cmd_convert(argv[0]);
		if (cmd_type < CMD_HELP || CMD_MAX <= cmd_type) {
			printf("invalid command!\n");
			continue;
		}

		ret = cmd_funcs[cmd_type](argc, argv);
		if (ret != 0) {
			printf("unexpected error!\n");
			continue;
		}
	}
}
static void exec_noninteractive(int argc, char *argv[])
{
	int cmd_type;
	int ret = 0;

	cmd_type = cmd_convert(argv[0]);
	if (cmd_type < CMD_HELP || CMD_MAX <= cmd_type) {
		printf("invalid command!\n");
		return;
	}

	ret = cmd_funcs[cmd_type](argc, argv);
	if (ret != 0) {
		printf("unexpected error!\n");
		return;
	}
}

static int exec_help(int argc, char *argv[])
{
	printf("Command Usage:\n");
	printf("\thelp\t: Display this usage.\n");
	printf("\tsetall\t: Set All FIX and BE values into unused membank using ioctl(QOS_IOCTL_SET_ALL_QOS).\n");
	printf("\tswitch\t: Switch membank using ioctl(QOS_IOCTL_SWITCH_MEMBANK).\n");
	printf("\texit\t: Exit from this application.\n");

	return 0;
}

static int exec_set_all(int argc, char *argv[])
{
	unsigned char read_file[64] = {0};

	if (argc == 1) {
		printf("Please input parameters...\n");
		printf("Usage : [csv file path]\n");
		printf("ex) setall >> csvdata.csv\n");
		printf("setall >> ");
		get_input(read_file, 64);
	} else if (argc == 2) {
		strncpy(read_file, argv[1], 64);
	} else {
		printf("parameter error!\n");
		return -1;
	}

	return qos_lib_setall_from_csv(qos_handle, read_file);
}

static int exec_switch_membank(int argc, char *argv[])
{
	return qos_lib_switch(qos_handle);
}

static int exec_exit(int argc, char *argv[])
{
	cmd_loop = 0;

	return 0;
}

static void get_input(char *buf, unsigned int size)
{
	char *p;

	fgets(buf, size, stdin);
	p = strchr(buf, '\n');
	if (p)
		*p = '\0';

}

static int cmd_convert(char *cmd)
{
	int i;

	for (i = 0 ; i < CMD_MAX ; i++) {
		if (strcmp(cmd, c_info[i].cmd_str) == 0)
			break;
	}

	return i;
}
