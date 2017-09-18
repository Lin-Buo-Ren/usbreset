/* 
 * An Linux utility to send a USB port reset to a USB device
 * 
 * Originally by Alan Stern © 2008/6/27 on a reply in the linux-usb mailinglist <http://www.marc.info/?l=linux-usb&m=121459435621262&w=2>: 
 * 
 * > In answer to Meher's question: Yes, there is a way to force Linux's USB
 * > stack to perform a port reset and re-enumerate a device.  It can be
 * > done using usbfs; I have attached a C program to carry it out.  Note
 * > however, that reset followed by re-enumeration is _not_ the same thing
 * > as power-cycle followed by reconnect and re-enumeration.
 * 
 * This version is copied from the answer of "How do you reset a USB device from the command line?" by Li Lo <https://askubuntu.com/users/289/li-lo> et. al. on Ask Ubuntu: https://askubuntu.com/questions/645/how-do-you-reset-a-usb-device-from-the-command-line
 * 
 * The original post doesn't claim the license of the code so it is yet to be determined.
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>

int main(int argc, char **argv)
{
    const char *filename;
    int fd;
    int rc;

    if (argc != 2) {
        fprintf(stderr, "Usage: usbreset device-filename\n");
        return 1;
    }
    filename = argv[1];

    fd = open(filename, O_WRONLY);
    if (fd < 0) {
        perror("Error opening output file");
        return 1;
    }

    printf("Resetting USB device %s\n", filename);
    rc = ioctl(fd, USBDEVFS_RESET, 0);
    if (rc < 0) {
        perror("Error in ioctl");
        return 1;
    }
    printf("Reset successful\n");

    close(fd);
    return 0;
}
