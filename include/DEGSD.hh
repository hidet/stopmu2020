#ifndef DEGSD_h
#define DEGSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DEGHit.hh"
#include "globals.hh"

#include "Common.h"
#include "DetectorConstruction.hh"
#include "Interaction.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class Interaction;
class DetectorConstruction;
class DEGSD : public G4VSensitiveDetector
{
  
public:
  DEGSD(G4String name);
  ~DEGSD();
  
  void Initialize(G4HCofThisEvent*HCE);
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*HCE);
  
private:
  DEGHitsCollection* hitsCollection;
  G4String          sensitiveDetectorName;
  G4int             DEGHCID[NbOfDEG];
  G4int             hit_trackID;
  Interaction       interaction;
  DetectorConstruction        dID;
};

#endif

