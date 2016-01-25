#ifndef ACMark2_HH
#define ACMark2_HH

#include "globals.hh"
#include "GeometryComptonCamera.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class ACMark2 : public GeometryComptonCamera{

public:
  ACMark2() {};
  virtual ~ACMark2() {};
  
  G4LogicalVolume* Construct();

};

}

#endif

