/*
 * Dark Photon Calorimeter Sensitive Detector
 *
 * !!!History 
 *    CJC 6.17.14 created
 */

#ifndef CalorimeterSD_h
#define CalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"

#include "CalorHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;

class CalorimeterSD : public G4VSensitiveDetector
{
public:
  CalorimeterSD(const G4String& name, 
		const G4String& hitsCollectionName);
  virtual ~CalorimeterSD();

  //methods from base class
  virtual void Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
  virtual void EndOfEvent(G4HCofThisEvent* hitCollection);

private:
  CalorimeterHitsCollection* fHitsCollection; 
  G4double thresholdEnergy;
};

#endif
