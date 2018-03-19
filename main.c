#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <progbase/console.h>
#include <console.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/port.h"



#define __USE_XOPEN_EXTENDED
#define error_message(FMT, ...) printf(FMT, __VA_ARGS__)


int main(void) {
    const char * portname = "/dev/ttyACM0";
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
   	 error_message ("error %d opening %s: %s", errno, portname, strerror (errno));
   	 return 1;
    }

    set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 1);                	// set blocking

	//mycode
    char C = '\0';
    while (1) {
    C = Console_getChar();
    char input[2];
    if(C == 'w'){
        input[0] = '1';
    }
    else if(C == 's'){
        input[0] = '0';
    }
    else{
        input[0] = 2;
    }
   	 input[1] = '\n';
   	 write(fd, &input, 2);
   	 //usleep ((2 + 25) * 100);
    }
    return 0;
}