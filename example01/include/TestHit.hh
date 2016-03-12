/*
 *Dark Photon Calorimeter Hit
 *
 *!!!History 
 *   CJC 6.28.14 created
 *
 */

#ifndef TestHit_h
#define TestHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

//Calorimeter hit class

class TestHit : public G4VHit
{
public:
  TestHit();
  TestHit(const TestHit&);
  TestHit(G4int z);
  virtual ~TestHit();

  //operators
  const TestHit& operator =(const TestHit&);
  G4int operator==(const TestHit&) const;

  inline void* operator new(size_t);
  inline void operator delete(void*);

  //methods from base class
  virtual void Draw();
  virtual void Print();

  //Set methods
  void SetEnergyDep(G4double energy)
  {fEnergyDep = energy;}
  void AddEdep(G4double edep)
  {fEnergyDep+=edep;}
  void SetPos(G4ThreeVector pos)
  {fPos = pos;}
  void SetLogV(G4LogicalVolume* vol)
  {fLogV = vol;}
  void SetCellID(G4int id)
  {fCellID = id;}

  //Get methods
  G4double GetEnergyDep()
  {return fEnergyDep;}
  G4ThreeVector GetPos()
  {return fPos;}
  const G4LogicalVolume* GetLogV() const
  {return fLogV;}
  G4int GetCellID()
  {return fCellID;}

private:

  G4double fEnergyDep;
  G4ThreeVector fPos;
  const G4LogicalVolume* fLogV;
  G4int fCellID;

};

//Allow for a hits collection of CalorHits
typedef G4THitsCollection<TestHit> TestHitsCollection;

extern G4ThreadLocal G4Allocator<TestHit>* TestHitAllocator;


//Easy source of Segmentation Faults
inline void* TestHit::operator new(size_t)
{
  if(!TestHitAllocator)
    TestHitAllocator = new G4Allocator<TestHit>; 
  return (void *) TestHitAllocator->MallocSingle();
}

inline void TestHit::operator delete(void *hit)
{
  TestHitAllocator->FreeSingle((TestHit*) hit);
}

#endif

