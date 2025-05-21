#include "PluginProcessor.h"
#include "PluginEditor.h"

GainControllerAudioProcessor::GainControllerAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, juce::Identifier("Params"),
        {
            std::make_unique<juce::AudioParameterFloat>("gain", "Gain",
                juce::NormalisableRange<float>(0.0f, 2.0f, 0.01f), 1.0f),
            std::make_unique<juce::AudioParameterFloat>("pan",  "Pan",
                juce::NormalisableRange<float>(-1.0f, 1.0f, 0.01f), 0.0f)
        })
{
    gainParam = parameters.getRawParameterValue("gain");
    panParam = parameters.getRawParameterValue("pan");
}

GainControllerAudioProcessor::~GainControllerAudioProcessor() {}

void GainControllerAudioProcessor::prepareToPlay(double /*sr*/, int /*spb*/)
{
    lastGain = gainParam->load();
    lastPan = panParam->load();
}

void GainControllerAudioProcessor::releaseResources() {}

void GainControllerAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    const int channels = buffer.getNumChannels();
    const int samples = buffer.getNumSamples();

    // Measure input peak
    float peakIn = 0.0f;
    for (int ch = 0; ch < channels; ++ch)
        for (int i = 0; i < samples; ++i)
            peakIn = std::max(peakIn, std::abs(buffer.getReadPointer(ch)[i]));
    inputLevelDb.store(juce::Decibels::gainToDecibels(peakIn, -100.0f));

    // Get targets
    float tgtGain = gainParam->load();
    float tgtPan = panParam->load();

    // Linear pan: center = unity
    auto computePan = [](float pan) {
        float left = pan <= 0.0f ? 1.0f : 1.0f - pan;
        float right = pan >= 0.0f ? 1.0f : 1.0f + pan;
        return std::make_pair(left, right);
        };
    auto [startL, startR] = computePan(lastPan);
    auto [endL, endR] = computePan(tgtPan);

    // Ramp gain & pan
    for (int ch = 0; ch < getTotalNumOutputChannels(); ++ch)
    {
        bool isLeft = (ch == 0);
        float g0 = lastGain * (isLeft ? startL : startR);
        float g1 = tgtGain * (isLeft ? endL : endR);
        buffer.applyGainRamp(ch, 0, samples, g0, g1);
    }
    lastGain = tgtGain;
    lastPan = tgtPan;

    // Measure output peak
    float peakOut = 0.0f;
    for (int ch = 0; ch < channels; ++ch)
        for (int i = 0; i < samples; ++i)
            peakOut = std::max(peakOut, std::abs(buffer.getReadPointer(ch)[i]));
    outputLevelDb.store(juce::Decibels::gainToDecibels(peakOut, -100.0f));
}

juce::AudioProcessorEditor* GainControllerAudioProcessor::createEditor() { return new GainControllerAudioProcessorEditor(*this); }
bool GainControllerAudioProcessor::hasEditor() const { return true; }

void GainControllerAudioProcessor::getStateInformation(juce::MemoryBlock& mb)
{
    copyXmlToBinary(*parameters.copyState().createXml(), mb);
}

void GainControllerAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    parameters.replaceState(juce::ValueTree::fromXml(*getXmlFromBinary(data, sizeInBytes)));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new GainControllerAudioProcessor(); }

