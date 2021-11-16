#include "BambooControl.hh"
#include "BambooGlobalVariables.hh"

#include <G4UImanager.hh>
#include <sstream>
#include <string>
#include <unistd.h>

G4int BambooControl::DETECTOR_TYPE = 0;
G4bool BambooControl::INTERACTIVE = false;
G4int BambooControl::NUM_EVENTS = 0;
G4String BambooControl::MacroFileName = "";
G4String BambooControl::DataFileName = "";
G4String BambooControl::XmlFileName = "";

BambooControl *BambooControl::theControl = 0;

BambooControl *BambooControl::getControl() {
    if (theControl == 0) {
        theControl = new BambooControl();
    }
    return theControl;
}

BambooControl::BambooControl() {}

BambooControl::~BambooControl() {}

void BambooControl::setup(int argc, char *argv[]) {
    double px = 0, py = 0, pz = 0, sigmaR = 0;
    int np = 1000;
    bool IsUniform = false;
    extern char *optarg;
    std::stringstream ss;
    while (true) {
        const int option = getopt(argc, argv, "f:m:n:o:x:i:X:Y:Z:S:N:U");
        if (option == -1)
            break;
        switch (option) {
        case 'f':
        case 'm':
            BambooControl::MacroFileName = optarg;
            break;
        case 'n':
            ss.clear();
            ss.str(optarg);
            ss >> BambooControl::NUM_EVENTS;
            break;
        case 'o':
            BambooControl::DataFileName = optarg;
            BambooGlobalVariables::Instance()->setOutDataName(optarg);
            break;
        case 'x':
            BambooControl::XmlFileName = optarg;
            if (!BambooGlobalVariables::Instance()->loadXMLFile(
                    BambooControl::XmlFileName))
                exit(1);
            break;
        case 'i':
            INTERACTIVE = true;
            break;
        case 'N':
            np          = (int)atoi(optarg);
            break;
        case 'X':
            px = (double)atoi(optarg);
            G4cout << "px: " << optarg << G4endl;
            break;
        case 'Y':
            py = (double)atoi(optarg);
            G4cout << "py: " << optarg << G4endl;
            break;
        case 'Z':
            G4cout << "pz: " << optarg << G4endl;
            pz = (double)atoi(optarg);
            break;
        case 'S':
            G4cout << "sigma for light source: " << optarg << G4endl;
            sigmaR = (double)atoi(optarg);
            break;
        case 'U':
            IsUniform   = true;
            break;
        }
    }
    BambooGlobalVariables::Instance()->setGLHLightSourcePos(px, py, pz);
    BambooGlobalVariables::Instance()->setGLHPhotonNumber(np);
    BambooGlobalVariables::Instance()->setGLHSigmaR(sigmaR);
    G4cout << "set px=" << px << ",py=" << py << ",sigmaR=" << sigmaR << G4endl;
    BambooGlobalVariables::Instance()->setGLHIsUniform(IsUniform);
    if(IsUniform) G4cout << "Uniform mode" << sigmaR << G4endl;

    if (XmlFileName.empty()) {
        G4cerr << "An XML file must be provided! Try '-x xml_file'." << G4endl;
        G4cout << "Usage: -x xmlFile -n RunNumber -o outputname -X xpos -Y ypos -S sigmaR(mm) -U IsUniform(true/false,default=false)" << G4endl;
        exit(1);
    }

    if (optind <= argc - 1) {
        G4cerr << optind << " vs " << argc - 1 << G4endl;
        G4cerr << "Unrecognized arguments!" << G4endl;
        exit(1);
    }
}
