/*
 *Dark Photon Event Action
 *
 *!!!History
 *   CJC 6.15.14 created
 *
 */

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "DetectorConstruction.hh"
#include "globals.hh"


class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void BeginOfEventAction(const G4Event* );
  virtual void EndOfEventAction(const G4Event* );

private:

  G4double CalcTheta(G4double x, G4double y);

  G4double fDistance; //used in CalcTheta(x,y)
  G4int fHCID;




};
 #endif
