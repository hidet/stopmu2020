#ifndef CommonXray_h
#define CommonXray_h 1

#include "G4SystemOfUnits.hh"

//using namespace CLHEP;

// see kaon and pion absorption at rest
const G4double max_xray_photonene = 40.0*keV;

// c.f. XrayDataBooklet

//Intensity of K_alpha and K_beta
static const G4double INTTIKA1 = 100.0;
static const G4double INTTIKA2 = 50.0;
static const G4double INTTIKB1 = 15.0;

static const G4double INTMNKA1 = 100.0;
static const G4double INTMNKA2 = 50.0;
static const G4double INTMNKB1 = 17.0;

static const G4double INTFEKA1 = 100.0;
static const G4double INTFEKA2 = 51.0;
static const G4double INTFEKB1 = 17.0;

static const G4double INTNIKA1 = 100.0;
static const G4double INTNIKA2 = 51.0;
static const G4double INTNIKB1 = 17.0;

static const G4double INTCUKA1 = 100.0;
static const G4double INTCUKA2 = 51.0;
static const G4double INTCUKB1 = 17.0;

static const G4double INTZRKA1 = 100.0;
static const G4double INTZRKA2 = 52.0;
static const G4double INTZRKB1 = 23.0;//(Kb1+Kb3)

static const G4double INTAGKA1 = 100.0;
static const G4double INTAGKA2 = 53.0;

// Energy
// Unit = [eV]
// Al
static const G4double ALKA = 1486.70*eV;
static const G4double ALKB = 1557.45*eV;
// Si
static const G4double SIKA = 1739.98*eV;
// Ti
static const G4double TIKA1 = 4510.84*eV;
static const G4double TIKA2 = 4504.86*eV;
static const G4double TIKA = TIKA1*INTTIKA1/(INTTIKA1+INTTIKA2)+TIKA2*INTTIKA2/(INTTIKA1+INTTIKA2);
static const G4double TIKB1 = 4931.81*eV;
// Cr
static const G4double CRKA = 5414.72*eV;
// Mn
static const G4double MNKA1 = 5898.75*eV;
static const G4double MNKA2 = 5887.65*eV;
static const G4double MNKA = MNKA1*INTMNKA1/(INTMNKA1+INTMNKA2)+MNKA2*INTMNKA2/(INTMNKA1+INTMNKA2);
static const G4double MNKB1 = 6490.45*eV;
// Fe
static const G4double FEKA1 = 6403.84*eV;
static const G4double FEKA2 = 6390.84*eV;
static const G4double FEKA = FEKA1*INTFEKA1/(INTFEKA1+INTFEKA2)+FEKA2*INTFEKA2/(INTFEKA1+INTFEKA2);
static const G4double FEKB1 = 7057.98*eV;
// Ni
static const G4double NIKA1 = 7478.15*eV;
static const G4double NIKA2 = 7460.89*eV;
static const G4double NIKA = NIKA1*INTNIKA1/(INTNIKA1+INTNIKA2)+NIKA2*INTNIKA2/(INTNIKA1+INTNIKA2);
static const G4double NIKB1 = 8264.66*eV;
// Cu
static const G4double CUKA1 = 8047.78*eV;
static const G4double CUKA2 = 8027.83*eV;
static const G4double CUKA = CUKA1*INTCUKA1/(INTCUKA1+INTCUKA2)+CUKA2*INTCUKA2/(INTCUKA1+INTCUKA2);
static const G4double CUKB1 = 8905.29*eV;
// Zr
static const G4double ZRKA1 = 15775.1*eV;
static const G4double ZRKA2 = 15600.9*eV;
static const G4double ZRKA = ZRKA1*INTZRKA1/(INTZRKA1+INTZRKA2)+ZRKA2*INTZRKA2/(INTZRKA1+INTZRKA2);
static const G4double ZRKB1 = 17667.8*eV;
// Ag
static const G4double AGKA1 = 21990.3*eV;
static const G4double AGKA2 = 22162.9*eV;
static const G4double AGKB1 = 24942.4*eV;
static const G4double AGKB2 = 25456.4*eV;
static const G4double AGKB3 = 24911.5*eV;


///////////////////////////////////////////////
// K4HeX
static const G4double KHEXLA =  6464.0*eV;
static const G4double KHEXLB =  8721.7*eV;
static const G4double KHEXLG =  9768.0*eV;
static const G4double KHEXLD = 10331.0*eV;

//KpX
static const G4double KPXKA = 6479.7*eV;
static const G4double KPXKB = 7676.6*eV;
static const G4double KPXKG = 8095.5*eV;
static const G4double KPXKD = 8289.4*eV;
static const G4double KPXKE = 8394.7*eV;

