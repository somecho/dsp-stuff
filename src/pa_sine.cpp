#include <assert.h>
#include <cmath>
#include <numbers>
#include <portaudio.h>
#include <print>

static constexpr float SAMPLE_RATE = 44100;

static constexpr float TAU = std::numbers::pi_v<float> * 2.f;

struct AudioData {
  float phase = 0.f;
} audioData;

static int callback(const void *inputBuffer, void *outputBuffer,
                    unsigned long framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags statusFlags, void *userData) {
  float *out = static_cast<float *>(outputBuffer);

  auto data = reinterpret_cast<AudioData *>(userData);

  constexpr float amp = 0.1f;
  for (size_t i = 0; i < framesPerBuffer; i++) {
    const float freq = 440.f;

    float sample = sinf(data->phase) * amp;
    data->phase += TAU * freq / SAMPLE_RATE;
    if (data->phase > TAU) {
      data->phase -= TAU;
    }
    *out++ = sample;
    *out++ = sample;
  }

  return paContinue;
}

static void finishedCallback(void *userData) {
  std::println("Stream finished");
}

int main() {
  auto err = Pa_Initialize();
  if (err != paNoError) {
    Pa_Terminate();
    return err;
  }

  auto numDevices = Pa_GetDeviceCount();
  assert(numDevices > 0);

  for (int i = 0; i < numDevices; i++) {
    auto deviceInfo = Pa_GetDeviceInfo(i);
    std::println("Device name {}: {}", i + 1, deviceInfo->name);
  }

  PaStreamParameters params;
  params.device = Pa_GetDefaultOutputDevice();
  auto deviceInfo = Pa_GetDeviceInfo(params.device);

  params.channelCount = 2;
  params.sampleFormat = paFloat32;
  params.suggestedLatency = deviceInfo->defaultLowOutputLatency;
  params.hostApiSpecificStreamInfo = nullptr;

  PaStream *stream(nullptr);
  err =
      Pa_OpenStream(&stream, nullptr, &params, static_cast<double>(SAMPLE_RATE),
                    256, paClipOff, callback, &audioData);

  if (err != paNoError) {
    auto errorText = Pa_GetErrorText(err);
    std::println("Failed to open stream: {}", errorText);
    Pa_Terminate();
    return err;
  }

  err = Pa_SetStreamFinishedCallback(stream, finishedCallback);
  if (err != paNoError) {
    auto errorText = Pa_GetErrorText(err);
    std::println("Failed to set stream finished callback: {}", errorText);
    Pa_Terminate();
    return err;
  }

  err = Pa_StartStream(stream);
  if (err != paNoError) {
    auto errorText = Pa_GetErrorText(err);
    std::println("{}", errorText);
    Pa_Terminate();
    return err;
  }

  Pa_Sleep(1000);

  assert((Pa_StopStream(stream) == paNoError));
  assert((Pa_CloseStream(stream) == paNoError));

  Pa_Terminate();
  return 0;
}
