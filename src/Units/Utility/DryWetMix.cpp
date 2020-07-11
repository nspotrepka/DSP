#include "DryWetMix.h"

const unsigned int dsp::DryWetMix::DRY_SIGNAL = 0;
const unsigned int dsp::DryWetMix::WET_SIGNAL = 1;
const unsigned int dsp::DryWetMix::MIX_AMOUNT = 2;

dsp::DryWetMix::DryWetMix(Type type, Space space) : Processor(type, type, space) {
    assert(type != Type::BINARY);
    assert(type != Type::INTEGER);
    pushInput(type, space);
    pushInput(Type::UNIPOLAR, space);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::DryWetMix::getDrySignal() const {
    return getInput(DRY_SIGNAL);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::DryWetMix::getWetSignal() const {
    return getInput(WET_SIGNAL);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::DryWetMix::getMixAmount() const {
    return getInput(MIX_AMOUNT);
}

void dsp::DryWetMix::process() {
    Unit::process();
    for (unsigned int i = 0; i < getNumChannels(); i++) {
        std::vector<DSP_FLOAT> &dryBuffer = getDrySignal()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &wetBuffer = getWetSignal()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &mixBuffer = getMixAmount()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &outputBuffer = getOutputSignal()->getChannel(i)->getBuffer();
        for (unsigned int k = 0; k < getBufferSize(); k++) {
            outputBuffer[k] = dryBuffer[k] + mixBuffer[k] * (wetBuffer[k] - dryBuffer[k]);
        }
    }
}
