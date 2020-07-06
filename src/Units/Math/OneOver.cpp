#include "OneOver.h"

dsp::OneOver::OneOver(Connection::Space space) : Processor(Connection::Type::RATIO, Connection::Type::RATIO, space) {}

void dsp::OneOver::process() {
    Unit::process();
    for (unsigned int i = 0; i < getNumChannels(); i++) {
        std::transform(getInputSignal()->getChannel(i)->getBuffer().begin(),
                       getInputSignal()->getChannel(i)->getBuffer().end(),
                       getOutputSignal()->getChannel(i)->getBuffer().begin(),
                       [](DSP_FLOAT x) { return 1.0 / x; });
    }
}