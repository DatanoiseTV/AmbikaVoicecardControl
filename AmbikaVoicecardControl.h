#include <SPI.h>
#define SPI_SETTINGS SPISettings(8000000, MSBFIRST, SPI_MODE0)

struct OscillatorSettings {
  uint8_t shape;
  uint8_t parameter;
  int8_t range;
  int8_t detune;
};

struct FilterSettings {
  uint8_t cutoff;
  uint8_t resonance;
  uint8_t mode;
};

struct EnvelopeLfoSettings {
  uint8_t attack;
  uint8_t decay;
  uint8_t sustain;
  uint8_t release;
  uint8_t shape;
  uint8_t rate;
  uint8_t padding;
  uint8_t retrigger_mode;
};

struct Modulation {
  uint8_t source;
  uint8_t destination;
  int8_t amount;
};

struct Modifier {
  uint8_t operands[2];
  uint8_t op;
};

enum OscillatorAlgorithm {
  WAVEFORM_NONE,
  WAVEFORM_SAW,
  WAVEFORM_SQUARE,
  WAVEFORM_TRIANGLE,
  WAVEFORM_SINE,
  WAVEFORM_CZ_SAW,
  WAVEFORM_CZ_SAW_LP,
  WAVEFORM_CZ_SAW_PK,
  WAVEFORM_CZ_SAW_BP,
  WAVEFORM_CZ_SAW_HP,
  WAVEFORM_CZ_PLS_LP,
  WAVEFORM_CZ_PLS_PK,
  WAVEFORM_CZ_PLS_BP,
  WAVEFORM_CZ_PLS_HP,
  WAVEFORM_CZ_TRI_LP,
  WAVEFORM_QUAD_SAW_PAD,
  WAVEFORM_FM,
  WAVEFORM_8BITLAND,
  WAVEFORM_DIRTY_PWM,
  WAVEFORM_FILTERED_NOISE,
  WAVEFORM_VOWEL,
  WAVEFORM_WAVETABLE_1,
  WAVEFORM_WAVETABLE_16 = WAVEFORM_WAVETABLE_1 - 1 + 16,
  WAVEFORM_WAVEQUENCE,
  WAVEFORM_LAST
};

enum SubOscillatorAlgorithm {
  WAVEFORM_SUB_OSC_SQUARE_1,
  WAVEFORM_SUB_OSC_TRIANGLE_1,
  WAVEFORM_SUB_OSC_PULSE_1,
  WAVEFORM_SUB_OSC_SQUARE_2,
  WAVEFORM_SUB_OSC_TRIANGLE_2,
  WAVEFORM_SUB_OSC_PULSE_2,
  WAVEFORM_SUB_OSC_CLICK,
  WAVEFORM_SUB_OSC_GLITCH,
  WAVEFORM_SUB_OSC_BLOW,
  WAVEFORM_SUB_OSC_METALLIC,
  WAVEFORM_SUB_OSC_POP,
  WAVEFORM_SUB_OSC_LAST
};

enum Operator {
  OP_SUM,
  OP_SYNC,
  OP_RING_MOD,
  OP_XOR,
  OP_FOLD,
  OP_BITS,
  OP_LAST
};

enum ModifierOp {
  MODIFIER_NONE,
  MODIFIER_SUM,
  MODIFIER_PRODUCT,
  MODIFIER_ATTENUATE,
  MODIFIER_MAX,
  MODIFIER_MIN,
  MODIFIER_XOR,
  MODIFIER_GE,
  MODIFIER_LE,
  MODIFIER_QUANTIZE,
  MODIFIER_LAG_PROCESSOR,
  MODIFIER_LAST
};

enum LfoWave {
  // For oscillators.
  LFO_WAVEFORM_TRIANGLE,
  LFO_WAVEFORM_SQUARE,
  LFO_WAVEFORM_S_H,
  LFO_WAVEFORM_RAMP,
  LFO_WAVEFORM_WAVE_1,
  LFO_WAVEFORM_WAVE_2,
  LFO_WAVEFORM_WAVE_3,
  LFO_WAVEFORM_WAVE_4,
  LFO_WAVEFORM_WAVE_5,
  LFO_WAVEFORM_WAVE_6,
  LFO_WAVEFORM_WAVE_7,
  LFO_WAVEFORM_WAVE_8,
  LFO_WAVEFORM_WAVE_9,
  LFO_WAVEFORM_WAVE_10,
  LFO_WAVEFORM_WAVE_11,
  LFO_WAVEFORM_WAVE_12,
  LFO_WAVEFORM_WAVE_13,
  LFO_WAVEFORM_WAVE_14,
  LFO_WAVEFORM_WAVE_15,
  LFO_WAVEFORM_WAVE_16,
  LFO_WAVEFORM_LAST
};

