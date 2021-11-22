/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "complex.h"
#include "fft.h"



/*********************** Directives of C Pre-processor ************************/

/************************** Conditional Compilation ***************************/

#define DEBUGGING                 /* Use directive when debugging some lines  */



/**************************** Symbolic  Constants *****************************/

/* ---------------------- Constants to Exit Functions ----------------------- */

#define SUCCEED              1    /* Succeeded ending in function execution   */
#define FAIL                 0    /* Failed    ending in function execution   */

/* ---------------------- Analysis in Frequency Domain ---------------------- */

#define FORWARD              1    /* Forward direction for FFT computation    */
#define REVERSE              0    /* Reverse direction for FFT computation    */

/* -------- Default Values for Iteration in Time & Frequency Domain --------- */

#define MAX_TIME_SAMPLES     128   /* Testing default value for time_samples */
#define PADDING_POWER        2                /* Default padding power factor */
#define MAX_FREQ_SAMPLES     MAX_TIME_SAMPLES<<PADDING_POWER  /* freq_samples */



/************************** Definition of Data Types **************************/

typedef union{
  float number;
  uint8_t bytes[4];
}value;

value mag;

typedef union{
  float number;
  uint8_t bytes[4];
}value2;

value2 freq;


/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

void ADC_read(float fs,int muestras,COMPLEX_T *x);


/******************************** Main Function *******************************/

int pin=22;
void setup() 
{
  
  pinMode(pin,OUTPUT);

  Serial.begin(250000);
  
  int i;
  int j;
  int k;
  int direction = FORWARD;
  
  int time_samples = MAX_TIME_SAMPLES;
  int freq_samples = MAX_FREQ_SAMPLES;
  int power = Find_Power( freq_samples );
  
  static COMPLEX_T Signal[MAX_FREQ_SAMPLES]; 
  
  float fs= 500; //Hz
  
  float delta_freq = fs / freq_samples;
  
  while(1){
  
    //Se toman las muestras de la señal
    ADC_read(fs,MAX_TIME_SAMPLES,Signal);
    
    //Se realiza la FFT
    Compute_FFT( direction, power, Signal );
    
    //Transmision matlab
    mag.number=123456;//Codigo de inicio de trama magnitud
    Serial.write(mag.bytes,4);
    for( i = 0; i < freq_samples/2; i++ ){
      mag.number=cplx_Magnitude(Signal[i]);
      Serial.write(mag.bytes,4);
    }
    freq.number=7891011;//Codigo de inicio de trama frecuencia
    Serial.write(freq.bytes,4);
    for( i = 0; i < freq_samples/2; i++ ){
      freq.number=i*delta_freq;
      Serial.write(freq.bytes,4);
    }
    
    //Limpiar la estructura
    for( i = 0; i < freq_samples; i++ ){
      Signal[i].real = 0 ;
      Signal[i].imag = 0 ;
    }
    
  }//while 1

} /* main  */

void loop(){}

void ADC_read(float fs,int muestras,COMPLEX_T *x){
  long Ts=(1/fs)*1000000;
  int estado=0;
  int counter_samples=0;
  long prev_time=micros();
  int finish=0;
  while(!finish){
    switch(estado){
      case 0:
        if( (micros()-prev_time)>=Ts ){       
          x[counter_samples].real=analogRead(A0)*0.0048828125;
          prev_time=micros();
          counter_samples++;
          estado=1;
        }
        break;
      case 1:
        if(counter_samples==muestras){
          finish=1;  
          estado=0;
        }else{
          estado=0;
        }
        break;
    }
  }
}
