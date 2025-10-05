#pragma once
#include "raylib.h"
#include <string>

class AutomationManager {
public:
    AutomationManager();
    ~AutomationManager();

    void Update();
    void ToggleRecording();        // Press 'F1'
    void TogglePlayback();         // Press 'F2'
    void ResetScene();             // Press 'F3'

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