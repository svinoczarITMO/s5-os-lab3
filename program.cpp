#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>

#define MY_IOCTL_CMD _IOWR('a', 'b', struct my_struct *)

struct my_struct {
    int id;
    char name[64];
};

int main() {
    int fd = open("/dev/my_dev", O_RDWR);
    if (fd < 0) {
        std::cerr << "Failed to open device" << std::endl;
        return 1;
    }

    struct my_struct data;
    if (ioctl(fd, MY_IOCTL_CMD, &data) < 0) {
        std::cerr << "ioctl failed" << std::endl;
        close(fd);
        return 1;
    }

    std::cout << "ID: " << data.id << std::endl;
    std::cout << "Name: " << data.name << std::endl;

    close(fd);
    return 0;
}