enum LfoSyncMode {
  LFO_SYNC_MODE_FREE,
  LFO_SYNC_MODE_SLAVE,
  LFO_SYNC_MODE_MASTER,
  LFO_SYNC_MODE_LAST
};

enum ModulationSource {
  MOD_SRC_ENV_1,
  MOD_SRC_ENV_2,
  MOD_SRC_ENV_3,

  MOD_SRC_LFO_1,
  MOD_SRC_LFO_2,
  MOD_SRC_LFO_3,
  MOD_SRC_LFO_4,

  MOD_SRC_OP_1,
  MOD_SRC_OP_2,
  MOD_SRC_OP_3,
  MOD_SRC_OP_4,

  MOD_SRC_SEQ_1,
  MOD_SRC_SEQ_2,
  MOD_SRC_ARP_STEP,

  MOD_SRC_VELOCITY,
  MOD_SRC_AFTERTOUCH,
  MOD_SRC_PITCH_BEND,
  MOD_SRC_WHEEL,
  MOD_SRC_WHEEL_2,
  MOD_SRC_EXPRESSION,

  MOD_SRC_NOTE,
  MOD_SRC_GATE,
  MOD_SRC_NOISE,
  MOD_SRC_RANDOM,
  MOD_SRC_CONSTANT_256,
  MOD_SRC_CONSTANT_128,
  MOD_SRC_CONSTANT_64,
  MOD_SRC_CONSTANT_32,
  MOD_SRC_CONSTANT_16,
  MOD_SRC_CONSTANT_8,
  MOD_SRC_CONSTANT_4,
  MOD_SRC_LAST
};

enum ModulationDestination {
  MOD_DST_PARAMETER_1,
  MOD_DST_PARAMETER_2,
  MOD_DST_OSC_1,
  MOD_DST_OSC_2,
  MOD_DST_OSC_1_2_COARSE,
  MOD_DST_OSC_1_2_FINE,

  MOD_DST_MIX_BALANCE,
  MOD_DST_MIX_PARAM,
  MOD_DST_MIX_NOISE,
  MOD_DST_MIX_SUB_OSC,
  MOD_DST_MIX_FUZZ,
  MOD_DST_MIX_CRUSH,

  MOD_DST_FILTER_CUTOFF,
  MOD_DST_FILTER_RESONANCE,

  MOD_DST_ATTACK,
  MOD_DST_DECAY,
  MOD_DST_RELEASE,
  MOD_DST_LFO_4,

  MOD_DST_VCA,

  MOD_DST_LAST
};

enum FilterMode {
  FILTER_MODE_LP,
  FILTER_MODE_BP,
  FILTER_MODE_HP,
  FILTER_MODE_NOTCH,
};

static const uint8_t kNumSyncedLfoRates = 15;
static const uint8_t kNumEnvelopes = 3;
static const uint8_t kNumLfos = kNumEnvelopes;
static const uint8_t kNumModulations = 14;
static const uint8_t kNumModifiers = 4;
static const uint8_t kNumOscillators = 2;
static const uint8_t kNumModulationSources = MOD_SRC_LAST;
static const uint8_t kNumModulationDestinations = MOD_DST_LAST;

struct Patch {
  // Offset: 0-8
  OscillatorSettings osc[kNumOscillators];

  // Offset: 8-16
  uint8_t mix_balance;
  uint8_t mix_op;
  uint8_t mix_parameter;
  uint8_t mix_sub_osc_shape;
  uint8_t mix_sub_osc;
  uint8_t mix_noise;
  uint8_t mix_fuzz;
  uint8_t mix_crush;

  // Offset: 16-24
  FilterSettings filter[2];
  int8_t filter_env;
  int8_t filter_lfo;

  // Offset: 24-48
  EnvelopeLfoSettings env_lfo[kNumEnvelopes];

