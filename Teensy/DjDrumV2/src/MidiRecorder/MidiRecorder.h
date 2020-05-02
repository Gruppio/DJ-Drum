#ifndef MIDI_RECORDER_H
#define MIDI_RECORDER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include <list>
#include "Models/MidiNoteRecord.h"

enum MidiRecorderState {Idle = 0, WaitStartRecording, Recording, WaitEndRecording, Playing};

class MidiRecorder
{
public:
    MidiRecorder();
    void pressedRecording();
    void releasedRecording();
    void recordNote(bool isOn, uint8_t note, uint8_t velocity, uint8_t channel);
    void update();

protected:
    MidiRecorderState state = Idle;
    unsigned long startRecordingTimestamp = 0;
    unsigned long recordingDuration = 0;
    unsigned long startPlayingTimestamp = 0;
    unsigned long oldUpdateTimestamp = 0;
    std::list<MidiNoteRecord *> recordedMidiNotes;
    std::list<MidiNoteRecord *>::iterator recordedMidiNotesIterator;
    bool hasRecording = false;

    void deleteRecording();
    void startRecording();
    void completeRecording();
    void startPlaying();
};

#endif