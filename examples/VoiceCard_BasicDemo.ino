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
