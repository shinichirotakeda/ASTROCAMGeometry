//!
// AHG4MaterialProperty:
//   written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp>
// $Id: AHG4MaterialProperty.hh,v 1.5 2004/11/08 09:12:12 ozaki Exp $
//
// This class holds a recipie of material.  The contents are density,
// composition and (optional) elementHandler.  This class is used when
// you register a material to an AHG4MaterialFactory.  The factory
// then have a copy of this class internally, so you can safely delete it
// whenever you want.  Note that you must NOT delete the elementHandler
// if you register it as a member of the property, because it can be used
// by AHG4MaterialFactory later.  Of course you can delete the handler
// after the factory is deleted.
//

#ifndef AHG4MaterialProperty_H
#define AHG4MaterialProperty_H 1

#include <iostream>
#include <map>
#include <string>

class AHG4ElementHandler;

class AHG4MaterialProperty {
public:
  //    typedef std::map<std::string,double> Composition;
  typedef std::map<std::string,int> NumberComposition;
  typedef std::map<std::string,double> MassComposition;
  typedef enum {NUMBER, MASS} CompositionType;

  AHG4MaterialProperty();
  //    AHG4MaterialProperty(const double density, const Composition& composition, AHG4ElementHandler* handler = 0);
  AHG4MaterialProperty(const double density, const NumberComposition& composition, AHG4ElementHandler* handler = 0);
  AHG4MaterialProperty(const double density, const MassComposition& composition, AHG4ElementHandler* handler = 0);
  ~AHG4MaterialProperty();

  void setDensity(const double density);
  void setComposition(const NumberComposition& composition);
  void setComposition(const MassComposition& composition);
  void setElementHandler(AHG4ElementHandler* handler);

  double              density();
  //    Composition         composition();
  CompositionType     compositionType();
  NumberComposition   numberComposition();
  MassComposition     massComposition();
  AHG4ElementHandler* elementHandler();

  friend std::ostream& operator<<(std::ostream&, AHG4MaterialProperty*);
  friend std::ostream& operator<<(std::ostream&, AHG4MaterialProperty&);

private:               
  double              m_density;
  //    Composition         m_composition;
  CompositionType     m_compositionType;
  NumberComposition   m_numberComposition;
  MassComposition     m_massComposition;
  AHG4ElementHandler* m_elementHandler;
};

#endif // AHG4MaterialProperty_H