// KpX
static const G4int    NKPX   =  8;
static const G4double KPSHIFT1S = 283*eV;
static const G4double KPWIDTH1S = 541*eV;
static const G4double KP2TO1 = 6481.2*eV;
static const G4double KP3TO1 = 7678.0*eV;
static const G4double KP4TO1 = 8096.8*eV;
static const G4double KP5TO1 = 8290.6*eV;
static const G4double KP6TO1 = 8395.9*eV;
static const G4double KP7TO1 = 8459.4*eV;
static const G4double KP8TO1 = 8500.6*eV;
static const G4double KP9TO1 = 8528.9*eV;
static const G4double KPXRAYS[NKPX] = {KP2TO1,KP3TO1,KP4TO1,KP5TO1,
				       KP6TO1,KP7TO1,KP8TO1,KP9TO1};

// KdX
static const G4int    NKDX   =  8;
static const G4double KDSHIFT1S = 500*eV;
static const G4double KDWIDTH1S = 1000*eV;
static const G4double KD2TO1 = 7834.0*eV;
static const G4double KD3TO1 = 9280.2*eV;
static const G4double KD4TO1 = 9786.2*eV;
static const G4double KD5TO1 = 10020.4*eV;
static const G4double KD6TO1 = 10147.6*eV;
static const G4double KD7TO1 = 10224.3*eV;
static const G4double KD8TO1 = 10274.1*eV;
static const G4double KD9TO1 = 10308.2*eV;
static const G4double KDXRAYS[NKDX] = {KD2TO1,KD3TO1,KD4TO1,KD5TO1,
				       KD6TO1,KD7TO1,KD8TO1,KD9TO1};

// K4HeX
static const G4int    NK4HEX    =  8;
static const G4double K4HESHIFT2P = 0*eV;
static const G4double K4HEWIDTH2P = 2*eV;
static const G4double K4HE3TO2  =  6463.3*eV;
static const G4double K4HE4TO2  =  8721.6*eV;
static const G4double K4HE5TO2  =  9766.6*eV;
static const G4double K4HE6TO2  = 10334.3*eV;
static const G4double K4HE7TO2  = 10676.5*eV;
static const G4double K4HE8TO2  = 10898.7*eV;
static const G4double K4HE9TO2  = 11050.9*eV;
static const G4double K4HE10TO2 = 11159.9*eV;
static const G4double K4HEXRAYS[NK4HEX] = {K4HE3TO2,K4HE4TO2,K4HE5TO2,K4HE6TO2,
					   K4HE7TO2,K4HE8TO2,K4HE9TO2,K4HE10TO2};

// K3HeX
static const G4int    NK3HEX    =  8;
static const G4double K3HESHIFT2P = 0*eV;
static const G4double K3HEWIDTH2P = 2*eV;
static const G4double K3HE3TO2  =  6224.6*eV;
static const G4double K3HE4TO2  =  8399.5*eV;
static const G4double K3HE5TO2  =  9406.0*eV;
static const G4double K3HE6TO2  =  9952.7*eV;
static const G4double K3HE7TO2  =  10282.3*eV;
static const G4double K3HE8TO2  =  10496.3*eV;
static const G4double K3HE9TO2  =  10642.9*eV;
static const G4double K3HE10TO2 =  10747.9*eV;
static const G4double K3HEXRAYS[NK3HEX] = {K3HE3TO2,K3HE4TO2,K3HE5TO2,K3HE6TO2,
					   K3HE7TO2,K3HE8TO2,K3HE9TO2,K3HE10TO2};

//KCX
static const G4int    NKCX    =  5;
static const G4double KCSHIFT =  0*eV;
static const G4double KCWIDTH =  2*eV;
static const G4double KC5TO4  =  10216.5*eV;
static const G4double KC6TO5  =  5544.9*eV;
static const G4double KC7TO5  =  8885.5*eV;
static const G4double KC6TO4  =  15759.4*eV;
static const G4double KC8TO6  =  5509.6*eV;
static const G4double KCXRAYS[NKCX] = {KC5TO4,KC6TO5,KC7TO5,KC6TO4,KC8TO6};

//KNX
static const G4int    NKNX    =  3;
static const G4double KNSHIFT =  0*eV;
static const G4double KNWIDTH =  2*eV;
static const G4double KN5TO4  = 13995.9*eV;
static const G4double KN6TO5  =  7595.4*eV;
static const G4double KN7TO6  =  4577.1*eV;
//static const G4double KNXRAYS[NKNX] = {KN7TO6,KN6TO5,KN5TO4};
static const G4double KNXRAYS[NKNX] = {KN5TO4,KN6TO5,KN7TO6};

