#ifndef TESSD_h
#define TESSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TESHit.hh"
#include "globals.hh"

#include "Common.h"
#include "DetectorConstruction.hh"
#include "Interaction.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class Interaction;
class DetectorConstruction;
class TESSD : public G4VSensitiveDetector
{
  
public:
  TESSD(G4String name);
  ~TESSD();
  
  void Initialize(G4HCofThisEvent*HCE);
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*HCE);
  
private:
  TESHitsCollection* hitsCollection;
  G4String           sensitiveDetectorName;
  G4int              TESHCID[NbOfTES];
  G4int              hit_trackID;
  Interaction        interaction;
  DetectorConstruction  dID;
};

#endif