  // Offset: 48-50
  uint8_t voice_lfo_shape;
  uint8_t voice_lfo_rate;

  // Offset: 50-92
  Modulation modulation[kNumModulations];

  // Offset: 92-104
  Modifier modifier[kNumModifiers];

  // Offset: 104-112
  uint8_t padding[8];
};


enum ProtocolCommands {
  COMMAND_BULK_SEND = 0x00,

  COMMAND_NOTE_ON = 0x10,
  COMMAND_NOTE_ON_LEGATO = 0x11,

  COMMAND_WRITE_PATCH_DATA = 0x20,
  COMMAND_WRITE_PART_DATA = 0x30,
  COMMAND_WRITE_MOD_MATRIX = 0x40,
  COMMAND_WRITE_LFO = 0x50,

  COMMAND_RELEASE = 0x60,
  COMMAND_KILL = 0x70,

  COMMAND_RETRIGGER_ENVELOPE = 0x80,

  COMMAND_RESET_ALL_CONTROLLERS = 0xf8,
  COMMAND_RESET = 0xf9,

  COMMAND_LIGHTS_OUT = 0xfa,
  COMMAND_FIRMWARE_UPDATE_MODE = 0xfb,
  COMMAND_GET_SLAVE_ID = 0xfc,
  COMMAND_GET_VERSION_ID = 0xfd,
  COMMAND_SYNC = 0xff
};

enum PatchParameter {
  PRM_PATCH_OSC1_SHAPE,
  PRM_PATCH_OSC1_PWM,
  PRM_PATCH_OSC1_RANGE,
  PRM_PATCH_OSC1_DETUNE,
  PRM_PATCH_OSC2_SHAPE,
  PRM_PATCH_OSC2_PWM,
  PRM_PATCH_OSC2_RANGE,
  PRM_PATCH_OSC2_DETUNE,

  PRM_PATCH_MIX_BALANCE,
  PRM_PATCH_MIX_OPERATOR,
  PRM_PATCH_MIX_PARAMETER,
  PRM_PATCH_MIX_SUB_SHAPE,
  PRM_PATCH_MIX_SUB_LEVEL,
  PRM_PATCH_MIX_NOISE_LEVEL,
  PRM_PATCH_MIX_FUZZ,
  PRM_PATCH_MIX_CRUSH,

  PRM_PATCH_FILTER1_CUTOFF,
  PRM_PATCH_FILTER1_RESONANCE,
  PRM_PATCH_FILTER1_MODE,
  PRM_PATCH_FILTER2_CUTOFF,
  PRM_PATCH_FILTER2_RESONANCE,
  PRM_PATCH_FILTER2_MODE,
  PRM_PATCH_FILTER1_ENV,
  PRM_PATCH_FILTER1_LFO,

  PRM_PATCH_ENV_ATTACK,
  PRM_PATCH_ENV_DECAY,
  PRM_PATCH_ENV_SUSTAIN,
  PRM_PATCH_ENV_RELEASE,
  PRM_PATCH_LFO_SHAPE,
  PRM_PATCH_LFO_RATE,
  PRM_PATCH_LFO_ATTACK,
  PRM_PATCH_LFO_SYNC,

  PRM_PATCH_VOICE_LFO_SHAPE = 48,
  PRM_PATCH_VOICE_LFO_RATE,

  PRM_PATCH_MOD_SOURCE,
  PRM_PATCH_MOD_DESTINATION,
  PRM_PATCH_MOD_AMOUNT,

  PRM_PATCH_MOD_OPERAND1 = 92,
  PRM_PATCH_MOD_OPERAND2,
  PRM_PATCH_MOD_OPERATOR
};

class AmbikaVoicecard
{
public:
  AmbikaVoicecard(int pin_cs)
  {
    _pin_cs = pin_cs;
    pinMode(_pin_cs, OUTPUT);
    SPI.begin();
  };

  void triggerNote(uint8_t pitch, uint8_t velocity, bool legato);
  void envelopeRelease(void);
  void envelopeRetrigger(uint8_t idx);

  void resetToDefaults(void);
  void reset(void);

  void patchSend(Patch patch);
  void patchWriteData(uint8_t addr, uint8_t data);
  void partWriteData(uint8_t addr, uint8_t data);

  void lfoWrite(uint8_t idx, uint8_t val);

private:
  int _pin_cs;
};
