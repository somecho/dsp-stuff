#include <cmath>
#include <numbers>
#include <portaudio.h>
#include <print>

typedef float seconds;
static constexpr float SAMPLE_RATE = 44100.f;
static constexpr float TAU = std::numbers::pi_v<float> * 2.f;

// Attack Release Envelop Generator
class AREnvGen {
public:
  AREnvGen() = default;
  AREnvGen(seconds attack, seconds release, float amplitude)
      : amplitude(amplitude) {
    numAttackSamples = SAMPLE_RATE * attack;
    numReleaseSamples = SAMPLE_RATE * release;
  }

  void update() {
    if (phase >= numAttackSamples + numReleaseSamples) {
      return;
    }
    phase++;
  }

  float sample() {
    float a = phase / numAttackSamples;
    float r = 1.f - ((phase - numAttackSamples) / numReleaseSamples);
    float val = phase < numAttackSamples ? a : r; // linear
    return val * amplitude;
  }

private:
  float amplitude = 0.4f;
  float phase = 0.0f;
  float numAttackSamples;
  float numReleaseSamples;
};

class SinOsc {
public:
  SinOsc() = default;
  SinOsc(float freq) : freq(freq) {};

  void update() {
    phase += TAU * freq / SAMPLE_RATE;
    if (phase > TAU) {
      phase -= TAU;
    }
  }

  float sample() { return sinf(phase); }

private:
  float phase = 0.f;
  float freq = 440.f;
};

struct AppData {
  AREnvGen env;
  SinOsc osc;
};

static int callback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags, void *userData) {

  auto *data = reinterpret_cast<AppData *>(userData);
  auto *out = static_cast<float *>(outputBuffer);

  for (size_t i = 0; i < framesPerBuffer; i++) {
    *out++ = data->osc.sample() * data->env.sample();
    *out++ = data->osc.sample() * data->env.sample();
    data->env.update();
    data->osc.update();
  }

  return paContinue;
}

int main() {
  auto err = Pa_Initialize();
  if (err != paNoError) {
    Pa_Terminate();
    return err;
  }

  auto defaultDevice = Pa_GetDefaultOutputDevice();
  auto deviceInfo = Pa_GetDeviceInfo(defaultDevice);
  PaStreamParameters params;
  params.device = defaultDevice;
  params.channelCount = 2;
  params.sampleFormat = paFloat32;
  params.suggestedLatency = deviceInfo->defaultLowOutputLatency;
  params.hostApiSpecificStreamInfo = nullptr;

  AppData data{.env = AREnvGen(0.01f, 2.f, 0.5f), .osc = SinOsc(432.f)};

  PaStream *stream(nullptr);

  err =
      Pa_OpenStream(&stream, nullptr, &params, static_cast<double>(SAMPLE_RATE),
                    256, paClipOff, callback, &data);
  std::println("Pa_OpenStream returned: {}", err);

  if (err != paNoError) {
    std::println("Error opening stream: {}", Pa_GetErrorText(err));
    return err;
  }

  err = Pa_StartStream(stream);
  if (err != paNoError) {
    std::println("Error starting stream: {}", Pa_GetErrorText(err));
    return err;
  }

  Pa_Sleep(5000);

  err = Pa_StopStream(stream);
  if (err != paNoError) {
    std::println("Error stopping stream: {}", Pa_GetErrorText(err));
    return err;
  }

  err = Pa_CloseStream(stream);
  if (err != paNoError) {
    std::println("Error closing stream: {}", Pa_GetErrorText(err));
    return err;
  }
  Pa_Terminate();

  return err;
}
