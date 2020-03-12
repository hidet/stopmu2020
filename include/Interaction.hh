#ifndef Interaction_h
#define Interaction_h 1

// transport
#define PRIMARY               9999
#define TRANSPORT                0
// decay                        
#define DECAY_REST               1
#define DECAY_FLIGHT             2
// EM                           
#define IONI                     3
#define H_IONI                   4
#define MSC                      5
#define ANNIHIL                  6
#define E_IONI                   7 
#define MU_IONI                  8
#define E_BREM                   9 
#define ION_IONI                10
#define MU_MSC                  11
// low-energy EM                
#define LE_PHOTO_ELEC           12
#define LE_RAY                  13
#define LE_COMP                 14
#define LE_BREM                 15
#define LE_CONV                 16
// kaon/pion inelastic          
#define KAON_PLUS_INELA         20
#define KAON_MINUS_INELA        21
#define KAON_ZEROL_INELA        22
#define PION_PLUS_INELA         23
#define PION_MINUS_INELA        24
// kaon/pion atrest             
#define KAON_MINUS_ABSORP       30
#define KAON_MINUS_ATREST       31
#define PION_MINUS_ABSORP       32
#define PION_MINUS_ATREST       33
#define H_BERTINI_ATREST        34
// hadron elastic               
#define HADRON_ELASTIC          40
// hadron inelastic             
#define PROTON_INELA            41
#define NEUTRON_INELA           42
#define DEUTERON_INELA          43
#define TRITON_INELA            44
#define ALPHA_INELA             45
#define HE3_INELA               46
#define ION_INELA               47
#define LAMBDA_INELASTIC        48
#define SIGMA_PLUS_INELASTIC    49
#define SIGMA_MINUS_INELASTIC   50
// muon atrest/nucleon capture/other
#define MU_MINUS_CAPTURE_ATREST 60
#define N_CAPTURE               61
#define RAD_DECAY               70
#define PHOTON_NUCLEAR          71
#define COULOMB_SCAT            72
#define ELECTRON_NUCLEAR        73
#define POSITRON_NUCLEAR        74
// kill
#define NKILLER                 90

// -----------------------------------------

#include "globals.hh"
class Interaction
{
private:
  G4int pID;

public:
  Interaction(){pID=-9999;}
  ~Interaction(){;}

  G4int GetProcessID(G4String proc, G4double prekene)
  {
    pID=-9999;
    if (proc=="")                               pID = PRIMARY;
    else if (proc=="Transportation")            pID = TRANSPORT;
    else if (proc=="Decay" && prekene==0)       pID = DECAY_REST;
    else if (proc=="Decay" && prekene!=0)       pID = DECAY_FLIGHT;

    else if (proc=="Ioni")                      pID = IONI;
    else if (proc=="hIoni")                     pID = H_IONI;
    else if (proc=="hLowEIoni")                 pID = H_IONI;
    else if (proc=="msc")                       pID = MSC;    
    else if (proc=="annihil")                   pID = ANNIHIL;
    else if (proc=="eIoni")                     pID = E_IONI;
    else if (proc=="muIoni")                    pID = MU_IONI;
    else if (proc=="eBrem")                     pID = E_BREM;
    else if (proc=="ionIoni")                   pID = ION_IONI;
    else if (proc=="muMsc")                     pID = MU_MSC;

    else if (proc=="phot")                      pID = LE_PHOTO_ELEC;
    else if (proc=="Rayl")                      pID = LE_RAY;
    else if (proc=="compt")                     pID = LE_COMP;
    else if (proc=="conv")                      pID = LE_CONV;
    
    else if (proc=="kaon+Inelastic")            pID = KAON_PLUS_INELA;
    else if (proc=="kaon-Inelastic")            pID = KAON_MINUS_INELA;
    else if (proc=="kaon0LInelastic")           pID = KAON_ZEROL_INELA;
    else if (proc=="pi+Inelastic")              pID = PION_PLUS_INELA;
    else if (proc=="pi-Inelastic")              pID = PION_MINUS_INELA;
    
    else if (proc=="KaonMinusAbsorption")       pID = KAON_MINUS_ATREST;
    else if (proc=="KaonMinusAbsorptionAtRest") pID = KAON_MINUS_ATREST;
    //else if (proc=="hBertiniCaptureAtRest")     pID = PION_MINUS_ATREST;
    else if (proc=="hBertiniCaptureAtRest")     pID = H_BERTINI_ATREST;

    else if (proc=="hadElastic")                pID = HADRON_ELASTIC;
    
    else if (proc=="protonInelastic")           pID = PROTON_INELA;
    else if (proc=="neutronInelastic")          pID = NEUTRON_INELA;
    else if (proc=="dInelastic")                pID = DEUTERON_INELA;
    else if (proc=="tInelastic")                pID = TRITON_INELA;
    else if (proc=="alphaInelastic")            pID = ALPHA_INELA;
    else if (proc=="He3Inelastic")              pID = HE3_INELA;
    else if (proc=="ionInelastic")              pID = ION_INELA;
    else if (proc=="lambdaInelastic")           pID = LAMBDA_INELASTIC;
    else if (proc=="sigmaPlusInelastic")        pID = SIGMA_PLUS_INELASTIC;
    else if (proc=="sigmaMinusInelastic")       pID = SIGMA_MINUS_INELASTIC;
    
    else if (proc=="muMinusCaptureAtRest")      pID = MU_MINUS_CAPTURE_ATREST;
    else if (proc=="nCapture")                  pID = N_CAPTURE;

    else if (proc=="RadioactiveDecay")          pID = RAD_DECAY;
    else if (proc=="photonNuclear")             pID = PHOTON_NUCLEAR;
    else if (proc=="CoulombScat")               pID = COULOMB_SCAT;
    else if (proc=="electronNuclear")           pID = ELECTRON_NUCLEAR;
    else if (proc=="positronNuclear")           pID = POSITRON_NUCLEAR;
    
    else if (proc=="nKiller")                   pID = NKILLER;

    else G4cout << " !!! unknown reaction : " << proc << G4endl;

    return pID;
  }
  
