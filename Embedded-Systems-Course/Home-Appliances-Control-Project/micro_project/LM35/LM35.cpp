#include "LM35.h"
 
LM35::LM35(PinName pin) :
    sensorPin(pin)
{
}
 
LM35::~LM35()
{
}
 
float LM35::get()
{
    avg=0;
    for(i=0;i<10;i++)
    {
        a[i]=sensorPin.read();
        wait(.02);
    }
    for(i=0;i<10;i++)
    {
        avg=avg+(a[i]/10);
    }

    tempC=(avg*3.685503686*100);
    
    return (tempC);
}
 
