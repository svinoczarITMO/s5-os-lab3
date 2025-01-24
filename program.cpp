#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>

#define MY_IOCTL_CMD _IOWR('a', 'b', struct my_struct *)

struct my_struct {
    int id;
    char name[64];
    int swag_percent;
    char birth_date[64];
};

int main() {
    int fd = open("/dev/ksv_shelter", O_RDWR);
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
    std::cout << "SWAG percentage: " << data.swag_percent << std::endl;
    std::cout << "Date of birth: " << data.birth_date << std::endl;

    close(fd);
    return 0;
}
