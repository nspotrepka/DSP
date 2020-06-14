# DSP

DSP is a lightweight C++ library for digital signal processing.

This project is still in development. Feedback and contributions are welcome!

## Usage

```cpp
#include "DSP.h"

int main() {
    std::shared_ptr<dsp::PassUnit> pass;

    // TODO: Do something more interesting than passing input to output
    pass = std::make_shared<dsp::PassUnit>(dsp::Connection::Type::BIPOLAR);
    pass->setNumChannels(2);

    // Setup engine
    dsp::Engine *engine = new dsp::Engine();
    std::vector<unsigned int> inputDevices = engine->getInputDevices();
    std::vector<unsigned int> outputDevices = engine->getOutputDevices();
    unsigned int inputDevice = inputDevices.size() > 0 ? inputDevices[0] : -1;
    unsigned int outputDevice = outputDevices.size() > 0 ? outputDevices[0] : -1;
    std::vector<unsigned int> sampleRates = engine->getAvailableSampleRates(inputDevice, outputDevice);
    unsigned int sampleRate = sampleRates.size() > 0 ? sampleRates[0] : 0;
    unsigned int bufferSize = 512;
    engine->setup(inputDevice, outputDevice, sampleRate, bufferSize);
    
    // Add units
    engine->getAudio()->pushUnit(pass);

    // Connect units
    engine->getAudio()->getAudioInput() >> pass->getInputSignal();
    pass->getOutputSignal() >> engine->getAudio()->getAudioOutput();
    
    delete engine;
}
```

## Future Direction

The following are possible directions for future development:
- Variable delay
- Delay effects
- Elliptic filter
- Cascading filters
- ADSR
- Real-time audio
- MIDI
- Sequencer
- Frequency response
- SIMD instructions
