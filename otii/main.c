#include "odroid_uart.h"

int main(){
	int fd = openport();
	send_uart("1 \n", fd);
	send_uart("2 \n", fd);
	send_uart("3 \n", fd);
	send_uart("4 \n", fd);
	close(fd);
}
