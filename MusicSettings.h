#define scaleLength 16

// NOTE VARIABLES
uint8_t currentScale[scaleLength];

float scaleBlueprint_DurPentaton[16];
float scaleBlueprint_MolPentaton[16];

float A2  = 110.00;
float AS2 = 116.54;
float B2  = 123.47;
float C2  = 130.81;
float CS2 = 138.59;
float D2  = 146.83;
float DS2 = 155.56;
float E2  = 164.81;
float F2  = 174.61;
float FS2 = 185.00;
float G2  = 196.00;
float GS2 = 207.65;

float A3;
float AS3;
float B3;
float C3;
float CS3;
float D3;
float DS3;
float E3;
float F3;
float FS3;
float G3;
float GS3;

float A4;
float AS4;
float B4;
float C4;
float CS4;
float D4;
float DS4;
float E4;
float F4;
float FS4;
float G4;
float GS4;

float A5;

uint8_t[] musicSettings_getScale(uint8_t scaleIndex, float scaleBlueprint[]) {
  uint8_t blueprintLength = sizeof(scaleBlueprint) / sizeof(float);
  uint8_t newScale[blueprintLength];

  float ratio = pow(1.05946, scaleIndex);

  for (int i = 0; i < count; ++i)
  {
    newScale[i] = round(scaleBlueprint[i] * ratio);
  }

  return newScale;
}

void musicSettings_setup() {

  A3 = A2 * 2.0;
  AS3 = AS2 * 2.0;
  B3 = B2 * 2.0;
  C3 = C2 * 2.0;
  CS3 = CS2 * 2.0;
  D3 = D2 * 2.0;
  DS3 = DS2 * 2.0;
  E3 = E2 * 2.0;
  F3 = F2 * 2.0;
  FS3 = FS2 * 2.0;
  G3 = G2 * 2.0;
  GS3 = GS2 * 2.0;

  A4 = A3 * 2.0;
  AS4 = AS3 * 2.0;
  B4 = B3 * 2.0;
  C4 = C3 * 2.0;
  CS4 = CS3 * 2.0;
  D4 = D3 * 2.0;
  DS4 = DS3 * 2.0;
  E4 = E3 * 2.0;
  F4 = F3 * 2.0;
  FS4 = FS3 * 2.0;
  G4 = G3 * 2.0;
  GS4 = GS3 * 2.0;

  A5 = A4 * 2.0;

  scaleBlueprint_DurPentaton = {  A2, B2, CS2, E2, FS2,
                                  A3, B3, CS3, E3, FS3,
                                  A4, B4, CS4, E4, FS4, A5};

  scaleBlueprint_MolPentaton = {  A2, B2, C2, E2, FS2,
                                  A3, B3, C3, E3, FS3,
                                  A4, B4, C4, E4, FS4, A5};

  currentScale = musicSettings_getScale(0, scaleBlueprint_DurPentaton);

}

unsigned int musicSettings_getFrequency(unsigned int _dist, unsigned int _maxDist) {
  uint8_t note = map(_dist, 0, _maxDist, 0, scaleLength);
  return notes[note];
}
