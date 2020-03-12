#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter; 
class G4UIcmdWithAString;        

class DetectorMessenger: public G4UImessenger
{
public:
  DetectorMessenger(DetectorConstruction* );
  ~DetectorMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  DetectorConstruction* DC;

  G4UIdirectory *changeTargetDir;
  G4UIcmdWithAString        *changeTargetMaterialCmd;
  G4UIcmdWithADoubleAndUnit *changeTargetDensityCmd;
  //G4UIcmdWithoutParameter   *updateCmd;
};
#endif
