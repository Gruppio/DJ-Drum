
#include "MidiNoteTimer.h"

MidiNoteTimer::MidiNoteTimer(Midi *midi)
{
    this->midi = midi;
}

void MidiNoteTimer::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel)
{
    midi->sendNoteOn(note, velocity, channel);
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
    midi->sendNoteOff(note, velocity, channel);
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