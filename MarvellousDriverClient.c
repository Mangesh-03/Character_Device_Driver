#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>

#define DEVICE_PATH "/dev/marvellous_driver"
#define BUFFER_SIZE 1024

int main()
{
    int fd = 0;
    int iRet = 0;
    char read_buffer[BUFFER_SIZE];
    char write_buffer[BUFFER_SIZE];

    printf("Opening the Marvellous Device...\n");

    // cat /dev/marvellous_driver
    fd = open(DEVICE_PATH,O_RDWR);

    if(fd < 0)
    {
        printf("Error : Unble to open Marvellous device\n");
        printf("reason : %s\n",strerror(errno));
        return -1;
    }

    printf("Marvellous Device opened successfully\n");

    printf("Enter the data for marvellous driver\n");

    fgets(write_buffer,BUFFER_SIZE,stdin);

    //echo "Jay Ganesh..." /dev/marvellous_driver
    write_buffer[strcspn(write_buffer,"\n")] = 0;

    printf("Writing to marvellous device...\n");

    iRet = write(fd,write_buffer,strlen(write_buffer));

    if(iRet < 0)
    {
        perror("Error : Unble to write into Marvellous Device\n");
        close(fd);
        return -1;
    }

    printf("Data successfully written into Marvellous Driver\n");

    printf("Reading the data from Marvellous Driver\n");

    // cat /dev/marvellous_driver
    iRet = read(fd,read_buffer,BUFFER_SIZE);

    if(iRet < 0)
    {
        printf("Error : Unble to read data from Marvellous Driver\n");
        close(fd);
        return -1;
    }

    read_buffer[iRet] = '\0';

    printf("Data recieved from Marvellous Driver : %s\n",read_buffer);

    printf("Closing Marvellous Driver...\n");
    
    close(fd);

    return 0;
}