#pragma once

#include "Connection.h"
#include "Runnable.h"
#include <map>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace dsp {

class Unit : public Runnable {

public:
    Unit();

    unsigned int getNumChannels() const;
    void setNumChannels(unsigned int numChannels);

    bool isActive() const;
    void setActive(bool active);

    unsigned int getNumInputs() const;
    unsigned int getNumOutputs() const;
    std::shared_ptr<InputParameter> getInput(unsigned int index) const;
    std::shared_ptr<OutputParameter> getOutput(unsigned int index) const;
    void pushInput(std::shared_ptr<InputParameter> input);
    void pushOutput(std::shared_ptr<OutputParameter> output);
    std::shared_ptr<InputParameter> pushInput(Type type, Space space = Space::TIME, DSP_FLOAT defaultValue = 0.0);
    std::shared_ptr<OutputParameter> pushOutput(Type type, Space space = Space::TIME, DSP_FLOAT defaultValue = 0.0);
    void replaceInput(std::shared_ptr<InputParameter> input, std::shared_ptr<InputParameter> replacement);
    void replaceOutput(std::shared_ptr<OutputParameter> output, std::shared_ptr<OutputParameter> replacement);
    void removeInput(std::shared_ptr<InputParameter> input);
    void removeOutput(std::shared_ptr<OutputParameter> output);

    unsigned int getNumUnits() const;
    std::shared_ptr<Unit> getUnit(unsigned int index) const;
    void pushUnit(std::shared_ptr<Unit> unit, bool sort = false);
    void pushUnits(std::vector<std::shared_ptr<Unit>> units, bool sort = false);
    void replaceUnit(std::shared_ptr<Unit> unit, std::shared_ptr<Unit> replacement);
    void removeUnit(std::shared_ptr<Unit> unit);
    void removeUnits(std::vector<std::shared_ptr<Unit>> units);
    void sortUnits();

    void run();

protected:
    std::vector<std::shared_ptr<InputParameter>> inputs;
    std::vector<std::shared_ptr<OutputParameter>> outputs;
    std::vector<std::shared_ptr<Unit>> children;

    void setSampleRateNoLock(unsigned int sampleRate) override;
    void setBufferSizeNoLock(unsigned int bufferSize) override;
    virtual void setNumChannelsNoLock(unsigned int numChannels);
    void sortUnitsNoLock();

    virtual void connect();
    virtual void disconnect();
    virtual void process();

private:
    unsigned int numChannels;
    bool active;

    void prepare();
};

} // namespace dsp
