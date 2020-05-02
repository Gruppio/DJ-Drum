
#include "MidiRecorder.h"

MidiRecorder::MidiRecorder()
{
}

void MidiRecorder::didPressRecording()
{
    if (DEBUG)
    {
        Serial.println(state);
        Serial.println("Did Press Recording");
    }

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

void MidiRecorder::didReleaseRecording()
{
    if (DEBUG)
    {
        Serial.println(state);
        Serial.println("Did Release Recording");
    }
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
    if (DEBUG)
    {
        Serial.println(state);
        Serial.println("Record Note");
    }
    switch (state)
    {
    case Idle:
        break;

    case WaitStartRecording:
    {
        startRecording();
        MidiNoteRecord *noteRecord = new MidiNoteRecord(isOn, note, velocity, channel, millis() - startRecordingTimestamp);
        recordedMidiNotes.push_back(noteRecord);
        break;
    }

    case Recording:
    {
        MidiNoteRecord *noteRecord = new MidiNoteRecord(isOn, note, velocity, channel, millis() - startRecordingTimestamp);
        recordedMidiNotes.push_back(noteRecord);
        Serial.print(isOn);
        Serial.print(" ");
        Serial.println(millis() - startRecordingTimestamp);
        break;
    }

    case WaitEndRecording:
    {
        completeRecording();
        startPlaying();
        break;
    }

    case Playing:
        break;

    default:
        break;
    }
}

void MidiRecorder::update()
{
    if (state != Playing || hasRecording == false)
        return;

    unsigned long currentTimestamp = millis() - startPlayingTimestamp;
    if (currentTimestamp >= recordingDuration)
    {
        startPlaying();
        currentTimestamp = 0;
    }

    if (recordedMidiNotesIterator != recordedMidiNotes.end())
    {
        MidiNoteRecord *midiNoteRecord = *recordedMidiNotesIterator;
        // Serial.println(midiNoteRecord->timestamp);
        // Serial.println(oldUpdateTimestamp < midiNoteRecord->timestamp);
        // Serial.println(currentTimestamp >= midiNoteRecord->timestamp);
        if (currentTimestamp >= midiNoteRecord->timestamp)
        {
            if (midiNoteRecord->isOn == true)
            {
                usbMIDI.sendNoteOn(midiNoteRecord->note, midiNoteRecord->velocity, midiNoteRecord->channel);
            }
            else
            {
                usbMIDI.sendNoteOff(midiNoteRecord->note, midiNoteRecord->velocity, midiNoteRecord->channel);
            }
            recordedMidiNotesIterator++;
        }
    }
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