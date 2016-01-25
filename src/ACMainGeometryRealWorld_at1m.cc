#include "ACMainGeometryRealWorld_at1m.hh"

#include "GeometryAC.hh"

#include "AHG4MaterialManager.hh"
#include "AHG4MaterialProperty.hh"
//#include "AHG4MaterialSampler.hh"

#include "globals.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"

#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
using namespace astrocamgeometry;

ACMainGeometryRealWorld_at1m::ACMainGeometryRealWorld_at1m(std::string detname)
  : constructed(false) , World_Logical(0) , World_Physical(0) , m_DetectorName(detname){
}

G4VPhysicalVolume* ACMainGeometryRealWorld_at1m::Construct() {
  Initialize();
  return World_Physical;
}

void ACMainGeometryRealWorld_at1m::Initialize() {
  if (!constructed) { 
      constructed = true;
      DefineMaterials();
      SetupGeometry();
    }
}

void ACMainGeometryRealWorld_at1m::SetupGeometry() {

  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Vacuum");

  // World ///////////////////////
  G4double World_xSize = 15000.0*mm;
  G4double World_ySize = 15000.0*mm;
  G4double World_zSize = 15000.0*mm;
  G4Box* World_Solid = new G4Box("World_Solid", World_xSize*0.5, World_ySize*0.5, World_zSize*0.5);
  World_Logical = new G4LogicalVolume(World_Solid, air, "World_Logical"); 
  World_Physical = new G4PVPlacement(0, G4ThreeVector(), World_Logical, "World_Physical", 0, false, 0);

  // SGD //////////////////////////
  //  G4double SGD_xSize = 300.0*mm;
  //  G4double SGD_ySize = 700.0*mm;
  //  G4double SGD_zSize = 560.0*mm;
  G4double SGD_xPos = 0.0*mm;
  G4double SGD_yPos = 0.0*mm;
  G4double SGD_zPos = 1000.0*mm;

  G4ThreeVector pos = G4ThreeVector(SGD_xPos,SGD_yPos,SGD_zPos);
  G4RotationMatrix rot = G4RotationMatrix();
  rot.rotateY(90.0*deg);

  GeometryAC* SGD_Geometry = new GeometryAC();
  G4LogicalVolume* SGD_Logical = SGD_Geometry->Construct(m_DetectorName);
  //  new G4PVPlacement(0, G4ThreeVector(SGD_xPos,SGD_yPos,SGD_zPos), SGD_Logical, "EM1", World_Logical, false, 0);
  new G4PVPlacement(G4Transform3D(rot, pos), SGD_Logical, "EM1", World_Logical, false, 0);

}
