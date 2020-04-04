
//
/// \file GeoFac.cc
/// \brief Main program of the GeoFac example

#include "GeoFacDetectorConstruction.hh"
#include "GeoFacActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "LBE.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "G4OpticalPhysics.hh"
#include "MyDataAnalysisHelper.hh"
#include "globals.hh"
#include "G4GeometryManager.hh"
#include "GeoFacPrimaryGeneratorAction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
  int numTreads = 3;
  int repeatEachThread =10 ;
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(numTreads);
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new GeoFacDetectorConstruction());
  GeoFacDetectorConstruction* fDetectorConstruction = (GeoFacDetectorConstruction*)runManager->GetUserDetectorConstruction();
  fDetectorConstruction->SetIsOriginModel(false);

  // Physics list
  G4VModularPhysicsList* physicsList = new LBE;
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
  physicsList->SetVerboseLevel(0);
  runManager->SetUserInitialization(physicsList);

  //Primary Generator Action
  GeoFacPrimaryGeneratorAction* fGPGA = (GeoFacPrimaryGeneratorAction*)runManager->GetUserPrimaryGeneratorAction();
  
  
    

  // User action initialization
  runManager->SetUserInitialization(new GeoFacActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  //Initial data analysis helper
  MyDataAnalysisHelper* myHelper = MyDataAnalysisHelper::GetInstance();
  myHelper->SetNumThreads(numTreads);
  myHelper->SetRepeats(repeatEachThread);
  myHelper->SetSavingMode(true);

  runManager->SetVerboseLevel(0);
  if(!ui)runManager->Initialize();
  

  

  

  if ( ! ui ) { 
    G4String fileName = argv[1];
    if(fileName=="convergence"||fileName=="-c"){
      
      int start = 16;
      int step = 1;
      int n = 15;
      //source light geometry
      fDetectorConstruction->SetThicknessOfPMMA(0);
      myHelper->SetExperimentType("source");
      for(int i=0;i<n;i++){
        int eventCnt = start + i*step;
        double p = (double)eventCnt/5.0;
        eventCnt = pow10(p);
        for(int j=0;j<repeatEachThread;j++){
          runManager->BeamOn(eventCnt);
        }
      }
      myHelper->WriteToFile();  
      
      //remission light geometry
      fDetectorConstruction->SetThicknessOfPMMA(0.283*CLHEP::cm);
      myHelper->SetExperimentType("reemit");
      for(int i=0;i<n;i++){
        int eventCnt = start + i*step;
        double p = (double)eventCnt/5.0;
        eventCnt = pow10(p);
        for(int j=0;j<repeatEachThread;j++){
          runManager->BeamOn(eventCnt);
        }
      }
      myHelper->WriteToFile();

    }else{
      G4String command = "/control/execute ";    
      UImanager->ApplyCommand(command+fileName);
    }
  }
  else { 
    // interactive mode
    //fGPGA->SetTestMode(true);
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    UImanager->ApplyCommand("/run/numberOfThreads 1");

    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}


