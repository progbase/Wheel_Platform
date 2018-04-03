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
#include <termios.h>


#define __USE_XOPEN_EXTENDED
#define _XOPEN_SOURCE 500 
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
    //
    while (1) {
   	 printf("Select LED-mode: ");
   	 char input[2] = "";
   	 fgets(input, 2, stdin);
   	 write(fd, &input, 2);
   	 sleep (5);
    }
    return 0;
}
