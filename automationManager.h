#pragma once
#include <raylib.h>
#include <string>

class AutomationManager {
public:
    AutomationManager();
    ~AutomationManager();

    void Update();
    void ToggleRecording();        // Press 'B'
    void TogglePlayback();         // Press 'N'
    void ResetScene();             // Press 'M'

    bool IsRecording() const { return eventRecording; }
    bool IsPlaying() const { return eventPlaying; }

private:
    AutomationEventList aelist;
    bool eventRecording;
    bool eventPlaying;
    unsigned int frameCounter;
    unsigned int playFrameCounter;
    unsigned int currentPlayFrame;
};