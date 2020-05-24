
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
    unsigned long offTime = millis() + (unsigned long) duration;

    for (std::list<MidiNoteRecord*>::iterator it = scheduledMidiNoteOff.begin(); it != scheduledMidiNoteOff.end(); ++it){
        if((*it)->note == note) {
            (*it)->timestamp = offTime;
        }
    }

    MidiNoteRecord *midiNoteOffRecord = new MidiNoteRecord(false, note, velocity, channel, offTime);
    scheduledMidiNoteOff.push_back(midiNoteOffRecord);
}

void MidiNoteTimer::update()
{
    if (scheduledMidiNoteOff.empty())
        return;

    for (std::list<MidiNoteRecord *>::iterator it = scheduledMidiNoteOff.begin(); it != scheduledMidiNoteOff.end(); ++it)
    {
        if ((*it)->timestamp <= millis())
        {
            sendNoteOff((*it)->note, (*it)->velocity, (*it)->channel);
            delete ((*it));
            it = scheduledMidiNoteOff.erase(it);
        }
    }
}

int MidiNoteTimer::numberOfNotesCurrenltyPlaying()
{
    return _numberOfNotesCurrenltyPlaying;
}