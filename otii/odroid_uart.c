#include "odroid_uart.h"
#define FALSE 0
#define TRUE 1


int openport(void){
	int fd = open(DEVICE, O_WRONLY | O_NOCTTY);
	printf("HERE WE GO %d\n",fd);
        if (fd <0){
        	 printf("ERROR in opening %s \n", DEVICE);        
	}
//copy current settings
	struct termios SerialSettings;
	tcgetattr(fd, &SerialSettings);
//baudrate set
	cfsetospeed(&SerialSettings, BAUDRATE);
	cfsetispeed(&SerialSettings, BAUDRATE);
	
//control falgs
	SerialSettings.c_cflag |= CS8;
	SerialSettings.c_cflag |= CSTOPB;
	SerialSettings.c_cflag &= ~PARENB;
	
//input flags
	SerialSettings.c_iflag = 0;
	
//ouput flags
	SerialSettings.c_oflag = 0; 
	
//local flags
	SerialSettings.c_lflag = 0;


	tcflush(fd, TCIFLUSH);

	if ( tcsetattr ( fd, TCSANOW, &SerialSettings ) != 0)
	{
		printf("some error \n");
	}else{
		printf("attribute setting worked \n");
	}

	printf("baudrate speed %u \n", cfgetospeed(&SerialSettings));
	return fd;
}

void send_uart(unsigned char *buffer, int fd){
	int n = write(fd, buffer, strlen(buffer));
	if (n<0){
		printf("Oh no it didnt work \n");
	}else{
		printf("%d bytes written to port \n", n);
	}
}
