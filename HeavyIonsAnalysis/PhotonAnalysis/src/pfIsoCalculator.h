#ifndef pfIsoCalculator_h
#define pfIsoCalculator_h

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

class pfIsoCalculator
{
  public:
    pfIsoCalculator(const edm::Event &iEvent, const edm::EDGetTokenT<edm::View<reco::PFCandidate> > pfCandidates, const math::XYZPoint& pv);

    double getPfIso(const reco::Photon& photon,  int pfId, double r1=0.4, double r2=0.00, double threshold=0, double jWidth=0.0);
    double getPfIso(const reco::GsfElectron& ele, int pfId, double r1=0.4, double r2=0.00, double threshold=0);

  private:
    edm::Handle<edm::View<reco::PFCandidate> > candidatesView;
    reco::Vertex::Point vtx_;
};

#endif
