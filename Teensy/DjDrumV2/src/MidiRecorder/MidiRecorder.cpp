
#include "MidiRecorder.h"

MidiRecorder::MidiRecorder()
{
}

void MidiRecorder::pressedRecording()
{
    switch (state)
    {
    case Idle:
        state = WaitStartRecording;
        break;

    case WaitStartRecording:
        break;

    case Recording:
        break;

    case WaitEndRecording:
        break;

    case Playing:
        state = Idle;
        break;

    default:
        break;
    }
}

void MidiRecorder::releasedRecording()
{
    switch (state)
    {
    case Idle:
        break;

    case WaitStartRecording:
        startPlaying();
        break;

    case Recording:
        state = WaitEndRecording;
        break;

    case WaitEndRecording:
        break;

    case Playing:
        break;
    
    default:
        break;
    }
}

void MidiRecorder::recordNote(bool isOn, uint8_t note, uint8_t velocity, uint8_t channel)
{
    switch (state)
    {
    case Idle:
        break;

    case WaitStartRecording:
        startRecording();
        MidiNoteRecord *noteRecord = new MidiNoteRecord(isOn, note, velocity, channel, millis() - startRecordingTimestamp);
        recordedMidiNotes.push_back(noteRecord);
        break;

    case Recording: 
        MidiNoteRecord *noteRecord2 = new MidiNoteRecord(isOn, note, velocity, channel, millis() - startRecordingTimestamp);
        recordedMidiNotes.push_back(noteRecord2);
        break;

    case WaitEndRecording:
        completeRecording();
        startPlaying();
        break;

    case Playing:
        break;

    default:
        break;
    }
}

void MidiRecorder::update()
{
    if (state != Playing)
        return;

    unsigned long currentTimestamp = millis() - startPlayingTimestamp;
    if (currentTimestamp >= recordingDuration)
        startPlaying();

    if(recordedMidiNotesIterator != recordedMidiNotes.end()) {
        MidiNoteRecord *midiNoteRecord = *recordedMidiNotesIterator;
        if(oldUpdateTimestamp < midiNoteRecord->timestamp && currentTimestamp >= midiNoteRecord->timestamp) {
            if(midiNoteRecord->isOn) {
                usbMIDI.sendNoteOn(midiNoteRecord->note, midiNoteRecord->velocity, midiNoteRecord->channel);
            } else {
                usbMIDI.sendNoteOff(midiNoteRecord->note, midiNoteRecord->velocity, midiNoteRecord->channel);
            }
            recordedMidiNotesIterator++;
        }
    }
        
    
    oldUpdateTimestamp = currentTimestamp;
}

void MidiRecorder::deleteRecording()
{
    MidiNoteRecord *recordedMidiNote = recordedMidiNotes.front();
    while (recordedMidiNote)
    {
        delete (recordedMidiNote);
        recordedMidiNotes.pop_front();
        recordedMidiNote = recordedMidiNotes.front();
    }
}

void MidiRecorder::startRecording()
{
    deleteRecording();
    hasRecording = false;
    state = Recording;
    startRecordingTimestamp = millis();
}

void MidiRecorder::completeRecording()
{
    recordingDuration = millis() - startRecordingTimestamp;
    hasRecording = true;
}

void MidiRecorder::startPlaying()
{
    if (!hasRecording)
            return;
    recordedMidiNotesIterator = recordedMidiNotes.begin();
    startPlayingTimestamp = millis();
    state = Playing;
}