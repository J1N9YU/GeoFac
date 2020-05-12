#ifndef dcm
#define dcm 1
#include "G4UImessenger.hh" 
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UImanager.hh"

#include "globals.hh"
#include "G4String.hh"

class G4ParticleGun; 
class G4ParticleTable; 
class G4UIcommand; 
class G4UIdirectory; 
class G4UIcmdWithoutParameter; 
class G4UIcmdWithAString; 
class G4UIcmdWithADoubleAndUnit; 
class G4UIcmdWith3Vector; 
class G4UIcmdWith3VectorAndUnit;
class G4string;
class GeoFacDetectorConstruction;

class GeoFacDetectorConstructionMessenger:public G4UImessenger{
    public:
    GeoFacDetectorConstructionMessenger(GeoFacDetectorConstruction* fDC);
    ~GeoFacDetectorConstructionMessenger();

    void SetNewValue(G4UIcommand* command,G4String newValues); 
    G4String GetCurrentValue(G4UIcommand* command);

    private:
    GeoFacDetectorConstruction* fDetectorConstruction;
    G4UIdirectory* directory;
    G4UIcmdWithADoubleAndUnit* SetPMMAThicknessCmd;
    G4UIcmdWithADoubleAndUnit* SetSiPDEdgeCmd;

};

#endif