// KO
static const G4int    NKOX    =  4;
static const G4double KOSHIFT =  0*eV;
static const G4double KOWIDTH =  2*eV;
static const G4double KO6TO5  =  9968.7*eV;
static const G4double KO7TO6  =  6006.8*eV;
static const G4double KO7TO5  =  15973.3*eV;
static const G4double KO8TO6  =  9902.7*eV;
static const G4double KOXRAYS[NKOX] = {KO6TO5,KO7TO6,KO7TO5,KO8TO6};

// KF
static const G4int    NKFX    =  3;
static const G4double KFSHIFT =  0*eV;
static const G4double KFWIDTH =  2*eV;
static const G4double KF6TO5  =  12684.5*eV;
static const G4double KF7TO6  =  7642.7*eV;
static const G4double KF8TO7  =  4958.0*eV;
static const G4double KFXRAYS[NKFX] = {KF6TO5,KF7TO6,KF8TO7};

// KAL
static const G4int    NKALX     =  4;
static const G4double KALSHIFT  =  0*eV;
static const G4double KALWIDTH  =  2*eV;
static const G4double KAL8TO7   =  10435.1*eV;
static const G4double KAL9TO8   =  7150.9*eV;
static const G4double KAL10TO9  =  5113.4*eV;
static const G4double KAL7TO6   =  16088.3*eV;
static const G4double KALXRAYS[NKALX] = {KAL8TO7,KAL9TO8,KAL10TO9,KAL7TO6};

// KSI
static const G4int    NKSIX     =  3;
static const G4double KSISHIFT  =  0*eV;
static const G4double KSIWIDTH  =  2*eV;
static const G4double KSI8TO7   =  12112.4*eV;
static const G4double KSI9TO8   =  8300.1*eV;
static const G4double KSI10TO9  =  5935.0*eV;
static const G4double KSIXRAYS[NKSIX] = {KSI8TO7,KSI9TO8,KSI10TO9};


// KTI
static const G4int    NKTIX     =  5;
static const G4double KTISHIFT  =  0*eV;
static const G4double KTIWIDTH  =  2*eV;
static const G4double KTI10TO9  =  14782.5*eV;
static const G4double KTI11TO10 =  10932.9*eV;
static const G4double KTI12TO11 =  8312.8*eV;
static const G4double KTI13TO12 =  6467.9*eV;
static const G4double KTI14TO13 =  5131.2*eV;
static const G4double KTIXRAYS[NKTIX] = {KTI10TO9,KTI11TO10,KTI12TO11,KTI13TO12,KTI14TO13};




// Ratio ---------->>>
static const G4double RTIKA1 = INTTIKA1/(INTTIKA1 + INTTIKA2 + INTTIKB1);
static const G4double RTIKA2 = INTTIKA2/(INTTIKA1 + INTTIKA2 + INTTIKB1);
static const G4double RTIKB1 = INTTIKB1/(INTTIKA1 + INTTIKA2 + INTTIKB1);

static const G4double RFEKA1 = INTFEKA1/(INTFEKA1 + INTFEKA2 + INTFEKB1);
static const G4double RFEKA2 = INTFEKA2/(INTFEKA1 + INTFEKA2 + INTFEKB1);
static const G4double RFEKB1 = INTFEKB1/(INTFEKA1 + INTFEKA2 + INTFEKB1);

static const G4double RMNKA1 = INTMNKA1/(INTMNKA1 + INTMNKA2 + INTMNKB1);
static const G4double RMNKA2 = INTMNKA2/(INTMNKA1 + INTMNKA2 + INTMNKB1);
static const G4double RMNKB1 = INTMNKB1/(INTMNKA1 + INTMNKA2 + INTMNKB1);

static const G4double RNIKA1 = INTNIKA1/(INTNIKA1 + INTNIKA2 + INTNIKB1);
static const G4double RNIKA2 = INTNIKA2/(INTNIKA1 + INTNIKA2 + INTNIKB1);
static const G4double RNIKB1 = INTNIKB1/(INTNIKA1 + INTNIKA2 + INTNIKB1);

static const G4double RCUKA1 = INTCUKA1/(INTCUKA1 + INTCUKA2 + INTCUKB1);
static const G4double RCUKA2 = INTCUKA2/(INTCUKA1 + INTCUKA2 + INTCUKB1);
static const G4double RCUKB1 = INTCUKB1/(INTCUKA1 + INTCUKA2 + INTCUKB1);

