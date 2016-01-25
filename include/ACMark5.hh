#ifndef ACMark5_HH
#define ACMark5_HH

#include "globals.hh"
#include "GeometryComptonCamera.hh"

class G4LogicalVolume;
class G4VPhysicalVolume;

namespace astrocamgeometry {

class ACMark5 : public GeometryComptonCamera{

public:
  ACMark5() {};
  virtual ~ACMark5() {};
  
  G4LogicalVolume* Construct();

};

}

#endif

