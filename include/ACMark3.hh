#ifndef ACMark3_HH
#define ACMark3_HH

#include "globals.hh"
#include "GeometryComptonCamera.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class ACMark3 : public GeometryComptonCamera{

public:
  ACMark3() {};
  virtual ~ACMark3() {};
  
  G4LogicalVolume* Construct();

};

}

#endif

