/*
 * Dark Photon Primary Generator Action
 * !!!History
 *    CJC 6.14.15 created
 *    CJC 1.4.16 MODIFIED
 *
 * file: Primary Generator Action
 *
 * Description
 * This class sets up the experiment, including the world volume and the 
 * particle beam.
 * Methods to update:
 * PrimaryGeneratorAction
 * {adjust energy settings of the gun and particles}
 */

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction()
{
  
  G4int nofParticles = 1;

  //Basic option, only fires number of particles with given kinetic info
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic

  // Choose particle
  G4ParticleDefinition* particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("gamma"); 

  fParticleGun->SetParticleDefinition(particleDefinition);

  //Direction of beam
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)); 
 

  //Note, this sets the KINETIC energy of the particle, not the TOTAL
  // for HEP, this is probably a negligible distinction
  
fParticleGun->SetParticleEnergy(1*GeV);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore.

  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV
    = G4LogicalVolumeStore::GetInstance()->GetVolume("World"); //Defined in DetectorConstruction.cc

  G4Box* worldBox = NULL;
  if ( worldLV ) worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
  if ( worldBox ) worldZHalfLength = worldBox->GetZHalfLength();
  else  {
    G4cerr << "World volume of box not found." << G4endl;
    G4cerr << "Perhaps you have changed geometry." << G4endl;
    G4cerr << "The gun will be place in the center." << G4endl;
  }

  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -worldZHalfLength));

  fParticleGun->GeneratePrimaryVertex(anEvent); //Creates event to run
 
}
