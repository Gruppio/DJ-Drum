
#include "MidiNoteTimer.h"

MidiNoteTimer::MidiNoteTimer(MidiRecorder *midiRecorder)
{
    this->midiRecorder = midiRecorder;
}

void MidiNoteTimer::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
    usbMIDI.sendNoteOn(note, velocity, channel);
    midiRecorder->recordNote(true, note, velocity, channel);
    _numberOfNotesCurrenltyPlaying++;
    if (DEBUG)
    {
        Serial.print("ON:");
        Serial.print(note);
        Serial.print(", V:");
        Serial.print(velocity);
        Serial.print(", C:");
        Serial.println(channel);
    }
}

void MidiNoteTimer::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel)
{
    usbMIDI.sendNoteOff(note, velocity, channel);
    midiRecorder->recordNote(false, note, velocity, channel);
    _numberOfNotesCurrenltyPlaying--;
    if (DEBUG)
    {
        Serial.print("OFF:");
        Serial.print(note);
        Serial.print(", V:");
        Serial.print(velocity);
        Serial.print(", C:");
        Serial.println(channel);
    }
}

void MidiNoteTimer::sendNote(uint8_t note, uint8_t velocity, uint8_t channel, int duration)
{
    sendNoteOn(note, velocity, channel);
    MidiNoteRecord *midiNoteOffRecord = new MidiNoteRecord(false, note, velocity, channel, millis() + (unsigned long) duration);
    scheduledMidiNoteOff.push_back(midiNoteOffRecord);
}

void MidiNoteTimer::update()
{
    if (scheduledMidiNoteOff.empty())
        return;

    MidiNoteRecord *noteRecord = scheduledMidiNoteOff.front();
    if (noteRecord->timestamp <= millis())
    {
        sendNoteOff(noteRecord->note, noteRecord->velocity, noteRecord->channel);
        scheduledMidiNoteOff.pop_front();
        delete (noteRecord);
    }
}

int MidiNoteTimer::numberOfNotesCurrenltyPlaying()
{
    return _numberOfNotesCurrenltyPlaying;
}