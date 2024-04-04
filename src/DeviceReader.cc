#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

int main() 
{
    // Open from the device file we just made
    //  O_NONBLOCK is a flag I don't use a whole lot. It's a Linux exclusive flag specifically for when
    //  we just want to open something and nothing more. RDWR is explicitly stated here though.
    int file = open("/dev/memory", O_RDWR | O_NONBLOCK);

    const char* toWrite = "Jared"; // Tried allowing cin, but it was being painful today

    // Write into that device file
    ssize_t writeTest = write(file, toWrite, std::strlen(toWrite));
    char bufStatus[1];

    // Read from that device file
    ssize_t readTest = read(file, bufStatus, 1);

    // Close the device file
    close(file);
    printf("%s\n", bufStatus);
}