#ifndef AnaManager_h
#define AnaManager_h 1

#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

// ----> see SteppingAction
struct StepData{
 public:
  G4int         EventID;
  G4int         track;
  G4int         status;
  G4int         procid;
  G4int         cprocid;
  G4int         parentID;
  G4int         pdg;
  G4double      pretime;
  G4double      posttime;
  G4ThreeVector prepos;
  G4ThreeVector premom;
  G4ThreeVector postpos;
  G4ThreeVector postmom;
  G4int         logvid;
};

// ---> see RunAction
struct RunData{
 public:
  G4int    RunID;
  G4long   Seed;
  G4int    NEvt;
  G4int    GEvt;
};


class AnaManager
{
private:
  G4int      eventID;
  RunData    runData;
  StepData   stepData;
  StepData   stepDataKM;
  StepData   stepDataKP;
  
public:
  AnaManager(){;}
  ~AnaManager(){;}
  
  // ----------------
  void FillRunData(RunData &runData0){runData=runData0;}
  G4int GetNumberOfToBeProcessed(){return runData.NEvt;}  
  // ----------------
  void SetEventID(G4int evid){eventID=evid;}  
  G4int GetEventID(){return eventID;}  
  // ----------------
  void FillStepData(StepData &stepData0){stepData=stepData0;}
  G4int GetEventIDStep(){return stepData.EventID;}
  G4int GetTrackID(){return stepData.track;}
  G4int GetProcessID(){return stepData.procid;}
  G4int GetPDGcode(){return stepData.pdg;}
  G4int GetStatus(){return stepData.status;}
  G4double GetStepPreTime(){return stepData.pretime;}
  G4double GetStepPostTime(){return stepData.posttime;}

  G4ThreeVector GetStepPrePos(){return stepData.prepos;}
  G4ThreeVector GetStepPreMom(){return stepData.premom;}
  G4ThreeVector GetStepPostPos(){return stepData.postpos;}
  G4ThreeVector GetStepPostMom(){return stepData.postmom;}
  G4int GetStepLogVID(){return stepData.logvid;}
  // K- ----------------
  void FillStepDataKM(StepData &stepData0){stepDataKM=stepData0;}
  G4int GetEventIDStepKM(){return stepDataKM.EventID;}
  G4int GetTrackIDKM(){return stepDataKM.track;}
  G4int GetProcessIDKM(){return stepDataKM.procid;}
  G4int GetPDGcodeKM(){return stepDataKM.pdg;}
  G4int GetStatusKM(){return stepDataKM.status;}
  G4double GetStepPreTimeKM(){return stepDataKM.pretime;}
  G4double GetStepPostTimeKM(){return stepDataKM.posttime;}
  G4ThreeVector GetStepPrePosKM(){return stepDataKM.prepos;}
  G4ThreeVector GetStepPreMomKM(){return stepDataKM.premom;}
  G4ThreeVector GetStepPostPosKM(){return stepDataKM.postpos;}
  G4ThreeVector GetStepPostMomKM(){return stepDataKM.postmom;}
  G4int GetStepLogVIDKM(){return stepDataKM.logvid;}
  // K+ ----------------
  void FillStepDataKP(StepData &stepData0){stepDataKP=stepData0;}
  G4int GetEventIDStepKP(){return stepDataKP.EventID;}
  G4int GetTrackIDKP(){return stepDataKP.track;}
  G4int GetProcessIDKP(){return stepDataKP.procid;}
  G4int GetPDGcodeKP(){return stepDataKP.pdg;}
  G4int GetStatusKP(){return stepDataKP.status;}
  G4double GetStepPreTimeKP(){return stepDataKP.pretime;}
  G4double GetStepPostTimeKP(){return stepDataKP.posttime;}
  G4ThreeVector GetStepPrePosKP(){return stepDataKP.prepos;}
  G4ThreeVector GetStepPreMomKP(){return stepDataKP.premom;}
  G4ThreeVector GetStepPostPosKP(){return stepDataKP.postpos;}
  G4ThreeVector GetStepPostMomKP(){return stepDataKP.postmom;}
  G4int GetStepLogVIDKP(){return stepDataKP.logvid;}
  // ----------------
};

#endif
