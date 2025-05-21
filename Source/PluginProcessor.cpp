#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

GainControllerAudioProcessor::GainControllerAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, juce::Identifier("Params"),
        {
            std::make_unique<juce::AudioParameterFloat>("gain", "Gain",
                juce::NormalisableRange<float>(0.0f, 2.0f, 0.01f), 1.0f),
            std::make_unique<juce::AudioParameterFloat>("pan",  "Pan",
                juce::NormalisableRange<float>(-1.0f, 1.0f, 0.01f), 0.0f),
            std::make_unique<juce::AudioParameterBool>("mode","Mono Mode", false)
        })
{
    gainParam = parameters.getRawParameterValue("gain");
    panParam = parameters.getRawParameterValue("pan");
    modeParam = parameters.getRawParameterValue("mode");
}

GainControllerAudioProcessor::~GainControllerAudioProcessor() {}

void GainControllerAudioProcessor::prepareToPlay(double, int)
{
    lastGain = gainParam->load();
    lastPan = panParam->load();
}

void GainControllerAudioProcessor::releaseResources() {}

void GainControllerAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const int channels = buffer.getNumChannels();
    const int samples = buffer.getNumSamples();

    // Measure input level
    float peakIn = 0.0f;
    for (int ch = 0; ch < channels; ++ch)
        for (int i = 0; i < samples; ++i)
            peakIn = std::max(peakIn, std::abs(buffer.getReadPointer(ch)[i]));
    inputLevelDb.store(juce::Decibels::gainToDecibels(peakIn, -100.0f));

    float tgtGain = gainParam->load();
    float tgtPan = panParam->load();
    bool  monoMode = (modeParam->load() > 0.5f);

    if (monoMode)
    {
        // Mono panning: sum to mono then crossfade preserving volume
        juce::AudioBuffer<float> monoBuf(1, samples);
        monoBuf.clear();
        for (int ch = 0; ch < channels; ++ch)
            monoBuf.addFrom(0, 0, buffer, ch, 0, samples, 0.5f);

        float gainStart = lastGain;
        float gainEnd = tgtGain;
        float panStart = lastPan;
        float panEnd = tgtPan;

        for (int i = 0; i < samples; ++i)
        {
            float t = float(i) / float(samples);
            float gCur = gainStart + (gainEnd - gainStart) * t;
            float p = panStart + (panEnd - panStart) * t;
            float lG = (p <= 0.0f) ? gCur : gCur * (1.0f - p);
            float rG = (p >= 0.0f) ? gCur : gCur * (p + 1.0f);
            float s = monoBuf.getSample(0, i);
            buffer.setSample(0, i, s * lG);
            buffer.setSample(1, i, s * rG);
        }

        lastGain = tgtGain;
        lastPan = tgtPan;
    }
    else
    {
        // Stereo panning: scale channels individually
        float leftStart = (lastPan <= 0.0f) ? 1.0f : 1.0f - lastPan;
        float rightStart = (lastPan >= 0.0f) ? 1.0f : 1.0f + lastPan;
        float leftEnd = (tgtPan <= 0.0f) ? 1.0f : 1.0f - tgtPan;
        float rightEnd = (tgtPan >= 0.0f) ? 1.0f : 1.0f + tgtPan;

        for (int ch = 0; ch < channels; ++ch)
        {
            float sG = lastGain * (ch == 0 ? leftStart : rightStart);
            float eG = tgtGain * (ch == 0 ? leftEnd : rightEnd);
            buffer.applyGainRamp(ch, 0, samples, sG, eG);
        }

        lastGain = tgtGain;
        lastPan = tgtPan;
    }

    // Measure output level
    float peakOut = 0.0f;
    for (int ch = 0; ch < channels; ++ch)
        for (int i = 0; i < samples; ++i)
            peakOut = std::max(peakOut, std::abs(buffer.getReadPointer(ch)[i]));
    outputLevelDb.store(juce::Decibels::gainToDecibels(peakOut, -100.0f));
}

// Create the editor
juce::AudioProcessorEditor* GainControllerAudioProcessor::createEditor()
{
    return new GainControllerAudioProcessorEditor(*this);
}

// Needed for standalone and hosts
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainControllerAudioProcessor();
}

bool GainControllerAudioProcessor::hasEditor() const { return true; }

void GainControllerAudioProcessor::getStateInformation(juce::MemoryBlock& mb)
{
    copyXmlToBinary(*parameters.copyState().createXml(), mb);
}

void GainControllerAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    parameters.replaceState(juce::ValueTree::fromXml(*getXmlFromBinary(data, sizeInBytes)));
}