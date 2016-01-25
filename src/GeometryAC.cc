#include <sstream>

#include "GeometryAC.hh"
#include "GeometryComptonCamera.hh"
#include "ACFull.hh"
#include "ACMark1.hh"
#include "ACMark2.hh"
#include "ACMark3.hh"
#include "ACMark4.hh"
#include "ACMark5.hh"


#include "AHG4MaterialManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

using namespace astrocamgeometry;

G4LogicalVolume* GeometryAC::Construct(std::string detname) {
  // !!! Do not make the Volume outside of your envelope !!!
  // SGD - ghostWorld (envelope) : Box
  // Full length X: 300*mm, Full length Y: 700*mm, Full length Z: 560*mm

  const bool surfaceCheck = false;

  G4double margin = 0.1*mm;  

  // Instantiate "!!LOCAL!!" Material //////
  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Vacuum");
  //  std::string matname;
  //  AHG4MaterialProperty* p;
  //  matname = "AHG4SGD.BGO";
  //  p = mmanager->RetrieveProperty("BGO");
  //  mmanager->registerMaterial(matname, *p);
  //  AHG4Material* bgo = mmanager->instantiate(matname);
  

  // Local World //////////////////////
  G4double LocalWorld_xSize = 300.0*mm;
  G4double LocalWorld_ySize = 700.0*mm;
  G4double LocalWorld_zSize = 560.0*mm;
  G4VSolid* LocalWorld_Solid = new G4Box("LocalWorld_Solid", LocalWorld_xSize*0.5, LocalWorld_ySize*0.5, LocalWorld_zSize*0.5);
  G4LogicalVolume* LocalWorld_Logical = new G4LogicalVolume(LocalWorld_Solid, air, "LocalWorld_Logical");

  // Compton Camera //////////////////


  GeometryComptonCamera* ComptonCamera_Geometry;
  if(detname=="ACFull"){
    ComptonCamera_Geometry = new ACFull();
  }else if(detname=="ACMark1"){
    ComptonCamera_Geometry = new ACMark1();
  }else if(detname=="ACMark2"){
    ComptonCamera_Geometry = new ACMark2();  
  }else if(detname=="ACMark3"){
    ComptonCamera_Geometry = new ACMark3();
  }else if(detname=="ACMark4"){
    ComptonCamera_Geometry = new ACMark4();
  }else if(detname=="ACMark5"){
    ComptonCamera_Geometry = new ACMark5();
  }

  G4LogicalVolume* ComptonCamera_Logical = ComptonCamera_Geometry->Construct();
  G4double ComptonCamera_xPos = 0.0*mm;
  G4double ComptonCamera_yPos = 0.0*mm;
  //G4double ComptonCamera_zPos = BaseFrame_zPos + BaseFrameBody_zSize*0.5 + 59.9*mm;
  //  G4double ComptonCamera_zPos = -109.9*mm;
  G4double ComptonCamera_zPos = -45.9*mm;
  new G4PVPlacement(0, G4ThreeVector(ComptonCamera_xPos, ComptonCamera_yPos, ComptonCamera_zPos), ComptonCamera_Logical, "ComptonCamera", LocalWorld_Logical, false, 0, surfaceCheck);

  return LocalWorld_Logical;
}
