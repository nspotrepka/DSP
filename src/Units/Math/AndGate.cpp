#include "AndGate.h"

dsp::AndGate::AndGate(Space space)
        : Generator(Type::BINARY, space) {}

void dsp::AndGate::pushInput() {
    Unit::pushInput(Type::BINARY, getOutputSignal()->getSpace(), 1.0);
}

void dsp::AndGate::process() {
    Unit::process();
    for (unsigned int i = 0; i < getNumChannels(); i++) {
        if (getNumInputs() > 0) {
            getOutputSignal()->getChannel(i)->fillBuffer(1.0);
            for (const auto &input : inputs) {
                std::transform(getOutputSignal()->getChannel(i)->getBuffer().begin(),
                               getOutputSignal()->getChannel(i)->getBuffer().end(),
                               input->getChannel(i)->getBuffer().begin(),
                               getOutputSignal()->getChannel(i)->getBuffer().begin(),
                               [](DSP_FLOAT x, DSP_FLOAT y) { return x && y; });
            }
        }
    }
}