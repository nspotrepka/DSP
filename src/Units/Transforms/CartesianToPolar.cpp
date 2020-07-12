#include "CartesianToPolar.h"

const unsigned int dsp::CartesianToPolar::REAL = 0;
const unsigned int dsp::CartesianToPolar::IMAGINARY = 1;
const unsigned int dsp::CartesianToPolar::MAGNITUDE = 0;
const unsigned int dsp::CartesianToPolar::PHASE = 1;

dsp::CartesianToPolar::CartesianToPolar() {
    pushInput(Type::BIPOLAR, Space::FREQUENCY);
    pushInput(Type::BIPOLAR, Space::FREQUENCY);
    pushOutput(Type::UNIPOLAR, Space::FREQUENCY);
    pushOutput(Type::UNIPOLAR, Space::FREQUENCY);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::CartesianToPolar::getReal() const {
    return getInput(REAL);
}

std::shared_ptr<dsp::Unit::InputParameter> dsp::CartesianToPolar::getImaginary() const {
    return getInput(IMAGINARY);
}

std::shared_ptr<dsp::Unit::OutputParameter> dsp::CartesianToPolar::getMagnitude() const {
    return getOutput(MAGNITUDE);
}

std::shared_ptr<dsp::Unit::OutputParameter> dsp::CartesianToPolar::getPhase() const {
    return getOutput(PHASE);
}

void dsp::CartesianToPolar::process() {
    Unit::process();
    for (unsigned int i = 0; i < getNumChannels(); i++) {
        std::vector<DSP_FLOAT> &realBuffer = getReal()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &imaginaryBuffer = getImaginary()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &magnitudeBuffer = getMagnitude()->getChannel(i)->getBuffer();
        std::vector<DSP_FLOAT> &phaseBuffer = getPhase()->getChannel(i)->getBuffer();
        for (unsigned int k = 0; k < getBufferSize(); k++) {
            magnitudeBuffer[k] = sqrt(realBuffer[k] * realBuffer[k] + imaginaryBuffer[k] * imaginaryBuffer[k]);
            DSP_FLOAT bipolar = ONE_OVER_TAU * atan2(imaginaryBuffer[k], realBuffer[k]);
            phaseBuffer[k] = bipolar < 0.0 ? bipolar + 1.0 : bipolar;
        }
    }
}