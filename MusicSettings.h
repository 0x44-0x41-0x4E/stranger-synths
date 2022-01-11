#define scaleLength 16

// NOTE VARIABLES
unsigned short currentScale[scaleLength];

float scaleBlueprint_DurPentaton[16];
float scaleBlueprint_MolPentaton[16];

float nA2  = 110.00;
float nAS2 = 116.54;
float nB2  = 123.47;
float nC2  = 130.81;
float nCS2 = 138.59;
float nD2  = 146.83;
float nDS2 = 155.56;
float nE2  = 164.81;
float nF2  = 174.61;
float nFS2 = 185.00;
float nG2  = 196.00;
float nGS2 = 207.65;

float nA3;
float nAS3;
float nB3;
float nC3;
float nCS3;
float nD3;
float nDS3;
float nE3;
float nF3;
float nFS3;
float nG3;
float nGS3;

float nA4;
float nAS4;
float nB4;
float nC4;
float nCS4;
float nD4;
float nDS4;
float nE4;
float nF4;
float nFS4;
float nG4;
float nGS4;

float nA5;

void musicSettings_setScale(uint8_t scaleIndex, float scaleBlueprint[]) {
  unsigned short newScale[scaleLength];

  float ratio = pow(1.05946, scaleIndex);

  for (int i = 0; i < scaleLength; ++i)
  {
    unsigned short newNoteFreq = round(scaleBlueprint[i] * ratio);
    currentScale[i] = newNoteFreq;
  }
}

void musicSettings_setup() {

  nA3 = nA2 * 2.0;
  nAS3 = nAS2 * 2.0;
  nB3 = nB2 * 2.0;
  nC3 = nC2 * 2.0;
  nCS3 = nCS2 * 2.0;
  nD3 = nD2 * 2.0;
  nDS3 = nDS2 * 2.0;
  nE3 = nE2 * 2.0;
  nF3 = nF2 * 2.0;
  nFS3 = nFS2 * 2.0;
  nG3 = nG2 * 2.0;
  nGS3 = nGS2 * 2.0;

  nA4 = nA3 * 2.0;
  nAS4 = nAS3 * 2.0;
  nB4 = nB3 * 2.0;
  nC4 = nC3 * 2.0;
  nCS4 = nCS3 * 2.0;
  nD4 = nD3 * 2.0;
  nDS4 = nDS3 * 2.0;
  nE4 = nE3 * 2.0;
  nF4 = nF3 * 2.0;
  nFS4 = nFS3 * 2.0;
  nG4 = nG3 * 2.0;
  nGS4 = nGS3 * 2.0;

  nA5 = nA4 * 2.0;

  scaleBlueprint_DurPentaton[0]   = nA2;
  scaleBlueprint_DurPentaton[1]   = nB2;
  scaleBlueprint_DurPentaton[2]   = nCS2;
  scaleBlueprint_DurPentaton[3]   = nE2;
  scaleBlueprint_DurPentaton[4]   = nFS2;
  scaleBlueprint_DurPentaton[5]   = nA3;
  scaleBlueprint_DurPentaton[6]   = nB3;
  scaleBlueprint_DurPentaton[7]   = nCS3;
  scaleBlueprint_DurPentaton[8]   = nE3;
  scaleBlueprint_DurPentaton[9]   = nFS3;
  scaleBlueprint_DurPentaton[10]  = nA4;
  scaleBlueprint_DurPentaton[11]  = nB4;
  scaleBlueprint_DurPentaton[12]  = nCS4;
  scaleBlueprint_DurPentaton[13]  = nE4;
  scaleBlueprint_DurPentaton[14]  = nFS4;
  scaleBlueprint_DurPentaton[15]  = nA5;

  scaleBlueprint_MolPentaton[0]   = nA2;
  scaleBlueprint_MolPentaton[1]   = nC2;
  scaleBlueprint_MolPentaton[2]   = nD2;
  scaleBlueprint_MolPentaton[3]   = nE2;
  scaleBlueprint_MolPentaton[4]   = nG2;
  scaleBlueprint_MolPentaton[5]   = nA3;
  scaleBlueprint_MolPentaton[6]   = nC3;
  scaleBlueprint_MolPentaton[7]   = nD3;
  scaleBlueprint_MolPentaton[8]   = nE3;
  scaleBlueprint_MolPentaton[9]   = nG3;
  scaleBlueprint_MolPentaton[10]  = nA4;
  scaleBlueprint_MolPentaton[11]  = nC4;
  scaleBlueprint_MolPentaton[12]  = nD4;
  scaleBlueprint_MolPentaton[13]  = nE4;
  scaleBlueprint_MolPentaton[14]  = nG4;
  scaleBlueprint_MolPentaton[15]  = nA5;

  musicSettings_setScale(0, scaleBlueprint_DurPentaton);

}

unsigned short musicSettings_getFrequency(unsigned int _dist, unsigned int _maxDist) {
  uint8_t note = map(_dist, 0, _maxDist, 0, scaleLength);
  Serial.println(note);
  return currentScale[note];
}
