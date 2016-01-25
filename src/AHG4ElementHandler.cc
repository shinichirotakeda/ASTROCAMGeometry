// AHG4ElementHandler
//    written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp>
// $Id: AHG4ElementHandler.cc,v 1.3 2004/08/26 10:28:39 ozaki Exp $
//
//   For detail, see AHG4ElementHandler.hh :-)

#include <string>
#include "G4Element.hh"
#include "AHG4ElementHandler.hh"

namespace {
  void prepareCommonElements(AHG4ElementHandler::ElementArray& a)
  {
    G4double Z = g/mole;
    //                      name        IUPAC   A    Z
    a["H"]  = new G4Element("Hydrogen",  "H",   1,   1.00794   *Z);
    a["He"] = new G4Element("Helium",    "He",  2,   4.002602  *Z);
    a["Li"] = new G4Element("Lithium",   "Li",  3,   6.941     *Z);
    a["Be"] = new G4Element("Beryllium", "Be",  4,   9.012182  *Z);
    a["B"]  = new G4Element("Boron",     "B",   5,  10.811     *Z);
    a["C"]  = new G4Element("Carbon",    "C",   6,  12.011     *Z);
    a["N"]  = new G4Element("Nitrogen",  "N" ,  7,  14.00674   *Z);
    a["O"]  = new G4Element("Oxygen"  ,  "O" ,  8,  15.9994    *Z);
    a["F"]  = new G4Element("Fluorine",  "F",   9,  18.9984032 *Z);
    a["Ne"] = new G4Element("Neon",      "Ne", 10,  20.1797    *Z);
    a["Na"] = new G4Element("Sodium",    "Na", 11,  22.989768  *Z);
    a["Mg"] = new G4Element("Magnesium", "Mg", 12,  24.3050    *Z);
    a["Al"] = new G4Element("Aluminium", "Al", 13,  26.981539  *Z);
    a["Si"] = new G4Element("Silicon",   "Si", 14,  28.0855    *Z);
    a["P"]  = new G4Element("Phosphor",  "P" , 15,  30.9738    *Z);
    a["S"]  = new G4Element("Sulfur",    "S",  16,  32.066     *Z);
    a["Cl"] = new G4Element("Chlorine",  "Cl", 17,  35.4527    *Z);
    a["Ar"] = new G4Element("Argon",     "Ar", 18,  39.984     *Z);
    a["K"]  = new G4Element("Potassium", "K",  19,  39.0983    *Z);
    a["Ca"] = new G4Element("Calcium",   "Ca", 20,  40.078     *Z);
    a["Sc"] = new G4Element("Scandium",  "Sc", 21,  44.955910  *Z);
    a["Ti"] = new G4Element("Titanium",  "Ti", 22,  47.867     *Z);
    a["V"]  = new G4Element("Vanadium",  "V",  23,  50.9415    *Z);
    a["Cr"] = new G4Element("Chromium",  "Cr", 24,  51.9961    *Z);
    a["Mn"] = new G4Element("Manganese", "Mn", 25,  54.93805   *Z);
    a["Fe"] = new G4Element("Iron",      "Fe", 26,  55.847     *Z);
    a["Co"] = new G4Element("Cobalt",    "Co", 27,  58.93320   *Z);
    a["Ni"] = new G4Element("Nickel",    "Ni", 28,  58.6934    *Z);
    a["Cu"] = new G4Element("Copper",    "Cu", 29,  63.546     *Z);
    a["Zn"] = new G4Element("Zinc",      "Zn", 30,  65.39      *Z);
    a["Ga"] = new G4Element("Gallium",   "Ga", 31,  69.723     *Z);
    a["Ge"] = new G4Element("Germanium", "Ge", 32,  72.61      *Z);
    a["Mo"] = new G4Element("Molybdenum","Mo", 42, 95.94       *Z);
    a["Ag"] = new G4Element("Silver",    "Ag", 47, 107.8682    *Z);
    a["Cd"] = new G4Element("Cadmium",   "Cd", 48, 112.411     *Z);
    a["Sn"] = new G4Element("Tin",       "Sn", 50, 118.710     *Z);
    a["Te"] = new G4Element("Tellurium", "Te", 52, 127.60      *Z);
    a["I"] =  new G4Element("Iodine",    "I",  53, 126.90447   *Z);
    a["Cs"] = new G4Element("Cesium",    "Cs", 55, 132.90543   *Z);
    a["Ba"] = new G4Element("Barium",    "Ba", 56, 137.327     *Z);
    a["Ce"] = new G4Element("Cerium",    "Ce", 58, 140.115     *Z);
    a["Gd"] = new G4Element("Gadolinium","Gd", 64, 157.25      *Z);
    a["Pt"] = new G4Element("Platinum",  "Pt", 78, 195.078     *Z);
    a["Au"] = new G4Element("Gold",      "Au", 79, 196.96654   *Z);
    a["Hg"] = new G4Element("Hydrargentum","Hg",80, 200.59      *Z);
    a["Pb"] = new G4Element("Lead",      "Pb", 82, 207.19	   *Z);
    a["Bi"] = new G4Element("Bismuth",   "Bi", 83, 208.98037   *Z);
  }
}


AHG4ElementHandler::ElementArray AHG4ElementHandler::m_commonElements;


AHG4ElementHandler::AHG4ElementHandler()
{
  if (m_commonElements.size() == 0){
    prepareCommonElements(m_commonElements);
  }
  m_elements = m_commonElements;
}



AHG4ElementHandler::~AHG4ElementHandler()
{
#if 0   // This class DOESN'T erase the contents.
  for (ElementArray::iterator p = m_elements.begin(); p != m_elements.end(); p++){
    delete p->second;
    m_elements.erase(p);
  }
#endif
}


G4Element*
AHG4ElementHandler::retrieve(std::string name)
{
  return m_elements.count(name) ? m_elements[name] : 0;
}


void
AHG4ElementHandler::registerElement(std::string name, G4Element* theElement)
{
  m_elements[name] = theElement;
}


AHG4ElementHandler::ElementList
AHG4ElementHandler::elementList()
{
  ElementList l;
  for (ElementArray::iterator i = m_elements.begin(); i != m_elements.end(); i++){
    l.push_back(i->first);
  }
  return l;
}
