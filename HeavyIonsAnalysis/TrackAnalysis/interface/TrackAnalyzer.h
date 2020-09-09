#ifndef TRKANALYZER_H
#define TRKANALYZER_H

// system include files
#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>

// CMSSW user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Candidate/interface/LeafCandidate.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticle.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingParticleFwd.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

// Particle Flow
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

//Gen info
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"

// Vertex significance
#include "RecoBTag/SecondaryVertex/interface/SecondaryVertex.h"

// Root include files
#include "TTree.h"

class TrackAnalyzer : public edm::EDAnalyzer {

  public:
    explicit TrackAnalyzer(const edm::ParameterSet&);
    ~TrackAnalyzer() override;

  private:
    void beginJob() override;
    void analyze(const edm::Event&, const edm::EventSetup&) override;
    void endJob() override;

    void fillVertices(const edm::Event& iEvent);
    void fillJets2(const edm::Event& iEvent);
    void fillGen(const edm::Event& iEvent);
    void fillTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup);
    void clearVectors();

     // ----------member data ---------------------------
     bool doTrack_;
     double trackPtMin_; 

     edm::InputTag vertexSrcLabel_;
     edm::EDGetTokenT<reco::VertexCollection> vertexSrc_;

     edm::InputTag packedCandLabel_;
     edm::EDGetTokenT<edm::View<pat::PackedCandidate>> packedCandSrc_;
     //edm::EDGetTokenT<pat::PackedCandidateCollection> packedCandSrc_;
     
     edm::InputTag lostTracksLabel_;
     edm::EDGetTokenT<edm::View<pat::PackedCandidate>> lostTracksSrc_;
     //edm::EDGetTokenT<pat::PackedCandidateCollection> lostTracksSrc_;

     edm::EDGetTokenT<reco::BeamSpot> beamSpotProducer_;

     //edm::InputTag jets1_;
     //edm::EDGetTokenT<pat::JetCollection> jets1Token_;
     edm::InputTag jets2_;
     edm::EDGetTokenT<pat::JetCollection> jets2Token_;
     //edm::InputTag jets3_;
     //edm::EDGetTokenT<pat::JetCollection> jets3Token_;
     //edm::InputTag jets4_;
     //edm::EDGetTokenT<pat::JetCollection> jets4Token_;

     edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
     edm::EDGetTokenT< std::vector<reco::GenJet> > packedGenJetToken_;

     edm::EDGetTokenT< GenEventInfoProduct > genEvtInfo_;

     edm::EDGetTokenT<pat::PackedCandidateCollection> pfToken_;

     edm::InputTag chi2MapLabel_;
     edm::EDGetTokenT<edm::ValueMap<float>> chi2Map_;
     edm::InputTag chi2MapLostLabel_;
     edm::EDGetTokenT<edm::ValueMap<float>> chi2MapLost_;

     edm::Service<TFileService> fs;
 
     // Root object
     TTree* trackTree_;
     //TTree* jetTree_;

     bool doGen;

     //Branch entries
     int nRun;
     int nEv;
     int nLumi;
     std::vector< float > xVtx;
     std::vector< float > yVtx;
     std::vector< float > zVtx;
     std::vector< float > xErrVtx;
     std::vector< float > yErrVtx;
     std::vector< float > zErrVtx;
     std::vector< float > chi2Vtx;
     std::vector< float > ndofVtx;
     std::vector< bool > isFakeVtx;
     std::vector< int > nTracksVtx;
     std::vector< float > ptSumVtx;

     std::vector< float > trkPt;
     std::vector< float > trkPtError;
     std::vector< float > trkEta;
     std::vector< float > trkPhi;
     std::vector< char > trkCharge;
     std::vector< int > trkPDGId;
     std::vector< char > trkNHits;
     std::vector< char > trkNLostHits;
     std::vector< char > trkNPixHits;
     std::vector< char > trkNLayers;
     std::vector< bool > highPurity;
     std::vector< float > trkNormChi2;

     std::vector< int > trkAssociatedVtxIndx;
     std::vector< int > trkAssociatedVtxQuality;
     std::vector< float > trkDzAssociatedVtx;
     std::vector< float > trkDzErrAssociatedVtx;
     std::vector< float > trkDxyAssociatedVtx;
     std::vector< float > trkDxyErrAssociatedVtx;
     
     std::vector< int > trkFirstVtxQuality;
     std::vector< float > trkDzFirstVtx;
     std::vector< float > trkDzErrFirstVtx;
     std::vector< float > trkDxyFirstVtx;
     std::vector< float > trkDxyErrFirstVtx;

     std::vector< float > jetEta;
     std::vector< float > dau_pt_sum;
     std::vector< float > jetPt;
     std::vector< float > jetPhi;
     std::vector< float > jetTheta;
     std::vector< float > jetMass;
     std::vector< int   > jetNumDaughters;
     std::vector< int   > muonMultiplicity;
     std::vector< int   > chargedMultiplicity;
     int jetN;

     float genQScale;
     float genWeight;
     int   genSignalProcessID;

     std::vector< float > genJetEta;
     std::vector< float > genJetPt;
     std::vector< float > genJetPhi;
     std::vector< int > genJetChargedMultiplicity;

     std::vector<std::vector<int>>		dau_chg;
     std::vector<std::vector<int>>	        dau_pid;
     std::vector<std::vector<unsigned int>>	dau_vref;
     std::vector<std::vector<float>>		dau_pt;
     std::vector<std::vector<float>>		dau_eta;
     std::vector<std::vector<float>>		dau_phi;
     std::vector<std::vector<float>>      	dau_theta;
     std::vector<std::vector<float>>		dau_vz;
     std::vector<std::vector<float>>		dau_vy;
     std::vector<std::vector<float>>		dau_vx;
     std::vector<std::vector<float>>		dau_vrefz;
     std::vector<std::vector<float>>		dau_vrefy;
     std::vector<std::vector<float>>		dau_vrefx;
     std::vector<std::vector<float>>		dau_vp_difZ;
     std::vector<std::vector<float>>		dau_vp_difY;
     std::vector<std::vector<float>>		dau_vp_difX;

     
     std::vector<std::vector<int>>		gendau_chg;
     std::vector<std::vector<int>>	        gendau_pid;
     std::vector<std::vector<float>>		gendau_pt;
     std::vector<std::vector<float>>		gendau_eta;
     std::vector<std::vector<float>>		gendau_phi;
};

