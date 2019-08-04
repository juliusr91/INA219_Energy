/*
 Copyright (C) 2019 Julius Roeder

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "odroid_uart.h"

//communicate between Odroid-XU4 and Otii over UART via pin 8 on CON10 as shown here: https://odroid.com/dokuwiki/doku.php?id=en:xu4_hardware
//connect the TX pin (Pin 8) to RX on the Otii and connect the ground
//baudrate is set to 115200 - make sure this is the same on the Otii and make sure the Otii shows the logs in the main window.
//the UART messages are also displayed in the CSV files that can be exported by the Otii software.

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
