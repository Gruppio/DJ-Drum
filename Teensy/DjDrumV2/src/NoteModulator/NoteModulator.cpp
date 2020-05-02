
#include "NoteModulator.h"

NoteModulator::NoteModulator()
{
    for(int i = 0; i < NUMBER_OF_MIDI_CHANNELS; i++) 
    {
        channelOctave[i] = DEFAULT_OCTAVE;
    }
}

uint8_t NoteModulator::noteForPad(int pad)
{
    int padOffset = padOffsets()[pad];
    int octave = channelOctave[channel];
    int intonation = channelIntonation[channel];
    int note = ((octave + 1) * 12) + intonation + padOffset;
    return (uint8_t)note;
}

int* NoteModulator::padOffsets() {
    Scale scale = getScale();
    switch (scale)
    {
    case Normal:
        return normalScale;
        break;
    case Major:
        return majorScale;
        break;
    case BlackAndWhite:
        return blackAndWhiteScale;
        break;
    }
    return normalScale;
}

uint8_t NoteModulator::getChannel()
{
    return channel + 1;
}

uint8_t NoteModulator::getOctave()
{
    return channelOctave[channel];
}

uint8_t NoteModulator::getIntonation()
{
    return channelIntonation[channel];
}

Scale NoteModulator::getScale()
{
    return (Scale)channelScale[channel];
}

void NoteModulator::incrChannel()
{
    channel = constrain(channel + 1, 0, NUMBER_OF_MIDI_CHANNELS);
}

void NoteModulator::decrChannel()
{
    channel = constrain(channel - 1, 0, NUMBER_OF_MIDI_CHANNELS);
}

void NoteModulator::incrOctave()
{
    channelOctave[channel] = constrain(channelOctave[channel] + 1, 0, NUMBER_OF_OCTAVES);
}

void NoteModulator::decrOctave()
{
    channelOctave[channel] = constrain(channelOctave[channel] - 1, 0, NUMBER_OF_OCTAVES);
}

void NoteModulator::incrScale()
{
    channelScale[channel] = constrain(channelScale[channel] + 1, 0, NUMBER_OF_SCALES);
}

void NoteModulator::decrScale()
{
    channelScale[channel] = constrain(channelScale[channel] - 1, 0, NUMBER_OF_SCALES);
}

void NoteModulator::incrIntonation()
{
    channelIntonation[channel] = constrain(channelIntonation[channel] + 1, 0, NUMBER_OF_INTONATIONS);
}

void NoteModulator::decrIntonation()
{
    channelIntonation[channel] = constrain(channelIntonation[channel] - 1, 0, NUMBER_OF_INTONATIONS);
}