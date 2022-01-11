// WAVE VARIABLES
unsigned int waveSampleIteration = 0;
unsigned int waveSampleCount = 1250;

uint8_t waveSamplesA[2500];
uint8_t waveSamplesB[2500];

uint8_t * activeBuffer;
uint8_t * inActiveBuffer;

bool nothingGenerated = true;

void waveGenerator_setup() {
  // SETUP AUDIO SAMPLE BUFFERS
  activeBuffer = waveSamplesA;
  inActiveBuffer = waveSamplesB;
}

uint8_t waveGenerator_getSawSample(int i, int sampleCount) {
  return i * (255 * 100 / sampleCount) / 100;
}

uint8_t waveGenerator_getSquareSample(int i, int sampleCount) {
  if (i < sampleCount / 2) {
    return 255;
  } else {
    return 0;
  }
}

uint8_t waveGenerator_getSinSample(int i, int sampleCount) {
  return 127 + 127 * sin(i / (float)sampleCount * 6.28);
}

void waveGenerator_swapBuffers() {
  if (activeBuffer == waveSamplesA) {
      activeBuffer = waveSamplesB;
      inActiveBuffer = waveSamplesA;
    } else {
      activeBuffer = waveSamplesA;
      inActiveBuffer = waveSamplesB;
    }
}

void waveGenerator_emptyWave() {
  memset((void*) inActiveBuffer, 0, sizeof(uint8_t) * 2500);

  //SwapBuffers();
  
  waveSampleCount = 1250;
}

void waveGenerator_generateWave(unsigned short f, uint8_t _sampleDelayms) {
    //Serial.println("Generating...");

    unsigned int T = 100000 / f;
    unsigned int sampleCount = T / (_sampleDelayms / 10);

    unsigned int sample;
    for(unsigned int i = 0; i < sampleCount; i++) {
        sample = waveGenerator_getSawSample(i, sampleCount);
        //sample = waveGenerator_getSquareSample(i, sampleCount);
        //sample = waveGenerator_getSinSample(i, sampleCount);
        
        //Serial.println(sample);
        inActiveBuffer[i] = sample;
    }

    waveGenerator_swapBuffers();

    waveSampleCount = sampleCount;

    if (nothingGenerated) {
      nothingGenerated = false;  
    }
}
