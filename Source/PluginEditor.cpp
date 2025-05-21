#include "PluginEditor.h"

GainControllerAudioProcessorEditor::GainControllerAudioProcessorEditor(GainControllerAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(gainSlider);
    gainAttachment.reset(new Attachment(processorRef.parameters, "gain", gainSlider));
    gainSlider.onValueChange = [this] { updateDisplay(); };

    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    panSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    panSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(panSlider);
    panAttachment.reset(new Attachment(processorRef.parameters, "pan", panSlider));
    panSlider.onValueChange = [this] { updateDisplay(); };

    panLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(panLabel);

    setSize(350, 300);
    startTimerHz(30);
    updateDisplay();
}

GainControllerAudioProcessorEditor::~GainControllerAudioProcessorEditor() {}

void GainControllerAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawFittedText("Gain & Pan Controller", getLocalBounds().removeFromTop(28), juce::Justification::centred, 1);

    // Level LEDs: IN left, OUT right
    g.setColour(inputLightColour);
    g.fillRect(20, 50, 20, 10);
    g.setColour(outputLightColour);
    g.fillRect(getWidth() - 40, 50, 20, 10);
}

void GainControllerAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().withTrimmedTop(40).reduced(10);
    auto leftArea = area.removeFromLeft(area.getWidth() / 2);
    auto rightArea = area;

    gainSlider.setBounds(leftArea.removeFromTop(leftArea.getHeight() - 30));
    gainLabel.setBounds(leftArea.removeFromTop(30));

    panSlider.setBounds(rightArea.removeFromTop(rightArea.getHeight() - 30));
    panLabel.setBounds(rightArea.removeFromTop(30));
}

void GainControllerAudioProcessorEditor::updateDisplay()
{
    // Gain dB
    float gVal = gainSlider.getValue();
    gainLabel.setText(juce::String(juce::Decibels::gainToDecibels(gVal), 1) + " dB",
        juce::dontSendNotification);
    // Pan %
    float pVal = panSlider.getValue();
    int pct = int(std::abs(pVal) * 100.0f);
    juce::String txt;
    if (pVal < -0.01f)      txt = "L " + juce::String(pct) + "%";
    else if (pVal > 0.01f) txt = "R " + juce::String(pct) + "%";
    else                    txt = "C";
    panLabel.setText(txt, juce::dontSendNotification);
}

void GainControllerAudioProcessorEditor::timerCallback()
{
    float inDb = processorRef.getInputLevelDb();
    float outDb = processorRef.getOutputLevelDb();
    auto chooseColour = [](float db)
        {
            if (db < -6.0f)     return juce::Colours::green;
            if (db < 0.0f)     return juce::Colours::yellow;
            return juce::Colours::red;
        };
    inputLightColour = chooseColour(inDb);
    outputLightColour = chooseColour(outDb);
    repaint(0, 50, getWidth(), 10);
}