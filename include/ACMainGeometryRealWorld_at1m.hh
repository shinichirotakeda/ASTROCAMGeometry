#ifndef ACMainGeometryRealWorld_at1m_HH
#define ACMainGeometryRealWorld_at1m_HH

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserParallelWorld.hh"

#include "globals.hh"
//#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

namespace astrocamgeometry {

class ACMainGeometryRealWorld_at1m : public G4VUserDetectorConstruction {

public:
  ACMainGeometryRealWorld_at1m(std::string detname);
  virtual ~ACMainGeometryRealWorld_at1m() {};
  
  virtual G4VPhysicalVolume* Construct();
  void Initialize();
  
private:
  void DefineMaterials() {};
  void SetupGeometry();

  G4int constructed;
  G4LogicalVolume* World_Logical;
  G4VPhysicalVolume* World_Physical;
  std::string m_DetectorName;
	
};

}
#endif
