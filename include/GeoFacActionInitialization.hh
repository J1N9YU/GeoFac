
#ifndef GeoFacActionInitialization_h
#define GeoFacActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class GeoFacActionInitialization : public G4VUserActionInitialization
{
  public:
    GeoFacActionInitialization();
    virtual ~GeoFacActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};


#endif

    
