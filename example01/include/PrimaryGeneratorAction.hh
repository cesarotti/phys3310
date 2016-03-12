/*
 * Dark Photon Generator Action
 * !!!History
 *    CJC 6.15.14 created
 */

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

//!!!
//May have to change depending on nature of final beam
class G4ParticleGun;
class G4Event; 

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();


  virtual void GeneratePrimaries(G4Event* );

  G4ParticleGun* GetParticleGun() {return fParticleGun;}

  //Set methods
  void SetRandomFlag(G4bool );

private :
  G4ParticleGun* fParticleGun; //G4 particle gun
};


#endif
