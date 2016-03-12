/*
 * Dark Photon Calorimeter Sensitive Detector
 *
 * !!!History 
 *    CJC 6.17.14 created
 */

#ifndef TestSD_h
#define TestSD_h 1

#include "G4VSensitiveDetector.hh"

#include "TestHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class TestSD : public G4VSensitiveDetector
{
public:
  TestSD(const G4String& name, 
		const G4String& hitsCollectionName);
  virtual ~TestSD();

  //methods from base class
  virtual void Initialize(G4HCofThisEvent* hitCollection);
  virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);

private:
  TestHitsCollection* fHitsCollection; 
  G4int fHCID;
};

#endif
