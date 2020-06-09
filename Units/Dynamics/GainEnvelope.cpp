#include "GainEnvelope.h"

const std::size_t dsp::GainEnvelope::ATTACK = 1;
const std::size_t dsp::GainEnvelope::RELEASE = 2;

dsp::GainEnvelope::GainEnvelope() : Processor(Connection::Type::DECIBELS, Connection::Type::DECIBELS) {
    pushInput(Connection::Type::SECONDS);
    pushInput(Connection::Type::SECONDS);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::GainEnvelope::getAttack() {
    return getInput(ATTACK);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::GainEnvelope::getRelease() {
    return getInput(RELEASE);
}

void dsp::GainEnvelope::setNumChannels(std::size_t numChannels) {
    lock();
    Unit::setNumChannelsNoLock(numChannels);
    outputPrevious.resize(numChannels, 0);
    unlock();
}

void dsp::GainEnvelope::process() {
    Generator::process();
    for (std::size_t i = 0; i < getNumChannels(); i++) {
        std::vector<DSP_FLOAT> &inputBuffer = getInputSignal()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &outputBuffer = getOutputSignal()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &attackBuffer = getAttack()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &releaseBuffer = getRelease()->getChannel(i)->getBuffer();
        for (int k = 0; k < getBufferSize(); k++) {
            DSP_FLOAT samples;
            if (abs(inputBuffer[k]) > abs(outputPrevious[i])) {
                samples = attackBuffer[k] * getSampleRate();
            } else {
                samples = releaseBuffer[k] * getSampleRate();
            }
            outputPrevious[i] = inputBuffer[k] - pow(0.001, 1.0 / samples) * (outputPrevious[i] - inputBuffer[k]);
            outputBuffer[k] = outputPrevious[i];
        }
    }
}