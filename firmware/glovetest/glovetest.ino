// This file is created by Robert Cross <@Quantum-cross> as a modification of
// LucidVR/lucidgloves which is released under the MIT License.
// See file LICENSE for details.

#include <RunningMedian.h>
#include <limits.h>

RunningMedian samplesA = RunningMedian(3);
RunningMedian samplesB = RunningMedian(3);
int sensorPinA = 4;    // select the input pin for the potentiometer
int sensorPinB = 15;    // select the input pin for the potentiometer

int amin, bmin;
int amax, bmax;
int amid, bmid;

int cycle = 0;
float pangle = 0;



void setup() {
  analogSetAttenuation(ADC_6db);

  amin = bmin = INT_MAX;
  amax = bmax = INT_MIN;
  amid = bmid = 1;
  Serial.begin(115200);
  delay(1000);
}

void loop() {

  samplesA.add(analogRead(sensorPinA));
  samplesB.add(analogRead(sensorPinB));
  
  int a = samplesA.getMedian();
  int b = samplesB.getMedian();

  amin = (a > 1000) ? min(amin, a) : amin;
  bmin = (b > 1000) ? min(bmin, b) : bmin;
  amax = max(amax, a);
  bmax = max(bmax, b);
  amid = (amax-amin);
  bmid = (bmax-bmin);

  amid = (amid==0) ? 1 : amid;
    bmid = (bmid==0) ? 1 : bmid;


  double aa = ((a - amin)/(1.0*amid));
  double bb = ((b - bmin)/(1.0*bmid));
  aa = sqrt(2)*(aa - .5);
  bb = sqrt(2)*(bb - .5);
  Serial.print(aa);
  Serial.print('\t');
  Serial.print(bb);
  Serial.print('\t');


  float angle = atan2(aa,bb)/(2*3.1415) + .5;
  
  Serial.print(angle);

  float adiff = angle - pangle;
  if (abs(adiff) > .75){
    cycle = (adiff > 0) ? cycle - 1 : cycle + 1;
  }
  Serial.print('\t');
  Serial.print(cycle + (angle));
  
  Serial.print('\n');

  pangle = angle;
  delay(4);

}
