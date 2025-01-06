#ifndef SOUND_H
#define SOUND_H
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

void beep(int freq, int duration) {
    Beep(freq, duration);
}

#else
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <fcntl.h>

void beep(int freq, int duration) {
    int console_fd = open("/dev/tty", O_WRONLY);
    if (console_fd == -1) {
        perror("Error: Could not open /dev/tty");
        return;
    }
    if (ioctl(console_fd, KIOCSOUND, 1193180 / freq) == -1) {
        perror("Error: Could not start beep");
        close(console_fd);
        return;
    }
    usleep(duration * 1000);
    if (ioctl(console_fd, KIOCSOUND, 0) == -1) {
        perror("Error: Could not stop beep");
    }
    close(console_fd);
}

#endif

#endif // SOUND_H