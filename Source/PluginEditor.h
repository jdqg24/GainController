// PluginEditor.h
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SwitchLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& tb,
        bool /*isMouseOver*/, bool /*isMouseDown*/) override
    {
        auto bounds = tb.getLocalBounds().toFloat().reduced(2.0f);
        // draw track
        g.setColour(juce::Colours::darkgrey);
        g.fillRoundedRectangle(bounds, bounds.getHeight() * 0.5f);
        // draw knob
        g.setColour(juce::Colours::lightgrey);
        float diameter = bounds.getHeight();
        float x = tb.getToggleState() ? bounds.getRight() - diameter : bounds.getX();
        juce::Rectangle<float> knobArea(x, bounds.getY(), diameter, diameter);
        g.fillEllipse(knobArea);
        // draw letter inside knob
        g.setColour(juce::Colours::black);
        g.setFont(juce::Font(diameter * 0.6f, juce::Font::bold));
        juce::String letter = tb.getToggleState() ? "M" : "S";
        g.drawFittedText(letter,
            knobArea.getX(), knobArea.getY(),
            (int)knobArea.getWidth(), (int)knobArea.getHeight(),
            juce::Justification::centred, 1);
    }
};

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

    juce::Slider gainSlider;  juce::Label gainLabel;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> gainAttachment;

    juce::Slider panSlider;   juce::Label panLabel;
    std::unique_ptr<SliderAttachment> panAttachment;

    juce::ToggleButton modeSwitch;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> modeAttachment;
    SwitchLookAndFeel switchLAF;

    juce::Colour inputLightColour{ juce::Colours::darkgrey };
    juce::Colour outputLightColour{ juce::Colours::darkgrey };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GainControllerAudioProcessorEditor)
};
