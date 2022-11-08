/* LM35.h */
#ifndef LM35_H_
#define LM35_H_
 
#include "mbed.h"

 
/** 
*/
class LM35
{
public:
    /** Constructor
     */
    LM35(PinName pin);
    
    /** Destructor
     */
    ~LM35();
    
    /** Get temperature
     */
    float get();
      
private:   
 
    AnalogIn sensorPin; 
    float tempC,a[10],avg;
    int i;

};
 
#endif /* LM35_H_ */