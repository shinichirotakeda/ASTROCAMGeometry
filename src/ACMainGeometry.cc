#include "ACMainGeometry.hh"
#include "ACMainGeometryRealWorld.hh"

using namespace anl;
using namespace anlgeant4;
using namespace astrocamgeometry;

ANLStatus ACMainGeometry::mod_startup() {
  
  register_parameter(&m_DetectorName, "Detector Name");
  set_parameter_description("Detector Name (ACFull, ACMrk1,ACMrk2,......) ");
  return AS_OK;
}

G4VUserDetectorConstruction* ACMainGeometry::create() {
  G4VUserDetectorConstruction* theGeometry = new ACMainGeometryRealWorld(m_DetectorName);
  return theGeometry;
}
