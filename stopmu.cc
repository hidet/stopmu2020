#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "Randomize.hh"

#include "Materials.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
//#include "TrackingAction.hh"
//#include "StackingAction.hh"
#include "SteppingAction.hh"
//#include "SteppingVerbose.hh"
#include "AnaManager.hh"

#ifdef G4VIS_USE
//#include "G4VisExecutive.hh"
#include "VisManager.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

using namespace CLHEP;


int main(int argc,char** argv) {
  // choose the Random engine
  HepRandom::setTheEngine(new RanecuEngine);
  
  //my Verbose output class
  //G4VSteppingVerbose* verbosity = new SteppingVerbose;
  //G4VSteppingVerbose::SetInstance(verbosity);
  
  // Construct the default run manager
  G4RunManager * runManager = new G4RunManager;

  Materials* mat = new Materials();
  DetectorConstruction* detector = new DetectorConstruction(mat);
  runManager->SetUserInitialization(detector);
  PhysicsList* physics = new PhysicsList;
  runManager->SetUserInitialization(physics);

  AnaManager* anam = new AnaManager();
  runManager->SetUserAction(new PrimaryGeneratorAction());
  runManager->SetUserAction(new RunAction(anam));
  runManager->SetUserAction(new EventAction(anam));
  //runManager->SetUserAction(new StackingAction);
  //runManager->SetUserAction(new TrackingAction(anam));
  runManager->SetUserAction(new SteppingAction(anam));
  
  //Initialize G4 kernel
  runManager->Initialize();    
  
  // get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  

  //#ifdef G4VIS_USE
  // visualization manager
  //G4VisManager* visManager = new G4VisExecutive;
  G4VisManager* visManager = new VisManager;
  visManager->Initialize();
  //#endif

  if (argc!=1)// Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }
  else
    {
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
      ui->SessionStart();
      delete ui;
#endif
    }
  
  //#ifdef G4VIS_USE
  delete visManager;
  //#endif

  // job termination
  delete anam;
  delete runManager;
  //delete verbosity;
  
  return 0;
}
