#pragma once
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
#include "../include/port.h"

int set_interface_attribs (int fd, int speed, int parity);

void set_blocking (int fd, int should_block);