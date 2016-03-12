/*
 * Dark Photon Detector Messenger
 *!!!History
 *   CJC 6.15.14 created
 */


#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

/*
 * The messenger class defines commands for the 
 * detector class
 * (once implemented)
 */

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction* );
    virtual ~DetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);


private:
  DetectorConstruction* fDetectorConstruction;

  G4UIdirectory* fDirectory;
  G4UIdirectory* fDetDirectory;

  G4UIcmdWithAString* fCalMatCmd;
  G4UIcmdWithADoubleAndUnit* fCalorPosCmd;

  G4UIcmdWithADoubleAndUnit* fStepMaxCmd;

};

#endif
