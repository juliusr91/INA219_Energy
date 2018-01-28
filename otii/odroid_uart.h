#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BAUDRATE B115200
#define DEVICE "/dev/ttySAC0"

int openport(void);
void send_uart(unsigned char *buffer, int fd);
