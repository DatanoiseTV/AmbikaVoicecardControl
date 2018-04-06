#include <AmbikaVoicecardControl.h>

// First voicecard on Pin 0 (CS)
AmbikaVoicecard voiceCard(0);

Patch samplePatch;

void setup() {

  samplePatch.filter[0].cutoff = 10;
  Serial.begin(115200);
  delay(1000);

  voiceCard.resetToDefaults();
  voiceCard.patchSend(samplePatch);
  voiceCard.patchWriteData(PRM_PATCH_FILTER1_CUTOFF, 53);
  voiceCard.patchWriteData(PRM_PATCH_VOICE_LFO_SHAPE, LFO_WAVEFORM_WAVE_3);
}

void loop() {
 voiceCard.triggerNote(50, 127, 0);
 delay(500);
 voiceCard.envelopeRelease(); // Release
 delay(500);
}
