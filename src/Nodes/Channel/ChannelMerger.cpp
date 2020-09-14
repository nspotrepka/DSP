#include "ChannelMerger.h"

dsp::ChannelMerger::ChannelMerger(Type type, Space space)
        : Producer(type, space) {}

std::shared_ptr<dsp::Input> dsp::ChannelMerger::getInput(size_t channel) const {
    DSP_ASSERT(channel < inputs.size());
    return inputs[channel];
}

void dsp::ChannelMerger::setNumInputChannelsNoLock(size_t numChannels) {}

void dsp::ChannelMerger::setNumOutputChannelsNoLock(size_t numChannels) {
    if (numChannels < getNumOutputChannels()) {
        inputs.resize(numChannels);
    } else {
        inputs.reserve(numChannels);
        for (size_t channel = numChannels; channel < getNumOutputChannels(); ++channel) {
            inputs.push_back(std::make_shared<Input>(getOutput()->getType(), getOutput()->getSpace(), getOutput()->getDefaultValue(), 1, getOutput()->getNumSamples()));
        }
    }
    Node::setNumOutputChannelsNoLock(numChannels);
}

void dsp::ChannelMerger::processNoLock() {

}
