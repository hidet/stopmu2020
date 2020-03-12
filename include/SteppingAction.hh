#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4VProcess.hh"

#include "AnaManager.hh"
#include "Interaction.hh"
#include "DetectorConstruction.hh"

class AnaManager;
class Interaction;
class DetectorConstruction;
class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(AnaManager* ana);
  ~SteppingAction();
  
  void UserSteppingAction(const G4Step*);
  
  private:
  AnaManager*    anam;
  StepData       stepData;
  StepData       stepDataKM;// kaon minus for DAFNE
  StepData       stepDataKP;// kaon plus for DAFNE
  Interaction    interaction;
  DetectorConstruction dID;
};

#endif
