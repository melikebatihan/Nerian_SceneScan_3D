// Scan3D.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "Modules/ReconstructionMod.h"
#include "Modules/FrameGrabber.h"
#include "Modules/DetectionMod.h"
#include "Modules/VisualizationMod.h"


std::mutex mtx;
std::condition_variable condition;
std::queue<ImageSet> frameQueue, depthQueue, detectionQueue;