// NOTE VARIABLES
unsigned int notes[15] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 523};

unsigned int musicSettings_getFrequency(unsigned int _dist, unsigned int _maxDist) {
  uint8_t note = map(_dist, 0, _maxDist, 0, 15);
  return notes[note];
}
