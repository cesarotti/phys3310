/*
 * Dark Photon  Detector Messenger 
 * !!!History 
 *    CJC 6.15.14 created
 * 
 * This class is important as it implements the commands necessary 
 * for complete construction of the detector geometry and materials
 */

#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  fDirectory = new G4UIdirectory("/example01/");
  fDirectory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/example01/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  fCalMatCmd = new G4UIcmdWithAString("/example01/det/setCalorMaterial",this);
  fCalMatCmd->SetGuidance("Select Material of the Calorimeter");
  fCalMatCmd->SetParameterName("choice",false);
  fCalMatCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fCalorPosCmd = new G4UIcmdWithADoubleAndUnit("/example01/det/setCalorDistance", this);
  fCalorPosCmd->SetGuidance("Define position of calorimeter");
  fCalorPosCmd->SetParameterName("calorPos", false);
  fCalorPosCmd->SetUnitCategory("Length");
  fCalorPosCmd->AvailableForStates(G4State_Idle);

  fStepMaxCmd = new G4UIcmdWithADoubleAndUnit("/example01/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("stepMax", false);
  fStepMaxCmd->SetUnitCategory("Length");
  fStepMaxCmd->AvailableForStates(G4State_Idle);

}


DetectorMessenger::~DetectorMessenger()
{
  delete fCalMatCmd;
  delete fStepMaxCmd;
  delete fCalorPosCmd;
  delete fDirectory;
  delete fDetDirectory;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{

  if( command == fStepMaxCmd ) {
    fDetectorConstruction
      ->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue));
  }   
  
  if( command == fCalMatCmd )
    {
      fDetectorConstruction 
	->SetCalorMaterial(newValue); 
    }

  if( command == fCalorPosCmd)
    {
      fDetectorConstruction
	->SetCalorDistance(fCalorPosCmd->GetNewDoubleValue(newValue));
    }

}
