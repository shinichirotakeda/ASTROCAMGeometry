#ifndef ACMainGeometry_H
#define ACMainGeometry_H 1

#include "VANLGeometry.hh"

class G4VUserDetectorConstruction;

namespace astrocamgeometry {

class ACMainGeometry : public anlgeant4::VANLGeometry
{
  DEFINE_ANL_MODULE(ACMainGeometry, 1.0);

public:
  ACMainGeometry() {}
  virtual ~ACMainGeometry() {}
  
  anl::ANLStatus mod_startup();

  G4VUserDetectorConstruction* create();

private:
  std::string m_DetectorName;

};

}

#endif /* ACMainGeometry_H */
