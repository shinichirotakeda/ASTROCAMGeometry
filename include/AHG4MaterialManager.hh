//!
// AHG4MaterialManager:
//   written by OZAKI Masanobu <ozaki@astro.isas.jaxa.jp>
//  $Id: AHG4MaterialManager.hh,v 1.3 2004/08/26 10:28:39 ozaki Exp $
// 
//  This class holds recipies of "AHG4Material"s, and instantiate them
//  with the request from clients.  As it holds no material instance,
//  you can delete it anytime you want.
//  You can register new recipie with arbitrary name.  You can even
//  overwrite existing entry by the same interface (i.e. registerMaterial),
//  but you have to explicitly elable it by setMaterialOverwriteEnable
//  in advance.
//  You can use (i.e. instantiate) multiple factories at the same time.
//  As each factories is independ from others, you can safely rename
//  some materials or register one material (such as A7075) with some
//  variants to different factories: identical to the real world.
//
//
// --------------------------------------------------------------------
// 2012-05-25 yasuda (Saitama-U)
// add a parametar of instantiate(), "relativeDensityFlag".


#ifndef AHG4MaterialManager_H
#define AHG4MaterialManager_H 1

//using namespace std;
#include <vector>
#include <string>
#include <map>

#include "AHG4Material.hh"
#include "AHG4MaterialProperty.hh"
#include "AHG4ElementHandler.hh"
#include "globals.hh"

class G4Element;

class AHG4MaterialManager
{
  public:
    /// static method to get this manager singleton object
    static AHG4MaterialManager* GetAHG4MaterialManager();

  protected:
    AHG4MaterialManager();

  public:
    ~AHG4MaterialManager();

  public:
    /// Instantiate all the known materials. This method is invoked when this manager
    /// is instantiated.
    void registerKnownMaterials();

  public:
    typedef std::map<std::string,AHG4MaterialProperty*> CompositionArray;
    /// The instantiater:
    ///  the default density changes material by material.
    //AHG4Material* instantiate(const std::string& name, double density = 0);
  AHG4Material* instantiate(const std::string& name, double density = 0, int relativeDensityFlag = 0);
	
	// Copy property
	AHG4MaterialProperty* RetrieveProperty(std::string name);

    /// You can add your favorite materials.
    bool registerMaterial(const std::string& name, const AHG4MaterialProperty& theProperty);
    void setMaterialOverwriteEnable(bool flag);
    bool materialOverwriteEnableFlag();

    const CompositionArray* compositionArray();

  private:
    static AHG4MaterialManager* fpAHG4MaterialManager;
    AHG4ElementHandler* m_elementHandler;
    CompositionArray    m_compositionArray;
    bool                m_arrayOverwriteEnable;
	
};

#endif // AHG4MaterialManager_H
