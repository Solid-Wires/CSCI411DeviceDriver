#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

int main() 
{
    // Open from the device file we just made
    //  O_NONBLOCK is a flag I haven't seen before. It's a Linux exclusive flag specifically for when
    //  we just want to open something and nothing more. RDWR is explicitly stated here though.
    int file = open("/dev/memory", O_RDWR | O_NONBLOCK);

    // I've allowed entering anything into the writer
    std::cout << "Write into the device: ";
    char toWrite[60];
    std::cin >> toWrite;

    // Write into that device file
    ssize_t writeTest = write(file, toWrite, 1);
    char bufStatus[1];

    // Read from that device file
    ssize_t readTest = read(file, bufStatus, 1);

    // Close the device file
    close(file);
    printf("%s\n", bufStatus);
    std::cout << std::endl; // For some reason, cin is echoing what I'm typing, which is annoying
    cout << "Input: ";
}