void TrackAnalyzer::clearVectors(){
  xVtx.clear();
  yVtx.clear();
  zVtx.clear();
  xErrVtx.clear();
  yErrVtx.clear();
  zErrVtx.clear();
  chi2Vtx.clear();
  ndofVtx.clear();
  isFakeVtx.clear();
  nTracksVtx.clear();
  ptSumVtx.clear();

  trkPt.clear();
  trkPtError.clear();
  trkEta.clear();
  trkPhi.clear();
  trkCharge.clear();
  trkPDGId.clear();
  trkNHits.clear();
  trkNPixHits.clear();
  trkNLayers.clear();
  trkNormChi2.clear();
  highPurity.clear();

  trkAssociatedVtxIndx.clear();
  trkAssociatedVtxQuality.clear();
  trkDzAssociatedVtx.clear();
  trkDzErrAssociatedVtx.clear();
  trkDxyAssociatedVtx.clear();
  trkDxyErrAssociatedVtx.clear();
  
  trkFirstVtxQuality.clear();
  trkDzFirstVtx.clear();
  trkDzErrFirstVtx.clear();
  trkDxyFirstVtx.clear();
  trkDxyErrFirstVtx.clear();
 
  jetEta.clear();
  jetPt.clear();
  jetPhi.clear();
  jetTheta.clear();
  jetMass.clear();
  jetNumDaughters.clear();
  chargedMultiplicity.clear();
  muonMultiplicity.clear();

dau_chg.clear();
dau_pid.clear();
dau_vref.clear();
dau_pt.clear();
dau_eta.clear();
dau_phi.clear();
dau_theta.clear();
dau_vz.clear();
dau_vy.clear();
dau_vx.clear();
dau_vrefz.clear();
dau_vrefy.clear();
dau_vrefx.clear();
dau_vp_difZ.clear();
dau_vp_difY.clear();
dau_vp_difX.clear();

dau_pt_sum.clear();
//jetN.clear();
  genQScale = -1;
  genWeight = -1;
  genSignalProcessID = -1;

  genJetEta.clear();
  genJetPhi.clear();
  genJetPt.clear();
  genJetChargedMultiplicity.clear();

  gendau_chg.clear();
  gendau_pid.clear();
  gendau_pt.clear();
  gendau_eta.clear();
  gendau_phi.clear();
}

#endif 
