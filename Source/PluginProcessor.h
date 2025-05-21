#pragma once

#include <JuceHeader.h>

class GainControllerAudioProcessor : public juce::AudioProcessor
{
public:
    GainControllerAudioProcessor();
    ~GainControllerAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState parameters;
    float getInputLevelDb() const noexcept { return inputLevelDb.load(); }
    float getOutputLevelDb() const noexcept { return outputLevelDb.load(); }

private:
    std::atomic<float>* gainParam = nullptr;
    std::atomic<float>* panParam = nullptr;
    std::atomic<float>* modeParam = nullptr;  // false = Stereo, true = Mono

    float lastGain = 1.0f;
    float lastPan = 0.0f;

    std::atomic<float> inputLevelDb{ -100.0f };
    std::atomic<float> outputLevelDb{ -100.0f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainControllerAudioProcessor)
};