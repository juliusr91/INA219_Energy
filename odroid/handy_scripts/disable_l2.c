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


#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[]) {

    uint32_t res = 0;
    __asm(
        "MRC p15, 0, <Rd>, c1, c0, 0" // read Control Register
        : [result] "=r" (res)
    );

    printf("%d\n", res);

    return 0;
}
