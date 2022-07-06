#ifndef _MYSTRING_H
#define _MYSTRING_H

short myStrSection(char *p_str,char *p_result,unsigned char p_size,char p_char,char p_pos);
char* myLongStr(signed long p_val,char *p_dest,short p_size,char p_base);
long myStrLong(char *p_str,char p_base);
float myStrFloat(char *p_str,char p_base);
void myfloatStr(double p_float,char *p_str);
char *myTrim(char *str); 						// TRIM OF WHITE SPACES FROM THE ENDS OF STRINGS
void myGmtDate(char *date);
char * myCharHex(char *in_tag, unsigned short tag_length);
#endif
