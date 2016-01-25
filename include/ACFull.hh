#ifndef ACFull_HH
#define ACFull_HH

#include "globals.hh"
#include "GeometryComptonCamera.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class ACFull : public GeometryComptonCamera{

public:
  ACFull() {};
  virtual ~ACFull() {};
  
  G4LogicalVolume* Construct();

};

}

#endif

