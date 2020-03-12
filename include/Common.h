#ifndef Common_h
#define Common_h 1

#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include "TString.h"

static const G4String SAVEDIR=Form("./geant_data");

// --- acceptance mode ---                                               
//#define ACCEPTANCE        
//#define TARGETUNIFORM_GEANTINO
//#define TARGETUNIFORM

// ------ Number of Detectors ----
const G4int NbOfTES   = 256;
const G4int NbOfDEG   = 1;// SDD
const G4int NbOfTG    = 1;

// ---------- Max Multiplicity -----------
const G4int BeamMultiMax   = 1;
const G4int TESMultiMax    = 5;
const G4int TGMultiMax     = 10;
const G4int DEGMultiMax    = 5;// SDD

//const G4double air_add  = 120*mm;
//const G4double air_add  = (352.-200.-3.9-16.0)*mm;
const G4double air_add  = 12.0*mm;
//const G4double adr_posx = 70.*mm;
const G4double adr_posx = 60.*mm;

// -- Detector Construction --
// World (Vacuum)
const G4double world_size[3] = {10.0*m,10.0*m,10.0*m};
// Air
const G4double air_z    = 3.0*mm + air_add;
const G4double air_rmin = 0.0*mm;
const G4double air_rmax = 110.0*mm/2.;
const G4double air_pos[3]={0., 0., air_z/2.};
// accelerator window (Kapton)
const G4double aw_z    = 0.100*mm;//  100 um
//const G4double aw_z    = 0.075*mm;//  75 um
//const G4double aw_z    = 0.050*mm;//  50 um
const G4double aw_rmin = 0.0*mm;
const G4double aw_rmax = 110.0*mm/2.;
const G4double aw_pos[3]={0., 0., -0.1*mm};
// beam window (Kapton)
const G4double bw_z    = 0.100*mm;// 100 um
const G4double bw_rmin = 0.0*mm;
const G4double bw_rmax = 110.0*mm/2.;
const G4double bw_pos[3]={0., 0., air_pos[2]+air_z/2.+bw_z/2.};
// target (Ne gas)
const G4double target_z    = 702.8*mm;// 16.-3.+3.9+400+3.9+282
const G4double target_rmin = 0.0*mm;
const G4double target_rmax = 134.2*mm/2.;
const G4double target_pos[3]={0., 0., target_z/2.+bw_pos[2]+bw_z/2.};
// target side (SUS)
const G4double targetside1_z    = 159.75*mm;// 16.-3.+3.9+200.-114.3/2.
const G4double targetside1_rmin = 134.2*mm/2.;
const G4double targetside1_rmax = 139.8*mm/2.;
const G4double targetside1_pos[3]={0., 0., targetside1_z/2.+bw_pos[2]+bw_z/2.};
// target side (SUS)
const G4double targetside2_z    = 428.75*mm;//200.+3.9+282.-114.3/2.*mm
const G4double targetside2_rmin = 134.2*mm/2.;
const G4double targetside2_rmax = 139.8*mm/2.;
const G4double targetside2_pos[3]={0., 0., air_add+16.+3.9+200.+114.3/2.+targetside2_z/2.};
// target side (SUS)
const G4double targetside3_z    = 114.3*mm;
const G4double targetside3_rmin = 134.2*mm/2.;
const G4double targetside3_rmax = 139.8*mm/2.;
const G4double targetside3_pos[3]={0., 0., air_add+16.+3.9+200.*mm};
// target end (SUS)
const G4double targetend_z    = 2.0*mm;
const G4double targetend_rmin = 0.;
const G4double targetend_rmax = 139.8*mm/2.;
const G4double targetend_pos[3]={0., 0., target_pos[2]+target_z/2.+targetend_z/2.};
// 300K vacuum snout (SUS)
const G4double snout300k_rmin = 40.*mm/2.;
const G4double snout300k_rmax = 101.6*mm/2.;
const G4double snout300k_z    = 2.*mm;
const G4double snout300kwnd_rmin = 0.*mm;
const G4double snout300kwnd_rmax = 40.*mm/2.;
const G4double snout300kwnd_z    = 0.3*mm;// 300um
const G4double snout300kside_rmin = 97.4*mm/2.;
const G4double snout300kside_rmax = 101.6*mm/2.;
const G4double snout300kside_z    = 113.3*mm;
const G4double snout300k_pos[3]={adr_posx,0.,air_add+16.+3.9+200.*mm};
const G4double snout300kwnd_pos[3]={snout300k_pos[0],snout300k_pos[1],snout300k_pos[2]};
const G4double snout300kside_pos[3]={snout300k_pos[0]+snout300k_z/2.+snout300kside_z/2.,snout300k_pos[1],snout300k_pos[2]};
// 60K snout
const G4double snout60kwnd_rmin = 0.*mm;
const G4double snout60kwnd_rmax = 17.5*mm/2.;
const G4double snout60k_rmin = snout60kwnd_rmax;
const G4double snout60k_rmax = 85.*mm/2.;
const G4double snout60k_z    = 1.*mm;
//const G4double snout60kwnd_rmax = 30.*mm/2.;
//const G4double snout60kwnd_z    = 0.040*mm;// Mylar 10um x4
const G4double snout60kwnd_z    = 0.005*mm;// Al 5um
const G4double snout60k_pos[3]={snout300k_pos[0]+10.5,snout300k_pos[1],snout300k_pos[2]};
const G4double snout60kwnd_pos[3]={snout60k_pos[0],snout60k_pos[1],snout60k_pos[2]};
// 3K snout
const G4double snout3kwnd_rmin = 0.*mm;
const G4double snout3kwnd_rmax = 17.5*mm/2.;
const G4double snout3k_rmin = snout3kwnd_rmax;
const G4double snout3k_rmax = 70.*mm/2.;
const G4double snout3k_z    = 1.*mm;
//const G4double snout3kwnd_rmax = 25.*mm/2.;
//const G4double snout3kwnd_z    = 0.025*mm;// Be 25 um
const G4double snout3kwnd_z    = 0.005*mm;// Al 5 um
const G4double snout3k_pos[3]={snout300k_pos[0]+13.5,snout300k_pos[1],snout300k_pos[2]};
const G4double snout3kwnd_pos[3]={snout3k_pos[0],snout3k_pos[1],snout3k_pos[2]};
// 50mK snout
const G4double snoutwnd_rmin = 0.*mm;
const G4double snoutwnd_rmax = 22*mm/2.;
const G4double snout_rmin = snoutwnd_rmax;
const G4double snout_rmax = 50.*mm/2.;
const G4double snout_z    = 1.*mm;
//const G4double snoutwnd_z    = 0.025*mm;// Be 25 um
const G4double snoutwnd_z    = 0.005*mm;// Al 5 um
const G4double snout_pos[3]={snout300k_pos[0]+17.5,snout300k_pos[1],snout300k_pos[2]};
const G4double snoutwnd_pos[3]={snout_pos[0],snout_pos[1],snout_pos[2]};
// TES Bi
//const G4double calo_size[3] = {0.320*mm,0.300*mm,0.004*mm};
//const G4double calo_size[3] = {0.320*mm,0.305*mm,0.0041*mm};// <- original collimator
const G4double calo_size[3] = {0.305*mm,0.290*mm,0.0041*mm};// with realistic gold coated collimator
const G4double calo_pos_c[3]={snout300k_pos[0]+20.5,snout300k_pos[1],snout300k_pos[2]};
// SDD Si
const G4double sdd_size[3] = {10.*mm,10.*mm,0.400*mm};
//const G4double sdd_pos[3] = {-70.*mm-10.*mm,0.*mm,snout300k_pos[2]};
const G4double sdd_pos[3] = {-70.*mm-25.*mm,0.*mm,snout300k_pos[2]};
// SDD window Be
const G4double sddwnd_rmin = 0.*mm;
const G4double sddwnd_rmax = 10*mm/2.;
const G4double sddwnd_z    = 0.125*mm;// Be 125 um
const G4double sddwnd_pos[3]={-70.*mm,0.*mm,snout300k_pos[2]};
// SDD window SUS
const G4double sddwndsus_rmin = 10*mm/2.;
const G4double sddwndsus_rmax = 90*mm/2.;
const G4double sddwndsus_z    = 3.*mm;// SUS
const G4double sddwndsus_pos[3]={-70.*mm,0.*mm,snout300k_pos[2]};

// TES collimator (Au 15um? x2 = 30um)
const G4double coli2_size[3] = {10.*mm,10.*mm,0.030*mm};
const G4double coli2_pos[3]={calo_pos_c[0]-calo_size[2]/2.-coli2_size[2]/2.-0.010*mm,snout300k_pos[1],snout300k_pos[2]};
// TES collimator (Si 50um)
const G4double coli1_size[3] = {10.*mm,10.*mm,0.050*mm};
const G4double coli1_pos[3]={coli2_pos[0]-coli2_size[2]/2.-coli1_size[2]/2.,snout300k_pos[1],snout300k_pos[2]};

#endif
