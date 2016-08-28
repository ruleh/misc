//#!/usr/bin/c
/*
 * Virtual Keyboard -- pretend to press keys
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>

#define KEY_PRESS_DELAY 20000
#define CREATE_DELAY	80000

int create_uhid(int fd) {
	int i;

	fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
	if (fd < 0) {
		return -1;
	}
	ioctl(fd, UI_SET_EVBIT, EV_KEY);
	ioctl(fd, UI_SET_EVBIT, EV_SYN);
	for(i = KEY_ESC; i <= KEY_F24; i++) {
		ioctl(fd,UI_SET_KEYBIT,i);
	}
	struct uinput_user_dev uidev;
	memset (&uidev, 0, sizeof(uidev));
	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "virtual keyboard");
	uidev.id.bustype = BUS_VIRTUAL;
	write(fd, &uidev, sizeof(uidev));
	ioctl(fd, UI_DEV_CREATE);
	return fd;
}

void write_keys(int fd, int normal_key, int special_key) {
	int i;
	struct input_event ev;

	memset(&ev, 0, sizeof(ev));
	for (i = 1; i >= 0; i--) {
		ev.type = EV_KEY;
		ev.code = special_key;
		ev.value = i;
		write(fd, &ev, sizeof(ev));
		ev.type = EV_KEY;
		ev.code = normal_key;
		ev.value = i;
		write(fd, &ev, sizeof(ev));
		ev.type = EV_SYN;
		ev.code = 0;
		ev.value = 0;
		write(fd, &ev, sizeof(ev));
		usleep(KEY_PRESS_DELAY);
	}
	return;
}

long unsigned int read_stdin() {
	char *lsd;
	lsd = 0;
	scanf("%s", &lsd);
	return (long unsigned int) lsd; //might overflow
}

int translate_keys(long unsigned int inpl, int *skey) {
	int inp = 0;
	switch(inpl) {
		/*numbers 0-9*/
		case 48:
			inp = KEY_0;
			break;
		case 49:
			inp = KEY_1;
			break;
		case 50:
			inp = KEY_2;
			break;
		case 51:
			inp = KEY_3;
			break;
		case 52:
			inp = KEY_4;
			break;
		case 53:
			inp = KEY_5;
			break;
		case 54:
			inp = KEY_6;
			break;
		case 55:
			inp = KEY_7;
			break;
		case 56:
			inp = KEY_8;
			break;
		case 57:
			inp = KEY_9;
			break;
		/*a-z in qwerty order*/
		case 113:
			inp = KEY_Q;
			break;
		case 119:
			inp = KEY_W;
			break;
		case 101:
			inp = KEY_E;
			break;
		case 114:
			inp = KEY_R;
			break;
		case 116:
			inp = KEY_T;
			break;
		case 121:
			inp = KEY_Y;
			break;
		case 117:
			inp = KEY_U;
			break;
		case 105:
			inp = KEY_I;
			break;
		case 111:
			inp = KEY_O;
			break;
		case 112:
			inp = KEY_P;
			break;

		case 97:
			inp = KEY_A;
			break;
		case 115:
			inp = KEY_S;
			break;
		case 100:
			inp = KEY_D;
			break;
		case 102:
			inp = KEY_F;
			break;
		case 103:
			inp = KEY_G;
			break;
		case 104:
			inp = KEY_H;
			break;
		case 106:
			inp = KEY_J;
			break;
		case 107:
			inp = KEY_K;
			break;
		case 108:
			inp = KEY_L;
			break;

		case 122:
			inp = KEY_Z;
			break;
		case 120:
			inp = KEY_X;
			break;
		case 99:
			inp = KEY_C;
			break;
		case 118:
			inp = KEY_V;
			break;
		case 98:
			inp = KEY_B;
			break;
		case 110:
			inp = KEY_N;
			break;
		case 109:
			inp = KEY_M;
			break;
		/*special characters*/
		case 4412229:       /*ESC*/
			inp = KEY_ESC;
			break;
		case 1480802626:    /*BACKSPACE*/
			inp = KEY_BACKSPACE;
			break;
		case 28252:         /*\n*/
			inp = KEY_ENTER;
			break;
		case 1163152965:    /*ENTER*/
			inp = KEY_ENTER;
			break;
		case 1128353875:    /*SPACE*/
			inp = KEY_SPACE;
			break;
		case 45:            /*-*/
			inp = KEY_MINUS;
			break;
		case 1431193933:   /*MINUS*/
			inp = KEY_MINUS;
			break;
		case 47:            /*/*/
			inp = KEY_SLASH;
			break;
		case 92:            /*\*/
			inp = KEY_BACKSLASH;
			break;
		case 96:            /*`*/
			inp = KEY_GRAVE;
			break;
		case 4342100:       /*TAB*/
			inp = KEY_TAB;
			break;
		case 20565:         /*UP*/
			inp = KEY_UP;
			break;
		case 1314344772:    /*DOWN*/
			inp = KEY_DOWN;
			break;
		case 1413891404:    /*LEFT*/
			inp = KEY_LEFT;
			break;
		case 1212631378:    /*RIGHT*/
			inp = KEY_RIGHT;
			break;
		/*modifier keys*/
		case 1179207763:    /*SHIFT*/
			*skey = KEY_LEFTSHIFT;		
			break;
		case 1280463939:    /*CTRL*/
			*skey = KEY_LEFTCTRL;
			break;
		case 5524545:       /*ALT*/
			*skey = KEY_LEFTALT;
			break;
	}	
	return inp;
}

int debug(int argn, char *argu, long key_dcode) {
	if (argn >= 2) {
		if (strncmp(argu, "-d", 2) == 0) {
		printf("%lu \n", key_dcode);
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	unsigned int key_dcode;
	int key;
	int fd;
	int skey;


	fd = create_uhid(fd);
	/*if (fd == -1){
		return 1;
	}*/
	usleep(CREATE_DELAY);
	do {
		key = 0;
		skey = 0;	
		key_dcode = read_stdin();
		key = translate_keys(key_dcode, &skey);
		debug(argc, argv[1], key_dcode);
		if (skey != 0) {
			key_dcode = read_stdin();
			key = translate_keys(key_dcode, &skey);
			debug(argc, argv[1], key_dcode);
		}
		if (argc == 3) {
			if (strncmp(argv[2], "-n", 2) == 0) {
				key = 0;
				skey = 0;
			}
		}
		write_keys(fd, key, skey);
	} while (key_dcode != 0);
	ioctl(fd, UI_DEV_DESTROY);
	return 0;
}
