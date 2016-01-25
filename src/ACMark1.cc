#include <sstream>

#include "ACMark1.hh"

#include "AHG4MaterialManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

using namespace astrocamgeometry;

G4LogicalVolume* ACMark1::Construct() {

  // !!! Do not make the Volume outside of your envelope !!!
  // SGD - ghostWorld (envelope) : Box
  // Full length X: 300*mm, Full length Y: 700*mm, Full length Z: 560*mm

  const bool surfaceCheck = false;

  char name[256];
  char name2[256];
  G4double margin = 0.1*mm;  

  // Instantiate "!!LOCAL!!" Material //////
  AHG4MaterialManager* mmanager = AHG4MaterialManager::GetAHG4MaterialManager();
  AHG4Material* air = mmanager->instantiate("Vacuum");	
  std::string matname;
  AHG4MaterialProperty* p;
  matname = "AHG4SGD.Si";
  p = mmanager->RetrieveProperty("Si");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* si = mmanager->instantiate(matname);
  matname = "AHG4SGD.CdTe";
  p = mmanager->RetrieveProperty("CdTe");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* cdte = mmanager->instantiate(matname);
  matname = "AHG4SGD.Polyimide";
  p = mmanager->RetrieveProperty("Polyimide");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* polyimide = mmanager->instantiate(matname);
  matname = "AHG4SGD.FR4";
  p = mmanager->RetrieveProperty("FR4");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* fr4 = mmanager->instantiate(matname);
  matname = "AHG4SGD.Alumina";
  p = mmanager->RetrieveProperty("Alumina");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* alumina = mmanager->instantiate(matname);
  matname = "AHG4SGD.Aluminium";
  p = mmanager->RetrieveProperty("Aluminium");
  mmanager->registerMaterial(matname, *p);
  AHG4Material* aluminium = mmanager->instantiate(matname);


  // Compton Camera ////////////////////
  G4double ComptonCamera_xSize = 122.4*mm;
  G4double ComptonCamera_ySize = 122.4*mm;
  G4double ComptonCamera_zSize = 119.8*mm;
  G4VSolid* ComptonCamera_Solid = new G4Box("ComptonCamera_Solid", ComptonCamera_xSize*0.5, ComptonCamera_ySize*0.5, ComptonCamera_zSize*0.5);
  G4LogicalVolume* ComptonCamera_Logical = new G4LogicalVolume(ComptonCamera_Solid, air, "ComptonCamera_Logical");

  // Main Detectors ///////////////////
  // TopCover ////////////////////////
  G4double TopCover_zSize = 1.0*mm;
  G4double TopCoverBody_xSize = 122.0*mm;
  G4double TopCoverBody_ySize = 122.0*mm;
  G4double TopCoverBody_zSize = TopCover_zSize;
  G4VSolid* TopCoverBody_Solid = new G4Box("TopCoverBody_Solid", TopCoverBody_xSize*0.5, TopCoverBody_ySize*0.5, TopCoverBody_zSize*0.5);
  G4double TopCoverHoleC_xSize = 51.2*mm;
  G4double TopCoverHoleC_ySize = 51.2*mm;
  G4double TopCoverHoleC_zSize = TopCover_zSize;
  G4double TopCoverHoleC_xPos = 0.0*mm;
  G4double TopCoverHoleC_yPos = 0.0*mm;
  G4double TopCoverHoleC_zPos = 0.0*mm;
  G4VSolid* TopCoverHoleC_Solid = new G4Box("TopCoverHoleC_Solid", TopCoverHoleC_xSize*0.5, TopCoverHoleC_ySize*0.5, TopCoverHoleC_zSize*0.5 + margin);
  G4VSolid* TopCover_Solid = new G4SubtractionSolid("TopCover_Solid", TopCoverBody_Solid, TopCoverHoleC_Solid, 0, G4ThreeVector(TopCoverHoleC_xPos, TopCoverHoleC_yPos, TopCoverHoleC_zPos));
  G4LogicalVolume* TopCover_Logical = new G4LogicalVolume(TopCover_Solid, aluminium, "TopCover_Logical");
  G4double TopCover_xPos = 0.0*mm;
  G4double TopCover_yPos = 0.0*mm;
  G4double TopCover_zPos = ComptonCamera_zSize*0.5 - TopCover_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(TopCover_xPos, TopCover_yPos, TopCover_zPos), TopCover_Logical, "TopCover", ComptonCamera_Logical, false, 0, surfaceCheck);
  // TopFrame /////////////////////////////
  // mendou dakara SiFrame toka to issho //
  G4double TopFrame_zSize = 11.7*mm;
  G4double TopFrameBody_xSize = 112.2*mm;
  G4double TopFrameBody_ySize = 112.2*mm;
  G4double TopFrameBody_zSize = TopFrame_zSize;
  G4VSolid* TopFrameBody_Solid = new G4Box("TopFrameBody_Solid", TopFrameBody_xSize*0.5, TopFrameBody_ySize*0.5, TopFrameBody_zSize*0.5);
  G4double TopFrameHoleC_xSize = 51.2*mm;
  G4double TopFrameHoleC_ySize = 51.2*mm;
  G4double TopFrameHoleC_zSize = TopFrame_zSize;
  G4double TopFrameHoleC_xPos = 0.0*mm;
  G4double TopFrameHoleC_yPos = 0.0*mm;
  G4double TopFrameHoleC_zPos = 0.0*mm;
  G4VSolid* TopFrameHoleC_Solid = new G4Box("TopFrameHoleC_Solid", TopFrameHoleC_xSize*0.5, TopFrameHoleC_ySize*0.5, TopFrameHoleC_zSize*0.5 + margin);
  G4double TopFrameHole1_xSize = 24.3*mm;
  G4double TopFrameHole1_ySize = 61.2*mm;
  G4double TopFrameHole1_zSize = TopFrame_zSize;
  G4double TopFrameHole1_xPos = TopFrameBody_xSize*0.5 - TopFrameHole1_xSize*0.5;
  G4double TopFrameHole1_yPos = TopFrameBody_ySize*0.5 - TopFrameHole1_ySize*0.5;
  G4double TopFrameHole1_zPos = 0.0*mm;
  G4VSolid* TopFrameHole1_Solid = new G4Box("TopFrameHole1_Solid", TopFrameHole1_xSize*0.5 + margin, TopFrameHole1_ySize*0.5 + margin, TopFrameHole1_zSize*0.5 + margin);
  G4double TopFrameHole2_xSize = 8.7*mm;
  G4double TopFrameHole2_ySize = 56.8*mm;
  G4double TopFrameHole2_zSize = TopFrame_zSize;
  G4double TopFrameHole2_xPos = TopFrameBody_xSize*0.5 - 18.6*mm - TopFrameHole2_xSize*0.5;
  G4double TopFrameHole2_yPos = TopFrameBody_ySize*0.5 - 13.1*mm - TopFrameHole2_ySize*0.5;
  G4double TopFrameHole2_zPos = 0.0*mm;
  G4VSolid* TopFrameHole2_Solid = new G4Box("TopFrameHole2_Solid", TopFrameHole2_xSize*0.5, TopFrameHole2_ySize*0.5, TopFrameHole2_zSize*0.5 + margin);
  G4VSolid* TopFrame_Solid = new G4SubtractionSolid("TopFrame_Solid", TopFrameBody_Solid, TopFrameHoleC_Solid, 0, G4ThreeVector(TopFrameHoleC_xPos, TopFrameHoleC_yPos, TopFrameHoleC_zPos));
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = TopFrame_Solid;
    G4ThreeVector pos = G4ThreeVector(TopFrameHole1_xPos + margin, TopFrameHole1_yPos + margin, TopFrameHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    TopFrame_Solid = new G4SubtractionSolid("TopFrame_Solid", tmp, TopFrameHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = TopFrame_Solid;
    G4ThreeVector pos = G4ThreeVector(TopFrameHole2_xPos, TopFrameHole2_yPos, TopFrameHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    TopFrame_Solid = new G4SubtractionSolid("TopFrame_Solid", tmp, TopFrameHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* TopFrame_Logical = new G4LogicalVolume(TopFrame_Solid, polyimide, "TopFrame_Logical");
  G4double TopFrame_xPos = 0.0*mm;
  G4double TopFrame_yPos = 0.0*mm;
  G4double TopFrame_zPos = ComptonCamera_zSize*0.5 - TopCover_zSize - TopFrame_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(TopFrame_xPos, TopFrame_yPos, TopFrame_zPos), TopFrame_Logical, "TopFrame", ComptonCamera_Logical, false, 0, surfaceCheck);
  // constant //
  const G4double stackpitchsi = 3.6*mm;
  const G4double stackpitchcdte = 4.4*mm;
  const G4double topcoverue2sipadue = TopCover_zSize + TopFrame_zSize + 1.0*mm;
  const G4double fec2tray = 0.14*mm;
  // SiModule ////////////////////////
  G4double SiModule_zSize = 3.6*mm;
  G4double SiModuleBody_xSize = 112.2*mm;
  G4double SiModuleBody_ySize = 112.2*mm;
  G4double SiModuleBody_zSize = SiModule_zSize;
  G4VSolid* SiModuleBody_Solid = new G4Box("SiModuleBody_Solid", SiModuleBody_xSize*0.5, SiModuleBody_ySize*0.5, SiModuleBody_zSize*0.5);
  G4double SiModuleHole1_xSize = 24.3*mm;
  G4double SiModuleHole1_ySize = 61.2*mm;
  G4double SiModuleHole1_zSize = SiModule_zSize;
  G4double SiModuleHole1_xPos = SiModuleBody_xSize*0.5 - SiModuleHole1_xSize*0.5;
  G4double SiModuleHole1_yPos = SiModuleBody_ySize*0.5 - SiModuleHole1_ySize*0.5;
  G4double SiModuleHole1_zPos = 0.0*mm;
  G4VSolid* SiModuleHole1_Solid = new G4Box("SiModuleHole1_Solid", SiModuleHole1_xSize*0.5 + margin, SiModuleHole1_ySize*0.5 + margin, SiModuleHole1_zSize*0.5 + margin);
  G4double SiModuleHole2_xSize = 8.7*mm;
  G4double SiModuleHole2_ySize = 56.8*mm;
  G4double SiModuleHole2_zSize = SiModule_zSize;
  G4double SiModuleHole2_xPos = SiModuleBody_xSize*0.5 - 18.6*mm - SiModuleHole2_xSize*0.5;
  G4double SiModuleHole2_yPos = SiModuleBody_ySize*0.5 - 13.1*mm - SiModuleHole2_ySize*0.5;
  G4double SiModuleHole2_zPos = 0.0*mm;
  G4VSolid* SiModuleHole2_Solid = new G4Box("SiModuleHole2_Solid", SiModuleHole2_xSize*0.5, SiModuleHole2_ySize*0.5, SiModuleHole2_zSize*0.5 + margin);
  G4VSolid* SiModule_Solid = SiModuleBody_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = SiModule_Solid;
    G4ThreeVector pos = G4ThreeVector(SiModuleHole1_xPos + margin, SiModuleHole1_yPos + margin, SiModuleHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    SiModule_Solid = new G4SubtractionSolid("SiModule_Solid", tmp, SiModuleHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = SiModule_Solid;
    G4ThreeVector pos = G4ThreeVector(SiModuleHole2_xPos, SiModuleHole2_yPos, SiModuleHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    SiModule_Solid = new G4SubtractionSolid("SiModule_Solid", tmp, SiModuleHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* SiModule_Logical = new G4LogicalVolume(SiModule_Solid, air, "SiModule_Logical");
  // SiPad //////////////////////////////
  G4double SiPad_xSize = 53.9*mm;
  G4double SiPad_ySize = 53.9*mm;
  G4double SiPad_zSize = 0.6*mm;
  G4VSolid* SiPad_Solid = new G4Box("SiPad_Solid", SiPad_xSize*0.5, SiPad_ySize*0.5, SiPad_zSize*0.5);
  G4LogicalVolume* SiPad_Logical = new G4LogicalVolume(SiPad_Solid, si, "SiPad_Logical");
  // SiTray /////////////////////////////
  G4double SiTray_zSize = 0.5*mm;
  G4double SiTrayBody_xSize = 112.2*mm;
  G4double SiTrayBody_ySize = 112.2*mm;
  G4double SiTrayBody_zSize = SiTray_zSize;
  G4VSolid* SiTrayBody_Solid = new G4Box("SiTrayBody_Solid", SiTrayBody_xSize*0.5, SiTrayBody_ySize*0.5, SiTrayBody_zSize*0.5);
  G4double SiTrayHoleC_xSize = 51.2*mm;
  G4double SiTrayHoleC_ySize = 51.2*mm;
  G4double SiTrayHoleC_zSize = SiTray_zSize;
  G4double SiTrayHoleC_xPos = 0.0*mm;
  G4double SiTrayHoleC_yPos = 0.0*mm;
  G4double SiTrayHoleC_zPos = 0.0*mm;
  G4VSolid* SiTrayHoleC_Solid = new G4Box("SiTrayHoleC_Solid", SiTrayHoleC_xSize*0.5, SiTrayHoleC_ySize*0.5, SiTrayHoleC_zSize*0.5 + margin);
  G4double SiTrayHole1_xSize = 24.3*mm;
  G4double SiTrayHole1_ySize = 61.2*mm;
  G4double SiTrayHole1_zSize = SiTray_zSize;
  G4double SiTrayHole1_xPos = SiTrayBody_xSize*0.5 - SiTrayHole1_xSize*0.5;
  G4double SiTrayHole1_yPos = SiTrayBody_ySize*0.5 - SiTrayHole1_ySize*0.5;
  G4double SiTrayHole1_zPos = 0.0*mm;
  G4VSolid* SiTrayHole1_Solid = new G4Box("SiTrayHole1_Solid", SiTrayHole1_xSize*0.5 + margin, SiTrayHole1_ySize*0.5 + margin, SiTrayHole1_zSize*0.5 + margin);
  G4double SiTrayHole2_xSize = 8.7*mm;
  G4double SiTrayHole2_ySize = 56.8*mm;
  G4double SiTrayHole2_zSize = SiTray_zSize;
  G4double SiTrayHole2_xPos = SiTrayBody_xSize*0.5 - 18.6*mm - SiTrayHole2_xSize*0.5;
  G4double SiTrayHole2_yPos = SiTrayBody_ySize*0.5 - 13.1*mm - SiTrayHole2_ySize*0.5;
  G4double SiTrayHole2_zPos = 0.0*mm;
  G4VSolid* SiTrayHole2_Solid = new G4Box("SiTrayHole2_Solid", SiTrayHole2_xSize*0.5, SiTrayHole2_ySize*0.5, SiTrayHole2_zSize*0.5 + margin);
  G4VSolid* SiTray_Solid = new G4SubtractionSolid("SiTray_Solid", SiTrayBody_Solid, SiTrayHoleC_Solid, 0, G4ThreeVector(SiTrayHoleC_xPos, SiTrayHoleC_yPos, SiTrayHoleC_zPos));
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = SiTray_Solid;
    G4ThreeVector pos = G4ThreeVector(SiTrayHole1_xPos + margin, SiTrayHole1_yPos + margin, SiTrayHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    SiTray_Solid = new G4SubtractionSolid("SiTray_Solid", tmp, SiTrayHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = SiTray_Solid;
    G4ThreeVector pos = G4ThreeVector(SiTrayHole2_xPos, SiTrayHole2_yPos, SiTrayHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    SiTray_Solid = new G4SubtractionSolid("SiTray_Solid", tmp, SiTrayHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* SiTray_Logical = new G4LogicalVolume(SiTray_Solid, polyimide, "SiTray_Logical");
  // FEC Kiban ////////////////////////
  G4double FecKiban_zSize = 0.4*mm;
  G4double FecKibanBody_xSize = 26.7*mm;
  G4double FecKibanBody_ySize = 28.25*mm;
  G4double FecKibanBody_zSize = FecKiban_zSize;
  G4VSolid* FecKibanBody_Solid = new G4Box("FecKibanBody_Solid", FecKibanBody_xSize*0.5, FecKibanBody_ySize*0.5, FecKibanBody_zSize*0.5);
  G4double FecKibanHole1_xSize = 3.0*mm;
  G4double FecKibanHole1_ySize = 15.15*mm;
  G4double FecKibanHole1_zSize = FecKiban_zSize;
  G4double FecKibanHole1_xPos = FecKibanBody_xSize*0.5 - FecKibanHole1_xSize*0.5;
  G4double FecKibanHole1_yPos = -FecKibanBody_ySize*0.5 + FecKibanHole1_ySize*0.5;
  G4double FecKibanHole1_zPos = 0.0*mm;
  G4VSolid* FecKibanHole1_Solid = new G4Box("FecKibanHole1_Solid", FecKibanHole1_xSize*0.5 + margin, FecKibanHole1_ySize*0.5 + margin, FecKibanHole1_zSize*0.5 + margin);
  G4double FecKibanHole2_xSize = 8.7*mm;
  G4double FecKibanHole2_ySize = 9.65*mm;
  G4double FecKibanHole2_zSize = FecKiban_zSize;
  G4double FecKibanHole2_xPos = -FecKibanBody_xSize*0.5 + FecKibanHole2_xSize*0.5;
  G4double FecKibanHole2_yPos = -FecKibanBody_ySize*0.5 + FecKibanHole2_ySize*0.5;
  G4double FecKibanHole2_zPos = 0.0*mm;
  G4VSolid* FecKibanHole2_Solid = new G4Box("FecKibanHole2_Solid", FecKibanHole2_xSize*0.5 + margin, FecKibanHole2_ySize*0.5 + margin, FecKibanHole2_zSize*0.5 + margin);
  G4VSolid* FecKibanSub1_Solid = new G4SubtractionSolid("FecKibanSub1", FecKibanBody_Solid, FecKibanHole1_Solid, 0, G4ThreeVector(FecKibanHole1_xPos + margin, FecKibanHole1_yPos - margin, FecKibanHole1_zPos));
  G4VSolid* FecKiban_Solid = new G4SubtractionSolid("FecKiban", FecKibanSub1_Solid, FecKibanHole2_Solid, 0, G4ThreeVector(FecKibanHole2_xPos - margin, FecKibanHole2_yPos - margin, FecKibanHole2_zPos));
  G4LogicalVolume* FecKiban_Logical = new G4LogicalVolume(FecKiban_Solid, fr4, "FecKiban_Logical");
  // ASIC /////////////////////////////
  G4double Asic_xSize = 6.5*mm;
  G4double Asic_ySize = 10.0*mm;
  G4double Asic_zSize = 0.6*mm;
  G4VSolid* Asic_Solid = new G4Box("Asic_Solid", Asic_xSize*0.5, Asic_ySize*0.5, Asic_zSize*0.5);
  G4LogicalVolume* Asic_Logical = new G4LogicalVolume(Asic_Solid, si, "Asic_Logical");
  // SiModule Placement ///////////////
  G4double SiTray_xPos = 0.0*mm;
  G4double SiTray_yPos = 0.0*mm;
  G4double SiTray_zPos = -0.05*mm;
  new G4PVPlacement(0, G4ThreeVector(SiTray_xPos, SiTray_yPos, SiTray_zPos), SiTray_Logical, "SiTray", SiModule_Logical, false, 0, surfaceCheck);
  G4double SiPadTop_xPos = 0.0*mm;
  G4double SiPadTop_yPos = 0.0*mm;
  G4double SiPadTop_zPos = SiTray_zPos + SiTray_zSize*0.5 + SiPad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SiPadTop_xPos, SiPadTop_yPos, SiPadTop_zPos), SiPad_Logical, "SiPadTop", SiModule_Logical, false, 0, surfaceCheck);
  G4double SiPadBtm_xPos = 0.0*mm;
  G4double SiPadBtm_yPos = 0.0*mm;
  G4double SiPadBtm_zPos = SiTray_zPos - SiTray_zSize*0.5 - SiPad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SiPadBtm_xPos, SiPadBtm_yPos, SiPadBtm_zPos), SiPad_Logical, "SiPadBtm", SiModule_Logical, false, 0, surfaceCheck);
  G4double FecKibanTop_xPos = 18.45*mm;
  G4double FecKibanTop_yPos = 41.975*mm;
  G4double FecKibanTop_zPos = SiTray_zPos + SiTray_zSize*0.5 + fec2tray + FecKiban_zSize*0.5;
  G4double AsicTop_xPos = 16.75*mm + Asic_xSize*0.5;
  G4double AsicTop_yPos = 28.55*mm + Asic_ySize*0.5;
  G4double AsicTop_zPos = SiTray_zPos + SiTray_zSize*0.5 + fec2tray + FecKiban_zSize + Asic_zSize*0.5;
  G4double FecKibanBtm_xPos = 18.45*mm;
  G4double FecKibanBtm_yPos = 41.975*mm;
  G4double FecKibanBtm_zPos = SiTray_zPos - SiTray_zSize*0.5 - fec2tray - FecKiban_zSize*0.5;
  G4double AsicBtm_xPos = 16.75*mm + Asic_xSize*0.5;
  G4double AsicBtm_yPos = 28.55*mm + Asic_ySize*0.5;
  G4double AsicBtm_zPos = SiTray_zPos - SiTray_zSize*0.5 - fec2tray - FecKiban_zSize - Asic_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector fectoppos = G4ThreeVector(FecKibanTop_xPos, FecKibanTop_yPos, FecKibanTop_zPos);
    G4ThreeVector asictoppos = G4ThreeVector(AsicTop_xPos, AsicTop_yPos, AsicTop_zPos);
    G4ThreeVector fecbtmpos = G4ThreeVector(FecKibanBtm_xPos, FecKibanBtm_yPos, FecKibanBtm_zPos);
    G4ThreeVector asicbtmpos = G4ThreeVector(AsicBtm_xPos, AsicBtm_yPos, AsicBtm_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    fectoppos.rotateZ(90.0*deg*i);
    asictoppos.rotateZ(90.0*deg*i);
    fecbtmpos.rotateZ(90.0*deg*i);
    asicbtmpos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    new G4PVPlacement(G4Transform3D(rot, fectoppos), FecKiban_Logical, "FecKibanTop", SiModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, asictoppos), Asic_Logical, "AsicTop", SiModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, fecbtmpos), FecKiban_Logical, "FecKibanBtm", SiModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, asicbtmpos), Asic_Logical, "AsicBtm", SiModule_Logical, false, i, surfaceCheck);
  }
  // SiModule Placement ////////////////////
  G4double SiModule_xPos = 0.0*mm;
  G4double SiModule_yPos = 0.0*mm;
  for (int i = 0; i < 16; i++) {
    G4double SiModule_zPos = ComptonCamera_zSize*0.5 - topcoverue2sipadue - SiPad_zSize - 0.2*mm - stackpitchsi * i;
    sprintf(name, "SiModule%02d", i);
    if(i==9||i==11||i==13||i==15) new G4PVPlacement(0, G4ThreeVector(SiModule_xPos, SiModule_yPos, SiModule_zPos), SiModule_Logical, name, ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // Plate /////////////////////////////
  G4double Plate_zSize = 1.2*mm;
  G4double PlateBody_xSize = 112.2*mm;
  G4double PlateBody_ySize = 112.2*mm;
  G4double PlateBody_zSize = Plate_zSize;
  G4VSolid* PlateBody_Solid = new G4Box("PlateBody_Solid", PlateBody_xSize*0.5, PlateBody_ySize*0.5, PlateBody_zSize*0.5);
  G4double PlateHole1_xSize = 24.3*mm;
  G4double PlateHole1_ySize = 61.2*mm;
  G4double PlateHole1_zSize = Plate_zSize;
  G4double PlateHole1_xPos = PlateBody_xSize*0.5 - PlateHole1_xSize*0.5;
  G4double PlateHole1_yPos = PlateBody_ySize*0.5 - PlateHole1_ySize*0.5;
  G4double PlateHole1_zPos = 0.0*mm;
  G4VSolid* PlateHole1_Solid = new G4Box("PlateHole1_Solid", PlateHole1_xSize*0.5 + margin, PlateHole1_ySize*0.5 + margin, PlateHole1_zSize*0.5 + margin);
  G4double PlateHole2_xSize = 8.7*mm;
  G4double PlateHole2_ySize = 56.8*mm;
  G4double PlateHole2_zSize = Plate_zSize;
  G4double PlateHole2_xPos = PlateBody_xSize*0.5 - 18.6*mm - PlateHole2_xSize*0.5;
  G4double PlateHole2_yPos = PlateBody_ySize*0.5 - 13.1*mm - PlateHole2_ySize*0.5;
  G4double PlateHole2_zPos = 0.0*mm;
  G4VSolid* PlateHole2_Solid = new G4Box("PlateHole2_Solid", PlateHole2_xSize*0.5, PlateHole2_ySize*0.5, PlateHole2_zSize*0.5 + margin);
  G4VSolid* Plate_Solid = PlateBody_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = Plate_Solid;
    G4ThreeVector pos = G4ThreeVector(PlateHole1_xPos + margin, PlateHole1_yPos + margin, PlateHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    Plate_Solid = new G4SubtractionSolid("Plate_Solid", tmp, PlateHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = Plate_Solid;
    G4ThreeVector pos = G4ThreeVector(PlateHole2_xPos, PlateHole2_yPos, PlateHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    Plate_Solid = new G4SubtractionSolid("Plate_Solid", tmp, PlateHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* Plate_Logical = new G4LogicalVolume(Plate_Solid, polyimide, "Plate_Logical");
  G4double Plate_xPos = 0.0*mm;
  G4double Plate_yPos = 0.0*mm;
  G4double Plate_zPos = ComptonCamera_zSize*0.5 - topcoverue2sipadue - SiPad_zSize - 0.2*mm - stackpitchsi * 15 - stackpitchsi*0.5 - Plate_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(Plate_xPos, Plate_yPos, Plate_zPos), Plate_Logical, "Plate", ComptonCamera_Logical, false, 0, surfaceCheck);
  // CdTePad //////////////////////////////
  G4double CdTePad_xSize = 26.75*mm;
  G4double CdTePad_ySize = 26.75*mm;
  G4double CdTePad_zSize = 0.75*mm;
  G4VSolid* CdTePad_Solid = new G4Box("CdTePad_Solid", CdTePad_xSize*0.5, CdTePad_ySize*0.5, CdTePad_zSize*0.5);
  G4LogicalVolume* CdTePad_Logical = new G4LogicalVolume(CdTePad_Solid, cdte, "CdTePad_Logical");
  // FanOut /////////////////////////////////
  G4double FanOut_xSize = 25.5*mm;
  G4double FanOut_ySize = 25.5*mm;
  G4double FanOut_zSize = 0.3*mm;
  G4VSolid* FanOut_Solid = new G4Box("FanOut_Solid", FanOut_xSize*0.5, FanOut_ySize*0.5, FanOut_zSize*0.5);
  G4LogicalVolume* FanOut_Logical = new G4LogicalVolume(FanOut_Solid, alumina, "FanOut_Logical");
  // CdTeBtmModule ////////////////////////
  G4double CdTeBtmModule_zSize = 4.4*mm;
  G4double CdTeBtmModuleBody_xSize = 112.2*mm;
  G4double CdTeBtmModuleBody_ySize = 112.2*mm;
  G4double CdTeBtmModuleBody_zSize = CdTeBtmModule_zSize;
  G4VSolid* CdTeBtmModuleBody_Solid = new G4Box("CdTeBtmModuleBody_Solid", CdTeBtmModuleBody_xSize*0.5, CdTeBtmModuleBody_ySize*0.5, CdTeBtmModuleBody_zSize*0.5);
  G4double CdTeBtmModuleHole1_xSize = 24.3*mm;
  G4double CdTeBtmModuleHole1_ySize = 61.2*mm;
  G4double CdTeBtmModuleHole1_zSize = CdTeBtmModule_zSize;
  G4double CdTeBtmModuleHole1_xPos = CdTeBtmModuleBody_xSize*0.5 - CdTeBtmModuleHole1_xSize*0.5;
  G4double CdTeBtmModuleHole1_yPos = CdTeBtmModuleBody_ySize*0.5 - CdTeBtmModuleHole1_ySize*0.5;
  G4double CdTeBtmModuleHole1_zPos = 0.0*mm;
  G4VSolid* CdTeBtmModuleHole1_Solid = new G4Box("CdTeBtmModuleHole1_Solid", CdTeBtmModuleHole1_xSize*0.5 + margin, CdTeBtmModuleHole1_ySize*0.5 + margin, CdTeBtmModuleHole1_zSize*0.5 + margin);
  G4double CdTeBtmModuleHole2_xSize = 8.7*mm;
  G4double CdTeBtmModuleHole2_ySize = 56.8*mm;
  G4double CdTeBtmModuleHole2_zSize = CdTeBtmModule_zSize;
  G4double CdTeBtmModuleHole2_xPos = CdTeBtmModuleBody_xSize*0.5 - 18.6*mm - CdTeBtmModuleHole2_xSize*0.5;
  G4double CdTeBtmModuleHole2_yPos = CdTeBtmModuleBody_ySize*0.5 - 13.1*mm - CdTeBtmModuleHole2_ySize*0.5;
  G4double CdTeBtmModuleHole2_zPos = 0.0*mm;
  G4VSolid* CdTeBtmModuleHole2_Solid = new G4Box("CdTeBtmModuleHole2_Solid", CdTeBtmModuleHole2_xSize*0.5, CdTeBtmModuleHole2_ySize*0.5, CdTeBtmModuleHole2_zSize*0.5 + margin);
  G4VSolid* CdTeBtmModule_Solid = CdTeBtmModuleBody_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = CdTeBtmModule_Solid;
    G4ThreeVector pos = G4ThreeVector(CdTeBtmModuleHole1_xPos + margin, CdTeBtmModuleHole1_yPos + margin, CdTeBtmModuleHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    CdTeBtmModule_Solid = new G4SubtractionSolid("CdTeBtmModule_Solid", tmp, CdTeBtmModuleHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = CdTeBtmModule_Solid;
    G4ThreeVector pos = G4ThreeVector(CdTeBtmModuleHole2_xPos, CdTeBtmModuleHole2_yPos, CdTeBtmModuleHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    CdTeBtmModule_Solid = new G4SubtractionSolid("CdTeBtmModule_Solid", tmp, CdTeBtmModuleHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* CdTeBtmModule_Logical = new G4LogicalVolume(CdTeBtmModule_Solid, air, "CdTeBtmModule_Logical");
  // CdTeBtmTray1 /////////////////////////////
  G4double CdTeBtmTray1_zSize = 0.5*mm;
  G4double CdTeBtmTray1Body_xSize = 112.2*mm;
  G4double CdTeBtmTray1Body_ySize = 112.2*mm;
  G4double CdTeBtmTray1Body_zSize = CdTeBtmTray1_zSize;
  G4VSolid* CdTeBtmTray1Body_Solid = new G4Box("CdTeBtmTray1Body_Solid", CdTeBtmTray1Body_xSize*0.5, CdTeBtmTray1Body_ySize*0.5, CdTeBtmTray1Body_zSize*0.5);
  G4double CdTeBtmTray1HoleC_xSize = 54.9*mm;
  G4double CdTeBtmTray1HoleC_ySize = 54.9*mm;
  G4double CdTeBtmTray1HoleC_zSize = CdTeBtmTray1_zSize;
  G4double CdTeBtmTray1HoleC_xPos = 0.0*mm;
  G4double CdTeBtmTray1HoleC_yPos = 0.0*mm;
  G4double CdTeBtmTray1HoleC_zPos = 0.0*mm;
  G4VSolid* CdTeBtmTray1HoleC_Solid = new G4Box("CdTeBtmTray1HoleC_Solid", CdTeBtmTray1HoleC_xSize*0.5, CdTeBtmTray1HoleC_ySize*0.5, CdTeBtmTray1HoleC_zSize*0.5 + margin);
  G4double CdTeBtmTray1Hole1_xSize = 24.3*mm;
  G4double CdTeBtmTray1Hole1_ySize = 61.2*mm;
  G4double CdTeBtmTray1Hole1_zSize = CdTeBtmTray1_zSize;
  G4double CdTeBtmTray1Hole1_xPos = CdTeBtmTray1Body_xSize*0.5 - CdTeBtmTray1Hole1_xSize*0.5;
  G4double CdTeBtmTray1Hole1_yPos = CdTeBtmTray1Body_ySize*0.5 - CdTeBtmTray1Hole1_ySize*0.5;
  G4double CdTeBtmTray1Hole1_zPos = 0.0*mm;
  G4VSolid* CdTeBtmTray1Hole1_Solid = new G4Box("CdTeBtmTray1Hole1_Solid", CdTeBtmTray1Hole1_xSize*0.5 + margin, CdTeBtmTray1Hole1_ySize*0.5 + margin, CdTeBtmTray1Hole1_zSize*0.5 + margin);
  G4double CdTeBtmTray1Hole2_xSize = 8.7*mm;
  G4double CdTeBtmTray1Hole2_ySize = 56.8*mm;
  G4double CdTeBtmTray1Hole2_zSize = CdTeBtmTray1_zSize;
  G4double CdTeBtmTray1Hole2_xPos = CdTeBtmTray1Body_xSize*0.5 - 18.6*mm - CdTeBtmTray1Hole2_xSize*0.5;
  G4double CdTeBtmTray1Hole2_yPos = CdTeBtmTray1Body_ySize*0.5 - 13.1*mm - CdTeBtmTray1Hole2_ySize*0.5;
  G4double CdTeBtmTray1Hole2_zPos = 0.0*mm;
  G4VSolid* CdTeBtmTray1Hole2_Solid = new G4Box("CdTeBtmTray1Hole2_Solid", CdTeBtmTray1Hole2_xSize*0.5, CdTeBtmTray1Hole2_ySize*0.5, CdTeBtmTray1Hole2_zSize*0.5 + margin);
  G4VSolid* CdTeBtmTray1_Solid = new G4SubtractionSolid("CdTeBtmTray1_Solid", CdTeBtmTray1Body_Solid, CdTeBtmTray1HoleC_Solid, 0, G4ThreeVector(CdTeBtmTray1HoleC_xPos, CdTeBtmTray1HoleC_yPos, CdTeBtmTray1HoleC_zPos));
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = CdTeBtmTray1_Solid;
    G4ThreeVector pos = G4ThreeVector(CdTeBtmTray1Hole1_xPos + margin, CdTeBtmTray1Hole1_yPos + margin, CdTeBtmTray1Hole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    CdTeBtmTray1_Solid = new G4SubtractionSolid("CdTeBtmTray1_Solid", tmp, CdTeBtmTray1Hole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = CdTeBtmTray1_Solid;
    G4ThreeVector pos = G4ThreeVector(CdTeBtmTray1Hole2_xPos, CdTeBtmTray1Hole2_yPos, CdTeBtmTray1Hole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    CdTeBtmTray1_Solid = new G4SubtractionSolid("CdTeBtmTray1_Solid", tmp, CdTeBtmTray1Hole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* CdTeBtmTray1_Logical = new G4LogicalVolume(CdTeBtmTray1_Solid, polyimide, "CdTeBtmTray1_Logical");
  // CdTeBtmTray2 /////////////////////
  G4double CdTeBtmTray2_xSize = 54.9*mm;
  G4double CdTeBtmTray2_ySize = 54.9*mm;
  G4double CdTeBtmTray2_zSize = 0.5*mm;
  G4VSolid* CdTeBtmTray2_Solid = new G4Box("CdTeBtmTray2_Solid", CdTeBtmTray2_xSize*0.5, CdTeBtmTray2_ySize*0.5, CdTeBtmTray2_zSize*0.5);
  G4LogicalVolume* CdTeBtmTray2_Logical = new G4LogicalVolume(CdTeBtmTray2_Solid, polyimide, "CdTeBtmTray2_Logical");
  // CdTeBtmTray3 /////////////////////
  G4double CdTeBtmTray3_xSize = 55.9*mm;
  G4double CdTeBtmTray3_ySize = 55.9*mm;
  G4double CdTeBtmTray3_zSize = 0.5*mm;
  G4VSolid* CdTeBtmTray3_Solid = new G4Box("CdTeBtmTray3_Solid", CdTeBtmTray3_xSize*0.5, CdTeBtmTray3_ySize*0.5, CdTeBtmTray3_zSize*0.5);
  G4LogicalVolume* CdTeBtmTray3_Logical = new G4LogicalVolume(CdTeBtmTray3_Solid, polyimide, "CdTeBtmTray3_Logical");
  // CdTeBtmModule Placement ///////////////
  G4double BtmCdTePad_Space = 1.0*mm;
  G4double CdTeBtmTray1_xPos = 0.0*mm;
  G4double CdTeBtmTray1_yPos = 0.0*mm;
  G4double CdTeBtmTray1_zPos = -0.05*mm;
  new G4PVPlacement(0, G4ThreeVector(CdTeBtmTray1_xPos, CdTeBtmTray1_yPos, CdTeBtmTray1_zPos), CdTeBtmTray1_Logical, "CdTeBtmTray1", CdTeBtmModule_Logical, false, 0, surfaceCheck);
  G4double CdTeBtmTray2_xPos = 0.0*mm;
  G4double CdTeBtmTray2_yPos = 0.0*mm;
  G4double CdTeBtmTray2_zPos = CdTeBtmTray1_zPos + CdTeBtmTray1_zSize*0.5 + 0.25*mm + CdTePad_zSize + 0.1*mm + FanOut_zSize + 0.1*mm + CdTeBtmTray2_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeBtmTray2_xPos, CdTeBtmTray2_yPos, CdTeBtmTray2_zPos), CdTeBtmTray2_Logical, "CdTeBtmTray2", CdTeBtmModule_Logical, false, 0, surfaceCheck);
  G4double CdTeBtmTray3_xPos = 0.0*mm;
  G4double CdTeBtmTray3_yPos = 0.0*mm;
  G4double CdTeBtmTray3_zPos = CdTeBtmTray1_zPos - CdTeBtmTray1_zSize*0.5 - 0.2*mm - CdTePad_zSize - 0.1*mm - FanOut_zSize - 0.05*mm - CdTeBtmTray3_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeBtmTray3_xPos, CdTeBtmTray3_yPos, CdTeBtmTray3_zPos), CdTeBtmTray3_Logical, "CdTeBtmTray3", CdTeBtmModule_Logical, false, 0, surfaceCheck);
  G4double BtmCdTePadTop_xPos = BtmCdTePad_Space*0.5 + CdTePad_xSize*0.5;
  G4double BtmCdTePadTop_yPos = BtmCdTePad_Space*0.5 + CdTePad_ySize*0.5;
  G4double BtmCdTePadTop_zPos = CdTeBtmTray1_zPos + CdTeBtmTray1_zSize*0.5 + 0.25*mm + CdTePad_zSize*0.5;
  G4double BtmFanOutTop_xPos = BtmCdTePad_Space*0.5 + CdTePad_xSize - FanOut_xSize*0.5;
  G4double BtmFanOutTop_yPos = BtmCdTePad_Space*0.5 + CdTePad_ySize - FanOut_ySize*0.5;
  G4double BtmFanOutTop_zPos = CdTeBtmTray1_zPos + CdTeBtmTray1_zSize*0.5 + 0.25*mm + CdTePad_zSize + 0.1*mm + FanOut_zSize*0.5;
  G4double BtmCdTePadBtm_xPos = BtmCdTePad_Space*0.5 + CdTePad_xSize*0.5;
  G4double BtmCdTePadBtm_yPos = BtmCdTePad_Space*0.5 + CdTePad_ySize*0.5;
  G4double BtmCdTePadBtm_zPos = CdTeBtmTray1_zPos - CdTeBtmTray1_zSize*0.5 - 0.2*mm - CdTePad_zSize*0.5;
  G4double BtmFanOutBtm_xPos = BtmCdTePad_Space*0.5 + CdTePad_xSize - FanOut_xSize*0.5;
  G4double BtmFanOutBtm_yPos = BtmCdTePad_Space*0.5 + CdTePad_ySize - FanOut_ySize*0.5;
  G4double BtmFanOutBtm_zPos = CdTeBtmTray1_zPos - CdTeBtmTray1_zSize*0.5 - 0.2*mm - CdTePad_zSize - 0.1*mm - FanOut_zSize*0.5;
  FecKibanTop_xPos = 18.45*mm;
  FecKibanTop_yPos = 41.975*mm;
  FecKibanTop_zPos = CdTeBtmTray1_zPos + CdTeBtmTray1_zSize*0.5 + fec2tray + FecKiban_zSize*0.5;
  AsicTop_xPos = 16.75*mm + Asic_xSize*0.5;
  AsicTop_yPos = 28.55*mm + Asic_ySize*0.5;
  AsicTop_zPos = CdTeBtmTray1_zPos + CdTeBtmTray1_zSize*0.5 + fec2tray + FecKiban_zSize + Asic_zSize*0.5;
  FecKibanBtm_xPos = 18.45*mm;
  FecKibanBtm_yPos = 41.975*mm;
  FecKibanBtm_zPos = CdTeBtmTray1_zPos - CdTeBtmTray1_zSize*0.5 - fec2tray - FecKiban_zSize*0.5;
  AsicBtm_xPos = 16.75*mm + Asic_xSize*0.5;
  AsicBtm_yPos = 28.55*mm + Asic_ySize*0.5;
  AsicBtm_zPos = CdTeBtmTray1_zPos - CdTeBtmTray1_zSize*0.5 - fec2tray - FecKiban_zSize - Asic_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector padtoppos = G4ThreeVector(BtmCdTePadTop_xPos, BtmCdTePadTop_yPos, BtmCdTePadTop_zPos);
    G4ThreeVector fanouttoppos = G4ThreeVector(BtmFanOutTop_xPos, BtmFanOutTop_yPos, BtmFanOutTop_zPos);
    G4ThreeVector padbtmpos = G4ThreeVector(BtmCdTePadBtm_xPos, BtmCdTePadBtm_yPos, BtmCdTePadBtm_zPos);
    G4ThreeVector fanoutbtmpos = G4ThreeVector(BtmFanOutBtm_xPos, BtmFanOutBtm_yPos, BtmFanOutBtm_zPos);
    G4ThreeVector fectoppos = G4ThreeVector(FecKibanTop_xPos, FecKibanTop_yPos, FecKibanTop_zPos);
    G4ThreeVector asictoppos = G4ThreeVector(AsicTop_xPos, AsicTop_yPos, AsicTop_zPos);
    G4ThreeVector fecbtmpos = G4ThreeVector(FecKibanBtm_xPos, FecKibanBtm_yPos, FecKibanBtm_zPos);
    G4ThreeVector asicbtmpos = G4ThreeVector(AsicBtm_xPos, AsicBtm_yPos, AsicBtm_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    padtoppos.rotateZ(90.0*deg*i);
    fanouttoppos.rotateZ(90.0*deg*i);
    padbtmpos.rotateZ(90.0*deg*i);
    fanoutbtmpos.rotateZ(90.0*deg*i);
    fectoppos.rotateZ(90.0*deg*i);
    asictoppos.rotateZ(90.0*deg*i);
    fecbtmpos.rotateZ(90.0*deg*i);
    asicbtmpos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    sprintf(name, "CdTePadTop%02d", i);
    sprintf(name2, "CdTePadBtm%02d", i);
    new G4PVPlacement(G4Transform3D(rot, padtoppos), CdTePad_Logical, name, CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, fanouttoppos), FanOut_Logical, "FanOutTop", CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, padbtmpos), CdTePad_Logical, name2, CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, fanoutbtmpos), FanOut_Logical, "FanOutBtm", CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, fectoppos), FecKiban_Logical, "FecKibanTop", CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, asictoppos), Asic_Logical, "AsicTop", CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, fecbtmpos), FecKiban_Logical, "FecKibanBtm", CdTeBtmModule_Logical, false, i, surfaceCheck);
    new G4PVPlacement(G4Transform3D(rot, asicbtmpos), Asic_Logical, "AsicBtm", CdTeBtmModule_Logical, false, i, surfaceCheck);
  }
  // CdTeBtmModule Placement ////////////////////
  G4double CdTeBtmModule_xPos = 0.0*mm;
  G4double CdTeBtmModule_yPos = 0.0*mm;
  G4double CdTeBtmModule_offset = Plate_zPos - Plate_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4double CdTeBtmModule_zPos = CdTeBtmModule_offset - stackpitchcdte*0.5 - stackpitchcdte * i;
    sprintf(name, "CdTeBtmModule%02d", i);
    if(i==1||i==3) new G4PVPlacement(0, G4ThreeVector(CdTeBtmModule_xPos, CdTeBtmModule_yPos, CdTeBtmModule_zPos), CdTeBtmModule_Logical, name, ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // CdTeSideModule /////////////////////////////
  G4double CdTeSideModule_xSize = 109.0*mm;
  G4double CdTeSideModule_ySize = 55.8*mm;
  G4double CdTeSideModule_zSize = 8.2*mm;
  G4VSolid* CdTeSideModule_Solid = new G4Box("CdTeSideModule_Solid", CdTeSideModule_xSize*0.5, CdTeSideModule_ySize*0.5, CdTeSideModule_zSize*0.5);
  G4LogicalVolume* CdTeSideModule_Logical = new G4LogicalVolume(CdTeSideModule_Solid, air, "CdTeSideModule_Logical");
  // CdTeSideTray1 //////////////////////////////
  G4double CdTeSideTray1_xSize = 109.0*mm;
  G4double CdTeSideTray1_ySize = 55.8*mm;
  G4double CdTeSideTray1_zSize = 1.3*mm;
  G4VSolid* CdTeSideTray1_Solid = new G4Box("CdTeSideTray1_Solid", CdTeSideTray1_xSize*0.5, CdTeSideTray1_ySize*0.5, CdTeSideTray1_zSize*0.5);
  G4LogicalVolume* CdTeSideTray1_Logical = new G4LogicalVolume(CdTeSideTray1_Solid, polyimide, "CdTeSideTray1_Logical");
  // CdTeSideFec1 //////////////////////////////
  G4double CdTeSideFec1_xSize = 109.0*mm;
  G4double CdTeSideFec1_ySize = 55.8*mm;
  G4double CdTeSideFec1_zSize = 0.4*mm;
  G4VSolid* CdTeSideFec1_Solid = new G4Box("CdTeSideFec1_Solid", CdTeSideFec1_xSize*0.5, CdTeSideFec1_ySize*0.5, CdTeSideFec1_zSize*0.5);
  G4LogicalVolume* CdTeSideFec1_Logical = new G4LogicalVolume(CdTeSideFec1_Solid, fr4, "CdTeSideFec1_Logical");
  // CdTeSideTray2 //////////////////////////////
  G4double CdTeSideTray2_xSize = 109.0*mm;
  G4double CdTeSideTray2_ySize = 55.8*mm;
  G4double CdTeSideTray2_zSize = 0.5*mm;
  G4VSolid* CdTeSideTray2_Solid = new G4Box("CdTeSideTray2_Solid", CdTeSideTray2_xSize*0.5, CdTeSideTray2_ySize*0.5, CdTeSideTray2_zSize*0.5);
  G4LogicalVolume* CdTeSideTray2_Logical = new G4LogicalVolume(CdTeSideTray2_Solid, polyimide, "CdTeSideTray2_Logical");
  // CdTeSideFec2 //////////////////////////////
  G4double CdTeSideFec2_xSize = 109.0*mm;
  G4double CdTeSideFec2_ySize = 55.8*mm;
  G4double CdTeSideFec2_zSize = 0.4*mm;
  G4VSolid* CdTeSideFec2_Solid = new G4Box("CdTeSideFec2_Solid", CdTeSideFec2_xSize*0.5, CdTeSideFec2_ySize*0.5, CdTeSideFec2_zSize*0.5);
  G4LogicalVolume* CdTeSideFec2_Logical = new G4LogicalVolume(CdTeSideFec2_Solid, fr4, "CdTeSideFec2_Logical");
  // CdTeSideTray3 //////////////////////////////
  G4double CdTeSideTray3_xSize = 109.0*mm;
  G4double CdTeSideTray3_ySize = 55.8*mm;
  G4double CdTeSideTray3_zSize = 1.0*mm;
  G4VSolid* CdTeSideTray3_Solid = new G4Box("CdTeSideTray3_Solid", CdTeSideTray3_xSize*0.5, CdTeSideTray3_ySize*0.5, CdTeSideTray3_zSize*0.5);
  // G4LogicalVolume* CdTeSideTray3_Logical = new G4LogicalVolume(CdTeSideTray3_Solid, polyimide, "CdTeSideTray3_Logical");
  G4LogicalVolume* CdTeSideTray3_Logical = new G4LogicalVolume(CdTeSideTray3_Solid, air, "CdTeSideTray3_Logical");
  // CdTeSideModule Placement ////////////////
  G4double CdTeSideTray1_xPos = 0.0*mm;
  G4double CdTeSideTray1_yPos = 0.0*mm;
  G4double CdTeSideTray1_zPos = CdTeSideModule_zSize*0.5 - CdTeSideTray1_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeSideTray1_xPos, CdTeSideTray1_yPos, CdTeSideTray1_zPos), CdTeSideTray1_Logical, "CdTeSideTray1", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double CdTeSideFec1_xPos = 0.0*mm;
  G4double CdTeSideFec1_yPos = 0.0*mm;
  G4double CdTeSideFec1_zPos = CdTeSideModule_zSize*0.5 - 2.95*mm - CdTeSideFec1_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeSideFec1_xPos, CdTeSideFec1_yPos, CdTeSideFec1_zPos), CdTeSideFec1_Logical, "CdTeSideFec1", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double CdTeSideTray2_xPos = 0.0*mm;
  G4double CdTeSideTray2_yPos = 0.0*mm;
  G4double CdTeSideTray2_zPos = CdTeSideModule_zSize*0.5 - 4.6*mm - CdTeSideTray2_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeSideTray2_xPos, CdTeSideTray2_yPos, CdTeSideTray2_zPos), CdTeSideTray2_Logical, "CdTeSideTray2", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double CdTeSideFec2_xPos = 0.0*mm;
  G4double CdTeSideFec2_yPos = 0.0*mm;
  G4double CdTeSideFec2_zPos = CdTeSideModule_zSize*0.5 - 6.75*mm - CdTeSideFec2_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeSideFec2_xPos, CdTeSideFec2_yPos, CdTeSideFec2_zPos), CdTeSideFec2_Logical, "CdTeSideFec2", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double CdTeSideTray3_xPos = 0.0*mm;
  G4double CdTeSideTray3_yPos = 0.0*mm;
  G4double CdTeSideTray3_zPos = CdTeSideModule_zSize*0.5 - 7.2*mm - CdTeSideTray3_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(CdTeSideTray3_xPos, CdTeSideTray3_yPos, CdTeSideTray3_zPos), CdTeSideTray3_Logical, "CdTeSideTray3", CdTeSideModule_Logical, false, 0, surfaceCheck);
  // CdTePadInside //
  G4double SideCdTePadInside00_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadInside00_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize + 0.3*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadInside00_zPos = CdTeSideModule_zSize*0.5 - 1.75*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadInside00_xPos, SideCdTePadInside00_yPos, SideCdTePadInside00_zPos), CdTePad_Logical, "SideCdTePadInside00", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadInside01_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadInside01_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize + 0.3*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadInside01_zPos = CdTeSideModule_zSize*0.5 - 1.75*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadInside01_xPos, SideCdTePadInside01_yPos, SideCdTePadInside01_zPos), CdTePad_Logical, "SideCdTePadInside01", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadInside02_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadInside02_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize + 0.3*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadInside02_zPos = CdTeSideModule_zSize*0.5 - 1.75*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadInside02_xPos, SideCdTePadInside02_yPos, SideCdTePadInside02_zPos), CdTePad_Logical, "SideCdTePadInside02", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadInside03_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadInside03_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadInside03_zPos = CdTeSideModule_zSize*0.5 - 1.75*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadInside03_xPos, SideCdTePadInside03_yPos, SideCdTePadInside03_zPos), CdTePad_Logical, "SideCdTePadInside03", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadInside04_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadInside04_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadInside04_zPos = CdTeSideModule_zSize*0.5 - 1.75*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadInside04_xPos, SideCdTePadInside04_yPos, SideCdTePadInside04_zPos), CdTePad_Logical, "SideCdTePadInside04", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadInside05_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadInside05_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadInside05_zPos = CdTeSideModule_zSize*0.5 - 1.75*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadInside05_xPos, SideCdTePadInside05_yPos, SideCdTePadInside05_zPos), CdTePad_Logical, "SideCdTePadInside05", CdTeSideModule_Logical, false, 0, surfaceCheck);
  // FanOutInside //
  G4double SideFanOutInside00_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize*0.5;
  G4double SideFanOutInside00_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize + 0.3*mm + FanOut_ySize*0.5;
  G4double SideFanOutInside00_zPos = CdTeSideModule_zSize*0.5 - 2.6*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutInside00_xPos, SideFanOutInside00_yPos, SideFanOutInside00_zPos), FanOut_Logical, "SideFanOutInside00", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutInside01_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutInside01_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize + 0.3*mm + FanOut_ySize*0.5;
  G4double SideFanOutInside01_zPos = CdTeSideModule_zSize*0.5 - 2.6*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutInside01_xPos, SideFanOutInside01_yPos, SideFanOutInside01_zPos), FanOut_Logical, "SideFanOutInside01", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutInside02_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutInside02_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize + 0.3*mm + FanOut_ySize*0.5;
  G4double SideFanOutInside02_zPos = CdTeSideModule_zSize*0.5 - 2.6*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutInside02_xPos, SideFanOutInside02_yPos, SideFanOutInside02_zPos), FanOut_Logical, "SideFanOutInside02", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutInside03_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize*0.5;
  G4double SideFanOutInside03_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize*0.5;
  G4double SideFanOutInside03_zPos = CdTeSideModule_zSize*0.5 - 2.6*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutInside03_xPos, SideFanOutInside03_yPos, SideFanOutInside03_zPos), FanOut_Logical, "SideFanOutInside03", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutInside04_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutInside04_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize*0.5;
  G4double SideFanOutInside04_zPos = CdTeSideModule_zSize*0.5 - 2.6*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutInside04_xPos, SideFanOutInside04_yPos, SideFanOutInside04_zPos), FanOut_Logical, "SideFanOutInside04", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutInside05_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutInside05_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize*0.5;
  G4double SideFanOutInside05_zPos = CdTeSideModule_zSize*0.5 - 2.6*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutInside05_xPos, SideFanOutInside05_yPos, SideFanOutInside05_zPos), FanOut_Logical, "SideFanOutInside05", CdTeSideModule_Logical, false, 0, surfaceCheck);
  // CdTePadOutside //
  G4double SideCdTePadOutside00_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadOutside00_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize + 0.3*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadOutside00_zPos = CdTeSideModule_zSize*0.5 - 5.55*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadOutside00_xPos, SideCdTePadOutside00_yPos, SideCdTePadOutside00_zPos), CdTePad_Logical, "SideCdTePadOutside00", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadOutside01_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadOutside01_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize + 0.3*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadOutside01_zPos = CdTeSideModule_zSize*0.5 - 5.55*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadOutside01_xPos, SideCdTePadOutside01_yPos, SideCdTePadOutside01_zPos), CdTePad_Logical, "SideCdTePadOutside01", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadOutside02_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadOutside02_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize + 0.3*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadOutside02_zPos = CdTeSideModule_zSize*0.5 - 5.55*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadOutside02_xPos, SideCdTePadOutside02_yPos, SideCdTePadOutside02_zPos), CdTePad_Logical, "SideCdTePadOutside02", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadOutside03_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadOutside03_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadOutside03_zPos = CdTeSideModule_zSize*0.5 - 5.55*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadOutside03_xPos, SideCdTePadOutside03_yPos, SideCdTePadOutside03_zPos), CdTePad_Logical, "SideCdTePadOutside03", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadOutside04_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadOutside04_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadOutside04_zPos = CdTeSideModule_zSize*0.5 - 5.55*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadOutside04_xPos, SideCdTePadOutside04_yPos, SideCdTePadOutside04_zPos), CdTePad_Logical, "SideCdTePadOutside04", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideCdTePadOutside05_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize + 1.35*mm + CdTePad_xSize*0.5;
  G4double SideCdTePadOutside05_yPos = -CdTeSideModule_ySize*0.5 + 1.0*mm + CdTePad_ySize*0.5;
  G4double SideCdTePadOutside05_zPos = CdTeSideModule_zSize*0.5 - 5.55*mm - CdTePad_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCdTePadOutside05_xPos, SideCdTePadOutside05_yPos, SideCdTePadOutside05_zPos), CdTePad_Logical, "SideCdTePadOutside05", CdTeSideModule_Logical, false, 0, surfaceCheck);
  // FanOutOutside //
  G4double SideFanOutOutside00_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize*0.5;
  G4double SideFanOutOutside00_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize + 0.3*mm + FanOut_ySize*0.5;
  G4double SideFanOutOutside00_zPos = CdTeSideModule_zSize*0.5 - 6.4*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutOutside00_xPos, SideFanOutOutside00_yPos, SideFanOutOutside00_zPos), FanOut_Logical, "SideFanOutOutside00", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutOutside01_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutOutside01_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize + 0.3*mm + FanOut_ySize*0.5;
  G4double SideFanOutOutside01_zPos = CdTeSideModule_zSize*0.5 - 6.4*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutOutside01_xPos, SideFanOutOutside01_yPos, SideFanOutOutside01_zPos), FanOut_Logical, "SideFanOutOutside01", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutOutside02_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutOutside02_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize + 0.3*mm + FanOut_ySize*0.5;
  G4double SideFanOutOutside02_zPos = CdTeSideModule_zSize*0.5 - 6.4*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutOutside02_xPos, SideFanOutOutside02_yPos, SideFanOutOutside02_zPos), FanOut_Logical, "SideFanOutOutside02", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutOutside03_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize*0.5;
  G4double SideFanOutOutside03_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize*0.5;
  G4double SideFanOutOutside03_zPos = CdTeSideModule_zSize*0.5 - 6.4*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutOutside03_xPos, SideFanOutOutside03_yPos, SideFanOutOutside03_zPos), FanOut_Logical, "SideFanOutOutside03", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutOutside04_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutOutside04_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize*0.5;
  G4double SideFanOutOutside04_zPos = CdTeSideModule_zSize*0.5 - 6.4*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutOutside04_xPos, SideFanOutOutside04_yPos, SideFanOutOutside04_zPos), FanOut_Logical, "SideFanOutOutside04", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double SideFanOutOutside05_xPos = -CdTeSideModule_xSize*0.5 + 7.5*mm + FanOut_xSize + 2.6*mm + FanOut_xSize + 2.6*mm + FanOut_xSize*0.5;
  G4double SideFanOutOutside05_yPos = -CdTeSideModule_ySize*0.5 + 2.25*mm + FanOut_ySize*0.5;
  G4double SideFanOutOutside05_zPos = CdTeSideModule_zSize*0.5 - 6.4*mm - FanOut_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideFanOutOutside05_xPos, SideFanOutOutside05_yPos, SideFanOutOutside05_zPos), FanOut_Logical, "SideFanOutOutside05", CdTeSideModule_Logical, false, 0, surfaceCheck);
  G4double CdTeSideModule_xPos = -28.85*mm - CdTeSideModule_zSize*0.5;
  G4double CdTeSideModule_yPos = -CdTeBtmModuleBody_ySize*0.5 + 69.9*mm - 0.1*mm - CdTeSideModule_ySize*0.5;
  G4double CdTeSideModule_zPos = ComptonCamera_zSize*0.5- 1.8*mm - CdTeSideModule_xSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector sidemodulepos = G4ThreeVector(CdTeSideModule_xPos, CdTeSideModule_yPos, CdTeSideModule_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateY(90.0*deg);
    rot.rotateZ(90.0*deg*i);
    sidemodulepos.rotateZ(90.0*deg*i);
    sprintf(name, "CdTeSideModule%02d", i);
    // new G4PVPlacement(G4Transform3D(rot, sidemodulepos), CdTeSideModule_Logical, name, ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // CdTeSideModule hamidashita tray ///////
  G4double SideHamidashiTray_xSize = 1.5*mm;
  G4double SideHamidashiTray_ySize = 39.3*mm;
  G4double SideHamidashiTray_zSize = 109.0*mm;
  G4VSolid* SideHamidashiTray_Solid = new G4Box("SideHamidashiTray_Solid", SideHamidashiTray_xSize*0.5, SideHamidashiTray_ySize*0.5, SideHamidashiTray_zSize*0.5);
  G4LogicalVolume* SideHamidashiTray_Logical = new G4LogicalVolume(SideHamidashiTray_Solid, polyimide, "SideHamidashiTray_Logical");
  G4double SideHamidashiTray_xPos = -28.85*mm - CdTeSideModule_zSize - SideHamidashiTray_xSize*0.5;
  G4double SideHamidashiTray_yPos = -CdTeBtmModuleBody_ySize*0.5 + 69.9*mm - 0.1*mm - 15.9*mm - SideHamidashiTray_ySize*0.5;
  G4double SideHamidashiTray_zPos = ComptonCamera_zSize*0.5- 1.8*mm - SideHamidashiTray_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector pos = G4ThreeVector(SideHamidashiTray_xPos, SideHamidashiTray_yPos, SideHamidashiTray_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateZ(90.0*deg*i);
    pos.rotateZ(90.0*deg*i);
    //    new G4PVPlacement(G4Transform3D(rot, pos), SideHamidashiTray_Logical, "SideHamidashiTray", ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // CdTeSideModule PWB ///////
  G4double SidePwb_xSize = 0.8*mm;
  G4double SidePwb_ySize = 31.2*mm;
  G4double SidePwb_zSize = 109.0*mm;
  G4VSolid* SidePwb_Solid = new G4Box("SidePwb_Solid", SidePwb_xSize*0.5, SidePwb_ySize*0.5, SidePwb_zSize*0.5);
  G4LogicalVolume* SidePwb_Logical = new G4LogicalVolume(SidePwb_Solid, fr4, "SidePwb_Logical"); // zaishitsu nazo
  G4double SidePwb_xPos = -28.85*mm - CdTeSideModule_zSize - SideHamidashiTray_xSize - 4.05*mm - SidePwb_xSize*0.5;
  G4double SidePwb_yPos = -CdTeBtmModuleBody_ySize*0.5 + 69.9*mm - 0.1*mm - 24.0*mm - SidePwb_ySize*0.5;
  G4double SidePwb_zPos = ComptonCamera_zSize*0.5- 1.8*mm - SidePwb_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector pos = G4ThreeVector(SidePwb_xPos, SidePwb_yPos, SidePwb_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateZ(90.0*deg*i);
    pos.rotateZ(90.0*deg*i);
    //   new G4PVPlacement(G4Transform3D(rot, pos), SidePwb_Logical, "SidePwb", ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // Adb //////////////////////
  G4double AdbModule_xSize = 8.0*mm;
  G4double AdbModule_ySize = 45.8*mm;
  G4double AdbModule_zSize = 107.0*mm;
  G4VSolid* AdbModule_Solid = new G4Box("AdbModule_Solid", AdbModule_xSize*0.5, AdbModule_ySize*0.5, AdbModule_zSize*0.5);
  G4LogicalVolume* AdbModule_Logical = new G4LogicalVolume(AdbModule_Solid, air, "AdbModule_Logical");
  G4double Adb_xSize = 2.0*mm;
  G4double Adb_ySize = 45.8*mm;
  G4double Adb_zSize = 107.0*mm;
  G4VSolid* Adb_Solid = new G4Box("Adb_Solid", Adb_xSize*0.5, Adb_ySize*0.5, Adb_zSize*0.5);
  G4LogicalVolume* Adb_Logical = new G4LogicalVolume(Adb_Solid, fr4, "Adb_Logical");
  G4double Adb_xPos = 3.0*mm;
  G4double Adb_yPos = 0.0*mm;
  G4double Adb_zPos = 0.0*mm;
  new G4PVPlacement(0, G4ThreeVector(Adb_xPos, Adb_yPos, Adb_zPos), Adb_Logical, "AdbInside", AdbModule_Logical, false, 0, surfaceCheck);
  new G4PVPlacement(0, G4ThreeVector(-Adb_xPos, Adb_yPos, Adb_zPos), Adb_Logical, "AdbOutside", AdbModule_Logical, false, 0, surfaceCheck);
  G4double AdbModule_xPos = -28.8*mm - 20.7*mm - AdbModule_xSize*0.5;
  G4double AdbModule_yPos = -CdTeBtmModuleBody_ySize*0.5 + 61.2*mm - 7.2*mm - AdbModule_ySize*0.5;
  G4double AdbModule_zPos = ComptonCamera_zSize*0.5 - 3.8*mm - AdbModule_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector pos = G4ThreeVector(AdbModule_xPos, AdbModule_yPos, AdbModule_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateZ(90.0*deg*i);
    pos.rotateZ(90.0*deg*i);
    new G4PVPlacement(G4Transform3D(rot, pos), AdbModule_Logical, "AdbModule", ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // Bottom Frame A ///////////////
  // mendou dakara Si Frame toka to issho /////
  G4double BottomFrameA_zSize = 3.7*mm;
  G4double BottomFrameABody_xSize = 112.2*mm;
  G4double BottomFrameABody_ySize = 112.2*mm;
  G4double BottomFrameABody_zSize = BottomFrameA_zSize;
  G4VSolid* BottomFrameABody_Solid = new G4Box("BottomFrameABody_Solid", BottomFrameABody_xSize*0.5, BottomFrameABody_ySize*0.5, BottomFrameABody_zSize*0.5);
  G4double BottomFrameAHole1_xSize = 24.3*mm;
  G4double BottomFrameAHole1_ySize = 61.2*mm;
  G4double BottomFrameAHole1_zSize = BottomFrameA_zSize;
  G4double BottomFrameAHole1_xPos = BottomFrameABody_xSize*0.5 - BottomFrameAHole1_xSize*0.5;
  G4double BottomFrameAHole1_yPos = BottomFrameABody_ySize*0.5 - BottomFrameAHole1_ySize*0.5;
  G4double BottomFrameAHole1_zPos = 0.0*mm;
  G4VSolid* BottomFrameAHole1_Solid = new G4Box("BottomFrameAHole1_Solid", BottomFrameAHole1_xSize*0.5 + margin, BottomFrameAHole1_ySize*0.5 + margin, BottomFrameAHole1_zSize*0.5 + margin);
  G4double BottomFrameAHole2_xSize = 8.7*mm;
  G4double BottomFrameAHole2_ySize = 56.8*mm;
  G4double BottomFrameAHole2_zSize = BottomFrameA_zSize;
  G4double BottomFrameAHole2_xPos = BottomFrameABody_xSize*0.5 - 18.6*mm - BottomFrameAHole2_xSize*0.5;
  G4double BottomFrameAHole2_yPos = BottomFrameABody_ySize*0.5 - 13.1*mm - BottomFrameAHole2_ySize*0.5;
  G4double BottomFrameAHole2_zPos = 0.0*mm;
  G4VSolid* BottomFrameAHole2_Solid = new G4Box("BottomFrameAHole2_Solid", BottomFrameAHole2_xSize*0.5, BottomFrameAHole2_ySize*0.5, BottomFrameAHole2_zSize*0.5 + margin);
  G4VSolid* BottomFrameA_Solid = BottomFrameABody_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameA_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameAHole1_xPos + margin, BottomFrameAHole1_yPos + margin, BottomFrameAHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameA_Solid = new G4SubtractionSolid("BottomFrameA_Solid", tmp, BottomFrameAHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameA_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameAHole2_xPos, BottomFrameAHole2_yPos, BottomFrameAHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameA_Solid = new G4SubtractionSolid("BottomFrameA_Solid", tmp, BottomFrameAHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* BottomFrameA_Logical = new G4LogicalVolume(BottomFrameA_Solid, air, "BottomFrameA_Logical");
  // BottomFrameAElement1 /////////////////////////////
  G4double BottomFrameAElement1_zSize = 1.7*mm;
  G4double BottomFrameAElement1Body_xSize = 112.2*mm;
  G4double BottomFrameAElement1Body_ySize = 112.2*mm;
  G4double BottomFrameAElement1Body_zSize = BottomFrameAElement1_zSize;
  G4VSolid* BottomFrameAElement1Body_Solid = new G4Box("BottomFrameAElement1Body_Solid", BottomFrameAElement1Body_xSize*0.5, BottomFrameAElement1Body_ySize*0.5, BottomFrameAElement1Body_zSize*0.5);
  G4double BottomFrameAElement1Hole1_xSize = 24.3*mm;
  G4double BottomFrameAElement1Hole1_ySize = 61.2*mm;
  G4double BottomFrameAElement1Hole1_zSize = BottomFrameAElement1_zSize;
  G4double BottomFrameAElement1Hole1_xPos = BottomFrameAElement1Body_xSize*0.5 - BottomFrameAElement1Hole1_xSize*0.5;
  G4double BottomFrameAElement1Hole1_yPos = BottomFrameAElement1Body_ySize*0.5 - BottomFrameAElement1Hole1_ySize*0.5;
  G4double BottomFrameAElement1Hole1_zPos = 0.0*mm;
  G4VSolid* BottomFrameAElement1Hole1_Solid = new G4Box("BottomFrameAElement1Hole1_Solid", BottomFrameAElement1Hole1_xSize*0.5 + margin, BottomFrameAElement1Hole1_ySize*0.5 + margin, BottomFrameAElement1Hole1_zSize*0.5 + margin);
  G4double BottomFrameAElement1Hole2_xSize = 8.7*mm;
  G4double BottomFrameAElement1Hole2_ySize = 56.8*mm;
  G4double BottomFrameAElement1Hole2_zSize = BottomFrameAElement1_zSize;
  G4double BottomFrameAElement1Hole2_xPos = BottomFrameAElement1Body_xSize*0.5 - 18.6*mm - BottomFrameAElement1Hole2_xSize*0.5;
  G4double BottomFrameAElement1Hole2_yPos = BottomFrameAElement1Body_ySize*0.5 - 13.1*mm - BottomFrameAElement1Hole2_ySize*0.5;
  G4double BottomFrameAElement1Hole2_zPos = 0.0*mm;
  G4VSolid* BottomFrameAElement1Hole2_Solid = new G4Box("BottomFrameAElement1Hole2_Solid", BottomFrameAElement1Hole2_xSize*0.5, BottomFrameAElement1Hole2_ySize*0.5, BottomFrameAElement1Hole2_zSize*0.5 + margin);
  G4VSolid* BottomFrameAElement1_Solid = BottomFrameAElement1Body_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameAElement1_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameAElement1Hole1_xPos + margin, BottomFrameAElement1Hole1_yPos + margin, BottomFrameAElement1Hole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameAElement1_Solid = new G4SubtractionSolid("BottomFrameAElement1_Solid", tmp, BottomFrameAElement1Hole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameAElement1_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameAElement1Hole2_xPos, BottomFrameAElement1Hole2_yPos, BottomFrameAElement1Hole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameAElement1_Solid = new G4SubtractionSolid("BottomFrameAElement1_Solid", tmp, BottomFrameAElement1Hole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* BottomFrameAElement1_Logical = new G4LogicalVolume(BottomFrameAElement1_Solid, polyimide, "BottomFrameAElement1_Logical");
  // BottomFrameAElement2 /////////////////////////////
  G4double BottomFrameAElement2_zSize = 2.0*mm;
  G4double BottomFrameAElement2Body_xSize = 112.2*mm;
  G4double BottomFrameAElement2Body_ySize = 112.2*mm;
  G4double BottomFrameAElement2Body_zSize = BottomFrameAElement2_zSize;
  G4VSolid* BottomFrameAElement2Body_Solid = new G4Box("BottomFrameAElement2Body_Solid", BottomFrameAElement2Body_xSize*0.5, BottomFrameAElement2Body_ySize*0.5, BottomFrameAElement2Body_zSize*0.5);
  G4double BottomFrameAElement2HoleC_xSize = 51.2*mm;
  G4double BottomFrameAElement2HoleC_ySize = 51.2*mm;
  G4double BottomFrameAElement2HoleC_zSize = BottomFrameAElement2_zSize;
  G4double BottomFrameAElement2HoleC_xPos = 0.0*mm;
  G4double BottomFrameAElement2HoleC_yPos = 0.0*mm;
  G4double BottomFrameAElement2HoleC_zPos = 0.0*mm;
  G4VSolid* BottomFrameAElement2HoleC_Solid = new G4Box("BottomFrameAElement2HoleC_Solid", BottomFrameAElement2HoleC_xSize*0.5, BottomFrameAElement2HoleC_ySize*0.5, BottomFrameAElement2HoleC_zSize*0.5 + margin);
  G4double BottomFrameAElement2Hole1_xSize = 24.3*mm;
  G4double BottomFrameAElement2Hole1_ySize = 61.2*mm;
  G4double BottomFrameAElement2Hole1_zSize = BottomFrameAElement2_zSize;
  G4double BottomFrameAElement2Hole1_xPos = BottomFrameAElement2Body_xSize*0.5 - BottomFrameAElement2Hole1_xSize*0.5;
  G4double BottomFrameAElement2Hole1_yPos = BottomFrameAElement2Body_ySize*0.5 - BottomFrameAElement2Hole1_ySize*0.5;
  G4double BottomFrameAElement2Hole1_zPos = 0.0*mm;
  G4VSolid* BottomFrameAElement2Hole1_Solid = new G4Box("BottomFrameAElement2Hole1_Solid", BottomFrameAElement2Hole1_xSize*0.5 + margin, BottomFrameAElement2Hole1_ySize*0.5 + margin, BottomFrameAElement2Hole1_zSize*0.5 + margin);
  G4double BottomFrameAElement2Hole2_xSize = 8.7*mm;
  G4double BottomFrameAElement2Hole2_ySize = 56.8*mm;
  G4double BottomFrameAElement2Hole2_zSize = BottomFrameAElement2_zSize;
  G4double BottomFrameAElement2Hole2_xPos = BottomFrameAElement2Body_xSize*0.5 - 18.6*mm - BottomFrameAElement2Hole2_xSize*0.5;
  G4double BottomFrameAElement2Hole2_yPos = BottomFrameAElement2Body_ySize*0.5 - 13.1*mm - BottomFrameAElement2Hole2_ySize*0.5;
  G4double BottomFrameAElement2Hole2_zPos = 0.0*mm;
  G4VSolid* BottomFrameAElement2Hole2_Solid = new G4Box("BottomFrameAElement2Hole2_Solid", BottomFrameAElement2Hole2_xSize*0.5, BottomFrameAElement2Hole2_ySize*0.5, BottomFrameAElement2Hole2_zSize*0.5 + margin);
  G4VSolid* BottomFrameAElement2_Solid = new G4SubtractionSolid("BottomFrameAElement2_Solid", BottomFrameAElement2Body_Solid, BottomFrameAElement2HoleC_Solid, 0, G4ThreeVector(BottomFrameAElement2HoleC_xPos, BottomFrameAElement2HoleC_yPos, BottomFrameAElement2HoleC_zPos));
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameAElement2_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameAElement2Hole1_xPos + margin, BottomFrameAElement2Hole1_yPos + margin, BottomFrameAElement2Hole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameAElement2_Solid = new G4SubtractionSolid("BottomFrameAElement2_Solid", tmp, BottomFrameAElement2Hole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameAElement2_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameAElement2Hole2_xPos, BottomFrameAElement2Hole2_yPos, BottomFrameAElement2Hole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameAElement2_Solid = new G4SubtractionSolid("BottomFrameAElement2_Solid", tmp, BottomFrameAElement2Hole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* BottomFrameAElement2_Logical = new G4LogicalVolume(BottomFrameAElement2_Solid, polyimide, "BottomFrameAElement2_Logical");
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, 1.0*mm), BottomFrameAElement1_Logical, "BottomFrameAElement1", BottomFrameA_Logical, false, 0, surfaceCheck);
  new G4PVPlacement(0, G4ThreeVector(0.0*mm, 0.0*mm, -0.85*mm), BottomFrameAElement2_Logical, "BottomFrameAElement2", BottomFrameA_Logical, false, 0, surfaceCheck);
  G4double BottomFrameA_xPos = 0.0*mm;
  G4double BottomFrameA_yPos = 0.0*mm;
  G4double BottomFrameA_zPos = CdTeBtmModule_offset - stackpitchcdte*4 - BottomFrameA_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(BottomFrameA_xPos, BottomFrameA_yPos, BottomFrameA_zPos), BottomFrameA_Logical, "BottomFrameA", ComptonCamera_Logical, false, 0, surfaceCheck);
  // BottomPwb /////////////////////////////
  G4double BottomPwb_zSize = 1.6*mm;
  G4double BottomPwbBody_xSize = 112.2*mm;
  G4double BottomPwbBody_ySize = 112.2*mm;
  G4double BottomPwbBody_zSize = BottomPwb_zSize;
  G4VSolid* BottomPwbBody_Solid = new G4Box("BottomPwbBody_Solid", BottomPwbBody_xSize*0.5, BottomPwbBody_ySize*0.5, BottomPwbBody_zSize*0.5);
  G4double BottomPwbHole1_xSize = 24.3*mm;
  G4double BottomPwbHole1_ySize = 61.2*mm;
  G4double BottomPwbHole1_zSize = BottomPwb_zSize;
  G4double BottomPwbHole1_xPos = BottomPwbBody_xSize*0.5 - BottomPwbHole1_xSize*0.5;
  G4double BottomPwbHole1_yPos = BottomPwbBody_ySize*0.5 - BottomPwbHole1_ySize*0.5;
  G4double BottomPwbHole1_zPos = 0.0*mm;
  G4VSolid* BottomPwbHole1_Solid = new G4Box("BottomPwbHole1_Solid", BottomPwbHole1_xSize*0.5 + margin, BottomPwbHole1_ySize*0.5 + margin, BottomPwbHole1_zSize*0.5 + margin);
  G4double BottomPwbHole2_xSize = 8.7*mm;
  G4double BottomPwbHole2_ySize = 56.8*mm;
  G4double BottomPwbHole2_zSize = BottomPwb_zSize;
  G4double BottomPwbHole2_xPos = BottomPwbBody_xSize*0.5 - 18.6*mm - BottomPwbHole2_xSize*0.5;
  G4double BottomPwbHole2_yPos = BottomPwbBody_ySize*0.5 - 13.1*mm - BottomPwbHole2_ySize*0.5;
  G4double BottomPwbHole2_zPos = 0.0*mm;
  G4VSolid* BottomPwbHole2_Solid = new G4Box("BottomPwbHole2_Solid", BottomPwbHole2_xSize*0.5, BottomPwbHole2_ySize*0.5, BottomPwbHole2_zSize*0.5 + margin);
  G4VSolid* BottomPwb_Solid = BottomPwbBody_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomPwb_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomPwbHole1_xPos + margin, BottomPwbHole1_yPos + margin, BottomPwbHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomPwb_Solid = new G4SubtractionSolid("BottomPwb_Solid", tmp, BottomPwbHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomPwb_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomPwbHole2_xPos, BottomPwbHole2_yPos, BottomPwbHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomPwb_Solid = new G4SubtractionSolid("BottomPwb_Solid", tmp, BottomPwbHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* BottomPwb_Logical = new G4LogicalVolume(BottomPwb_Solid, fr4, "BottomPwb_Logical");
  G4double BottomPwb_xPos = 0.0*mm;
  G4double BottomPwb_yPos = 0.0*mm;
  G4double BottomPwb_zPos = CdTeBtmModule_offset - stackpitchcdte*4 - BottomFrameA_zSize - BottomPwb_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(BottomPwb_xPos, BottomPwb_yPos, BottomPwb_zPos), BottomPwb_Logical, "BottomPwb", ComptonCamera_Logical, false, 0, surfaceCheck);
  // BottomFrameB /////////////////////////////
  G4double BottomFrameB_zSize = 17.1*mm;
  G4double BottomFrameBBody_xSize = 118.0*mm;
  G4double BottomFrameBBody_ySize = 118.0*mm;
  G4double BottomFrameBBody_zSize = BottomFrameB_zSize;
  G4VSolid* BottomFrameBBody_Solid = new G4Box("BottomFrameBBody_Solid", BottomFrameBBody_xSize*0.5, BottomFrameBBody_ySize*0.5, BottomFrameBBody_zSize*0.5);
  G4double BottomFrameBHoleC_xSize = 49.6*mm;
  G4double BottomFrameBHoleC_ySize = 49.6*mm;
  G4double BottomFrameBHoleC_zSize = BottomFrameB_zSize;
  G4double BottomFrameBHoleC_xPos = 0.0*mm;
  G4double BottomFrameBHoleC_yPos = 0.0*mm;
  G4double BottomFrameBHoleC_zPos = 0.0*mm;
  G4VSolid* BottomFrameBHoleC_Solid = new G4Box("BottomFrameBHoleC_Solid", BottomFrameBHoleC_xSize*0.5, BottomFrameBHoleC_ySize*0.5, BottomFrameBHoleC_zSize*0.5 + margin);
  G4double BottomFrameBHole1_xSize = 20.6*mm;
  G4double BottomFrameBHole1_ySize = 60.7*mm;
  G4double BottomFrameBHole1_zSize = BottomFrameB_zSize;
  G4double BottomFrameBHole1_xPos = BottomFrameBBody_xSize*0.5 - BottomFrameBHole1_xSize*0.5;
  G4double BottomFrameBHole1_yPos = BottomFrameBBody_ySize*0.5 - BottomFrameBHole1_ySize*0.5;
  G4double BottomFrameBHole1_zPos = 0.0*mm;
  G4VSolid* BottomFrameBHole1_Solid = new G4Box("BottomFrameBHole1_Solid", BottomFrameBHole1_xSize*0.5 + margin, BottomFrameBHole1_ySize*0.5 + margin, BottomFrameBHole1_zSize*0.5 + margin);
  G4double BottomFrameBHole2_xSize = 30.2*mm;
  G4double BottomFrameBHole2_ySize = 60.7*mm;
  G4double BottomFrameBHole2_zSize = BottomFrameB_zSize;
  G4double BottomFrameBHole2_xPos = BottomFrameBBody_xSize*0.5 - BottomFrameBHole2_xSize*0.5;
  G4double BottomFrameBHole2_yPos = BottomFrameBBody_ySize*0.5 - 14.8*mm - BottomFrameBHole2_ySize*0.5;
  G4double BottomFrameBHole2_zPos = 0.0*mm;
  G4VSolid* BottomFrameBHole2_Solid = new G4Box("BottomFrameBHole2_Solid", BottomFrameBHole2_xSize*0.5 + margin, BottomFrameBHole2_ySize*0.5, BottomFrameBHole2_zSize*0.5 + margin);
  G4VSolid* BottomFrameB_Solid = new G4SubtractionSolid("BottomFrameB_Solid", BottomFrameBBody_Solid, BottomFrameBHoleC_Solid, 0, G4ThreeVector(BottomFrameBHoleC_xPos, BottomFrameBHoleC_yPos, BottomFrameBHoleC_zPos));
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameB_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameBHole1_xPos + margin, BottomFrameBHole1_yPos + margin, BottomFrameBHole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameB_Solid = new G4SubtractionSolid("BottomFrameB_Solid", tmp, BottomFrameBHole1_Solid, G4Transform3D(rot, pos));
  }
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomFrameB_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomFrameBHole2_xPos + margin, BottomFrameBHole2_yPos, BottomFrameBHole2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomFrameB_Solid = new G4SubtractionSolid("BottomFrameB_Solid", tmp, BottomFrameBHole2_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* BottomFrameB_Logical = new G4LogicalVolume(BottomFrameB_Solid, polyimide, "BottomFrameB_Logical");
  G4double BottomFrameB_xPos = 0.0*mm;
  G4double BottomFrameB_yPos = 0.0*mm;
  G4double BottomFrameB_zPos = CdTeBtmModule_offset - stackpitchcdte*4 - BottomFrameA_zSize - BottomPwb_zSize - BottomFrameB_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(BottomFrameB_xPos, BottomFrameB_yPos, BottomFrameB_zPos), BottomFrameB_Logical, "BottomFrameB", ComptonCamera_Logical, false, 0, surfaceCheck);
  // BottomPwb2 //////////////////////
  G4double BottomPwb2_xSize = 48.6*mm;
  G4double BottomPwb2_ySize = 48.6*mm;
  G4double BottomPwb2_zSize = 1.6*mm;
  G4VSolid* BottomPwb2_Solid = new G4Box("BottomPwb2_Solid", BottomPwb2_xSize*0.5, BottomPwb2_ySize*0.5, BottomPwb2_zSize*0.5);
  G4LogicalVolume* BottomPwb2_Logical = new G4LogicalVolume(BottomPwb2_Solid, fr4, "BottomPwb2_Logical");
  G4double BottomPwb2_xPos = 0.0*mm;
  G4double BottomPwb2_yPos = 0.0*mm;
  G4double BottomPwb2_zPos = CdTeBtmModule_offset - stackpitchcdte*4 - BottomFrameA_zSize - BottomPwb_zSize - 4.55*mm - BottomPwb2_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(BottomPwb2_xPos, BottomPwb2_yPos, BottomPwb2_zPos), BottomPwb2_Logical, "BottomPwb2", ComptonCamera_Logical, false, 0, surfaceCheck);
  // BottomPwb3 /////////////////////////////
  G4double BottomPwb3_zSize = 2.0*mm;
  G4double BottomPwb3Body_xSize = 111.0*mm;
  G4double BottomPwb3Body_ySize = 111.0*mm;
  G4double BottomPwb3Body_zSize = BottomPwb3_zSize;
  G4VSolid* BottomPwb3Body_Solid = new G4Box("BottomPwb3Body_Solid", BottomPwb3Body_xSize*0.5, BottomPwb3Body_ySize*0.5, BottomPwb3Body_zSize*0.5);
  G4double BottomPwb3Hole1_xSize = 28.5*mm;
  G4double BottomPwb3Hole1_ySize = 18.7*mm;
  G4double BottomPwb3Hole1_zSize = BottomPwb3_zSize;
  G4double BottomPwb3Hole1_xPos = BottomPwb3Body_xSize*0.5 - 29.2*mm - BottomPwb3Hole1_xSize*0.5;
  G4double BottomPwb3Hole1_yPos = BottomPwb3Body_ySize*0.5 - BottomPwb3Hole1_ySize*0.5;
  G4double BottomPwb3Hole1_zPos = 0.0*mm;
  G4VSolid* BottomPwb3Hole1_Solid = new G4Box("BottomPwb3Hole1_Solid", BottomPwb3Hole1_xSize*0.5, BottomPwb3Hole1_ySize*0.5 + margin, BottomPwb3Hole1_zSize*0.5 + margin);
  G4VSolid* BottomPwb3_Solid = BottomPwb3Body_Solid;
  for (int i = 0; i < 4; i++) {
    G4VSolid* tmp = BottomPwb3_Solid;
    G4ThreeVector pos = G4ThreeVector(BottomPwb3Hole1_xPos, BottomPwb3Hole1_yPos + margin, BottomPwb3Hole1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    pos.rotateZ(90.0*deg*i);
    rot.rotateZ(90.0*deg*i);
    BottomPwb3_Solid = new G4SubtractionSolid("BottomPwb3_Solid", tmp, BottomPwb3Hole1_Solid, G4Transform3D(rot, pos));
  }
  G4LogicalVolume* BottomPwb3_Logical = new G4LogicalVolume(BottomPwb3_Solid, fr4, "BottomPwb3_Logical");
  G4double BottomPwb3_xPos = 0.0*mm;
  G4double BottomPwb3_yPos = 0.0*mm;
  G4double BottomPwb3_zPos = CdTeBtmModule_offset - stackpitchcdte*4 - BottomFrameA_zSize - BottomPwb_zSize - BottomFrameB_zSize - 0.1*mm - BottomPwb3_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(BottomPwb3_xPos, BottomPwb3_yPos, BottomPwb3_zPos), BottomPwb3_Logical, "BottomPwb3", ComptonCamera_Logical, false, 0, surfaceCheck);
  // SideCover ////////////////////////
  G4double SideCover_zSize = 108.0*mm;
  G4double SideCoverBody_xSize = 122.4*mm;
  G4double SideCoverBody_ySize = 122.4*mm;
  G4double SideCoverBody_zSize = SideCover_zSize;
  G4VSolid* SideCoverBody_Solid = new G4Box("SideCoverBody_Solid", SideCoverBody_xSize*0.5, SideCoverBody_ySize*0.5, SideCoverBody_zSize*0.5);
  G4double SideCoverHoleC_xSize = 118.4*mm;
  G4double SideCoverHoleC_ySize = 118.4*mm;
  G4double SideCoverHoleC_zSize = SideCover_zSize;
  G4double SideCoverHoleC_xPos = 0.0*mm;
  G4double SideCoverHoleC_yPos = 0.0*mm;
  G4double SideCoverHoleC_zPos = 0.0*mm;
  G4VSolid* SideCoverHoleC_Solid = new G4Box("SideCoverHoleC_Solid", SideCoverHoleC_xSize*0.5, SideCoverHoleC_ySize*0.5, SideCoverHoleC_zSize*0.5 + margin);
  G4VSolid* SideCover_Solid = new G4SubtractionSolid("SideCover_Solid", SideCoverBody_Solid, SideCoverHoleC_Solid, 0, G4ThreeVector(SideCoverHoleC_xPos, SideCoverHoleC_yPos, SideCoverHoleC_zPos));
  G4LogicalVolume* SideCover_Logical = new G4LogicalVolume(SideCover_Solid, aluminium, "SideCover_Logical");
  G4double SideCover_xPos = 0.0*mm;
  G4double SideCover_yPos = 0.0*mm;
  G4double SideCover_zPos = ComptonCamera_zSize*0.5 - 3.5*mm - SideCover_zSize*0.5;
  new G4PVPlacement(0, G4ThreeVector(SideCover_xPos, SideCover_yPos, SideCover_zPos), SideCover_Logical, "SideCover", ComptonCamera_Logical, false, 0, surfaceCheck);
  // HeatPass1 //////////////////////
  G4double HeatPass1Body_xSize = 21.5*mm;
  G4double HeatPass1Body_ySize = 26.0*mm;
  G4double HeatPass1Body_zSize = 115.5*mm;
  G4VSolid* HeatPass1Body_Solid = new G4Box("HeatPass1Body_Solid", HeatPass1Body_xSize*0.5, HeatPass1Body_ySize*0.5, HeatPass1Body_zSize*0.5);
  G4double HeatPass1Hole1_xSize = 21.5*mm;
  G4double HeatPass1Hole1_ySize = 13.0*mm;
  G4double HeatPass1Hole1_zSize = 90.9*mm;
  G4VSolid* HeatPass1Hole1_Solid = new G4Box("HeatPass1Hole1_Solid", HeatPass1Hole1_xSize*0.5 + margin, HeatPass1Hole1_ySize*0.5 + margin, HeatPass1Hole1_zSize*0.5 + margin);
  G4double HeatPass1Hole2_xSize = 2.5*mm;
  G4double HeatPass1Hole2_ySize = 13.0*mm;
  G4double HeatPass1Hole2_zSize = 104.4*mm;
  G4VSolid* HeatPass1Hole2_Solid = new G4Box("HeatPass1Hole2_Solid", HeatPass1Hole2_xSize*0.5 + margin, HeatPass1Hole2_ySize*0.5 + margin, HeatPass1Hole2_zSize*0.5 + margin);
  G4double HeatPass1Hole3_xSize = 1.5*mm;
  G4double HeatPass1Hole3_ySize = 26.0*mm;
  G4double HeatPass1Hole3_zSize = 12.6*mm;
  G4VSolid* HeatPass1Hole3_Solid = new G4Box("HeatPass1Hole3_Solid", HeatPass1Hole3_xSize*0.5 + margin, HeatPass1Hole3_ySize*0.5 + margin, HeatPass1Hole3_zSize*0.5 + margin);
  G4double HeatPass1Hole4_xSize = 9.5*mm;
  G4double HeatPass1Hole4_ySize = 8.0*mm;
  G4double HeatPass1Hole4_zSize = 115.5*mm;
  G4VSolid* HeatPass1Hole4_Solid = new G4Box("HeatPass1Hole4_Solid", HeatPass1Hole4_xSize*0.5 + margin, HeatPass1Hole4_ySize*0.5 + margin, HeatPass1Hole4_zSize*0.5 + margin);
  G4double HeatPass1Hole5_xSize = 2.0*mm;
  G4double HeatPass1Hole5_ySize = 8.0*mm;
  G4double HeatPass1Hole5_zSize = 115.5*mm;
  G4VSolid* HeatPass1Hole5_Solid = new G4Box("HeatPass1Hole5_Solid", HeatPass1Hole5_xSize*0.5 + margin, HeatPass1Hole5_ySize*0.5 + margin, HeatPass1Hole5_zSize*0.5 + margin);
  G4double HeatPass1Hole6_xSize = 16.6*mm;
  G4double HeatPass1Hole6_ySize = 8.0*mm;
  G4double HeatPass1Hole6_zSize = 89.5*mm;
  G4VSolid* HeatPass1Hole6_Solid = new G4Box("HeatPass1Hole6_Solid", HeatPass1Hole6_xSize*0.5 + margin, HeatPass1Hole6_ySize*0.5 + margin, HeatPass1Hole6_zSize*0.5);
  G4double HeatPass1Hole7_xSize = 21.5*mm;
  G4double HeatPass1Hole7_ySize = 8.0*mm;
  G4double HeatPass1Hole7_zSize = 11.2*mm;
  G4VSolid* HeatPass1Hole7_Solid = new G4Box("HeatPass1Hole7_Solid", HeatPass1Hole7_xSize*0.5 + margin, HeatPass1Hole7_ySize*0.5 + margin, HeatPass1Hole7_zSize*0.5 + margin);
  G4double HeatPass1Hole1_xPos = 0.0*mm;
  G4double HeatPass1Hole1_yPos = -HeatPass1Body_ySize*0.5 + HeatPass1Hole1_ySize*0.5;
  G4double HeatPass1Hole1_zPos = HeatPass1Body_zSize*0.5 - HeatPass1Hole1_zSize*0.5;
  G4double HeatPass1Hole2_xPos = HeatPass1Body_xSize*0.5 - HeatPass1Hole2_xSize*0.5; 
  G4double HeatPass1Hole2_yPos = -HeatPass1Body_ySize*0.5 + HeatPass1Hole2_ySize*0.5;
  G4double HeatPass1Hole2_zPos = HeatPass1Body_zSize*0.5 - HeatPass1Hole2_zSize*0.5;
  G4double HeatPass1Hole3_xPos = HeatPass1Body_xSize*0.5 - HeatPass1Hole3_xSize*0.5;
  G4double HeatPass1Hole3_yPos = 0.0*mm;
  G4double HeatPass1Hole3_zPos = -HeatPass1Body_zSize*0.5 + HeatPass1Hole3_zSize*0.5;
  G4double HeatPass1Hole4_xPos = HeatPass1Body_xSize*0.5 - HeatPass1Hole4_xSize*0.5;
  G4double HeatPass1Hole4_yPos = HeatPass1Body_ySize*0.5 - HeatPass1Hole4_ySize*0.5;
  G4double HeatPass1Hole4_zPos = 0.0*mm;
  G4double HeatPass1Hole5_xPos = -HeatPass1Body_xSize*0.5 + HeatPass1Hole5_xSize*0.5;
  G4double HeatPass1Hole5_yPos = HeatPass1Body_ySize*0.5 - HeatPass1Hole5_ySize*0.5;
  G4double HeatPass1Hole5_zPos = 0.0*mm;
  G4double HeatPass1Hole6_xPos = HeatPass1Body_xSize*0.5 - HeatPass1Hole6_xSize*0.5;
  G4double HeatPass1Hole6_yPos = HeatPass1Body_ySize*0.5 - HeatPass1Hole6_ySize*0.5;
  G4double HeatPass1Hole6_zPos = HeatPass1Body_zSize*0.5 - 8.8*mm - HeatPass1Hole6_zSize*0.5;
  G4double HeatPass1Hole7_xPos = 0.0*mm;
  G4double HeatPass1Hole7_yPos = HeatPass1Body_ySize*0.5 - HeatPass1Hole7_ySize*0.5;
  G4double HeatPass1Hole7_zPos = -HeatPass1Body_zSize*0.5 + HeatPass1Hole7_zSize*0.5;
  G4VSolid* HeatPass1_Solid = HeatPass1Body_Solid;
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole1_Solid, 0, G4ThreeVector(HeatPass1Hole1_xPos, HeatPass1Hole1_yPos - margin, HeatPass1Hole1_zPos + margin));
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole2_Solid, 0, G4ThreeVector(HeatPass1Hole2_xPos + margin, HeatPass1Hole2_yPos - margin, HeatPass1Hole2_zPos + margin));
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole3_Solid, 0, G4ThreeVector(HeatPass1Hole3_xPos + margin, HeatPass1Hole3_yPos, HeatPass1Hole3_zPos - margin));
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole4_Solid, 0, G4ThreeVector(HeatPass1Hole4_xPos + margin, HeatPass1Hole4_yPos + margin, HeatPass1Hole4_zPos));
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole5_Solid, 0, G4ThreeVector(HeatPass1Hole5_xPos - margin, HeatPass1Hole5_yPos + margin, HeatPass1Hole5_zPos));
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole6_Solid, 0, G4ThreeVector(HeatPass1Hole6_xPos + margin, HeatPass1Hole6_yPos + margin, HeatPass1Hole6_zPos));
  HeatPass1_Solid = new G4SubtractionSolid("HeatPass1_Solid", HeatPass1_Solid, HeatPass1Hole7_Solid, 0, G4ThreeVector(HeatPass1Hole7_xPos, HeatPass1Hole7_yPos + margin, HeatPass1Hole7_zPos - margin));
  G4LogicalVolume* HeatPass1_Logical = new G4LogicalVolume(HeatPass1_Solid, aluminium, "HeatPass1_Logical");
  G4double HeatPass1_xPos = 28.8*mm + 8.7*mm + HeatPass1Body_xSize*0.5;
  G4double HeatPass1_yPos = -5.1*mm + 1.6*mm - 13.0*mm + HeatPass1Body_ySize*0.5;
  G4double HeatPass1_zPos = ComptonCamera_zSize*0.5 - 3.5*mm - HeatPass1Body_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector pos = G4ThreeVector(HeatPass1_xPos, HeatPass1_yPos, HeatPass1_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateZ(90.0*deg*i);
    pos.rotateZ(90.0*deg*i);
    new G4PVPlacement(G4Transform3D(rot, pos), HeatPass1_Logical, "HeatPass1", ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // HeatPass2 ////////////////
  G4double HeatPass2Body_xSize = 9.5*mm;
  G4double HeatPass2Body_ySize = 4.0*mm;
  G4double HeatPass2Body_zSize = 58.0*mm;
  G4VSolid* HeatPass2Body_Solid = new G4Box("HeatPass2Body_Solid", HeatPass2Body_xSize*0.5, HeatPass2Body_ySize*0.5, HeatPass2Body_zSize*0.5);
  G4double HeatPass2Hole1_xSize = 2.3*mm;
  G4double HeatPass2Hole1_ySize = 1.0*mm;
  G4double HeatPass2Hole1_zSize = 58.0*mm;
  G4VSolid* HeatPass2Hole1_Solid = new G4Box("HeatPass2Hole1_Solid", HeatPass2Hole1_xSize*0.5 + margin, HeatPass2Hole1_ySize*0.5 + margin, HeatPass2Hole1_zSize*0.5 + margin);
  G4double HeatPass2Hole1_xPos = -HeatPass2Body_xSize*0.5 + HeatPass2Hole1_xSize*0.5;
  G4double HeatPass2Hole1_yPos = -HeatPass2Body_ySize*0.5 + HeatPass2Hole1_ySize*0.5;
  G4double HeatPass2Hole1_zPos = 0.0*mm;
  G4VSolid* HeatPass2_Solid = HeatPass2Body_Solid;
  HeatPass2_Solid = new G4SubtractionSolid("HeatPass2_Solid", HeatPass2_Solid, HeatPass2Hole1_Solid, 0, G4ThreeVector(HeatPass2Hole1_xPos - margin, HeatPass2Hole1_yPos - margin, HeatPass2Hole1_zPos));
  G4LogicalVolume* HeatPass2_Logical = new G4LogicalVolume(HeatPass2_Solid, aluminium, "HeatPass2_Logical");
  G4double HeatPass2_xPos = 28.8*mm - 15.0*mm - 8.7*mm - 7.4*mm - HeatPass2Body_xSize*0.5;
  G4double HeatPass2_yPos = 28.8*mm + 13.6*mm + HeatPass2Body_ySize*0.5;
  G4double HeatPass2_zPos = ComptonCamera_zSize*0.5 - 22.5*mm - HeatPass2Body_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector pos = G4ThreeVector(HeatPass2_xPos, HeatPass2_yPos, HeatPass2_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateZ(90.0*deg*i);
    pos.rotateZ(90.0*deg*i);
    new G4PVPlacement(G4Transform3D(rot, pos), HeatPass2_Logical, "HeatPass2", ComptonCamera_Logical, false, i, surfaceCheck);
  }
  // HeatPass3 //////////////////
  G4double HeatPass3_xSize = 14.9*mm;
  G4double HeatPass3_ySize = 8.8*mm;
  G4double HeatPass3_zSize = 86.0*mm;
  G4VSolid* HeatPass3_Solid = new G4Box("HeatPass3_Solid", HeatPass3_xSize*0.5, HeatPass3_ySize*0.5, HeatPass3_zSize*0.5);
  G4LogicalVolume* HeatPass3_Logical = new G4LogicalVolume(HeatPass3_Solid, aluminium, "HeatPass3_Logical");
  G4double HeatPass3_xPos = 28.8*mm + 3.0*mm + 6.8*mm + HeatPass3_xSize*0.5;
  G4double HeatPass3_yPos = -5.1*mm + 54.1*mm + HeatPass3_ySize*0.5;
  G4double HeatPass3_zPos = ComptonCamera_zSize*0.5 - 12.7*mm - HeatPass3_zSize*0.5;
  for (int i = 0; i < 4; i++) {
    G4ThreeVector pos = G4ThreeVector(HeatPass3_xPos, HeatPass3_yPos, HeatPass3_zPos);
    G4RotationMatrix rot = G4RotationMatrix();
    rot.rotateZ(90.0*deg*i);
    pos.rotateZ(90.0*deg*i);
    new G4PVPlacement(G4Transform3D(rot, pos), HeatPass3_Logical, "HeatPass3", ComptonCamera_Logical, false, i, surfaceCheck);
  }


  // Visualization Attributes /////////////
  G4VisAttributes* sipad_Attributes = new G4VisAttributes(G4Colour::Red());
  sipad_Attributes->SetForceSolid(surfaceCheck);
  SiPad_Logical->SetVisAttributes(sipad_Attributes);
  G4VisAttributes* cdtepad_Attributes = new G4VisAttributes(G4Colour::Blue());
  cdtepad_Attributes->SetForceSolid(surfaceCheck);
  CdTePad_Logical->SetVisAttributes(cdtepad_Attributes);
  

  return ComptonCamera_Logical;
}
