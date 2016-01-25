#ifndef GeometryComptonCamera_HH
#define GeometryComptonCamera_HH

#include "globals.hh"
//#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;



namespace astrocamgeometry {

class GeometryComptonCamera {

public:
  GeometryComptonCamera() {};
  virtual ~GeometryComptonCamera() {};
  
  virtual G4LogicalVolume* Construct();

private:

  void DefineMaterials() {};
  void SetupGeometry() {};
  
};

}

#endif

