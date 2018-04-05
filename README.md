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
