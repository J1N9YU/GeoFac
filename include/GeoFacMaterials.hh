

#ifndef GeoFacMaterials_h
#define GeoFacMaterials_h 1

#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "GeoFacDetectorConstruction.hh"

class GeoFacMaterials
{
  public:

    virtual ~GeoFacMaterials();
 
    static GeoFacMaterials* GetInstance();

    G4Material* GetMaterial(const G4String);
 
  private:
 
    GeoFacMaterials();

    void CreateMaterials();

  private:

    static GeoFacMaterials* fInstance;

    G4NistManager*     fNistMan;

    G4Material*        fAir;

    G4Material*        fPMMA;
    G4Material*        fPCB;
    G4Material*        fMetal;
    G4Material*        fSiPD;

};

#endif /*GeoFacMaterials_h*/
