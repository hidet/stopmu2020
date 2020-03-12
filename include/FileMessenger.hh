#ifndef FileMessenger_h
#define FileMessenger_h 1


#include "G4UImessenger.hh"
#include "globals.hh"

class EventAction;
class G4UIdirectory;
class G4UIcmdWithAString; 
class G4UIcmdWithABool; 

class FileMessenger: public G4UImessenger
{
public:
  FileMessenger(EventAction*);
  ~FileMessenger();

  void SetNewValue(G4UIcommand*, G4String);
    
private:
  EventAction* EA;
  G4UIdirectory*       FileDir;
  G4UIcmdWithABool*    timeNowCmd; 
  G4UIcmdWithAString*  fileNameCmd;
};

#endif
