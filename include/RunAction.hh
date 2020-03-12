#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include "AnaManager.hh"

class G4Run;
class RunAction : public G4UserRunAction
{
private:
  AnaManager* anam;
  RunData     runData;

public:
  RunAction(AnaManager* ana);
  ~RunAction();
  
public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

};


#endif
