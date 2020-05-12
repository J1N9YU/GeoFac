#include "GeoFacDetectorConstructionMessnger.hh"
#include "GeoFacDetectorConstruction.hh"



class GeoFacDetectorConstruction;
class G4String;

GeoFacDetectorConstructionMessenger::GeoFacDetectorConstructionMessenger(GeoFacDetectorConstruction* fdc):fDetectorConstruction(fdc){
    directory = new G4UIdirectory("/Construction/");
    directory->SetGuidance("Commands to change geometry");

    SetPMMAThicknessCmd = new G4UIcmdWithADoubleAndUnit("/Construction/SetPMMAThickness",this);
    SetPMMAThicknessCmd->SetParameterName("thicknessOfPMMA",true,true);
    SetPMMAThicknessCmd->SetDefaultUnit("cm");
    SetPMMAThicknessCmd->SetGuidance("change the thickness of PMMA");

    SetSiPDEdgeCmd = new G4UIcmdWithADoubleAndUnit("/Construction/SetSiPDEdge",this);
    SetSiPDEdgeCmd->SetGuidance("change the edge of SiPD");
    SetSiPDEdgeCmd->SetParameterName("photodiodeEdge",true,true);
    SetSiPDEdgeCmd->SetDefaultUnit("cm");

}

GeoFacDetectorConstructionMessenger::~GeoFacDetectorConstructionMessenger(){
    delete directory;
    delete SetPMMAThicknessCmd;
    delete SetSiPDEdgeCmd;
}

void GeoFacDetectorConstructionMessenger::SetNewValue(G4UIcommand * command,G4String newValues){
    if(command==SetPMMAThicknessCmd){
        fDetectorConstruction->SetThicknessOfPMMA(SetPMMAThicknessCmd->GetNewDoubleValue(newValues));
        G4cout<<"Now thickness is"<<fDetectorConstruction->GetThicknessOfPMMA()<<G4endl;
        
        
    }
    if(command==SetSiPDEdgeCmd){
        fDetectorConstruction->SetphotodiodeEdge(SetSiPDEdgeCmd->GetNewDoubleValue(newValues));
    }
    G4UImanager::GetUIpointer()->ApplyCommand("/control/execute init_vis.mac");
}

G4String GeoFacDetectorConstructionMessenger::GetCurrentValue(G4UIcommand* command){
    G4String cv;
    return cv;
}
