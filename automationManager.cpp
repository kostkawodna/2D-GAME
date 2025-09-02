#include "automationManager.h"

AutomationManager::AutomationManager() {
    aelist = LoadAutomationEventList(0); // start empty
    SetAutomationEventList(&aelist);
    eventRecording = false;
    eventPlaying = false;
    frameCounter = 0;
    playFrameCounter = 0;
    currentPlayFrame = 0;
}

AutomationManager::~AutomationManager() {
    UnloadAutomationEventList(aelist);
}

void AutomationManager::Update() {
    if (eventPlaying) {
        while (playFrameCounter == aelist.events[currentPlayFrame].frame) {
            PlayAutomationEvent(aelist.events[currentPlayFrame]);
            currentPlayFrame++;
            if (currentPlayFrame == aelist.count) {
                eventPlaying = false;
                currentPlayFrame = 0;
                playFrameCounter = 0;
                TraceLog(LOG_INFO, "REPLAY ENDED!");
                break;
            }
        }
        playFrameCounter++;
    }

    if (eventRecording || eventPlaying) frameCounter++;
    else frameCounter = 0;
}

void AutomationManager::ToggleRecording() {
    if (!eventPlaying) {
        if (eventRecording) {
            StopAutomationEventRecording();
            eventRecording = false;
            ExportAutomationEventList(aelist, "automation.rae");
            TraceLog(LOG_INFO, "RECORDED FRAMES: %i", aelist.count);
        }
        else {
            SetAutomationEventBaseFrame(180);
            StartAutomationEventRecording();
            eventRecording = true;
        }
    }
}

void AutomationManager::TogglePlayback() {
    if (!eventRecording && (aelist.count > 0)) {
        eventPlaying = true;
        playFrameCounter = 0;
        currentPlayFrame = 0;
    }
}

void AutomationManager::ResetScene() {
    frameCounter = 0;
    playFrameCounter = 0;
    currentPlayFrame = 0;
    eventRecording = false;
    eventPlaying = false;
}