/* Ruler 1         2         3         4         5         6         7        */

/********************************  complex.h  *********************************/
/*                                                                            */
/*   Purpose: Header to operate complex numbers                               */
/*                                                                            */
/******************************************************************************/

#ifndef COMPLEX_H
#define COMPLEX_H

/************************** Definition of Data Types **************************/

/* ---------------------------- Complex Numbers ----------------------------- */

typedef struct {
	float real; /* Real part of type complex number      */
	float imag; /* Imaginary part of type complex number */
} COMPLEX_T;



/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

COMPLEX_T cplx_Set     ( float, float );
float    cplx_Get_Real( COMPLEX_T );
float    cplx_Get_Imag( COMPLEX_T );
int       cplx_Swap    ( COMPLEX_T *, COMPLEX_T * );

COMPLEX_T cplx_Null();
COMPLEX_T cplx_Multiply( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Divide  ( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Subtract( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Add     ( COMPLEX_T, COMPLEX_T );
COMPLEX_T cplx_Scale   ( COMPLEX_T, float );

float cplx_Magnitude  ( COMPLEX_T );
float cplx_Phase      ( COMPLEX_T );
float cplx_Ratio      ( COMPLEX_T, COMPLEX_T );

#endif /* COMPLEX_H */
