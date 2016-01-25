#ifndef ACMainGeometry_at1m_H
#define ACMainGeometry_at1m_H 1

#include "VANLGeometry.hh"

class G4VUserDetectorConstruction;

namespace astrocamgeometry {

class ACMainGeometry_at1m : public anlgeant4::VANLGeometry
{

  DEFINE_ANL_MODULE(ACMainGeometry_at1m, 1.0);

public:
  ACMainGeometry_at1m() {}
  virtual ~ACMainGeometry_at1m() {}
  
  anl::ANLStatus mod_startup();

  G4VUserDetectorConstruction* create();

private:
  std::string m_DetectorName;

};

}

#endif /* ACMainGeometry_at1m_H */
