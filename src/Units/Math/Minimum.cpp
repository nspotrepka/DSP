#include "Minimum.h"

dsp::Minimum::Minimum(Connection::Type type) : Processor(type, type), type(type) {}

void dsp::Minimum::pushInput() {
    Unit::pushInput(type);
}

void dsp::Minimum::process() {
    Unit::process();
    for (std::size_t i = 0; i < getNumChannels(); i++) {
        getOutputSignal()->getChannel(i)->fillBuffer(std::numeric_limits<DSP_FLOAT>::infinity());
        for (const auto &input : inputs) {
            std::transform(getOutputSignal()->getChannel(i)->getBuffer().begin(),
                           getOutputSignal()->getChannel(i)->getBuffer().end(),
                           input->getChannel(i)->getBuffer().begin(),
                           getOutputSignal()->getChannel(i)->getBuffer().begin(),
                           [](DSP_FLOAT x, DSP_FLOAT y) { return fmin(x, y); });
        }
    }
}