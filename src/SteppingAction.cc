#include "SteppingAction.hh"
#include "AnaManager.hh"
#include "RunAction.hh"
#include "Interaction.hh"

#include "G4RunManager.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction(class AnaManager* ana)
  : anam(ana)
{;}

SteppingAction::~SteppingAction()
{;}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4double edep  = aStep->GetTotalEnergyDeposit();
  G4double stepl = aStep->GetStepLength();
  G4Track* track = aStep->GetTrack();
  G4TrackStatus trackstatus = track->GetTrackStatus();
  G4int trackID  = track->GetTrackID();
  G4int parentID = track->GetParentID();
  G4String pname = track->GetDefinition()->GetParticleName();
  G4int pdg = track->GetDynamicParticle()->GetPDGcode();
  
  G4StepPoint* PreStep  = aStep->GetPreStepPoint();
  G4StepPoint* PostStep = aStep->GetPostStepPoint();
  
  G4ThreeVector prepos = PreStep->GetPosition();
  G4ThreeVector premom = PreStep->GetMomentum();
  G4double     pretime = PreStep->GetGlobalTime();
  G4double     prekene = PreStep->GetKineticEnergy();

  //G4ThreeVector postpos = PostStep->GetPosition();
  //G4ThreeVector postmom = PostStep->GetMomentum();
  //G4double     posttime = PostStep->GetGlobalTime();
  //G4double     postkene = PostStep->GetKineticEnergy();
  G4double      postkene = track->GetKineticEnergy();
  G4ThreeVector postpos  = track->GetPosition();
  G4ThreeVector postmom  = track->GetMomentum();
  G4double      posttime = track->GetGlobalTime();
  
  // pre volume
  G4int      absNo = PreStep->GetTouchable()->GetVolume()->GetCopyNo();
  G4String logname = PreStep->GetTouchable()->GetVolume()->GetLogicalVolume()->GetName();
  G4int     logvid = dID.GetDetectorID(logname);

  // vertex information
  G4ThreeVector    vpos = aStep->GetTrack()->GetVertexPosition();
  G4ThreeVector   vmomd = aStep->GetTrack()->GetVertexMomentumDirection();
  G4double        vkene = aStep->GetTrack()->GetVertexKineticEnergy();
  G4String        vname = aStep->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
  G4int           vlvid = dID.GetDetectorID(vname);

  G4String cproc = "";  G4int cprocessID  = -9999;
  if (aStep->GetTrack()->GetCreatorProcess() != NULL) {
    cproc = aStep->GetTrack()->GetCreatorProcess()->GetProcessName();
    cprocessID = interaction.GetProcessID(cproc,prekene);
  } else {
    cproc = "Primary";
    cprocessID = 9999;
  }

  G4String proc = "";  G4int procid  = -9999;
  if ( PostStep->GetProcessDefinedStep() != NULL ) {
    proc = PostStep->GetProcessDefinedStep()->GetProcessName();
    procid = interaction.GetProcessID(proc,prekene);
  } else {
    G4cout << "Not well defined a PostSetpPoint: kill step" << G4endl;
    return;
  }

  //G4int evid = anam->GetEventID();
  G4int evid = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
  G4bool FILL =false;
  
  G4bool POSITIVE=false;
  G4bool NEGATIVE=false;
  if ( pname=="gamma" || pname=="kaon-" || pname=="pi-" || pname=="e-" || pname=="mu-") NEGATIVE=true;
  if ( pname=="kaon+" || pname=="pi+" || pname=="e+" || pname=="mu+" ) POSITIVE=true;

  
  // ---- Print Status ----
  // photon
  if ( (cproc=="Primary") && 
       (//pname=="gamma"  ||
        pname=="e-"     || pname=="e+"     ||
        pname=="mu-"    || pname=="mu+"    ||
        //pname=="kaon-"    || pname=="kaon+"  //||
        pname=="pi-"  || pname=="pi+"  //||
        //pname=="proton" || pname=="deuteron" || pname=="triton" || pname=="alpha" ||
        //pname=="sigma-" || pname=="sigma0" || 
        //pname=="sigma+" || pname=="lambda"
        ) && 
       !(procid==TRANSPORT || procid==MSC || procid==E_IONI ||
         procid==MU_IONI || procid==H_IONI ))
    {
      //interaction.PrintStatus(evid,logname,pdg,pname,prekene,edep,stepl,proc,procid,cproc,cprocessID);
    }
  

  // ------- filling condition ----------
  if ( (cproc=="Primary") && 
       (pname=="gamma"  ||
        pname=="e-"     || pname=="e+"     ||
        pname=="mu-"    || pname=="mu+"    ||
        pname=="kaon-"    || pname=="kaon+"  ||
        pname=="pi-"  || pname=="pi+"  //||
        //pname=="proton" || pname=="deuteron" || pname=="triton" || pname=="alpha" ||
        //pname=="sigma-" || pname=="sigma0" || 
        //pname=="sigma+" || pname=="lambda"
        )) {
    FILL=true;
    //      //if ( cproc=="Primary" && logname=="lead_shield_log" && postkene==0 ) 
    //      if ( logname=="lead_shield_log") 
    //	{
    //	  //track->SetTrackStatus(fStopAndKill);
    //	  //track->SetTrackStatus(fKillTrackAndSecondaries);
    //	}
    //      
    //      //if ( cproc=="Primary" && logname=="lead_colli_log" && postkene==0 ) 
    //      if ( logname=="lead_colli_log") 
    //	{
    //	  //track->SetTrackStatus(fKillTrackAndSecondaries);
    //	  //track->SetTrackStatus(fStopAndKill);
    //	}
    //
    //      if (logname=="deg_main_log" && postkene==0 ) 
    //	{
    //	  //track->SetTrackStatus(fStopAndKill);
    //	  //track->SetTrackStatus(fKillTrackAndSecondaries);
    //	}
  }
  
  if (FILL) {// primary step filling
    stepData.EventID     = evid;
    stepData.procid      = procid;
    stepData.cprocid     = cprocessID;
    stepData.status      = trackstatus;
    stepData.track       = trackID;
    stepData.parentID    = parentID;
    stepData.pdg         = pdg;
    stepData.pretime     = pretime;
    stepData.posttime    = posttime;
    stepData.prepos      = prepos;
    stepData.postpos     = postpos;
    stepData.premom      = premom;
    stepData.postmom     = postmom;
    stepData.logvid      = logvid;
    if(NEGATIVE) {
      stepDataKM.EventID     = evid;
      stepDataKM.procid      = procid;
      stepDataKM.cprocid     = cprocessID;
      stepDataKM.status      = trackstatus;
      stepDataKM.track       = trackID;
      stepDataKM.parentID    = parentID;
      stepDataKM.pdg         = pdg;
      stepDataKM.pretime     = pretime;
      stepDataKM.posttime    = posttime;
      stepDataKM.prepos      = prepos;
      stepDataKM.postpos     = postpos;
      stepDataKM.premom      = premom;
      stepDataKM.postmom     = postmom;
      stepDataKM.logvid      = logvid;
    } else if (POSITIVE) {
      stepDataKP.EventID     = evid;
      stepDataKP.procid      = procid;
      stepDataKP.cprocid     = cprocessID;
      stepDataKP.status      = trackstatus;
      stepDataKP.track       = trackID;
      stepDataKP.parentID    = parentID;
      stepDataKP.pdg         = pdg;
      stepDataKP.pretime     = pretime;
      stepDataKP.posttime    = posttime;
      stepDataKP.prepos      = prepos;
      stepDataKP.postpos     = postpos;
      stepDataKP.premom      = premom;
      stepDataKP.postmom     = postmom;
      stepDataKP.logvid      = logvid;
    }
    
    if (trackstatus==fStopButAlive || trackstatus==fStopAndKill 
        || fKillTrackAndSecondaries) {
      anam->FillStepData(stepData);
      if (NEGATIVE) anam->FillStepDataKM(stepDataKM);
      else if (POSITIVE) anam->FillStepDataKP(stepDataKP);
    } else if (trackstatus!=fAlive) {
      G4cout << "killed or suspended or postponed... : " << evid << " " <<  trackstatus << G4endl;
    }
  }
  
  return;
}
