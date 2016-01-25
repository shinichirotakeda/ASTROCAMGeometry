#include "ACMainGeometry_at1m.hh"
#include "ACMainGeometryRealWorld_at1m.hh"

using namespace anl;
using namespace anlgeant4;
using namespace astrocamgeometry;


ANLStatus ACMainGeometry_at1m::mod_startup() {
  
  register_parameter(&m_DetectorName, "Detector Name");
  set_parameter_description("Detector Name (ACFull, ACMrk1,ACMrk2,......) ");
  return AS_OK;
}

G4VUserDetectorConstruction* ACMainGeometry_at1m::create() {
  G4VUserDetectorConstruction* theGeometry = new ACMainGeometryRealWorld_at1m(m_DetectorName);
  return theGeometry;
}
