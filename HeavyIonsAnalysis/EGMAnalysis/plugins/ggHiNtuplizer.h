#ifndef HEAVYIONSANALYSIS_EGMANALYSIS_GGHINTUPLIZER_H
#define HEAVYIONSANALYSIS_EGMANALYSIS_GGHINTUPLIZER_H

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"

#include <TTree.h>

class ggHiNtuplizer : public edm::EDAnalyzer {
public:
  ggHiNtuplizer(const edm::ParameterSet&);
  ~ggHiNtuplizer() override;

private:
  void analyze(const edm::Event&, const edm::EventSetup&) override;

  void fillPileupInfo(const edm::Event&);
  void fillGenParticles(const edm::Event&);
  void fillElectrons(const edm::Event&, const edm::EventSetup&, reco::Vertex&);
  void fillPhotons(const edm::Event&, const edm::EventSetup&, reco::Vertex&);
  void fillMuons(const edm::Event&, const edm::EventSetup&, reco::Vertex&);

  // Et and pT sums
  float getGenCalIso(edm::Handle<std::vector<reco::GenParticle>>&,
                     reco::GenParticleCollection::const_iterator,
                     float dR2Max,
                     bool removeMu,
                     bool removeNu);
  float getGenTrkIso(edm::Handle<std::vector<reco::GenParticle>>&,
                     reco::GenParticleCollection::const_iterator,
                     float dR2Max);

  // switches
  bool doGenParticles_;
  bool doElectrons_;
  bool doPhotons_;
  bool doMuons_;

  bool isParticleGun_;

  // handles to collections of objects
  edm::EDGetTokenT<std::vector<PileupSummaryInfo>> pileupToken_;
  edm::EDGetTokenT<std::vector<reco::GenParticle>> genParticlesToken_;
  edm::EDGetTokenT<std::vector<reco::Vertex>> vertexToken_;
  edm::EDGetTokenT<double> rhoToken_;
  edm::EDGetTokenT<edm::View<reco::GsfElectron>> electronsToken_;
  edm::EDGetTokenT<edm::View<reco::Photon>> photonsToken_;
  edm::EDGetTokenT<edm::View<reco::Muon>> muonsToken_;
  edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
  edm::EDGetTokenT<reco::ConversionCollection> conversionsToken_;

  const TransientTrackBuilder* tb;

  TTree* tree_;

  UInt_t run_;
  ULong64_t event_;
  UInt_t lumis_;

  float rho_;

  // PileupSummaryInfo
  int nPUInfo_;
  std::vector<int> nPU_;
  std::vector<int> puBX_;
  std::vector<float> puTrue_;

  // reco::GenParticle
  int nMC_;

  std::vector<float> mcVtx_x_;
  std::vector<float> mcVtx_y_;
  std::vector<float> mcVtx_z_;

  std::vector<int> mcPID_;
  std::vector<int> mcStatus_;
  std::vector<float> mcPt_;
  std::vector<float> mcEta_;
  std::vector<float> mcPhi_;
  std::vector<float> mcE_;
  std::vector<float> mcEt_;
  std::vector<float> mcMass_;

  std::vector<int> mcParentage_;
  std::vector<int> mcMomPID_;
  std::vector<float> mcMomPt_;
  std::vector<float> mcMomEta_;
  std::vector<float> mcMomPhi_;
  std::vector<float> mcMomMass_;
  std::vector<int> mcGMomPID_;

  std::vector<int> mcIndex_;

  std::vector<float> mcCalIsoDR03_;
  std::vector<float> mcCalIsoDR04_;
  std::vector<float> mcTrkIsoDR03_;
  std::vector<float> mcTrkIsoDR04_;

  // electrons
  int nEle_;

  std::vector<float> eleD0_;
  std::vector<float> eleDz_;
  std::vector<float> eleD0Err_;
  std::vector<float> eleDzErr_;
  std::vector<float> eleTrkPt_;
  std::vector<float> eleTrkEta_;
  std::vector<float> eleTrkPhi_;
  std::vector<int> eleTrkCharge_;
  std::vector<float> eleTrkPtErr_;
  std::vector<float> eleTrkChi2_;
  std::vector<float> eleTrkNdof_;
  std::vector<float> eleTrkNormalizedChi2_;
  std::vector<int> eleTrkValidHits_;
  std::vector<int> eleTrkLayers_;
  std::vector<int> eleMissHits_;
  std::vector<float> eleIP3D_;
  std::vector<float> eleIP3DErr_;

  std::vector<float> elePt_;
  std::vector<float> eleEta_;
  std::vector<float> elePhi_;
  std::vector<int> eleCharge_;
  std::vector<float> eleEn_;

  std::vector<float> eleSCEn_;
  std::vector<float> eleESEn_;
  std::vector<float> eleSCEta_;
  std::vector<float> eleSCPhi_;
  std::vector<float> eleSCRawEn_;
  std::vector<float> eleSCEtaWidth_;
  std::vector<float> eleSCPhiWidth_;
  std::vector<int> eleSCClustersSize_;
  std::vector<float> eleSeedEn_;
  std::vector<float> eleSeedEta_;
  std::vector<float> eleSeedPhi_;

  std::vector<float> eleHoverE_;
  std::vector<float> eleHoverEBc_;
  std::vector<float> eleEoverP_;
  std::vector<float> eleEoverPInv_;
  std::vector<float> eleEcalE_;
  std::vector<float> elePAtVtx_;
  std::vector<float> elePAtSC_;
  std::vector<float> elePAtCluster_;
  std::vector<float> elePAtSeed_;
  std::vector<float> eledEtaAtVtx_;
  std::vector<float> eledPhiAtVtx_;
  std::vector<float> eledEtaSeedAtVtx_;
  std::vector<float> eleSigmaIEtaIEta_;
  std::vector<float> eleSigmaIPhiIPhi_;
  std::vector<float> eleBrem_;

