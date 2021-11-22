/* Ruler 1         2         3         4         5         6         7        */

/********************************  complex.c  *********************************/
/*                                                                            */
/*   Purpose: Module to perform some basic operations with complex numbers    */
/*                                                                            */
/*   Origin:  Module tested and documented by jcgiraldo, since June 4th, 2013 */
/*                                                                            */
/*   Notes:   None                                                            */
/*                                                                            */
/*   DATE         RESPONSIBLE  COMMENT                                        */
/*   -----------------------------------------------------------------------  */
/*   Mar 01/2019  J.C.Giraldo  cplx_Divide was incorporated                   */
/*   Nov 07/2017  J.C.Giraldo  complex was changed to COMPLEX_T               */
/*   Nov 07/2017  J.C.Giraldo  cplx_Phase was incorporated                    */
/*   Nov 07/2017  J.C.Giraldo  cplx_Ratio was incorporated                    */
/*   Jun 05/2013  J.C.Giraldo  Initial implementation                         */
/*                                                                            */
/******************************************************************************/

/*********************** Directives of C Pre-processor ************************/

/************************** Conditional Compilation ***************************/

#define DEBUGGING                 /* Use directive when debugging some lines  */



/**************************** Symbolic  Constants *****************************/

/* ---------------------- Constants to Exit Functions ----------------------- */

#define SUCCEED              1    /* Succeeded ending in function execution   */
#define FAIL                 0    /* Failed    ending in function execution   */



/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Std Headers ------------------------ */

#include <math.h>   /* Due to sqrt */

/* ----------------------- Inclusion of Other Headers ----------------------- */

#include "complex.h"
#include "fft.h"



/*****************************  Public Functions  *****************************/

/* ---------------------- Analysis in Frequency Domain ---------------------- */

/*FN****************************************************************************
*
*   int
*   Compute_FFT( int dir, int pow, COMPLEX_T *x );
*
*   Return:          Transformation in values passed by reference
*
*   Purpose:         Compute an in-place complex-to-complex FFT
*
*   Note:            This function computes an in-place complex-to-complex FFT
*                    x.real and y.imag are the real and imaginary arrays of
*                    2^pow points.
*                    dir = 1 or FORWARD gives forward transform
*                    dir = 0 or REVERSE gives reverse transform
*
*                    There is a modification by Peter Cusak to utilize the
*                    Microsoft complex type.
*
*   Plan:
*           Part 1: Calculate the number of points
*           Part 2: Do the bit reversal
*           Part 3: Compute the FFT
*           Part 4: Scale for forward transformation
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   -------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Incorporation of functions with complex numbers
*   May 03/2013  J.C.Giraldo  Readable identifiers
*   Jun --/1993  P. Bourkes   Initial implementation
*
*******************************************************************************/

int
Compute_FFT( int dir, int pow, COMPLEX_T *x )
{
  long    points, i, j, k, l, i1, i2, l1, l2;
  COMPLEX_T c, temp, u;	
  int state=0;
  int termino=0;
  points=1;
  i=0;
  
  while(!termino){
  	switch( state ) {
  		
    	case 0:   
        if( i < pow ) {
    			points <<= 1;
    			i++;
        	state = 0; /*next state*/
        } else {
         	i2 = points >> 1;
      		j = 0;
  		  	i=0;
        	state = 1; /*next state*/
        }
    	break;
  		
  		case 1:   
        if( i < points-1 ) {
        	state = 2; /*next state*/
        } else {
    			c.real = -1.0;
  	  		c.imag =  0.0;
  		  	l2 =  1;
  			  l = 0;
        	state = 4; /*next state*/
  	  	}
    	break;
  
  		case 2:   
        if( i<j ) {
    			cplx_Swap( &x[i], &x[j] );
  	  		k=i2;
        	state = 3; /*next state*/
        } else {
    			k=i2;
        	state = 3; /*next state*/
    		}
    	break;
  
  		case 3:   
        if( k <= j) {
    			j -= k, k >>= 1;
        	state=3; /*next state*/
    		} else {
    			j+=k;
    			i++;
    			state = 1; /*next state*/	
    		}
    	break;
  
  		case 4:   
        if( l < pow ) {
      		l1 = l2;
      		l2 <<= 1;
      		u.real = 1.0;
      		u.imag = 0.0;
      		j =0;
        	state = 5; /*next state*/
      	} else {
      		state = 8; /*next state*/	
      	}
    	break;
  		
  		case 5:   
        if( j < l1 ) {
    			i = j;
        	state = 6; /*next state*/
    		} else {
  	  		c.imag = sqrt( ( 1.0 - c.real ) / 2.0 );
  		  	state = 7; /*next state*/	
  		  }
    	break;
  
  		case 6:
  	  	if( i < points ) {
  		  	i1    = i + l1;
  			  temp  = cplx_Multiply( u, x[i1] );
  			  x[i1] = cplx_Subtract( x[i], temp );
    			x[i]  = cplx_Add( x[i], temp );
  	  		i+=l2; 
        	state = 6; /*next state*/
    		} else {
  	  		u = cplx_Multiply( u, c );
  		  	j++;
  			  state = 5; /*next state*/	
  		  }
    	break;
  
  		case 7:
    		if( dir == FORWARD ) {
  	  		c.imag = -c.imag;
  		  	c.real = sqrt( ( 1.0 + c.real ) / 2.0 );
  			  l = l +1;		 
        	state = 4; /*next state*/
    		} else {
  	  		c.real = sqrt( ( 1.0 + c.real ) / 2.0 );
  		  	l = l +1;
  			  state = 4; /*next state*/	
  	    }
    	break;
  		
  		case 8:
    		if( dir == FORWARD ) {
  	  		i = 0;
        	state = 9; /*next state*/
    		} else {
  	  		termino = 1; /*next state*/	
  		  }
    	break;
  
  		case 9:
    		if( i < points ) {
  	  		x[i] = cplx_Scale( x[i], points );
  		  	i++;
        	state = 9; /*next state*/
    		} else {
  	  		termino = 1; /*next state*/	
  		  }
    	break;
    } /* switch */ 
  }/* while */
return( SUCCEED );

} /* Compute_FFT */



/*FN****************************************************************************
*
*   int
*   Find_Power( int number );
*
*   Purpose:         Return the (integer) logarithm in base 2 of a number
*
*   Note:            Number must be an integer equal to zero or greater
*                    Another option is shifting and truncation
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE  COMMENT
*   -----------------------------------------------------------------------
*   May 03/13  J.C.Giraldo  Readable identifiers
*   --- --/--  P. Bourkes   Initial implementation
*
*******************************************************************************/

int
Find_Power( long number )
{
int power = 0;

while( number != 1 ) {
    number = (long)( number/2 );
    power++;
}

return( power );

} /* Find_Power */
