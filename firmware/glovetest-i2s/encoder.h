
#pragma once

#include "Arduino.h"
#include "driver/i2s.h"

class Encoder {
  public:
  
  uint16_t amin, bmin;
  uint16_t amax, bmax;
  int asize, bsize;

//  amin = min(amin, a);
//  bmin = min(bmin, b);
//  amax = max(amax, a);
//  bmax = max(bmax, b);
//  asize = (amax-amin);
//  bsize = (bmax-bmin);
//
//  asize = max(asize, 1);
//  bsize = max(bsize, 1);

  int cycle = 0;
  float pangle = 0;
  
  Encoder(adc_channel_t, adc_channel_t);
  void addSample(uint16_t, uint16_t);
  float getAngle() {return pangle;};
  float getPos() {return cycle+pangle;};


//    adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_6);                             // INIT ADC GPIO
//    adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_7);                             // INIT ADC GPIO
//    return;
//  }

  private:
};
