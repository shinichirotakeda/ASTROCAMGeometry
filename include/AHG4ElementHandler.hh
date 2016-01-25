//!
// AHG4ElementHandler:
//     written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp>
// $Id: AHG4ElementHandler.hh,v 1.3 2004/08/26 10:28:39 ozaki Exp $
// 
//   This class holds the pointers to AHG4Element instances, and deliver
//   them for the requests from clients.  As it holds only pointers,
//   you can safely delete any handler instance if unused: but be careful
//   that AHG4MaterialFactory DOES use it if you instantiate a handler
//   and registered it as a part of AHG4MaterialProperty; in such case,
//   you should not delete it, of course.  If you want to do that,
//   you must delete the factory first.
//
//   You can use any number of AHG4ElementHandler at the same time:
//   each of them is independent from others.
//   You can register any elements with any name: if the handler already
//   holds some element with the same name, it will be discarded and
//   the new entry will be registered; at that time, the instance of
//   old entry remains untouched, so no (bad) interference occurs.
//
//   You must NOT delete retrieved or registered element: other part
//   of your program might use it in some part even if you are not aware;
//   AHG4Element itself has a static collection of instances, so some
//   part or library might be trying to access it via other element.
//   Be a paranoia!
//


#ifndef AHG4ElementHandler_H
#define AHG4ElementHandler_H 1

//using namespace std;
#include <string>
#include <map>

#include "G4Element.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

class G4Element;

class AHG4ElementHandler
{
  public:
    typedef std::map<std::string,G4Element*> ElementArray;
    typedef std::vector<std::string> ElementList;

    AHG4ElementHandler();
    ~AHG4ElementHandler();

    /// You can retrieve an element, but you must not delete it.
    G4Element* retrieve(std::string name);

    /// You can add (or even overwrite) your favorite elements.
    /// Note: you must not delete the registered element by yourself,
    ///       that is, you must not feed the element of auto variable.
    void registerElement(std::string name, G4Element* theElement);
    /// You can retrieve the catalog of known element.
    //  Note that it is rather high cost function because it makes
    //  internal copy of element names and copies again to the caller's
    //  variable.
    ElementList elementList();

  private:
    static ElementArray  m_commonElements;
    ElementArray         m_elements;
};

#endif // AHG4ElementHandler_H
