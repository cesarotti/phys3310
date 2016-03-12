/*
 * Dark Photon Event Action
 *!!!History
 *   CJC 6.15.14 created
 *   CJC 6.16.14 analysis added
 *
 * file: EventAction.cc
 *
 * Description: 
 * Event Action method is called after every event. We are using it 
 * to store data from event to event in large runs
 * Methods to update:
 *
 * BeginOfEventAction
 * {Reset the variables you want to keep track of}
*
 * EndOfEventAction
 * {fill all of the data storage methods with the analysis manager, 
 * i.e. histograms or ntuples. Also include whatever verbose arguments
 * you want in your final read out.}
 *
 * 
 */

#include "EventAction.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iomanip>

#include "Analysis.hh"

#include "G4PhysicalConstants.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"

#include "TestHit.hh"


EventAction::EventAction()
  : G4UserEventAction(),
    fDistance(0.), //distance from center of target to front of calorimeter
    fHCID(-1)
{
  // DetectorConstruction* detector = new DetectorConstruction();
  fDistance = 10*m;
}


EventAction::~EventAction()
{}

//!!!
//Reset your variables
void EventAction::BeginOfEventAction(const G4Event* /* run*/)
{
  

  if(fHCID==-1) {
    G4SDManager* sdMan = G4SDManager::GetSDMpointer();
    fHCID = sdMan->GetCollectionID("TestHitsCollection"); //Access Hits Collection
  }

}

/*
 *Calculates the angle from the Z axis the photon hits the target
 *returns G4double angle in degrees
 */
G4double EventAction::CalcTheta(G4double x, G4double y)
{
  G4double distance;
  distance  = std::sqrt(x*x+y*y);

  G4float theta =  std::atan(distance/fDistance);


  return G4double(theta*180/pi);
}

//!!!
//Fill your data analysis
//Add verbosity
void EventAction::EndOfEventAction(const G4Event* event)
{
 

  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if (!hce)
    {
      G4cout << "Your error is in the hits collection. " << G4endl;
    }

  TestHitsCollection* tHC
 = static_cast<TestHitsCollection*>(hce->GetHC(fHCID));

  G4AnalysisManager* analysisMan = G4AnalysisManager::Instance();

  G4double energyDep(0.);
  G4double zPos(0.); // Just to test

  for (G4int i=0; i<50; i++)
    {
      TestHit* hit = (*tHC)[i];
      G4double eDep = hit->GetEnergyDep();
      if (eDep>0.)
	{
	  energyDep+= eDep;
	  analysisMan->FillNtupleDColumn(hit->GetCellID(), eDep);
	}

      if (i==0)
	zPos = hit->GetPos().getZ();

    }

  analysisMan->FillNtupleDColumn(50, energyDep);
  analysisMan->FillNtupleDColumn(51, zPos);

  analysisMan->AddNtupleRow();
    

}

