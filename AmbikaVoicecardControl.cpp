
#include <AmbikaVoicecardControl.h>

void AmbikaVoicecard::triggerNote(uint8_t pitch, uint8_t velocity, bool legato)
{
  uint8_t note_lsb = 0;
  uint8_t note_msb = pitch & 127;
  uint8_t velocity_scaled = velocity << 1;
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x10 | legato);
  SPI.transfer(note_msb);
  SPI.transfer(note_lsb);
  SPI.transfer(velocity_scaled);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::envelopeRelease(void)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x60);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::envelopeRetrigger(uint8_t idx)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x80 | (idx & 0b11));
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::reset(void)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0xF9);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::resetToDefaults(void)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0xF8);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::patchSend(Patch patch)
{
  uint16_t patchSize = sizeof(Patch);

  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x00);
  SPI.transfer(patchSize);
  const byte * p = (const byte*) &patch;
  for(int i=0; i < patchSize; i++)
  {
    SPI.transfer(*p++);
  }
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::patchWriteData(uint8_t addr, uint8_t data)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x20);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::partWriteData(uint8_t addr, uint8_t data)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x30);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}

void AmbikaVoicecard::lfoWrite(uint8_t idx, uint8_t val)
{
  SPI.beginTransaction(SPI_SETTINGS);
  digitalWrite (_pin_cs, LOW);
  SPI.transfer(0x50 | (idx & 0b11));
  SPI.transfer(val);
  digitalWrite (_pin_cs, HIGH);
  SPI.endTransaction();
}
