/*
 *
 * parametrizes concentric rings
 *
 */

#include "RingParam.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"

RingParam::RingParam(  
        G4int    noChambers, 
        G4double startZ, 
	G4double radius, 
	G4double length) 
 : G4VPVParameterisation()
{
   fNoChambers =  noChambers; 
   fStartZ     =  startZ; 
   fLength = length;
   fRadInc = radius;
}

RingParam::~RingParam()
{ }

// Not necessary as objects 
// Don't worry about this nonsense it is to simply remove compiler warnings
// CJC 1/18/16

void RingParam::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  G4int copy2 = copyNo;
  bool test=false;
  if (copy2>9)
    test = false;
  if (physVol)
    test = true;
}


void RingParam::ComputeDimensions
(G4Tubs& ring, const G4int copyNo, const G4VPhysicalVolume*) const
{
  // Note: copyNo will start with zero!
  G4double rmax =  (copyNo+1) * fRadInc;
  G4double rmin =  copyNo*fRadInc;
  ring.SetInnerRadius(rmin);
  ring.SetOuterRadius(rmax);
  ring.SetZHalfLength(fLength/2);
  ring.SetStartPhiAngle(0.*deg);
  ring.SetDeltaPhiAngle(360.*deg);
}
