#ifndef Materials_H
#define Materials_H 1

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"

class Materials
{
private:
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double n;  // number of nucleus
  G4double density;
  G4String symbol;				   
  G4int ncomponents, natoms;
  G4double abundance;
  G4double fractionmass;

public:
  // -- Elements--
  // H
  G4Element* elH  = new G4Element("Hydrogen",symbol="H", z=1., a=1.00794*g/mole);
  G4Isotope* h1   = new G4Isotope("h1", z=1., n=1., a=1.007825*g/mole);
  G4Element* elH1 = new G4Element("Hydrogen-1",symbol="H1", ncomponents=1);
  // D
  G4Element* elD  = new G4Element("Deuterium",symbol="D", z=1., a=2.01410177803*g/mole);
  G4Isotope* h2   = new G4Isotope("h2", z=1., n=2., a=2.01410177803*g/mole);
  G4Element* elH2 = new G4Element("Hydrogen-2",symbol="H2", ncomponents=1);
  // T
  G4Element* elT  = new G4Element("Tritium",symbol="T", z=1., a=3.0160492*g/mole);
  G4Isotope* h3 = new G4Isotope("h3", z=1., n=3., a=3.0160492*g/mole);
  G4Element* elH3 = new G4Element("Hydrogen-3",symbol="H3", ncomponents=1);
  // He3
  G4Isotope* he3  = new G4Isotope("he3", z=2., n=3., a=3.016029*g/mole);
  G4Element* elHe3 = new G4Element("Helium-3",symbol="He3", ncomponents=1);
  // He4
  G4Element* elHe = new G4Element("Helium",symbol="He", z=2., a=4.002602*g/mole);
  G4Isotope* he4 = new G4Isotope("he4", z=2., n=4., a=4.002602*g/mole);
  G4Element* elHe4 = new G4Element("Helium-4",symbol="He4", ncomponents=1);
  // Li6
  G4Element* elLi = new G4Element("Lithium",symbol="Li", z=3., a=6.941*g/mole);
  G4Isotope* li6 = new G4Isotope("li6", z=3., n=6., a=6.015122795*g/mole);
  G4Element* elLi6 = new G4Element("Lithium-6",symbol="Li6", ncomponents=1);
  // Li7
  G4Isotope* li7 = new G4Isotope("li7", z=3., n=7., a=7.01600455*g/mole);
  G4Element* elLi7 = new G4Element("Lithium-7",symbol="Li7", ncomponents=1);
  // others
  G4Element* elC  = new G4Element("Carbon",   symbol="C",  z=6.,  a=12.01*g/mole);
  G4Element* elN  = new G4Element("Nitrogen", symbol="N",  z=7.,  a=14.0067*g/mole);
  G4Element* elO  = new G4Element("Oxygen",   symbol="O",  z=8.,  a=16.00*g/mole);
  G4Element* elF  = new G4Element("Fluorine", symbol="F",  z=9.,  a=18.9984032*g/mole);
  G4Element* elNe = new G4Element("Neon",     symbol="Ne", z=10., a=20.1797*g/mole);
  G4Element* elSi = new G4Element("Silicon",  symbol="Si", z=14., a=28.09*g/mole);
  G4Element* elCl = new G4Element("Chlorine", symbol="Cl", z=17., a=35.45*g/mole);
  G4Element* elAr = new G4Element("Argon",    symbol="Ar", z=18., a=39.948*g/mole);
  G4Element* elCr = new G4Element("Chromium", symbol="Cr", z=24., a=51.996*g/mole);
  G4Element* elMn = new G4Element("Manganese",symbol="Mn", z=25., a=54.94*g/mole);
  G4Element* elFe = new G4Element("Iron",     symbol="Fe", z=26., a=55.85*g/mole);
  G4Element* elNi = new G4Element("Nickel",   symbol="Ni", z=28., a=58.70*g/mole);
  G4Element* elGa = new G4Element("Galium",   symbol="Ga", z=31., a=69.72*g/mole);
  G4Element* elAs = new G4Element("Arsenic",  symbol="As", z=33., a=74.92*g/mole);

