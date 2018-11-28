#include "DataFormats/Math/interface/deltaPhi.h"

#include "HeavyIonsAnalysis/PhotonAnalysis/src/pfIsoCalculator.h"

pfIsoCalculator::pfIsoCalculator(const edm::Event &iEvent,
                                 const edm::EDGetTokenT<edm::View<reco::PFCandidate> > pfCandidates_,
                                 const math::XYZPoint& pv)
{
  iEvent.getByToken(pfCandidates_, candidatesView);

  vtx_ = pv;
}

double pfIsoCalculator::getPfIso(const reco::Photon& photon, int pfId,
                                 double r1, double r2, double threshold,
                                 double jWidth)
{
  double photonEta = photon.eta();
  double photonPhi = photon.phi();
  double totalEt = 0;

  for (const auto& pf : *candidatesView) {
    if ( pf.particleId() != pfId )   continue;
    double pfEta = pf.eta();
    double pfPhi = pf.phi();

    double dEta = std::abs(photonEta - pfEta);
    double dPhi = reco::deltaPhi(pfPhi, photonPhi);
    double dR2 = dEta*dEta + dPhi*dPhi;
    double pfPt = pf.pt();

    // remove the photon itself
    if ( pf.superClusterRef() == photon.superCluster() ) continue;

    if(pf.particleId() == reco::PFCandidate::h){
      float dz = std::abs(pf.vz() - vtx_.z());
      if (dz > 0.2) continue;
      double dxy = ((vtx_.x() - pf.vx())*pf.py() + (pf.vy() - vtx_.y())*pf.px()) / pf.pt();
      if (std::abs(dxy) > 0.1) continue;
    }

    // Jurassic Cone /////
    if (dR2 > r1 *r1) continue;
    if (dR2 < r2 * r2) continue;
    if (std::abs(dEta) < jWidth)  continue;
    if (pfPt < threshold) continue;
    totalEt += pfPt;
  }

  return totalEt;
}

double pfIsoCalculator::getPfIso(const reco::GsfElectron& ele, int pfId,
                                 double r1, double r2, double threshold)
{
  double eleEta = ele.eta();
  double elePhi = ele.phi();
  double totalEt = 0.;

  for (const auto& pf : *candidatesView) {
    if ( pf.particleId() != pfId )   continue;
    double pfEta = pf.eta();
    double pfPhi = pf.phi();

    double dEta = std::abs(eleEta - pfEta);
    double dPhi = reco::deltaPhi(pfPhi, elePhi);
    double dR2 = dEta*dEta + dPhi*dPhi;
    double pfPt = pf.pt();

    // remove electron itself
    if (pf.particleId() == reco::PFCandidate::e) continue;

    if (pf.particleId() == reco::PFCandidate::h) {
      float dz = std::abs(pf.vz() - vtx_.z());
      if (dz > 0.2) continue;
      double dxy = ((vtx_.x() - pf.vx())*pf.py() + (pf.vy() - vtx_.y())*pf.px()) / pf.pt();
      if (std::abs(dxy) > 0.1) continue;
    }

    // inside the cone size
    if (dR2 > r1 * r1) continue;
    if (dR2 < r2 * r2) continue;
    if (pfPt < threshold) continue;
    totalEt += pfPt;

  }

  return totalEt;
}
