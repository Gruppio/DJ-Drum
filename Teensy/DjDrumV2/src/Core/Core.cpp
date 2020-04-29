#include "Core/Core.h"

Core::Core()
{
}

void Core::padPressed(int pad, uint8_t velocity)
{
    uint8_t note = noteModulator->noteForPad(pad);
    uint8_t midiChannel = noteModulator->getChannel();
    midi->sendNote(note, velocity, midiChannel, noteDuration);
}

void Core::update()
{
    midi->update();
}

void Core::updateDisplay()
{
    digitalWrite(LED_BUILTIN, midi->numberOfNotesCurrenltyPlaying() > 0);
    display->update();
}

void Core::incrChannel()
{
    noteModulator->incrChannel();
    display->writeTitle2Value('c', 'h', noteModulator->getChannel());
}

void Core::decrChannel()
{
    noteModulator->decrIntonation();
    display->writeTitle2Value('c', 'h', noteModulator->getChannel());
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
}

void Core::decrScale()
{
    noteModulator->decrScale();
    displayWriteScale();
}

void Core::incrIntonation()
{
    noteModulator->incrIntonation();
    display->writeTitle2Value('i', 'n', noteModulator->getIntonation());
}

void Core::decrIntonation()
{
    noteModulator->decrIntonation();
    display->writeTitle2Value('i', 'n', noteModulator->getIntonation());
}

void Core::displayWriteScale() 
{
    Scale scale = noteModulator->getScale();
    switch (scale)
    {
    case Normal:
        display->write("norm");
        break;
    
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