  // -- Materials --
  // Vacuum
  G4Material* Vacuum = new G4Material("interGalactic",z=1.,a=1.008*g/mole,density=1.1e-25*g/cm3,kStateGas,2.73*kelvin,3.e-18*pascal);
  G4Material* Li = new G4Material("Lithium",  z=3.,  a=6.941*g/mole,      density=0.534*g/cm3);
  G4Material* Be = new G4Material("Beryllium",z=4.,  a=9.01*g/mole,       density=1.85 *g/cm3);
  G4Material* C  = new G4Material("Carbon",   z=6.,  a=12.01*g/mole,      density=2.00 *g/cm3);
  G4Material* Al = new G4Material("Aluminum", z=13., a=26.9815386*g/mole, density=2.699*g/cm3);
  G4Material* Si = new G4Material("Silicon",  z=14., a=28.09*g/mole,      density=2.330*g/cm3);
  G4Material* Ar = new G4Material("ArgonGas", z=18., a=39.948*g/mole,     density=0.001782*g/cm3);
  G4Material* Ti = new G4Material("Titanium", z=22., a=47.867*g/mole,     density=4.54 *g/cm3);
  G4Material* Cr = new G4Material("Chromium", z=24., a=51.996*g/mole,     density=7.19 *g/cm3);
  G4Material* Mn = new G4Material("Manganese",z=25., a=54.94*g/mole,      density=7.47 *g/cm3);
  G4Material* Fe = new G4Material("Iron",     z=26., a=55.85*g/mole,      density=7.87 *g/cm3);
  G4Material* Co = new G4Material("Cobalt",   z=27., a=58.93*g/mole,      density=8.82 *g/cm3);
  G4Material* Ni = new G4Material("Nickel",   z=28., a=58.69*g/mole,      density=8.90 *g/cm3);
  G4Material* Cu = new G4Material("Copper",   z=29., a=63.546*g/mole,     density=8.960*g/cm3);
  // there are two isotopes in natural 63Cu(69.15%) and 65Cu(30.85%).
  G4Material* Zn = new G4Material("Zinc",     z=30., a=65.37*g/mole,      density=7.13  *g/cm3);
  G4Material* Ga = new G4Material("Gallium",  z=31., a=69.72*g/mole,      density=5.91  *g/cm3);
  G4Material* Ge = new G4Material("Germanium",z=32., a=72.59*g/mole,      density=5.32  *g/cm3);
  G4Material* As = new G4Material("Arsenic",  z=33., a=74.92*g/mole,      density=5.78  *g/cm3);
  G4Material* Se = new G4Material("Selenium", z=34., a=78.96*g/mole,      density=4.81  *g/cm3);
  G4Material* Zr = new G4Material("Zirconium",z=40., a=91.22*g/mole,      density=6.51  *g/cm3);
  G4Material* Ag = new G4Material("Silver",   z=47., a=107.87*g/mole,     density=10.5  *g/cm3);
  G4Material* Sn = new G4Material("Tin",      z=50., a=118.69*g/mole,     density=7.29  *g/cm3);
  G4Material* W  = new G4Material("Tungsten", z=74., a=183.85*g/mole,     density=19.3  *g/cm3);
  G4Material* Au = new G4Material("Gold",     z=79., a=196.966570*g/mole, density=19.3  *g/cm3);
  G4Material* Pb = new G4Material("Lead",     z=82., a=207.2*g/mole,      density=11.350*g/cm3);
  G4Material* Bi = new G4Material("Bithmus",  z=83., a=208.98*g/mole,     density=9.80  *g/cm3);

