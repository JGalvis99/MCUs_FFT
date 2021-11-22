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

#include <stdio.h>  /* Due to fprintf           */
#include <stdlib.h> /* Due to exit              */
#include <math.h>   /* Due to sqrt, atan2, fabs */

/* ----------------------- Inclusion of Other Headers ----------------------- */

#include "complex.h"



/*****************************  Public Functions  *****************************/

/* ---------------------------- Complex Numbers ----------------------------- */

/*FN****************************************************************************
*
*   COMPLEX_T cplx_Set( float real, float imag );
*
*   Return:          Initiates a complex number from real and imaginary numbers
*
*   Purpose:         Set values for real and imaginary components
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Set( float real, float imag )
{
COMPLEX_T tmp = { real, imag };

return tmp;

} /* cplx_Set */



/*FN****************************************************************************
*
*   float cplx_Get_Real( COMPLEX_T );
*
*   Purpose:         Return the real part of a complex number
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

float
cplx_Get_Real( COMPLEX_T a )
{
return a.real;

} /* cplx_Get_Real */



/*FN****************************************************************************
*
*   float cplx_Get_Imag( COMPLEX_T );
*
*   Purpose:         Return the imaginary part of a complex number
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

float
cplx_Get_Imag( COMPLEX_T a )
{
return a.imag;

} /* cplx_Get_Imag */



/*FN****************************************************************************
*
*   int cplx_Swap( COMPLEX_T *a, COMPLEX_T *b );
*
*   Return:          Nothing (result is passed by reference)
*
*   Purpose:         Exchange two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

int
cplx_Swap( COMPLEX_T *a, COMPLEX_T *b )
{
COMPLEX_T t;

t  = *a;
*a = *b;
*b =  t;

return SUCCEED;

} /* cplx_Swap */



/*FN****************************************************************************
*
*   COMPLEX_T cplx_Null();
*
*   Purpose:         Return a complex vector with zeros
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Null()
{
COMPLEX_T t = { 0.0, 0.0 };

return t;

} /* cplx_Null */



/*FN****************************************************************************
*
*   COMPLEX_T cplx_Multiply( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the product of two complex numbers
*
*   Note:            Temporal vble t is required in order to avoid changing
*                    result when computing
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Multiply( COMPLEX_T a, COMPLEX_T b )
{
COMPLEX_T t;

t.real = a.real * b.real - a.imag * b.imag;
t.imag = a.real * b.imag + a.imag * b.real;

return t;

} /* cplx_Multiply */



/*FN****************************************************************************
*
*   COMPLEX_T cplx_Divide( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the division of two complex numbers
*
*   Note:            Temporal vble t is required in order to avoid changing
*                    result when computing
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Mar 01/2019  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Divide( COMPLEX_T a, COMPLEX_T b )
{
COMPLEX_T t;
float divider = b.real * b.real + b.imag * b.imag;

if( b.real == 0.0 && b.imag == 0.0 ) {
	fprintf( stderr, "Division by 0 + 0i isn't allowed.\n" );
	exit( 0 );
}

t.real = ( a.real * b.real + a.imag * b.imag ) / divider;
t.imag = ( a.imag * b.real - a.real * b.imag ) / divider;

return t;

} /* cplx_Divide */



/*FN****************************************************************************
*
*   COMPLEX_T cplx_Subtract( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the subtraction of two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Subtract( COMPLEX_T a, COMPLEX_T b )
{
a.real -= b.real;
a.imag -= b.imag;

return a;

} /* cplx_Subtract */



/*FN****************************************************************************
*
*   COMPLEX_T cplx_Add( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the summation of two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 04/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Add( COMPLEX_T a, COMPLEX_T b )
{
a.real += b.real;
a.imag += b.imag;

return a;

} /* cplx_Add */



/*FN****************************************************************************
*
*   COMPLEX_T cplx_Scale( COMPLEX_T a, float factor );
*
*   Purpose: Return each component scaled a given factor
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Mar 02/2019  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

COMPLEX_T
cplx_Scale( COMPLEX_T a, float factor )
{
a.real *= factor, a.imag *= factor;

return a;

} /* cplx_Scale */



/*FN****************************************************************************
*
*   float cplx_Magnitude( COMPLEX_T a );
*
*   Purpose:         Return the magnitude of a complex number
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Jun 05/2013  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

float
cplx_Magnitude( COMPLEX_T a )
{
return sqrt( a.real * a.real + a.imag * a.imag );

} /* cplx_Magnitude */



/*FN****************************************************************************
*
*   float cplx_Phase( COMPLEX_T a );
*
*   Purpose:         Return the phase of a complex number
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Nov 07/2017  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

float
cplx_Phase( COMPLEX_T a )
{
return atan2( a.imag, a.real );

} /* cplx_Phase */



/*FN****************************************************************************
*
*   float cplx_Ratio( COMPLEX_T a, COMPLEX_T b );
*
*   Purpose:         Return the ratio of the real part of two complex numbers
*
*   Register of Revisions (Debugging Process):
*
*   DATE         RESPONSIBLE  COMMENT
*   ------------------------------------------------------------------------
*   Nov 07/2017  J.C.Giraldo  Initial implementation
*
*******************************************************************************/

float
cplx_Ratio( COMPLEX_T a, COMPLEX_T b )
{
return fabs( a.real / b.real );

} /* cplx_Ratio */
