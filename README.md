# Ambika Voice Card Library for Arduino
This Library allows you to control an Ambika Voice Card via an Arduino.

# API
```
  void triggerNote(uint8_t pitch, uint8_t velocity, bool legato);
  void envelopeRelease(void);
  void envelopeRetrigger(uint8_t idx);

  void resetToDefaults(void);
  void reset(void);

  void patchSend(Patch patch);
  void patchWriteData(uint8_t addr, uint8_t data);
  void partWriteData(uint8_t addr, uint8_t data);

  void lfoWrite(uint8_t idx, uint8_t val);
```

# Example 
```
#include <AmbikaVoicecardControl.h>

// First voicecard on Pin 0 (CS)
AmbikaVoicecard voiceCard(0);

Patch samplePatch;

void setup() {
  Serial.begin(115200);
  delay(1000);

  voiceCard.resetToDefaults();
  voiceCard.patchSend(samplePatch);
}

void loop() {
 voiceCard.triggerNote(50, 127, 0);
 delay(500);
 voiceCard.envelopeRelease(); // Release
 delay(500);
}
```
