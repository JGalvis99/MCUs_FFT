# MCUs_FFT
##Implementation of a spectrum analyzer in real time with an mcu 

The implementation in this case was carried out with an arduino MEGA 2506, if you want to do it with another mcu, you must change the libraries to suit your microcontroller, the code acquires data through an analog port and sends it serially, the acquisition It can be done by matlab with the Serial_Reception.m file, you just have to set the analog pin to use in arduino and the port in matlab to start acquiring the signal in real time, it is important to mention that the spectrum analyzer only works for low frequencies , it is possible to increase this resolution if you have a mcu with much more memory by increasing the sampling time of the signals. 