  std::vector<int> eleConvVeto_;

  std::vector<float> eleR9_;
  std::vector<float> eleE3x3_;
  std::vector<float> eleE5x5_;
  std::vector<float> eleR9Full5x5_;
  std::vector<float> eleE3x3Full5x5_;
  std::vector<float> eleE5x5Full5x5_;
  std::vector<float> eleSigmaIEtaIEta_2012_;

  std::vector<float> elePFChIso_;
  std::vector<float> elePFPhoIso_;
  std::vector<float> elePFNeuIso_;
  std::vector<float> elePFPUIso_;

  std::vector<float> eleSeedCryEta_;
  std::vector<float> eleSeedCryPhi_;
  std::vector<float> eleSeedCryIeta_;
  std::vector<float> eleSeedCryIphi_;

  // photons
  int nPho_;

  std::vector<float> phoE_;
  std::vector<float> phoEt_;
  std::vector<float> phoEta_;
  std::vector<float> phoPhi_;

  std::vector<float> phoEcorrStdEcal_;
  std::vector<float> phoEcorrPhoEcal_;
  std::vector<float> phoEcorrRegr1_;
  std::vector<float> phoEcorrRegr2_;
  std::vector<float> phoEcorrErrStdEcal_;
  std::vector<float> phoEcorrErrPhoEcal_;
  std::vector<float> phoEcorrErrRegr1_;
  std::vector<float> phoEcorrErrRegr2_;

  std::vector<float> phoSCE_;
  std::vector<float> phoSCRawE_;
  std::vector<float> phoSCEta_;
  std::vector<float> phoSCPhi_;
  std::vector<float> phoSCEtaWidth_;
  std::vector<float> phoSCPhiWidth_;
  std::vector<float> phoSCBrem_;
  std::vector<int> phoSCnHits_;
  std::vector<uint32_t> phoSCflags_;
  std::vector<int> phoSCinClean_;
  std::vector<int> phoSCinUnClean_;
  std::vector<int> phoSCnBC_;
  std::vector<float> phoESEn_;

  std::vector<int> phoIsPFPhoton_;
  std::vector<int> phoIsStandardPhoton_;
  std::vector<int> phoHasPixelSeed_;
  std::vector<int> phoHasConversionTracks_;
  std::vector<float> phoHadTowerOverEm_;
  std::vector<float> phoHoverE_;
  std::vector<int> phoHoverEValid_;
  std::vector<float> phoSigmaIEtaIEta_;
  std::vector<float> phoR9_;
  std::vector<float> phoE1x5_;
  std::vector<float> phoE2x5_;
  std::vector<float> phoE3x3_;
  std::vector<float> phoE5x5_;
  std::vector<float> phoMaxEnergyXtal_;
  std::vector<float> phoSigmaEtaEta_;

  std::vector<float> phoSigmaIEtaIEta_2012_;
  std::vector<float> phoR9_2012_;
  std::vector<float> phoE1x5_2012_;
  std::vector<float> phoE2x5_2012_;
  std::vector<float> phoE3x3_2012_;
  std::vector<float> phoE5x5_2012_;
  std::vector<float> phoMaxEnergyXtal_2012_;
  std::vector<float> phoSigmaEtaEta_2012_;

  std::vector<float> phoBC1E_;
  std::vector<float> phoBC1Ecorr_;
  std::vector<float> phoBC1Eta_;
  std::vector<float> phoBC1Phi_;
  std::vector<int> phoBC1size_;
  std::vector<uint32_t> phoBC1flags_;
  std::vector<int> phoBC1inClean_;
  std::vector<int> phoBC1inUnClean_;
  std::vector<uint32_t> phoBC1rawID_;

  std::vector<int> pho_genMatchedIndex_;

  // muons
  int nMu_;

  std::vector<float> muPt_;
  std::vector<float> muEta_;
  std::vector<float> muPhi_;
  std::vector<int> muCharge_;
  std::vector<int> muType_;
  std::vector<int> muIsGood_;

  std::vector<float> muD0_;
  std::vector<float> muDz_;
  std::vector<float> muIP3D_;
  std::vector<float> muD0Err_;
  std::vector<float> muDzErr_;
  std::vector<float> muIP3DErr_;
  std::vector<float> muChi2NDF_;
  std::vector<float> muInnerD0_;
  std::vector<float> muInnerDz_;

  std::vector<float> muInnerD0Err_;
  std::vector<float> muInnerDzErr_;
  std::vector<float> muInnerPt_;
  std::vector<float> muInnerPtErr_;
  std::vector<float> muInnerEta_;

  std::vector<int> muTrkLayers_;
  std::vector<int> muPixelLayers_;
  std::vector<int> muPixelHits_;
  std::vector<int> muMuonHits_;
  std::vector<int> muTrkQuality_;
  std::vector<int> muStations_;
  std::vector<float> muIsoTrk_;
  std::vector<float> muPFChIso_;
  std::vector<float> muPFPhoIso_;
  std::vector<float> muPFNeuIso_;
  std::vector<float> muPFPUIso_;

  std::vector<int> muIDSoft_;
  std::vector<int> muIDLoose_;
  std::vector<int> muIDMedium_;
  std::vector<int> muIDMediumPrompt_;
  std::vector<int> muIDTight_;
  std::vector<int> muIDGlobalHighPt_;
  std::vector<int> muIDTrkHighPt_;
  std::vector<int> muIDInTime_;
};

#endif /* HEAVYIONSANALYSIS_EGMANALYSIS_GGHINTUPLIZER_H */
