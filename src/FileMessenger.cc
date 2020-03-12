#include "FileMessenger.hh"
#include "EventAction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"


FileMessenger::FileMessenger(EventAction* eva)
:EA(eva)
{
  FileDir = new G4UIdirectory("/file/");
  FileDir -> SetGuidance("set output file");
  
  fileNameCmd = new G4UIcmdWithAString("/file/name",this);
  fileNameCmd->SetGuidance("Set the filename for the root-output");
  fileNameCmd->SetParameterName("name",true);
  fileNameCmd->SetDefaultValue("hoge");
  fileNameCmd->AvailableForStates(G4State_Idle,G4State_PreInit);
  
  timeNowCmd = new G4UIcmdWithABool("/file/timenow",this);
  timeNowCmd  -> SetParameterName("timenow",true); 
  timeNowCmd  -> SetDefaultValue(true);
  timeNowCmd  -> SetGuidance("Set local time string for the filename");
  timeNowCmd  -> AvailableForStates(G4State_Idle, G4State_PreInit);
  
}

/////////////////////////////////////////////////////////////////////////////
FileMessenger::~FileMessenger()
{
  delete FileDir;
  delete fileNameCmd; 
  delete timeNowCmd;
}

/////////////////////////////////////////////////////////////////////////////
void FileMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == timeNowCmd)
    { EA -> SetTimeNow(timeNowCmd -> GetNewBoolValue(newValue)); }
  else if (command == fileNameCmd)
    { EA -> SetFileName(newValue); }
}

