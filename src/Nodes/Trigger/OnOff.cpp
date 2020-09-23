#include "OnOff.h"

dsp::OnOff::OnOff()
        : Producer(Type::BINARY)
        , onTrigger(std::make_shared<Input>(Type::BINARY))
        , offTrigger(std::make_shared<Input>(Type::BINARY)) {
    getInputs().push_back(onTrigger);
    getInputs().push_back(offTrigger);
}

std::shared_ptr<dsp::Input> dsp::OnOff::getOnTrigger() const {
    return onTrigger;
}

std::shared_ptr<dsp::Input> dsp::OnOff::getOffTrigger() const {
    return offTrigger;
}

void dsp::OnOff::setNumOutputChannelsNoLock(size_t numChannels) {
    Node::setNumOutputChannelsNoLock(numChannels);
    state.resize(numChannels, false);
}

void dsp::OnOff::processNoLock() {
    for (size_t channel = 0; channel < getNumChannels(); ++channel) {
        Sample *onTriggerChannel = getOnTrigger()->getWrapper().getChannelPointer(channel);
        Sample *offTriggerChannel = getOffTrigger()->getWrapper().getChannelPointer(channel);
        Sample *outputChannel = getOutput()->getWrapper().getChannelPointer(channel);
        for (size_t sample = 0; sample < getNumSamples(); ++sample) {
            if (onTriggerChannel[sample]) {
                state[channel] = true;
            }
            if (offTriggerChannel[sample]) {
                state[channel] = false;
            }
            outputChannel[sample] = state[channel];
        }
    }
}
