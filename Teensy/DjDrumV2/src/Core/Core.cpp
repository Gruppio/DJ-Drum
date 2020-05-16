#include "Core/Core.h"

Core::Core()
{
    // for(int i = 0; i < NUM_PADS; i++) {
    //     uint8_t note = noteModulator->noteForPad(i);
    //     NoteSymbol noteSymbol = noteSymbolForNote(note);
    //     padLeds->turnOffPad(i, noteSymbol);
    // }
}

void Core::padPressed(int pad, uint8_t velocity)
{
    // WARNING the velocity parameter is not used, it is used the parameter noteVelocity
    uint8_t note = noteModulator->noteForPad(pad);
    uint8_t midiChannel = noteModulator->getChannel();
    midiNoteTimer->sendNote(note, noteVelocity, midiChannel, noteDuration);
    displayWriteNote(note);
}

void Core::update()
{
    midi->update();
    midiRecorder->update();
    midiNoteTimer->update();
}

void Core::updateDisplay()
{
    digitalWrite(LED_BUILTIN, midiNoteTimer->numberOfNotesCurrenltyPlaying() > 0);
    display->update();
}

void Core::incrChannel()
{
    noteModulator->incrChannel();
    display->writeTitle2Value('c', 'h', noteModulator->getChannel());
    updateAllLightColors();
}

void Core::decrChannel()
{
    noteModulator->decrChannel();
    display->writeTitle2Value('c', 'h', noteModulator->getChannel());
    updateAllLightColors();
}

void Core::incrOctave()
{
    noteModulator->incrOctave();
    display->writeTitle2Value('o', 'c', noteModulator->getOctave());
}

void Core::decrOctave()
{
    noteModulator->decrOctave();
    display->writeTitle2Value('o', 'c', noteModulator->getOctave());
}

void Core::incrScale()
{
    noteModulator->incrScale();
    displayWriteScale();
    updateAllLightColors();
}

void Core::decrScale()
{
    noteModulator->decrScale();
    displayWriteScale();
    updateAllLightColors();
}

void Core::incrIntonation()
{
    noteModulator->incrIntonation();
    displayWriteNote(noteModulator->getIntonation());
    updateAllLightColors();
}

void Core::decrIntonation()
{
    noteModulator->decrIntonation();
    displayWriteNote(noteModulator->getIntonation());
    updateAllLightColors();
}

void Core::didPressRecording() 
{
    midiRecorder->didPressRecording();
}

void Core::didReleaseRecording() 
{
    midiRecorder->didReleaseRecording();
}

void Core::setNoteDuration(int duration)
{
    noteDuration = duration;
    display->writeValue(duration);
}

void Core::setNoteVelocity(uint8_t velocity)
{
    noteVelocity = velocity;
    display->writeTitleValue('v', noteVelocity);
}

void Core::displayWriteScale() 
{
    Scale scale = noteModulator->getScale();
    switch (scale)
    {
    case Normal: display->write("norm"); break;
    
    case Major:
        display->write("majo");
        break;
    
    case BlackAndWhite:
        display->write("blwh");
        break;

    default:
        break;
    }
}

void Core::displayWriteNote(byte note) 
{
    NoteSymbol noteSymbol = noteSymbolForNote(note);
    switch (noteSymbol)
    {
    case C: display->write("do c"); break;
    case Cd: display->write("d#c#"); break;
    case D: display->write("re d"); break;
    case Dd: display->write("r#c#"); break;
    case E: display->write("mi e"); break;
    case F: display->write("fa f"); break;
    case Fd: display->write("f#f#"); break;
    case G: display->write("solg"); break;
    case Gd: display->write("s#g#"); break;
    case A: display->write("la a"); break;
    case Ad: display->write("l#a#"); break;
    case B: display->write("si b"); break;
    }
}

NoteSymbol Core::noteSymbolForNote(byte note)
{
  return NoteSymbol(note % 12);
}

void Core::updateAllLightColors() {
    for(int pad = 0; pad < NUM_PADS; pad++) {
        uint8_t note = noteModulator->noteForPad(pad);
        uint8_t midiChannel = noteModulator->getChannel();
        lightController->sendNoteOn(note, noteVelocity, midiChannel);
        delay(5);
        lightController->sendNoteOff(note, noteVelocity, midiChannel);
        delay(5);
    }
}