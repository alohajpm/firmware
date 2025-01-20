#pragma once

#include <GxEPD.h>
#include "MeshTypes.h"
#include "NodeDB.h"

class DisplayFormatters {
  public:
    static const char *getModemPresetDisplayName(meshtastic_Config_LoRaConfig_ModemPreset preset, bool useShortName);
    static void displayNodeId(GxEPD_Class *display); 
    static void displayShortName(GxEPD_Class *display); 
    static void displayLongName(GxEPD_Class *display); 
};