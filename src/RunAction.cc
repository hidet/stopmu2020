#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"

using namespace CLHEP;

RunAction::RunAction(AnaManager* ana)
  :anam(ana)
{;}

RunAction::~RunAction()
{;}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  runData.RunID = aRun->GetRunID();
  runData.NEvt  = aRun->GetNumberOfEventToBeProcessed();
  G4cout << "====================================================" << G4endl;
  G4cout << "### Run " << runData.RunID << " start." << G4endl;
  G4cout << "    to be processed: " << runData.NEvt << G4endl;
  // inform the runManager to save random number seed
  // 2006/Apr/21 comment outed Tatsuno
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);
  HepRandom::setTheEngine(new RanecuEngine);
  G4long seed=time(0);
  HepRandom::setTheSeed(seed);
  HepRandom::showEngineStatus();  
  runData.Seed = seed;
  anam->FillRunData(runData);
}

void RunAction::EndOfRunAction(const G4Run* aRun) 
{
  runData.GEvt  = aRun->GetNumberOfEvent();
  G4cout << G4endl;
  G4cout << "### Run " << runData.RunID << " end." << G4endl;
  G4cout << "### Events generated = " << runData.GEvt << G4endl;
  G4cout << "====================================================" << G4endl;
}
