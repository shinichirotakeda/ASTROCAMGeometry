// AHG4MaterialManager:
//   written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp>
//  $Id: AHG4MaterialManager.cc,v 1.5 2004/09/07 12:14:09 yterada Exp $
//
//    For detail, see AHG4MaterialManager.hh :-)
//
//
// --------------------------------------------------------------------
// 2012-05-25 yasuda (Saitama-U)
// add a parametar of instantiate(), "relativeDensityFlag".


#include "AHG4MaterialManager.hh"

#include <string>

#include "AHG4MaterialManager.hh"
#include "AHG4Material.hh"
#include "AHG4MaterialProperty.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Element.hh"

AHG4MaterialManager* AHG4MaterialManager::fpAHG4MaterialManager = 0;

AHG4MaterialManager* AHG4MaterialManager::GetAHG4MaterialManager()
{
  if(!fpAHG4MaterialManager)
  { fpAHG4MaterialManager = new AHG4MaterialManager(); }
  return fpAHG4MaterialManager;
}

AHG4MaterialManager::AHG4MaterialManager()
 :m_arrayOverwriteEnable(false)
{
  registerKnownMaterials();
  m_elementHandler = new AHG4ElementHandler;
}

AHG4MaterialManager::~AHG4MaterialManager()
{
  typedef CompositionArray::iterator I;
  for (I i = m_compositionArray.begin(); i != m_compositionArray.end(); i++){
    delete i->second;
    m_compositionArray.erase(i);
  }
  delete m_elementHandler;
}

