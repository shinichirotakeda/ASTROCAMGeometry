//!
// AHG4Material: Tamotsu Sato 2011-1-20
// 
// based on
// AsteMaterial:
//   Material class custormized for Astro-E2 simulator
//   written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp> Dec. 2003
//     $Id: AsteMaterial.hh,v 1.2 2004/03/18 04:42:22 ozaki Exp $
//

#ifndef AHG4Material_H
#define AHG4Material_H 1

#include "G4Material.hh"

/// Currentry, this class has no additional feature from G4Material
typedef G4Material AHG4Material;

//#include <hash_map>
//#include <string>

/// Vector (or container) to hold instantiated materials.
/// Note: the materials will be discarded automaticaly when the vector
/// is destructed.
//typedef hash_map<string, AHG4Material*> AHG4MaterialCollection;

#endif // AHG4Material_H