  // H2 gas
  G4Material* H2Gas = new G4Material("HydrogenGas",density=0.01*g/cm3,ncomponents=1);
  // D2 gas
  G4Material* D2Gas = new G4Material("DeuteriumGas",density=0.01*g/cm3,ncomponents=1);
  // T gas
  G4Material* TGas = new G4Material("TritiumGas",density=0.01*g/cm3,ncomponents=1);
  // He3 gas
  G4Material* He3Gas = new G4Material("He3Gas",density=0.001*g/cm3,ncomponents=1);
  // He3 liquid
  // density must be checked !!!
  G4Material* LHe3 = new G4Material("LHelium-3",density=0.080*g/cm3,ncomponents=1);
  // He4 gas
  //density = 0.09*g/cm3;// calculation
  //density = 0.1786/1000.*10.*g/cm3;// 10 rho_STP 1.79 g/L
  //density = 0.1786/1000.*9.*g/cm3;// 9 rho_STP
  //density =0.1786/1000.*g/cm3;// 1 rho_STP
  G4Material* He4Gas = new G4Material("He4Gas",density=0.1786*mg/cm3,ncomponents=1);
  // He4 liquid
  // super-fluid !!!
  G4Material* LHe4 = new G4Material("LHelium-4",density=0.145*g/cm3,ncomponents=1);
  G4Material* LHe4SF = new G4Material("LHelium-4SF",density=0.145*g/cm3,ncomponents=1);
  // Li6
  G4Material* Li6 = new G4Material("Li6",density=0.534*g/cm3,ncomponents=1);
  // Li7
  G4Material* Li7 = new G4Material("Li7",density=0.534*g/cm3,ncomponents=1);
  // N2 gas
  G4Material* N2Gas = new G4Material("NitrogenGas",density=0.01*g/cm3,ncomponents=1);
  // Ne gas
  G4Material* NeGas = new G4Material("NeGas",density=0.9005*mg/cm3,ncomponents=1);
  G4Material* NeGas1atm = new G4Material("NeGas1atm",density=0.9005*mg/cm3,ncomponents=1);
  G4Material* NeGas05atm = new G4Material("NeGas05atm",density=0.45025*mg/cm3,ncomponents=1);
  G4Material* NeGas01atm = new G4Material("NeGas01atm",density=0.09005*mg/cm3,ncomponents=1);
  G4Material* NeGas100atm = new G4Material("NeGas100atm",density=0.9005*mg/cm3,ncomponents=1);
  G4Material* NeGas090atm = new G4Material("NeGas090atm",density=0.81045*mg/cm3,ncomponents=1);
  G4Material* NeGas075atm = new G4Material("NeGas075atm",density=0.675375*mg/cm3,ncomponents=1);
  G4Material* NeGas050atm = new G4Material("NeGas050atm",density=0.45025*mg/cm3,ncomponents=1);
  G4Material* NeGas040atm = new G4Material("NeGas040atm",density=0.3602*mg/cm3,ncomponents=1);
  G4Material* NeGas025atm = new G4Material("NeGas025atm",density=0.225125*mg/cm3,ncomponents=1);
  G4Material* NeGas010atm = new G4Material("NeGas010atm",density=0.09005*mg/cm3,ncomponents=1);
  G4Material* NeGas001atm = new G4Material("NeGas001atm",density=0.009005*mg/cm3,ncomponents=1);

  // Ar gas target
  G4Material* ArGas100atm = new G4Material("ArGas100atm",density=1.782*mg/cm3,ncomponents=1);
  G4Material* ArGas050atm = new G4Material("ArGas050atm",density=0.891*mg/cm3,ncomponents=1);
  G4Material* ArGas030atm = new G4Material("ArGas030atm",density=0.5346*mg/cm3,ncomponents=1);
  G4Material* ArGas010atm = new G4Material("ArGas010atm",density=0.1782*mg/cm3,ncomponents=1);
  
