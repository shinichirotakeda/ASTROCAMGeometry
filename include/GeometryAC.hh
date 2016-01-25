#ifndef GeometryAC_HH
#define GeometryAC_HH

#include "globals.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class GeometryAC {

public:
  GeometryAC() {};
  virtual ~GeometryAC() {};
  
  G4LogicalVolume* Construct(std::string detname);

private:

  void DefineMaterials() {};
  void SetupGeometry() {};
};

}

#endif


