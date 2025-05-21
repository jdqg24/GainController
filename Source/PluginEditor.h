#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class GainControllerAudioProcessorEditor : public juce::AudioProcessorEditor,
    private juce::Timer
{
public:
    GainControllerAudioProcessorEditor(GainControllerAudioProcessor&);
    ~GainControllerAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void updateDisplay();
    void timerCallback() override;

    GainControllerAudioProcessor& processorRef;
    juce::Slider gainSlider;
    juce::Label  gainLabel;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> gainAttachment;

    juce::Slider panSlider;
    juce::Label  panLabel;
    std::unique_ptr<Attachment> panAttachment;

    juce::Colour inputLightColour{ juce::Colours::green };
    juce::Colour outputLightColour{ juce::Colours::green };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainControllerAudioProcessorEditor)
};
