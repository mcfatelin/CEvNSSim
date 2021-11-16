message("enable pandax_iiii")
set(source_path ${PROJECT_SOURCE_DIR}/detectors/pandax_iiii)
set(Detector ${Detector} ${source_path}/XenonDetector.cc)
set(Detector ${Detector} ${source_path}/Shield.cc)
set(Detector ${Detector} ${source_path}/PandaXMaterial.cc)
set(Detector ${Detector} ${source_path}/PandaXLab.cc)
set(Detector ${Detector} ${source_path}/Cryostat.cc)

