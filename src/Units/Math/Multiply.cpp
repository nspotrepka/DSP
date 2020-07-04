#include "Multiply.h"

dsp::Multiply::Multiply(Connection::Type type, Connection::Space space)
        : Processor(type, type, space), type(type), space(space) {}

void dsp::Multiply::pushInputBipolar() {
    Unit::pushInput(Connection::Type::BIPOLAR, space);
}

void dsp::Multiply::pushInputUnipolar() {
    Unit::pushInput(Connection::Type::UNIPOLAR, space);
}

void dsp::Multiply::pushInputRatio() {
    Unit::pushInput(Connection::Type::RATIO, space);
}

void dsp::Multiply::process() {
    Unit::process();
    for (std::size_t i = 0; i < getNumChannels(); i++) {
        getOutputSignal()->getChannel(i)->fillBuffer(1.0);
        for (const auto &input : inputs) {
            std::transform(getOutputSignal()->getChannel(i)->getBuffer().begin(),
                           getOutputSignal()->getChannel(i)->getBuffer().end(),
                           input->getChannel(i)->getBuffer().begin(),
                           getOutputSignal()->getChannel(i)->getBuffer().begin(),
                           std::multiplies<DSP_FLOAT>());
        }
    }
}
