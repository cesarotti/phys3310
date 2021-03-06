/*
 * Dark Photon Detector Construction
 * !!!History:
 *    CJC 6.15.14 created
 *    CJC 6.18.14 changed calorimeter into tube
 *
 * file: DetectorConstruction.cc
 */

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "TestSD.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UnionSolid.hh"

#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4RunManager.hh"

#include "G4PVParameterised.hh"
#include "RingParam.hh"



//G4ThreadLocal
//G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0;

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fLogicCalor(NULL),
    fPhysCalor(NULL),
    fNumRing(0), 
    fCalorMaterial(NULL), //material of calorimeter
    fWorldMaterial(NULL),
    fCalorPos(0.),
    fStepLimit(NULL), 
    fCheckOverlaps(true),
    fLeadMaterial(NULL)
{
 fMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
  delete fStepLimit;
  delete fMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  //Define the materials
  DefineMaterials();

  //Define volumes
  return DefineVolumes();
}

/*
 * Method used to set the materials of the experiment
 * Liquid hydrogen for the target has to be defined
 * as well as Cesium Iodide for the crystals. Other materials
 * can be found in the NIST directory
 * CJC 6.18.14
 * vacuum for tunnel 
 */

void DetectorConstruction::DefineMaterials()
{

  G4NistManager* nistManager = G4NistManager::Instance();

  nistManager->FindOrBuildMaterial("G4_AIR");
 
  G4double z, a, density, pressure, temperature;
  G4String name, symbol;
  G4int nComp;


  //Vacuum for chamber
  density = universe_mean_density;
  pressure = 1.e-19*pascal;
  temperature = 0.1*kelvin;
  G4Material* vacuum = new G4Material(name="Vacuum", z=1., a=1.01*g/mole, 
					  density, kStateGas, temperature, 
					  pressure);

  fWorldMaterial = vacuum;


  //Cesium Iodide for the crystals

  a = 132.9*g/mole;
  G4Element* ele_Cs = new G4Element(name = "Cesium", symbol = "Cs", z = 55., a);

  a =126.9*g/mole;
  G4Element* ele_I = new G4Element(name="Iodide", symbol = "I", z = 53., a);

  density = 4.51*g/cm3;
  G4Material* CsI = new G4Material(name="Cesium Iodide", density, nComp=2);
  CsI->AddElement(ele_Cs, 1);
  CsI->AddElement(ele_I, 1); 

  nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");

  a = 207.20*g/mole;
  G4Element* elPb = new G4Element(name="Lead"    ,symbol="Pb", z=82., a);
  G4Material* lead = new G4Material(name="Lead", z=82., a,
				    density =11.34*g/cm3);

  fLeadMaterial = lead;

  //Print Materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;


}

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{

  G4Material* Air = G4Material::GetMaterial("G4_AIR");

  G4Material* csI = G4Material::GetMaterial("G4_CESIUM_IODIDE");


  fCalorMaterial = csI;

  //Sizes and lengths

  G4double crystalLength = 12.0*cm; 
  G4double crystalWidth = 2.5*cm;
  G4double worldLength = 12*2.54*cm;
  G4double pbThick = 1.*cm; 
  G4double pbFace = 5.*cm; 
  G4double spacing = 5.*2.54*cm;

  G4int leadPlace=4;


  G4GeometryManager::GetInstance()->SetWorldMaximumExtent(worldLength);


  G4cout << "Computed tolerance = "
	 << G4GeometryTolerance::GetInstance()->GetSurfaceTolerance()/mm
	 << " mm" << G4endl;


  //World

G4Box* worldS = 
  new G4Box("world", 
	    worldLength/2, worldLength/2, worldLength/2);
G4LogicalVolume* worldLV
  = new G4LogicalVolume(
			worldS, // solid
			fWorldMaterial,  // material
			"World"); //logical volume's name

// Place the world

G4VPhysicalVolume* worldPV
  = new G4PVPlacement(
		      0, //no rotation
		      G4ThreeVector(), // at origin
		      worldLV, //logical volume
		      "World", // name
		      0, // no mother volume
		      false, //no booleans
		      0, //copy number
		      fCheckOverlaps); // true



G4Tubs* crystal = 
  new G4Tubs("crystal", 0., crystalWidth, crystalLength/2, 0., 2*pi*rad);

 G4LogicalVolume* crystalLV = new G4LogicalVolume(
						crystal,
						fCalorMaterial, 
						"CrystalLV"); 

  new G4PVPlacement(
		      0, 
		      G4ThreeVector(0., 0., spacing/2+leadPlace*pbThick/2), 
		      crystalLV, 
		      "Crystal", 
		      worldLV, 
		      false, 
		      0, 
		      fCheckOverlaps); 



G4Box* leadBlock = 
  new G4Box("leadBlock", pbFace/2, pbFace/2, pbThick/2);

 G4LogicalVolume* leadBlockLV = new G4LogicalVolume(
						  leadBlock, 
						  fLeadMaterial, 
						  "BlockLV"); 
						  

  //LEAD BLOCKING
  if (leadPlace==0) {}
  else {
    for (int i=0; i<leadPlace; i++)
      {
	new G4PVPlacement(
			  0, 
			  G4ThreeVector(0., 0.,i*pbThick/2), 
			  leadBlockLV, 
			  "LeadBlock", 
			  worldLV, 
			  false, 
			  0, 
			  fCheckOverlaps);
      }
    
    
  }

  
  
  
						

 G4double maxStep = 1.0*cm;
 fStepLimit = new G4UserLimits(maxStep);



 return worldPV; //Return world physical volume!

}

void DetectorConstruction::ConstructSDandField()
{
  
  //!!!
  //Create a sensitive detector and put it with logical volumes
  
   G4String testSDname = "TestSD";
  TestSD* testSD =
    new TestSD(testSDname, "TestHitsCollection");

  SetSensitiveDetector("CrystalLV", testSD, true); //sets SD to all logical volumes with the name CrystalLV
  

  G4cout << "SD Construction.....Complete!" << G4endl;
}


// This method is used by the DetectorMessenger.cc program
//
void DetectorConstruction::SetCalorMaterial(G4String materialName)
{
  G4NistManager* nistMan = G4NistManager::Instance();
  
  G4Material* mat = nistMan->FindOrBuildMaterial(materialName); 
  
  if (fCalorMaterial != mat) {
    if (mat)
      { 
	fCalorMaterial = mat; 
	if (fLogicCalor) fLogicCalor->SetMaterial(fCalorMaterial);
	G4cout << 
	  G4endl << "-----> The calor is made of " << materialName << G4endl;
      }
    else
      {
	G4cout << "---> WARNING from SetCalorMaterial: " << materialName <<
	  " not found!" << G4endl;
      }
  }
}

void DetectorConstruction::SetCalorDistance(G4double dist)
{
 
  if (!fPhysCalor)
    {
      G4cerr << "Detector has not yet been constructed." << G4endl;
      return;
    }

  fCalorPos = dist;
  fPhysCalor->SetTranslation(G4ThreeVector(0., 0., fCalorPos)); 

  //So the run manager knows to updaete the geometry
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}


void DetectorConstruction::SetMaxStep(G4double maxStep)
{
  if ((fStepLimit)&&(maxStep>0.)) fStepLimit->SetMaxAllowedStep(maxStep);
}

void DetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps)
{
  G4cout << "Checking overlaps....." <<G4endl;
  fCheckOverlaps = checkOverlaps; 
  G4cout << fCheckOverlaps <<G4endl;
}




