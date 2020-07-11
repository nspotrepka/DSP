#pragma once

#include "Audio.h"
#include "Midi.h"

#define USE_RTAUDIO 1

#if USE_RTAUDIO
#include "RtAudio.h"
#endif

namespace dsp {

class Engine {

public:
    Engine();
    ~Engine();

    std::vector<unsigned int> getInputDevices();
    std::vector<unsigned int> getOutputDevices();
    std::vector<unsigned int> getSampleRates(unsigned int inputDevice, unsigned int outputDevice);

    unsigned int getDefaultInputDevice();
    unsigned int getDefaultOutputDevice();
    unsigned int getDefaultSampleRate(unsigned int inputDevice, unsigned int outputDevice);

    void setup(unsigned int inputDevice, unsigned int outputDevice, unsigned int sampleRate, unsigned int bufferSize);
    void start();

    std::string getDeviceName(unsigned int device);
    std::string getInputDeviceName();
    std::string getOutputDeviceName();

    unsigned int getNumInputChannels();
    unsigned int getNumOutputChannels();
    unsigned int getSampleRate();
    unsigned int getBufferSize();

    std::shared_ptr<Unit::OutputParameter> getAudioInput();
    std::shared_ptr<Unit::InputParameter> getAudioOutput();

    unsigned int getNumUnits();
    std::shared_ptr<Unit> getUnit(unsigned int index);
    void pushUnit(std::shared_ptr<Unit> unit);
    void insertUnit(unsigned int index, std::shared_ptr<Unit> unit);
    void removeUnit(std::shared_ptr<Unit> unit);
    void removeUnit(unsigned int index);
    void sortUnits();

    unsigned int getNumMidiInputs();
    unsigned int getNumMidiOutputs();
    std::shared_ptr<Midi::MidiInput> getMidiInput(unsigned int index);
    std::shared_ptr<Midi::MidiOutput> getMidiOutput(unsigned int index);
    void pushMidiInput(unsigned int port);
    void pushMidiOutput(unsigned int port);
    void removeMidiInput(unsigned int index);
    void removeMidiOutput(unsigned int index);

private:
    std::shared_ptr<Audio> audio;
    std::shared_ptr<Midi> midi;
#if USE_RTAUDIO
    RtAudio dac;
#endif
    std::string inputDeviceName;
    std::string outputDeviceName;
    unsigned int numInputChannels;
    unsigned int numOutputChannels;
    unsigned int sampleRate;
    unsigned int bufferSize;
#if USE_RTAUDIO
    static int tick(void *outputBuffer,
                    void *inputBuffer,
                    unsigned int nBufferFrames,
                    double streamTime,
                    RtAudioStreamStatus status,
                    void *pointer);
#endif
    static void process(DSP_FLOAT *inputBuffer,
                        DSP_FLOAT *outputBuffer,
                        unsigned int numFrames,
                        unsigned int numInputChannels,
                        unsigned int numOutputChannels,
                        Engine *engine);
    unsigned int getDeviceCount();
    std::vector<unsigned int> getInputSampleRates(unsigned int inputDevice);
    std::vector<unsigned int> getOutputSampleRates(unsigned int outputDevice);
};

} // namespace dsp
