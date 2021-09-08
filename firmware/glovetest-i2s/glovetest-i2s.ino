// This file is created by Robert Cross <@Quantum-cross> as a modification of
// LucidVR/lucidgloves which is released under the MIT License.
// See file LICENSE for details.

#include "driver/i2s.h"

uint16_t amin, bmin;
uint16_t amax, bmax;
int asize, bsize;

int cycle = 0;
float pangle = 0;

int i = 0;
const i2s_port_t I2S_PORT = I2S_NUM_0;
void setup() {
  amin = bmin = INT_MAX;
  amax = bmax = INT_MIN;
  asize = bsize = 1;
  Serial.begin(115200);
  Serial.println(++i);

  //configs --------------
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate =  5000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 20,
    .use_apll = false,
  };
  
  adc_digi_pattern_table_t adc1_pattern[2];
  
  adc1_pattern[0].atten= 2;
  adc1_pattern[0].bit_width= 3;
  adc1_pattern[0].channel= 6;
  adc1_pattern[1].atten= 2;
  adc1_pattern[1].bit_width= 3;
  adc1_pattern[1].channel= 7;
  
  adc_digi_config_t adc_digi_config = {
    .conv_limit_en = true,
    .conv_limit_num = 255,
    .adc1_pattern_len = 2,
    .adc1_pattern = adc1_pattern,
    .conv_mode = ADC_CONV_SINGLE_UNIT_1,
    .format =  ADC_DIGI_FORMAT_12BIT,
  };



  //-------------------------------------- end configs

  ESP_ERROR_CHECK(i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL)); // INIT I2S

  adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_6);                             // INIT ADC GPIO
  adc_gpio_init(ADC_UNIT_1, ADC_CHANNEL_7);                             // INIT ADC GPIO
  ESP_ERROR_CHECK(adc_digi_init());                                     // INIT ADC DIGITAL CONTROLLER
  ESP_ERROR_CHECK(adc_digi_controller_config(&adc_digi_config));        // CONFIG ADC DIGI CONTROLLER

  ESP_ERROR_CHECK(adc_set_i2s_data_source(ADC_I2S_DATA_SRC_ADC));       // CONNECT ADC TO I2S
  
}

void loop() {
  uint16_t sample[8] = {0};
  size_t bytes_read = 0;

  i2s_read(I2S_PORT, sample, 20, &bytes_read, portMAX_DELAY);

  if (bytes_read == 20) {

  uint16_t a = (((adc_digi_output_data_t *)(&(sample[0])))->type1.data);
  uint16_t b = (((adc_digi_output_data_t *)(&(sample[1])))->type1.data);
  
//  a = samplesA.getMedian();
//  b = samplesB.getMedian();

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

//  Serial.print(aa);
//  Serial.print('\t');
//  Serial.print(bb);
//  Serial.print('\t');


  float angle = atan2(aa,bb)/(2*3.1415) + .5;
  
//  Serial.print(angle);

  float adiff = angle - pangle;
  if (abs(adiff) > .75){
    cycle = (adiff > 0) ? cycle - 1 : cycle + 1;
//    Serial.println(cycle + angle);
  }
//  Serial.print('\t');

  i++;
  if (i == 100){i=0;
//    Serial.print(aa);
//  Serial.print('\t');
//  Serial.print(bb);
//  Serial.print('\t');
  Serial.print(cycle + (angle));
  Serial.print('\n');
  }

  pangle = angle;

    }

}
