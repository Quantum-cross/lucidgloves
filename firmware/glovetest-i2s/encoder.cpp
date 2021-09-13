#include "encoder.h"

  Encoder::Encoder(adc_channel_t ch1, adc_channel_t ch2){
    amin = bmin = 99999;
    amax = bmax = 0;
    asize = bsize = 1;
    cycle = 0;
    pangle = 0;

    adc_gpio_init(ADC_UNIT_1, ch1);                             // INIT ADC GPIO
    adc_gpio_init(ADC_UNIT_2, ch2);                             // INIT ADC GPIO
    return;
  }


void Encoder::addSample(uint16_t a, uint16_t b){

  amin = min(amin, a);
  bmin = min(bmin, b);
  amax = max(amax, a);
  bmax = max(bmax, b);
  asize = (amax-amin);
  bsize = (bmax-bmin);

  asize = max(asize, 1);
  bsize = max(bsize, 1);


  float aa = ((a - amin)/((float)asize))-.5;
  float bb = ((b - bmin)/((float)bsize))-.5;

  float angle = atan2(aa,bb)/(2*3.1415) + .5;
  
  float adiff = angle - pangle;
  if (abs(adiff) > .75){
    cycle = (adiff > 0) ? cycle - 1 : cycle + 1;
  }

  pangle = angle;

}