  void PrintStatus(G4int evid, G4String physname, G4int pdg, G4String pname,
                   G4double prekene, G4double edep, G4double stepl, 
                   G4String proc, G4int processID, G4String cproc, G4int cprocessID)
  {
    G4cout << "   SteppingAction   " << G4endl;
    G4cout << "   eventID:         " << evid << G4endl;;
    G4cout << "   next step :      " << physname << G4endl;
    G4cout << "   PDG code  =      " << pdg << " " << pname << G4endl;
    G4cout << "   prekene(eV) =    " << prekene/eV << G4endl;
    G4cout << "   edep(eV) =       " << edep/eV << G4endl;
    G4cout << "   stepl(nm) =      " << stepl/nm << G4endl;
    G4cout << "   process          " << proc << " " << processID << G4endl;
    G4cout << "   cprocess         " << cproc << " " << cprocessID << G4endl;
    G4cout << G4endl;
  }


  // precondition: the particle is secondary (vertex is in the volume)
  G4bool DeltaRayCheck(G4int cprocessID) {
    if ( cprocessID==IONI     || cprocessID==H_IONI  || cprocessID==MSC     || 
	 cprocessID==MU_MSC   || cprocessID==E_IONI  || cprocessID==MU_IONI || 
	 cprocessID==ION_IONI || cprocessID==LE_PHOTO_ELEC || cprocessID==LE_RAY ||
	 cprocessID==LE_COMP  || cprocessID==LE_CONV || cprocessID==LE_BREM || cprocessID==E_BREM ||
	 cprocessID==HADRON_ELASTIC
	 ) {
      return true;
    }  else {
      return false;
    }
  }

  // precondition: secandary and multi hit
  G4bool VertexPosCheck(G4ThreeVector vpos, G4ThreeVector lpos) {
    if ( (vpos.x()==lpos.x()) && (vpos.y()==lpos.y()) && (vpos.z()==lpos.z()) ) {
      return true;
    }  else {
      return false;
    }
    
  }

  // precondition: secandary and multi hit
  G4bool CreatorProcCheck(G4int cprocid, G4int lprocid) {
    if ( cprocid==lprocid ) {
      return true;
    }  else if (cprocid==11 && lprocid==10){
      return true;
    } else {
      return false;
    }
  }

  // precondition: secandary and multi hit
  G4bool IntCheck(G4int i, G4int j) {
    if ( i==j ) {
      return true;
    } else {
      return false;
    }
  }
  
};

#endif
