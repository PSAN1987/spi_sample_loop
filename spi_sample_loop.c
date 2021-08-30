//bcm2835 library install
//$ sudo wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.44.tar.gz
//$ tar zxvf bcm2835-1.44.tar.gz
//$ cd bcm2835-1.44/
//$ sudo ./configure
//$ sudo make
//$ sudo make install
//https://masaeng.hatenablog.com/entry/2020/05/10/234342
//airspayce.com/mikem/bcm2835/index.html
//About SPI: https://www.analog.com/jp/analog-dialogue/articles/introduction-to-spi-interface.html

// spin.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a number of bytes to and from an SPI device
//
// After installing bcm2835, you can build this 
// with something like:
// gcc -o spin spin.c -l bcm2835
// sudo ./spin
//
// Or you can test it before installing with:
// gcc -o spin -I ../../src ../../src/bcm2835.c spin.c
// sudo ./spin
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $
 
#include <bcm2835.h>
#include <stdio.h>
 
int main (int argc, char **argv)
{
    int i =0;
    while (i < 20) {
        
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
 
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_begin();
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);                   // AXL345 is MODE3
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    
    // Send a some bytes to the slave and simultaneously read 
    // some bytes back from the slave
    // Most SPI devices expect one or 2 bytes of command, after which they will send back
    // some data. In such a case you will have the command bytes first in the buffer,
    // followed by as many 0 bytes as you expect returned data bytes. After the transfer, you 
    // Can the read the reply bytes from the buffer.
    // If you tie MISO to MOSI, you should read back what was sent.
    
    char buf[] = { 0x2D, 0x08, 0xF2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }; // Data to send
    bcm2835_spi_transfern(buf, sizeof(buf));
    // buf will now be filled with the data that was read from the slave
    //printf("Read from SPI: %02X  %02X  %02X  %02X  %02X  %02X  %02X  %02X  %02X\n", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8]);
    int x = (buf[4]<<8) | buf[3];
    int y = (buf[6]<<8) | buf[5];
    int z = (buf[8]<<8) | buf[7];
    //int x_data = 0;
    //int y_data = 0;
    //int z_data = 0;
    
    //printf("x raw data: %04X\n", x);
    //printf("y raw data: %04X\n", y);
    //printf("z raw data: %04X\n", z);
    
    // ２の補数は先頭ビットが1であり、2進数のビットを反転してそれに1を足した数字
    if ((x & 0x8000) == 0x8000) 
    {
        int x_data = ((~x & 0xFFFF)+1)*-1;
        printf ("x_data: %d", x_data);
    }
    else {
        int x_data = x;
        printf ("x_data: %d", x_data);
    }
    
    if ((y & 0x8000) == 0x8000) 
    {
        int y_data = ((~y & 0xFFFF)+1)*-1;
        printf (", y_data: %d", y_data);
    }
    else {
        int y_data = y;
        printf (". y_data: %d", y_data);
    }    

    if ((z & 0x8000) == 0x8000) 
    {
        int z_data = ((~z & 0xFFFF)+1)*-1;
        printf (", z_data: %d\n", z_data);
    }
    else {
        int z_data = z;
        printf (", z_data: %d\n", z_data);
    }
    
    //printf("x, y, z data (g): %d %d %d\n", x_data, y_data, z_data);
    
    bcm2835_spi_end();
    bcm2835_close();
    delay (1000);
    i++;

    }
    return 0;
}
