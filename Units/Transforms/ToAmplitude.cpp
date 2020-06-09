#include "DecibelsToUnipolar.h"

dsp::DecibelsToUnipolar::DecibelsToUnipolar() : Processor(Connection::Type::DECIBELS, Connection::Type::UNIPOLAR) {}

void dsp::DecibelsToUnipolar::process() {
    Processor::process();
    for (std::size_t i = 0; i < getNumChannels(); i++) {
        std::transform(getInputSignal()->getChannel(i)->getBuffer().begin(),
                       getInputSignal()->getChannel(i)->getBuffer().end(),
                       getOutputSignal()->getChannel(i)->getBuffer().begin(),
                       decibelsToAmplitude);
    }
}
