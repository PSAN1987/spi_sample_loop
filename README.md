# spi_sample_loop
- This code can print out X, Y, Z axis raw data (g) for 20times with 1000msec delay 
- AXL345 module is used
- SPI IF is used for RPi4 and AXL345 module (4-wire, Mode3)
- Library is used with BCM235, https://airspayce.com/mikem/bcm2835/index.html

# Build Code
- for pre-set up such as library install, please refer to https://github.com/PSAN1987/spi_test-code
- Build code $ gcc -o spi spi_sample_loop.c -l bcm2835 $ sudo ./spi

# Example of code execution
pi@raspberrypi:~/Documents/SPI $ sudo ./spi
x_data: -14. y_data: 8, z_data: 305
x_data: -16. y_data: 8, z_data: 303
x_data: -16. y_data: 8, z_data: 303
x_data: -15. y_data: 9, z_data: 305
x_data: -15. y_data: 8, z_data: 304
x_data: -16. y_data: 9, z_data: 304
x_data: -15. y_data: 8, z_data: 303
x_data: -16. y_data: 8, z_data: 303
x_data: -16. y_data: 8, z_data: 305
x_data: -16. y_data: 9, z_data: 303
x_data: -15. y_data: 9, z_data: 302
x_data: -15. y_data: 8, z_data: 304
x_data: -16. y_data: 8, z_data: 305
x_data: -15. y_data: 8, z_data: 305
x_data: -16. y_data: 8, z_data: 303
x_data: -16. y_data: 8, z_data: 305
x_data: -16. y_data: 8, z_data: 302
x_data: -16. y_data: 8, z_data: 303
x_data: -15. y_data: 7, z_data: 303
x_data: -16. y_data: 8, z_data: 303
