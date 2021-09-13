#include "driver/i2s.h"
//#include "soc/syscon_reg.h"
//#include "hal/adc_ll.h"
//#include "hal/adc_types.h"
//#include "hal/adc_hal.h"
#include "encoder.h"



int cycle = 0;
float pangle = 0;

int i = 0;
const i2s_port_t I2S_PORT = I2S_NUM_0;


Encoder encoder1 = Encoder(ADC_CHANNEL_6, ADC_CHANNEL_8);
Encoder encoder2 = Encoder(ADC_CHANNEL_7, ADC_CHANNEL_9);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println(++i);

  //configs --------------
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate =  5000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
//    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
//    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 8,
    .use_apll = false,
  };
  
  adc_digi_pattern_table_t adc1_pattern[2];
  adc_digi_pattern_table_t adc2_pattern[2];
  
  adc1_pattern[0].atten= 2;
  adc1_pattern[0].bit_width= 2;
  adc1_pattern[0].channel= 6;
  adc1_pattern[1].atten= 2;
  adc1_pattern[1].bit_width= 2;
  adc1_pattern[1].channel= 7;

  adc2_pattern[0].atten= 2;
  adc2_pattern[0].bit_width= 2;
  adc2_pattern[0].channel= 8;
  adc2_pattern[1].atten= 2;
  adc2_pattern[1].bit_width= 2;
  adc2_pattern[1].channel= 9;
  
  adc_digi_config_t adc_digi_config = {
    .conv_limit_en = true,
    .conv_limit_num = 2,
    
    .adc1_pattern_len = 2,
    .adc2_pattern_len = 2,

    .adc1_pattern = adc1_pattern,
    .adc2_pattern = adc2_pattern,
    
//    .conv_mode = ADC_CONV_BOTH_UNIT,
    .conv_mode = ADC_CONV_ALTER_UNIT,

//    .conv_mode = ADC_CONV_SINGLE_UNIT_1,
    .format =  ADC_DIGI_FORMAT_11BIT,
  };



  //-------------------------------------- end configs


    //ESP_ERROR_CHECK(i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_1));
  //ESP_ERROR_CHECK(i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_0));


  
  ESP_ERROR_CHECK(i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL)); // INIT I2S

  // -=-=-=Init encoders here=-=-=

  ESP_ERROR_CHECK(adc_digi_init());                                     // INIT ADC DIGITAL CONTROLLER
  ESP_ERROR_CHECK(adc_digi_controller_config(&adc_digi_config));        // CONFIG ADC DIGI CONTROLLER

  ESP_ERROR_CHECK(adc_set_i2s_data_source(ADC_I2S_DATA_SRC_ADC));       // CONNECT ADC TO I2S
  


}


void loop() {
  // put your main code here, to run repeatedly:
  uint16_t sample[64] = {0};
  size_t bytes_read = 0;
  int TOREAD = 4;
  i2s_read(I2S_PORT, sample, TOREAD*2, &bytes_read, portMAX_DELAY);

//  Serial.print(bytes_read);
//  Serial.print(": \t");
  uint16_t a = (((adc_digi_output_data_t *)(&(sample[0])))->type2.data);
  uint16_t b = (((adc_digi_output_data_t *)(&(sample[1])))->type2.data);

  uint16_t c = (((adc_digi_output_data_t *)(&(sample[2])))->type2.data);
  uint16_t d = (((adc_digi_output_data_t *)(&(sample[3])))->type2.data);

//  for (int j = 0; j < TOREAD; j++){
//    Serial.print((((adc_digi_output_data_t *)(&(sample[j])))->type2.unit));
//    Serial.print('.');
//    Serial.print((((adc_digi_output_data_t *)(&(sample[j])))->type2.channel));
//    Serial.print('\t');
//  }
//Serial.println('\t');
  
  
  
//  Serial.print('\t');
//  Serial.print(a);
//  Serial.print('\t');p
//  Serial.print(b);
//  Serial.print('\t');

  
  encoder1.addSample(c, d);
  encoder2.addSample(a, b);

  if (i == 100){
    i = 0;
        Serial.print(encoder1.getPos());
    Serial.print('\t');

    Serial.println(encoder2.getPos());
  }
  i++;

}
