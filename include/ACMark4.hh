#ifndef ACMark4_HH
#define ACMark4_HH

#include "globals.hh"
#include "GeometryComptonCamera.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class ACMark4 : public GeometryComptonCamera{

public:
  ACMark4() {};
  virtual ~ACMark4() {};
  
  G4LogicalVolume* Construct();

};

}

#endif

