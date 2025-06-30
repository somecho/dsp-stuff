// WRITE A 4 SECOND LONG WAV FILE OF A 440 SINE WAVE

#include <cmath>
#include <sndfile.hh>

static constexpr size_t SAMPLE_COUNT = 44100;
static constexpr size_t DURATION_S = 4;

int main() {

  const size_t numSamples = SAMPLE_COUNT * DURATION_S;

  float buffer[numSamples] = {};

  float freq = 440;
  float amplitude = 0.2;

  for (size_t i = 0; i < SAMPLE_COUNT * 4; i++) {
    float theta = static_cast<float>(i) / SAMPLE_COUNT * M_PI * 2 * freq;
    buffer[i] = sinf(theta) * amplitude;
  }

  const int format = SF_FORMAT_WAV | SF_FORMAT_PCM_32;
  const int numChannels = 1;
  const int sampleRate = SAMPLE_COUNT;

  std::string outputPath("sinewave.wav");
  SndfileHandle outfile(outputPath, SFM_WRITE, format, numChannels, sampleRate);
  outfile.write(buffer, numSamples);

  return 0;
}