void AHG4MaterialManager::registerKnownMaterials()
{
  typedef AHG4MaterialProperty::NumberComposition	NC;
  typedef AHG4MaterialProperty::MassComposition	MC;
  const char* name;
  double density;

  {
    name = "Alumina";
    density = 3.97 * g/cm3;
    NC c; // NumberComposition
    c["Al"] = 2;
    c["O"] = 3;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "A5083";         // uncertain !!!!!!!!!!!
    density = 2.69 * g/cm3;
    MC c; // MassComposition
    c["Al"] = 94.8 * perCent;
    c["Mg"] = 4.0 * perCent;
    c["Mn"] = 0.4 * perCent;
    c["Fe"] = 0.4 * perCent;
    c["Si"] = 0.4 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Au";
    density = 19.3 * g/cm3;
    NC c; // NumberComposition
    c["Au"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }       
  {
    name = "HgTe";
    density = 7.86 * g/cm3;
    NC c; // NumberComposition
    c["Hg"] = 1;
    c["Te"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "VanadiumPermender";
    density = 7.9 * g/cm3;  // uncertain
    MC c;
    c["Fe"] = 49. * perCent; 
    c["Co"] = 49. * perCent; 
    c["V"] = 2. * perCent; 
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "LiquidHelium";
    //density = 125.0 * g/l;
    density = 0.144 * g/cm3;
    NC c;
    c["He"] = 1; 
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "SulfuricAcid";
    density = 1.84 * g/cm3;
    NC c;
    c["H"] = 2;
    c["S"] = 1;
    c["O"] = 4;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Molybdenum";
    density = 10.28 * g/cm3;
    NC c;
    c["Mo"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Polyimide"; // Kapton
    density = 1.42 * g/cm3;
    NC c;
    c["C"] = 22; // Really ?
    c["N"] = 2;
    c["O"] = 5;
    c["H"] = 10;              // added 20121109
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Beryllium";
    density = 1.85 * g/cm3;
    NC c;
    c["Be"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Aluminium";
    density = 2.70 * g/cm3;
    NC c; // NumberComposition
    c["Al"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Titanium";
    density = 4.54 * g/cm3;
    NC c; 
    c["Ti"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Vacuum";
    density = universe_mean_density;
    NC c;
    c["H"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Air";
    density = 1.290 * mg/cm3;
    MC c;
    c["N"] = 75.575 * perCent;
    c["O"] = 23.143 * perCent;
    c["Ar"] = 1.282 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "A6061"; // XXX FIXME!! XXX
    density = 2.69 * g/cm3;
    MC c;
    c["Al"] = 98.9 * perCent;
    c["Mg"] =  0.7 * perCent;
    c["Si"] =  0.4 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
    name = "AlAlloy";
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "A7075"; // XXX FIXME!! XXX
    density = 2.69 * g/cm3;
    MC c;
    c["Al"] = 90.5 * perCent;
    c["Cu"] =  1.5 * perCent;
    c["Zn"] =  2.5 * perCent;
    c["Mg"] =  5.5 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "SUS304";
    density = 7.9 * g/cm3;
    MC c;
    c["Fe"] = 70.5 * perCent;
    c["Cr"] = 19.0 * perCent;
    c["Ni"] =  9.0 * perCent;
    c["Mn"] =  1.0 * perCent;
    c["Si"] =  0.5 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "CdTe";
    density = 5.85 * g/cm3;
    NC c;
    c["Cd"] = 1;
    c["Te"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "CdZnTe";
    density = 5.81 * g/cm3;
    NC c;
    c["Cd"] = 45;
    c["Zn"] =  5;
    c["Te"] = 50;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Si";
    density = 2.34 * g/cm3;
    NC c;
    c["Si"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
    name = "Silicon";
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Ge";
    density = 5.32 * g/cm3;
    NC c;
    c["Ge"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Cu";
    density = 8.93 * g/cm3;
    NC c;
    c["Cu"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
    name = "Copper";
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Pb";
    density = 11.35 * g/cm3;
    NC c;
    c["Pb"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
    name = "Lead";
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Sn";
    density = 7.31 * g/cm3;
    NC c;
    c["Sn"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
    name = "Tin";
    registerMaterial(name, AHG4MaterialProperty(density, c));
  } 
  {
    name = "NaI";
    density = 3.67 * g/cm3;
    NC c;
    c["Na"] = 1;
    c["I"]  = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "CsI";
    density = 4.53 * g/cm3;
    NC c;
    c["Cs"] = 1;
    c["I"]  = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
#if 0
  {
    name = "GSO";
    density = 6.71 * g/cm3;
    C c;
    c["Gd"] = (2./(2+1+5)) * 95.0 * perCent;
    c["Si"] = (1./(2+1+5)) * 95.0 * perCent;
    c["O"]  = (5./(2+1+5)) * 95.0 * perCent;
    c["Ce"] = 5.0 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
#endif
  {
    name = "BGO";
    density = 7.13 * g/cm3;
    NC c;
    c["Bi"] =  4;
    c["Ge"] =  3;
    c["O"]  = 12;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "MuMetal";  // XXX FIXME!! XXX
    density = 8. * g/cm3;
    NC c;
    c["Fe"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "BaSO4";
    density = 5. * g/cm3;
    NC c;
    c["Ba"] = 1;
    c["S"]  = 1;
    c["O"]  = 4;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "GoreTex";  // a kind of PTFE
    density = 2.3 * g/cm3;
    NC c;
    c["C"] = 1;
    c["F"] = 2;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Rubber";
    density = 1. * g/cm3;
    NC c;
    c["C"] = 1;
    c["S"] = 1;
    c["H"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "CFRP";
    density = 2.0 * g/cm3;
    MC c;
    c["C"] = 89.5 * perCent;
    c["H"] =  3.1 * perCent;
    c["O"] =  7.4 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "CuSnP";
    density = 8.83 * g/cm3;
    MC c;
    c["Cu"] = 92.5 * perCent;
    c["Sn"] =  7.0 * perCent;
    c["P"]  =  0.5 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "AlHoneycomb";
    density = 0.2 * g/cm3;
    NC c;
    c["Al"] = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "AlN";
    density = 3.255 * g/cm3;
    NC c;
    c["Al"] = 1;
    c["N"]  = 1;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "PC";
    density = 1.2 * g/cm3;
    NC c;
    c["C"] = 16;
    c["H"] = 14;
    c["O"] = 3;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "FR4";
    density = 1.8 * g/cm3;
    NC c;
    c["C"] = 18;
    c["H"] = 42;
    c["O"] = 2;


    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  {
    name = "Steel";
    density = 7.874*g/cm3;
    MC c;
    c["Fe"] = 100.0*perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
  }
  /*==============* // Template
    {
    name = "";
    density = * g/cm3;
    C c;
    c[""] = 100.0 * perCent;
    registerMaterial(name, AHG4MaterialProperty(density, c));
    }
    *==============*/
}


AHG4Material*
AHG4MaterialManager::instantiate(const std::string& name, double density, int relativeDensityFlag )
{
  if (m_compositionArray.find(name) == m_compositionArray.end()){
    return 0;
  }
  AHG4MaterialProperty* p = m_compositionArray[name];
  AHG4ElementHandler*   f = p->elementHandler()
                          ? p->elementHandler()
                          : m_elementHandler;

  if (density == 0) density = p->density();
  else if(density == 0 && relativeDensityFlag != 0){
    G4cout << "[ERROR] parameter of relative rate of density is empty (" << name << ")" << G4endl;
  }
  else if(relativeDensityFlag != 0){
    density = p->density() * density;
  }

  AHG4Material* m = 0;
  if (p->compositionType() == AHG4MaterialProperty::NUMBER){
    AHG4MaterialProperty::NumberComposition c = p->numberComposition();
    m = new AHG4Material(name, density, c.size());
    typedef AHG4MaterialProperty::NumberComposition::iterator I;
    for (I i = c.begin(); i != c.end(); i++){
      m->AddElement(f->retrieve(i->first), i->second);
    }
  } else if (p->compositionType() == AHG4MaterialProperty::MASS){
    AHG4MaterialProperty::MassComposition c = p->massComposition();
    m = new AHG4Material(name, density, c.size());
    typedef AHG4MaterialProperty::MassComposition::iterator I;
    for (I i = c.begin(); i != c.end(); i++){
      m->AddElement(f->retrieve(i->first), i->second);
    }
  }
  return m;
}

AHG4MaterialProperty*
AHG4MaterialManager::RetrieveProperty(std::string name)
{
	if (m_compositionArray.find(name) == m_compositionArray.end()){
		return 0;
	}
	AHG4MaterialProperty* p = m_compositionArray[name];
	return p;
}

bool
AHG4MaterialManager::registerMaterial(const std::string& name, const AHG4MaterialProperty& p)
{
  if (m_compositionArray.find(name) != m_compositionArray.end()){
    if (m_arrayOverwriteEnable){
      delete m_compositionArray[name];
    } else {
      return false;
    }
  }
  m_compositionArray[name] = new AHG4MaterialProperty(p);
  return true;
}


void
AHG4MaterialManager::setMaterialOverwriteEnable(bool flag)
{
  m_arrayOverwriteEnable = flag;
}


bool
AHG4MaterialManager::materialOverwriteEnableFlag()
{
  return m_arrayOverwriteEnable;
}


const
AHG4MaterialManager::CompositionArray*
AHG4MaterialManager::compositionArray()
{
  return &m_compositionArray;
}
