/*******************************************************************
/* file name : four7Seg.h 
/*******************************************************************
/* description    : Driver for four seven segment displays 
/*                  common anode and multiplexed for Arduino. 
/* programmer     : Joaquin Sopena 
/* lenguage       : ANSI C 
/* date           : October 25, 2020
/********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                        Exported functions                                  */
/******************************************************************************/

void splitnumber(float value, int *h, int *t, int *u, int *th);

void multiplexDisplay(float value, int a, int b, int c, int d);

void initDisplay();



#ifdef __cplusplus
}
#endif
