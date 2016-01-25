// AHG4MaterialProperty:
//   written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp>
// $Id: AHG4MaterialProperty.cc,v 1.4 2004/09/01 03:04:59 ozaki Exp $
//
//   For detail, see AHG4MaterialProperty.hh :-)

#include "AHG4ElementHandler.hh"
#include "AHG4MaterialProperty.hh"
#include <iomanip>


AHG4MaterialProperty::AHG4MaterialProperty()
{
  m_elementHandler = 0;
}

#if 0
AHG4MaterialProperty::AHG4MaterialProperty(const double density, const AHG4MaterialProperty::Composition& composition, AHG4ElementHandler* handler)
{
  m_density = density;
  m_composition = composition;
  m_elementHandler = handler;
}
#else
AHG4MaterialProperty::AHG4MaterialProperty(const double density, const AHG4MaterialProperty::NumberComposition& composition, AHG4ElementHandler* handler)
{
  m_density = density;
  m_compositionType = NUMBER;
  m_numberComposition = composition;
  m_elementHandler = handler;
}

AHG4MaterialProperty::AHG4MaterialProperty(const double density, const AHG4MaterialProperty::MassComposition& composition, AHG4ElementHandler* handler)
{
  m_density = density;
  m_compositionType = MASS;
  m_massComposition = composition;
  m_elementHandler = handler;
}
#endif

AHG4MaterialProperty::~AHG4MaterialProperty()
{
}


void
AHG4MaterialProperty::setDensity(const double density)
{
  m_density = density;
}

#if 0
void
AHG4MaterialProperty::setComposition(const AHG4MaterialProperty::Composition& composition)
{
  m_composition = composition;
}
#else
void
AHG4MaterialProperty::setComposition(const AHG4MaterialProperty::NumberComposition& composition)
{
  m_compositionType = NUMBER;
  m_numberComposition = composition;
}

void
AHG4MaterialProperty::setComposition(const AHG4MaterialProperty::MassComposition& composition)
{
  m_compositionType = MASS;
  m_massComposition = composition;
}
#endif

void
AHG4MaterialProperty::setElementHandler(AHG4ElementHandler* handler)
{
  m_elementHandler = handler;
}


double
AHG4MaterialProperty::density()
{
  return m_density;
}

#if 0
AHG4MaterialProperty::Composition
AHG4MaterialProperty::composition()
{
  return m_composition;
}
#else
AHG4MaterialProperty::CompositionType
AHG4MaterialProperty::compositionType()
{
  return m_compositionType;
}

AHG4MaterialProperty::NumberComposition
AHG4MaterialProperty::numberComposition()
{
  return m_numberComposition;
}

AHG4MaterialProperty::MassComposition
AHG4MaterialProperty::massComposition()
{
  return m_massComposition;
}
#endif


AHG4ElementHandler*
AHG4MaterialProperty::elementHandler()
{
  return m_elementHandler;
}


std::ostream&
operator<<(std::ostream& o, AHG4MaterialProperty* p)
{
  o << "density    : " << p->m_density << "\n"
    << "compositionType: " << p->m_compositionType << "\n"
    << "composition: " << "\n";
  if (p->m_compositionType == AHG4MaterialProperty::NUMBER){
    typedef AHG4MaterialProperty::NumberComposition::iterator I;
    for (I i = p->m_numberComposition.begin(); i != p->m_numberComposition.end(); i++){
      o << " " << i->first << ": " << i->second << "\n";
    }
  } else if (p->m_compositionType == AHG4MaterialProperty::MASS){
    typedef AHG4MaterialProperty::MassComposition::iterator I;
    for (I i = p->m_massComposition.begin(); i != p->m_massComposition.end(); i++){
      o << " " << i->first << ": " << i->second << "\n";
    }
  }
  return o;
}


std::ostream&
operator<<(std::ostream& o, AHG4MaterialProperty& p)
{
  o << &p;
  return o;
}