static const G4double RZRKA1 = INTZRKA1/(INTZRKA1 + INTZRKA2 + INTZRKB1);
static const G4double RZRKA2 = INTZRKA2/(INTZRKA1 + INTZRKA2 + INTZRKB1);
static const G4double RZRKB1 = INTZRKB1/(INTZRKA1 + INTZRKA2 + INTZRKB1);



// PIpX
static const G4int    NPIPX   =  5;
static const G4double PIPSHIFT1S = 7.1*eV;
static const G4double PIPWIDTH1S = 0.85*eV;
static const G4double PIP2TO1 = 2426.42*eV;
static const G4double PIP3TO1 = 2875.72*eV;
static const G4double PIP4TO1 = 3032.98*eV;
static const G4double PIP5TO1 = 3105.76*eV;
static const G4double PIP6TO1 = 3145.30*eV;
static const G4double PIPXRAYS[NPIPX] = {PIP2TO1,PIP3TO1,PIP4TO1,PIP5TO1,PIP6TO1};

// PIdX
static const G4int    NPIDX   =  5;
static const G4double PIDSHIFT1S = -2.4*eV;
static const G4double PIDWIDTH1S =  1.0*eV;
static const G4double PID2TO1 = 2594.30*eV;
static const G4double PID3TO1 = 3077.95*eV;
static const G4double PID4TO1 = 3242.83*eV;
static const G4double PID5TO1 = 3320.65*eV;
static const G4double PID6TO1 = 3362.93*eV;
static const G4double PIDXRAYS[NPIDX] = {PID2TO1,PID3TO1,PID4TO1,PID5TO1,PID6TO1};

// PI3HeX
static const G4int    NPI3HEX    =  5;
static const G4double PI3HESHIFT1S = 32.*eV;
static const G4double PI3HEWIDTH1S = 30.*eV;
static const G4double PI3HE2TO1  =  10624.29*eV;
static const G4double PI3HE3TO1  =  12591.17*eV;
static const G4double PI3HE4TO1  =  13598.18*eV;
static const G4double PI3HE5TO1  =  13771.26*eV;
static const G4double PI3HE6TO1  =  13875.62*eV;
static const G4double PI3HEXRAYS[NPI3HEX] = {PI3HE2TO1,PI3HE3TO1,PI3HE4TO1,PI3HE5TO1,PI3HE6TO1};


// PI4HeX
static const G4int    NPI4HEX    =  5;
static const G4double PI4HESHIFT1S = -75.*eV;
static const G4double PI4HEWIDTH1S = 45*eV;
static const G4double PI4HE2TO1  =  10749.77*eV;
static const G4double PI4HE3TO1  =  12739.88*eV;
static const G4double PI4HE4TO1  =  13436.40*eV;
static const G4double PI4HE5TO1  =  13758.78*eV;
static const G4double PI4HE6TO1  =  13933.91*eV;
static const G4double PI4HEXRAYS[NPI4HEX] = {PI4HE2TO1,PI4HE3TO1,PI4HE4TO1,PI4HE5TO1,PI4HE6TO1};

//PICX
static const G4int    NPICX    =  4;
static const G4double PICSHIFT =  0*eV;
static const G4double PICWIDTH =  0*eV;
static const G4double PIC3TO2  =  18359.38*eV;
static const G4double PIC4TO3  =   6424.06*eV;
static const G4double PIC5TO3  =   9397.25*eV;
static const G4double PIC6TO3  =  11012.27*eV;
static const G4double PICXRAYS[NPICX] = {PIC3TO2,PIC4TO3,PIC5TO3,PIC6TO3};

//PINX
static const G4int    NPINX    =  4;
static const G4double PINSHIFT =  0*eV;
static const G4double PINWIDTH =  0*eV;
static const G4double PIN4TO3  =  8759.82*eV;
static const G4double PIN5TO3  = 12813.94*eV;
static const G4double PIN6TO3  = 15016.08*eV;
static const G4double PIN5TO4  =  4054.12*eV;
static const G4double PINXRAYS[NPINX] = {PIN4TO3,PIN5TO3,PIN6TO3,PIN5TO4};

// PIO
static const G4int    NPIOX    =  5;
static const G4double PIOSHIFT =  0*eV;
static const G4double PIOWIDTH =  0*eV;
static const G4double PIO4TO3  = 11457.26*eV;
static const G4double PIO5TO3  = 16759.61*eV;
static const G4double PIO5TO4  =  5302.35*eV;
static const G4double PIO6TO4  =  8182.47*eV;
static const G4double PIO7TO4  =  9919.04*eV;
static const G4double PIOXRAYS[NPIOX] = {PIO4TO3,PIO5TO3,PIO5TO4,PIO6TO4,PIO7TO4};




#endif
