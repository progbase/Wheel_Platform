#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
//#include <progbase.h>
#include <progbase/console.h>
#include <stdlib.h>
#include <stdio.h>



#define __USE_XOPEN_EXTENDED
#define error_message(FMT, ...) printf(FMT, __VA_ARGS__)

int
set_interface_attribs (int fd, int speed, int parity)
{
    	struct termios tty;
    	memset (&tty, 0, sizeof tty);
    	if (tcgetattr (fd, &tty) != 0)
    	{
            	error_message ("error %d from tcgetattr", errno);
            	return -1;
    	}

    	cfsetospeed (&tty, speed);
    	cfsetispeed (&tty, speed);

    	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; 	// 8-bit chars
    	// disable IGNBRK for mismatched speed tests; otherwise receive break
    	// as \000 chars
    	tty.c_iflag &= ~IGNBRK;     	// disable break processing
    	tty.c_lflag = 0;            	// no signaling chars, no echo,
                                    	// no canonical processing
    	tty.c_oflag = 0;            	// no remapping, no delays
    	tty.c_cc[VMIN]  = 0;        	// read doesn't block
    	tty.c_cc[VTIME] = 5;        	// 0.5 seconds read timeout

    	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    	// enable reading
    	tty.c_cflag &= ~(PARENB | PARODD);  	// shut off parity
    	tty.c_cflag |= parity;
    	tty.c_cflag &= ~CSTOPB;
    	tty.c_cflag &= ~CRTSCTS;

    	if (tcsetattr (fd, TCSANOW, &tty) != 0)
    	{
            	error_message ("error %d from tcsetattr", errno);
            	return -1;
    	}
    	return 0;
}

void
set_blocking (int fd, int should_block)
{
    	struct termios tty;
    	memset (&tty, 0, sizeof tty);
    	if (tcgetattr (fd, &tty) != 0)
    	{
            	error_message ("error %d from tggetattr", errno);
            	return;
    	}

    	tty.c_cc[VMIN]  = should_block ? 1 : 0;
    	tty.c_cc[VTIME] = 5;        	// 0.5 seconds read timeout

    	if (tcsetattr (fd, TCSANOW, &tty) != 0)
            	error_message ("error %d setting term attributes", errno);
}

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
   	 usleep ((2 + 25) * 100);
    }
    return 0;
}
