#include "PluginEditor.h"
#include "BinaryData.h"

GainControllerAudioProcessorEditor::GainControllerAudioProcessorEditor(GainControllerAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(520, 380);

    // gain control
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    gainSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF884FFC));
    addAndMakeVisible(gainSlider);
    gainAttachment.reset(new SliderAttachment(processorRef.parameters, "gain", gainSlider));
    gainSlider.onValueChange = [this] { updateDisplay(); };
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    // pan control
    panSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    panSlider.setColour(juce::Slider::thumbColourId, juce::Colour(0xFF884FFC));
    addAndMakeVisible(panSlider);
    panAttachment.reset(new SliderAttachment(processorRef.parameters, "pan", panSlider));
    panSlider.onValueChange = [this] { updateDisplay(); };
    panLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(panLabel);

    // mode switch
    modeSwitch.setLookAndFeel(&switchLAF);
    addAndMakeVisible(modeSwitch);
    modeAttachment.reset(new juce::AudioProcessorValueTreeState::ButtonAttachment(
        processorRef.parameters, "mode", modeSwitch));

    startTimerHz(30);
    updateDisplay();
}

GainControllerAudioProcessorEditor::~GainControllerAudioProcessorEditor()
{
    modeSwitch.setLookAndFeel(nullptr);
}

void GainControllerAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    // LEDs aligned with switch
    int y = modeSwitch.getY() + modeSwitch.getHeight() / 2 - 6;
    g.setColour(inputLightColour);
    g.fillRect(30, y, 24, 12);
    g.setColour(outputLightColour);
    g.fillRect(getWidth() - 54, y, 24, 12);
}

void GainControllerAudioProcessorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();
    int knobW = 200;
    int marginX = (w - 2 * knobW) / 3;
    int topY = 50;

    gainSlider.setBounds(marginX, topY, knobW, knobW);
    gainLabel.setBounds(marginX, topY + knobW + 5, knobW, 24);

    panSlider.setBounds(2 * marginX + knobW, topY, knobW, knobW);
    panLabel.setBounds(2 * marginX + knobW, topY + knobW + 5, knobW, 24);

    // center switch
    int switchW = 60, switchH = 30;
    int switchX = (w - switchW) / 2;
    int switchY = topY + knobW + 40;
    modeSwitch.setBounds(switchX, switchY, switchW, switchH);
}

void GainControllerAudioProcessorEditor::updateDisplay()
{
    float g = gainSlider.getValue();
    juce::String gt = (g <= 0.0001f)
        ? "Silent"
        : juce::String(juce::Decibels::gainToDecibels(g), 1) + " dB";
    gainLabel.setText(gt, juce::dontSendNotification);

    float p = panSlider.getValue();
    int pct = int(std::abs(p) * 100.0f);
    juce::String pt;
    if (p < -0.01f) pt = "L " + juce::String(pct) + "%";
    else if (p > 0.01f) pt = "R " + juce::String(pct) + "%";
    else                 pt = "C";
    panLabel.setText(pt, juce::dontSendNotification);
}

void GainControllerAudioProcessorEditor::timerCallback()
{
    auto inDb = processorRef.getInputLevelDb();
    auto outDb = processorRef.getOutputLevelDb();
    auto chooseColour = [](float db)
        {
            // multi-stage gradient: darkgreen -> lightgreen -> yellow, red on clip
            if (db < -24.0f)
                return juce::Colours::darkgrey;
            if (db > 0.0f)
                return juce::Colours::red;

            auto blend = [](juce::Colour a, juce::Colour b, float t)
                {
                    return a.interpolatedWith(b, juce::jlimit(0.0f, 1.0f, t));
                };

            if (db < -6.0f)
            {
                // db in [-24, -6): t in [0,1]
                float t = (db + 24.0f) / 18.0f;
                return blend(juce::Colours::darkgreen, juce::Colours::green, t);
            }
            else
            {
                // db in [-6, 0): t in [0,1]
                float t = (db + 6.0f) / 6.0f;
                return blend(juce::Colours::green, juce::Colours::yellow, t);
            }
        };

    inputLightColour = chooseColour(inDb);
    outputLightColour = chooseColour(outDb);
    repaint(0, 0, getWidth(), getHeight());
}
