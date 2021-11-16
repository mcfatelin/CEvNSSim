#ifndef PANDAXMATERIAL_H
#define PANDAXMATERIAL_H

#include "detector/BambooMaterial.hh"
#include "detector/BambooMaterialFactory.hh"

class G4OpticalSurface;

class PandaXMaterial : public BambooMaterial
{

public:

  PandaXMaterial(const G4String &name);

  virtual void defineMaterials();

  static MaterialRegister<PandaXMaterial> reg;
  
private:

  static const G4double c_abs_len_gxe;
  static const G4double c_abs_len_gxe_mesh;
  
  static const G4double c_abs_len_lxe;
  static const G4double c_abs_len_lxe_mesh;
  static const G4double c_abs_len_lxe_grid;
};


#endif // PANDAXMATERIAL_H

