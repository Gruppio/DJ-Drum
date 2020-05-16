
#include "RecorderMidiDecorator.h"

RecorderMidiDecorator::RecorderMidiDecorator(MidiRecorder *midiRecorder, Midi *midi): MidiDecorator(midi), midiRecorder(midiRecorder) {}

void RecorderMidiDecorator::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
    midiRecorder->recordNote(true, note, velocity, channel);
    midi->sendNoteOn(note, velocity, channel);
}

void RecorderMidiDecorator::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel)
{
    midiRecorder->recordNote(false, note, velocity, channel);
    midi->sendNoteOff(note, velocity, channel);
}

void RecorderMidiDecorator::update()
{
    midiRecorder->update();
    midi->update();
}