  // Plastic Scintillator
  G4Material* Scinti = new G4Material("Plastic",density=1.032*g/cm3,ncomponents=2);
  // CFRP
  G4Material* CFRP = new G4Material("CFRP",density=1.700*g/cm3,ncomponents=1);
  // Air
  G4Material* Air = new G4Material("Air",density=1.184*mg/cm3,ncomponents=2);
  G4Material* Air25C = new G4Material("Air25C",density=1.184*mg/cm3,ncomponents=2);
  G4Material* Air0C  = new G4Material("Air0C",density=1.290*mg/cm3,ncomponents=2);
  // SUS304
  G4Material* SUS = new G4Material("SUS", density=8.0*g/cm3, ncomponents=5);
  // ChamberGas
  G4Material* ChamberGas = new G4Material("ChamberGas",density=0.766*mg/cm3,ncomponents=3);
  // Water
  G4Material* Water = new G4Material("Water",density=1.00*g/cm3,ncomponents=2);
  // PET
  G4Material* PET = new G4Material("PET",density=1.39*g/cm3,ncomponents=3);
  G4Material* PETMit = new G4Material("PETMit",density=1.34*g/cm3,ncomponents=3);
  // Mylar
  G4Material* Mylar = new G4Material("Mylar", density=1.39*g/cm3, ncomponents=3);
  // Kapton
  G4Material* Kapton = new G4Material("Kapton", density=1.42*g/cm3, ncomponents=4);
  // paper
  G4Material* Paper = new G4Material("Paper",density=0.80*g/cm3,ncomponents=3);
  // Black tape
  // I don't know this materiall well
  G4Material* Scotch = new G4Material("Scotch",density=1.40*g/cm3,ncomponents=3);
  // Black tape
  // for K-mask 2008/12/04
  // density is 1.38 to 1.41 g/cm3 CH2=CH-Cl
  G4Material* BlackPVC = new G4Material("BlackPVC",density=1.40*g/cm3,ncomponents=3);
  // GaAs crystal
  G4Material* GaAs = new G4Material("GaAs", density=5.3176*g/cm3, ncomponents=2);


  
public:
  Materials()
  {
    elH1       -> AddIsotope(h1, abundance=100.*perCent);
    elH2       -> AddIsotope(h2, abundance=100.*perCent);
    elH3       -> AddIsotope(h3, abundance=100.*perCent);
    elHe3      -> AddIsotope(he3, abundance=100.*perCent);
    elHe4      -> AddIsotope(he4, abundance=100.*perCent);
    elLi6      -> AddIsotope(li6, abundance=100.*perCent);
    elLi7      -> AddIsotope(li7, abundance=100.*perCent);
                  
    H2Gas      -> AddElement(elH1, fractionmass=100.*perCent);
    D2Gas      -> AddElement(elH2, fractionmass=100.*perCent);
    TGas       -> AddElement(elH3, fractionmass=100.*perCent);
    He3Gas     -> AddElement(elHe3, fractionmass=100.*perCent);
    LHe3       -> AddElement(elHe3, fractionmass=100.*perCent);
    He4Gas     -> AddElement(elHe4, fractionmass=100.*perCent);
    LHe4       -> AddElement(elHe4, fractionmass=100.*perCent);
    Li6        -> AddElement(elLi6, fractionmass=100.*perCent);
    Li7        -> AddElement(elLi7, fractionmass=100.*perCent);
    N2Gas      -> AddElement(elN, fractionmass=100.*perCent);
    NeGas      -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas1atm  -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas05atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas01atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas100atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas090atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas075atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas050atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas040atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas025atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas010atm -> AddElement(elNe, fractionmass=100.*perCent);
    NeGas001atm -> AddElement(elNe, fractionmass=100.*perCent);
    ArGas100atm -> AddElement(elAr, fractionmass=100.*perCent);
    ArGas050atm -> AddElement(elAr, fractionmass=100.*perCent);
    ArGas030atm -> AddElement(elAr, fractionmass=100.*perCent);
    ArGas010atm -> AddElement(elAr, fractionmass=100.*perCent);

    Scinti->AddElement(elC, natoms=8);
    Scinti->AddElement(elH, natoms=8);

    CFRP->AddElement(elC, fractionmass=1.0);

    Air->AddElement(elN, fractionmass=0.75);
    Air->AddElement(elO, fractionmass=0.25);

    SUS->AddElement(elFe, natoms=6875);
    SUS->AddElement(elSi, natoms=75);
    SUS->AddElement(elMn, natoms=200);
    SUS->AddElement(elCr, natoms=1800);
    SUS->AddElement(elNi, natoms=105);

    ChamberGas->AddElement(elHe4, natoms=1);
    ChamberGas->AddElement(elC, natoms=2);
    ChamberGas->AddElement(elH, natoms=6);

    Water->AddElement(elH, natoms=2);
    Water->AddElement(elO, natoms=1);

    PET->AddElement(elC, natoms=10);
    PET->AddElement(elH, natoms= 8);
    PET->AddElement(elO, natoms= 4);

    Mylar->AddElement(elC, natoms=10);
    Mylar->AddElement(elH, natoms= 8);
    Mylar->AddElement(elO, natoms= 4);

    Kapton->AddElement(elC, natoms= 22);
    Kapton->AddElement(elH, natoms= 10);
    Kapton->AddElement(elO, natoms= 5);
    Kapton->AddElement(elN, natoms= 2);

    //Paper->AddElement(elC, natoms= 6);
    //Paper->AddElement(elH, natoms=10);
    //Paper->AddElement(elO, natoms= 5);
    Paper->AddElement(elC, natoms=10);
    Paper->AddElement(elH, natoms= 8);
    Paper->AddElement(elO, natoms= 4);

    Scotch->AddElement(elC, natoms=10);
    Scotch->AddElement(elH, natoms= 8);
    Scotch->AddElement(elO, natoms= 4);
    
    BlackPVC->AddElement(elC,  natoms=2);
    BlackPVC->AddElement(elH,  natoms=3);
    BlackPVC->AddElement(elCl, natoms=1);
    
    GaAs->AddElement(elGa, fractionmass=0.482);
    GaAs->AddElement(elAs, fractionmass=0.518);

    //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
  }
  ~Materials(){;}
};


#endif
