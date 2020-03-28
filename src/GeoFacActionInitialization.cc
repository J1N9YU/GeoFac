

#include "GeoFacActionInitialization.hh"
#include "GeoFacPrimaryGeneratorAction.hh"
#include "GeoFacRunAction.hh"
#include "GeoFacEventAction.hh"




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacActionInitialization::GeoFacActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GeoFacActionInitialization::~GeoFacActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GeoFacActionInitialization::BuildForMaster() const
{
  GeoFacRunAction* runAction = new GeoFacRunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GeoFacActionInitialization::Build() const
{
  SetUserAction(new GeoFacPrimaryGeneratorAction);

  GeoFacRunAction* runAction = new GeoFacRunAction;
  SetUserAction(runAction);
  
  GeoFacEventAction* eventAction = new GeoFacEventAction(runAction);
  SetUserAction(eventAction);
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
