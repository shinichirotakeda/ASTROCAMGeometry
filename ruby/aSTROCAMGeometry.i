%module aSTROCAMGeometry
%{

#include "ACMainGeometry.hh"
#include "ACMainGeometry_at1m.hh"

#include "class_list_anlGeant4.hh"

%}

%import "anlGeant4.i"

namespace astrocamgeometry {


 class ACMainGeometry : public anlgeant4::VANLGeometry
 {
 public:
   ACMainGeometry() {}
   virtual ~ACMainGeometry() {}

 };

 class ACMainGeometry_at1m : public anlgeant4::VANLGeometry
 {
 public:
   ACMainGeometry_at1m() {}
   virtual ~ACMainGeometry_at1m() {}

 };

}

