#ifndef CALIB_SRC
#define CALIB_SRC 1

#include <stdio.h>
#include <stdlib.h>

#include "Randomize.hh"
#include "CommonXray.h"


// --- Fe55 ---
static const G4double FE55_MNKA1_INT = 0.169;
static const G4double FE55_MNKA2_INT = 0.085;
static const G4double FE55_MNKB_INT  = 0.0101+0.0198;


// --- Co57 ---
static const G4double CO57_FEKA1_INT = 0.326;
static const G4double CO57_FEKA2_INT = 0.164;
static const G4double CO57_FEKB_INT  = 0.0199+0.0388;
static const G4double CO57_GAMMA_1 = 14.41300*keV;
static const G4double CO57_GAMMA_2 = 122.0614*keV;
static const G4double CO57_GAMMA_3 = 136.4743*keV;
static const G4double CO57_GAMMA_1_INT = 0.0916;
static const G4double CO57_GAMMA_2_INT = 0.8560;
static const G4double CO57_GAMMA_3_INT = 0.1068;

// --- Cd109 ---
static const G4double CD109_GAMMA_1 = 88.04*keV;
static const G4double CD109_GAMMA_1_INT = 0.0361;
static const G4double CD109_AGKA1_INT = 0.557;
static const G4double CD109_AGKA2_INT = 0.295;
static const G4double CD109_AGKB1_INT = 0.092;
static const G4double CD109_AGKB2_INT = 0.0230;
static const G4double CD109_AGKB3_INT = 0.0476;

// --------------------------------------------------------------


// ---- Fe55 ----

inline G4double Fe55MnXray()
{
  G4double beam_mom = 0.;
  G4double rand = G4UniformRand();
  if (0 <= rand && rand <= FE55_MNKA1_INT)                                  beam_mom = MNKA1;
  else if (FE55_MNKA1_INT < rand && rand <= FE55_MNKA1_INT+FE55_MNKA2_INT)  beam_mom = MNKA2;
  else if (FE55_MNKA1_INT+FE55_MNKA2_INT < rand 
	   && rand <= FE55_MNKA1_INT+FE55_MNKA2_INT+FE55_MNKB_INT)          beam_mom = MNKB1;
  
  return beam_mom;
}



// ---- Co57 ----

inline G4double Co57FeXray()
{
  G4double beam_mom = 0.;
  G4double rand = G4UniformRand();
  if (0 <= rand && rand <= CO57_FEKA1_INT)                                  beam_mom = FEKA1;
  else if (CO57_FEKA1_INT < rand && rand <= CO57_FEKA1_INT+CO57_FEKA2_INT)  beam_mom = FEKA2;
  else if (CO57_FEKA1_INT+CO57_FEKA2_INT < rand 
	   && rand <= CO57_FEKA1_INT+CO57_FEKA2_INT+CO57_FEKB_INT)          beam_mom = FEKB1;
  
  return beam_mom;
}


inline G4double Co57Gamma2(G4double rand1)
{
  G4double beam_mom = 0.;
  if (0 <= rand1 && rand1 <= CO57_GAMMA_2_INT)  beam_mom = CO57_GAMMA_2;
  
  return beam_mom;
}



inline G4double Co57Gamma3(G4double rand1, G4double rand2)
{
  G4double beam_mom = 0.;
  if (rand1 > CO57_GAMMA_2_INT) {
    if (0 <= rand2 && rand2 <= CO57_GAMMA_3_INT)  beam_mom = CO57_GAMMA_3;
  }
  
  return beam_mom;
}



inline G4double Co57Gamma1(G4double rand1, G4double rand3)
{
  G4double beam_mom = 0.;
  if (rand1 > CO57_GAMMA_2_INT) {
    if (0 <= rand3 && rand3 <= CO57_GAMMA_1_INT)  beam_mom = CO57_GAMMA_1;
  }
  
  return beam_mom;
}




// ---- Cd109 ----

inline G4double Cd109Gamma1(G4double rand1)
{
  G4double beam_mom = 0.;
  if (0 <= rand1 && rand1 <= CD109_GAMMA_1_INT)  beam_mom = CD109_GAMMA_1;
  
  return beam_mom;
}

inline G4double Cd109AgXray()
{
  G4double beam_mom = 0.;
  G4double rand = G4UniformRand();
  if (0 <= rand && rand <= CD109_AGKA1_INT)                                    beam_mom = AGKA1;
  else if (CD109_AGKA1_INT < rand && rand <= CD109_AGKA1_INT+CD109_AGKA2_INT)  beam_mom = AGKA2;
  
  else if (CD109_AGKA1_INT+CD109_AGKA2_INT < rand 
	   && rand <= CD109_AGKA1_INT+CD109_AGKA2_INT+CD109_AGKB1_INT)         beam_mom = AGKB1;
  
  else if (CD109_AGKA1_INT+CD109_AGKA2_INT+CD109_AGKB1_INT < rand 
	   && rand <= CD109_AGKA1_INT+CD109_AGKA2_INT
	   +CD109_AGKB1_INT+CD109_AGKB2_INT)                                   beam_mom = AGKB2;
  
  else if (CD109_AGKA1_INT+CD109_AGKA2_INT+CD109_AGKB1_INT+CD109_AGKB2_INT < rand 
	   && rand <= CD109_AGKA1_INT+CD109_AGKA2_INT
	   +CD109_AGKB1_INT+CD109_AGKB2_INT+CD109_AGKB3_INT)                   beam_mom = AGKB3;
  
  return beam_mom;
}



// --------------------------------------------------------------



#endif
