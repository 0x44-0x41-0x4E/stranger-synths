#include <TimerOne.h>
#include "WaveGenerator.h"
#include "MusicSettings.h"
#include "MenuSystem.h"

// DISTANCE PINS
#define distTrigPin 40
#define distEchoPin 41

// Test LED pin
#define testPin 13

//BUTTON PIN
#define buttPin 3

#define sampleDelayms 10

// DISTANCE VARIABlES
long distDuration;
unsigned int distance = 5;
unsigned int maxDistance = 720;

/*
uint8_t previousFrameDistance = 0;
*/
unsigned int previousNoteDistance = 0;
unsigned int previousNoteFrequency = 80;

//Function prototypes
void samplerISR();
void buttISR();


void setup() {
  
  // PINMODES  (Data Direction) 
  pinMode(distTrigPin, OUTPUT);
  pinMode(distEchoPin, INPUT);
  pinMode(buttPin, INPUT);
  pinMode(testPin, OUTPUT);

  // DAC SETUP
  DDRA = 0b11111111;

  Serial.begin(9600);

  waveGenerator_setup();

  // START AUDIO LOOP
  Timer1.initialize(sampleDelayms);
  Timer1.attachInterrupt(samplerISR);

  //ATTACH BUTTUN INTERRUPT
  attachInterrupt(digitalPinToInterrupt(buttPin), buttISR, RISING);

  menuSystem_setup();
  menuSystem_goToMenu("keySelection");
}

void loop() {

  //DEBUG PRINTS
  //  -- Serial.println(digitalRead(buttPin));
  
  //DEBUG PRINTS END
  
  distance = getDistanceFromSensor();

  if (distance > maxDistance - 50) {
    //waveGenerator_emptyWave();
    waveGenerator_generateWave(previousNoteFrequency / 2, sampleDelayms);
  } else {
    unsigned int distChange = distance - previousNoteDistance;

    if (distChange > 5 || distChange < -5) {
      unsigned int frequency = musicSettings_getFrequency(distance, maxDistance);
      waveGenerator_generateWave(frequency, sampleDelayms);
      previousNoteFrequency = frequency;
      previousNoteDistance = distance;
    }
  }

  delay(50);  // MAYBE?
  
}

int getDistanceFromSensor() {
  
  // Clear the trigPin by setting it LOW:
  digitalWrite(distTrigPin, LOW);
  delayMicroseconds(5);
  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(distTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(distTrigPin, LOW);
  
  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  distDuration = pulseIn(distEchoPin, HIGH);
  
  // Calculate the distance:
  return distDuration /** 0.034 / 2*/;
}

void samplerISR() {

  if (nothingGenerated) {
    return;
  }

  uint8_t sample;

  sample = activeBuffer[waveSampleIteration];
  
  waveSampleIteration++;
  if (waveSampleIteration > waveSampleCount) {
    waveSampleIteration = 0;
  }
  
  PORTA = sample;
}

void buttISR(){
  
  //PLACEHOLDER CODE
  if(digitalRead(testPin)){
    digitalWrite(testPin, LOW);
  }
  else{
    digitalWrite(testPin, HIGH);
  }
  //PLACEHOLDER END
  
}
