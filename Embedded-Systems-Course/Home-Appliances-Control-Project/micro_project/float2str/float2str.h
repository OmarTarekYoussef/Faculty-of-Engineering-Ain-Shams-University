/*
    Copyright (c) 2016 Jens Strümper
 
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
 
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
 
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef MBED_H
#include "mbed.h"
#endif

#ifndef FLOAT2STR_H
#define FLOAT2STR_H 1

namespace js {

/** float2str converts floating point numbers to a character array. Its purpose is to 
 * have a character representation of floating point numbers when printf floating point support
 * is not enabled by compiler options. 
 *
 * This is done by:  . 
 *  <ul>
 *  <li> Separating the integer from the fract part of the floating point number. </li>
 *  <li> Casting both parts to integer </li> 
 *  <li> Convert the integers to char arrays </li>
 *  <li> Add the "." seperator and padding zeros behind the "." </li>
 *  <li> return the compile charater array </li>
 *  </ul>
 * The toString function takes two arguments:
 *  <ul>
 *  <li> Floating point number that shall be converted </li>
 *  <li> Number of digits after the "." </li> 
 *  </ul>
 *
 * Only callbacks that have been attached will be called by the library.
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "float2str.h"
 *
 * float number = 13.467472;
 * char *string;
 *
 * int main(){
 *
 * while(1){
 *   float number = static_cast <float> (rand()) / (static_cast <float> (100000));
 *   charArray = toString (number, 5);
 *   printf ("Char Array: %s Float: %f \r\n", charArray, number );
 *   wait(1);
 * }    
 * @endcode
 *
 * This example will convert randomly generated floating point numbers to a character array of fixed lenght [10]. 
 *
 */


/*
** reverse string in place 
*/
void reverse(char *s) {
char *j;
int c;
 
    j = s + strlen(s) - 1;
    while(s < j) {
        c = *s;
        *s++ = *j;
        *j-- = c;
    }
}
/*
** itoa:  convert n to characters in s 
*/
void itoa(int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)                 /* record sign */
        n = -n;                         /* make n positive */
        i = 0;
    do {                                /* generate digits in reverse order */
         s[i++] = n % 10 + '0';         /* get next digit */
        } while ((n /= 10) > 0);        /* delete it */
    if (sign < 0)
        s[i++] = '-';
        s[i] = '\0';
    reverse(s);
}

/*
** toString:  convert floating point number to 
*/

char *toString(float number, uint8_t digits)
{
    int d1;
    int d2;
    char buf_d1[10];
    char buf_d2[10];
    static char buf_out[10];
//    char padzero[10];
    double fractpart, intpart;   
    int multiplier=1;
    
    for (int j=0; j < digits; j++){
        multiplier = multiplier * 10;
        } 
    fractpart = modf (number , &intpart);
    d2 = int(fractpart*multiplier);
    d1 = int(intpart);    
    itoa(d1, buf_d1);
    itoa(d2, buf_d2); 
       
    strcpy(buf_out, buf_d1);
    
    if (digits > 0){
        strcat(buf_out, ".");
        
        if (strlen(buf_d2) < digits) {      /* adding n padding zero's if nessesary */
            for (uint8_t k=0; k < (digits - strlen(buf_d2)); k++){
                strcat(buf_out, "0");
            }
        }
        strcat(buf_out, buf_d2);  
    }
    return buf_out;  
}

}; 

using namespace js;

#endif