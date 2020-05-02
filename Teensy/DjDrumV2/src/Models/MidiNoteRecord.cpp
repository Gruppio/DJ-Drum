
#include "MidiNoteRecord.h"

MidiNoteRecord::MidiNoteRecord(bool isOn, uint8_t note, uint8_t velocity, uint8_t channel, unsigned long timestamp)
{
    this->isOn;
    this->note = note;
    this->velocity = velocity;
    this->channel = channel;
    this->timestamp = timestamp;
}