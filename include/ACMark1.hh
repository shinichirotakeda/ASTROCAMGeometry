#ifndef ACMark1_HH
#define ACMark1_HH

#include "globals.hh"
#include "GeometryComptonCamera.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class ACMark1 : public GeometryComptonCamera{

public:
  ACMark1() {};
  virtual ~ACMark1() {};
  
  G4LogicalVolume* Construct();

};

}

#endif

