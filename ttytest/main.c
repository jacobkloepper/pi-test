// quick and light sanity check for termios
// no checks etc

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void scan(char* devname) {
    int serial_port = open(devname, O_RDWR);
    
    struct termios tty;
    tty.c_cc[VMIN] = 4;
    tcflush(serial_port, TCIFLUSH);

    unsigned long cbuf[33];
    int rerr = read(serial_port, &buf, sizeof(buf));

    //printf("%s\n", buf);
    //cbuf[32] = '\0';

    printf("%lu\n", *cbuf);
    close(serial_port);

    return;
}

int main() {
    char acm0[13] = "/dev/ttyACM0";

    scan(acm0);
    return 0;
}
