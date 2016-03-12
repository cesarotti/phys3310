/*
 *Dark Photon Calorimeter Hit
 *
 *!!!History 
 *   CJC 6.17.14 created
 *
 */

#ifndef CalorHit_h
#define CalorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

//Calorimeter hit class

class CalorHit : public G4VHit
{
public:
  CalorHit();
  CalorHit(const CalorHit&);
  virtual ~CalorHit();

  //operators
  const CalorHit& operator =(const CalorHit&);
  G4int operator==(const CalorHit&) const;

  inline void* operator new(size_t);
  inline void operator delete(void*);

  //methods from base class
  virtual void Draw();
  virtual void Print();

  //Set methods
  void SetTrackID (G4int track)
  { fTrackID = track;};
  void SetTotalEnergy(G4double energy)
  {fTotalEnergy = energy;};
  void SetPos(G4ThreeVector pos)
  {fPos = pos;};
  void SetMomentum(G4ThreeVector pv)
  {fMomentum = pv;};
  void SetColumn(G4int copyNo)
  {fColumn = copyNo;};
  void SetRow(G4int row)
  {fRow = row;};

  //Get methods
  G4int GetTrack()
 {return fTrackID;};
  G4double GetTotalEnergy()
  {return fTotalEnergy;};
  G4ThreeVector GetPos()
  {return fPos;};
  G4ThreeVector GetMomentum()
  {return fMomentum;};
  G4int GetColumn()
  {return fColumn;};
  G4int GetRow()
  {return fRow;};

private:

  G4int fTrackID;
  G4double fTotalEnergy;
  G4ThreeVector fPos;
  G4ThreeVector fMomentum;
  G4int fColumn;
  G4int fRow;
};

//Allow for a hits collection of CalorHits
typedef G4THitsCollection<CalorHit> CalorimeterHitsCollection;

extern G4ThreadLocal G4Allocator<CalorHit>* CalorimeterHitAllocator;


//Easy source of Segmentation Faults
inline void* CalorHit::operator new(size_t)
{
  if(!CalorimeterHitAllocator)
    CalorimeterHitAllocator = new G4Allocator<CalorHit>; 
  return (void *) CalorimeterHitAllocator->MallocSingle();
}

inline void CalorHit::operator delete(void *hit)
{
  CalorimeterHitAllocator->FreeSingle((CalorHit*) hit);
}

#endif

