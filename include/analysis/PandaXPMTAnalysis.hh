#ifndef PANDAXPMTANALYSIS_H
#define PANDAXPMTANALYSIS_H

#include "analysis/BambooAnalysis.hh"
#include "analysis/PandaXPMTDM.hh"

#include "analysis/BambooAnalysisFactory.hh"

#include <memory>

using std::shared_ptr;

class PandaXPMTAnalysis : public BambooAnalysis {
public:
    PandaXPMTAnalysis(const G4String &name);

    ~PandaXPMTAnalysis();

    static AnalysisRegister<PandaXPMTAnalysis> reg;

private:
    shared_ptr<PandaXPMTDM> dm;
};

#endif // PANDAXPMTANALYSIS_H
