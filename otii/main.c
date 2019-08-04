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
//quick test script to test the UART sending
//shows how to use it
int main(){
	int fd = openport();
	send_uart("1 \n", fd);
	send_uart("2 \n", fd);
	send_uart("3 \n", fd);
	send_uart("4 \n", fd);
	close(fd);
}
