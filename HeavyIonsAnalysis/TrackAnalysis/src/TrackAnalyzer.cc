#include "HeavyIonsAnalysis/TrackAnalysis/interface/TrackAnalyzer.h"

TrackAnalyzer::TrackAnalyzer(const edm::ParameterSet& iConfig)
{
  doTrack_ = iConfig.getUntrackedParameter<bool>("doTrack",true);

  trackPtMin_ = iConfig.getUntrackedParameter<double>("trackPtMin",0.01);

  vertexSrcLabel_ = iConfig.getParameter<edm::InputTag>("vertexSrc");
  vertexSrc_ = consumes<reco::VertexCollection>(vertexSrcLabel_);

  packedCandLabel_ = iConfig.getParameter<edm::InputTag>("packedCandSrc");
  packedCandSrc_ = consumes<pat::PackedCandidateCollection>(packedCandLabel_);
  
  beamSpotProducer_ = consumes<reco::BeamSpot>(iConfig.getUntrackedParameter<edm::InputTag>("beamSpotSrc",edm::InputTag("offlineBeamSpot")));
}

//--------------------------------------------------------------------------------------------------
TrackAnalyzer::~TrackAnalyzer()
{
}

//--------------------------------------------------------------------------------------------------
void TrackAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  nEv = (int)iEvent.id().event();
  nRun = (int)iEvent.id().run();
  nLumi = (int)iEvent.luminosityBlock();

  clearVectors();

  fillVertices(iEvent);

  if(doTrack_) fillTracks(iEvent, iSetup);
  
  trackTree_->Fill();
}

//--------------------------------------------------------------------------------------------------
void TrackAnalyzer::fillVertices(const edm::Event& iEvent) {
  // Fill reconstructed vertices.
  const reco::VertexCollection* recoVertices;
  edm::Handle<reco::VertexCollection> vertexCollection;
  iEvent.getByToken(vertexSrc_,vertexCollection);
  recoVertices = vertexCollection.product();

  unsigned int nVertex = recoVertices->size();
  for (unsigned int i = 0; i < nVertex; ++i) {
    xVtx.push_back( recoVertices->at(i).position().x() );
    yVtx.push_back( recoVertices->at(i).position().y() );
    zVtx.push_back( recoVertices->at(i).position().z() );
    xErrVtx.push_back( recoVertices->at(i).xError() );
    yErrVtx.push_back( recoVertices->at(i).yError() );
    zErrVtx.push_back( recoVertices->at(i).zError() );
  
    chi2Vtx.push_back( recoVertices->at(i).chi2() );
    ndofVtx.push_back( recoVertices->at(i).ndof() );

    isFakeVtx.push_back( recoVertices->at(i).isFake() );

    //number of tracks having a weight in vtx fit above 0.5
    nTracksVtx.push_back( recoVertices->at(i).nTracks() );

    float ptSum = 0;
    for( auto ref = recoVertices->at(i).tracks_begin(); ref != recoVertices->at(i).tracks_end(); ref++){
      ptSum += (*ref)->pt();
    }
    ptSumVtx.push_back( ptSum );
  }   
}

//--------------------------------------------------------------------------------------------------
void
TrackAnalyzer::fillTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<std::vector<pat::PackedCandidate>> cands;
  iEvent.getByToken(packedCandSrc_,cands);
  for(unsigned it = 0; it<cands->size(); ++it){
    const pat::PackedCandidate & c = (*cands)[it];

    if(!c.hasTrackDetails()) continue;

    reco::Track t = c.pseudoTrack();
    trkPt.push_back( t.pt() );
    trkPtError.push_back( t.ptError() );
    trkEta.push_back( t.eta() );
    trkPhi.push_back( t.phi() );
    trkCharge.push_back( (char) t.charge() );
    trkPDGId.push_back( c.pdgId() );
    trkNHits.push_back( (char) t.numberOfValidHits() );
    trkNPixHits.push_back( (char) t.hitPattern().numberOfValidPixelHits() );
    trkNLayers.push_back( (char) t.hitPattern().trackerLayersWithMeasurement() );
    highPurity.push_back( t.quality(reco::TrackBase::qualityByName("highPurity")));
  }
}


// ------------ method called once each job just before starting event loop  ------------
void TrackAnalyzer::beginJob()
{
  trackTree_ = fs->make<TTree>("trackTree","v1");

  // event
  trackTree_->Branch("nRun",&nRun,"nRun/I");
  trackTree_->Branch("nEv",&nEv,"nRun/I");
  trackTree_->Branch("nLumi",&nLumi,"nLumi/I");

  // vertex
  trackTree_->Branch("xVtx",&xVtx);
  trackTree_->Branch("yVtx",&yVtx);
  trackTree_->Branch("zVtx",&zVtx);
  trackTree_->Branch("xErrVtx",&xErrVtx);
  trackTree_->Branch("yErrVtx",&yErrVtx);
  trackTree_->Branch("zErrVtx",&zErrVtx);
  trackTree_->Branch("chi2Vtx",&chi2Vtx);
  trackTree_->Branch("ndofVtx",&ndofVtx);
  trackTree_->Branch("isFakeVtx",&isFakeVtx);
  trackTree_->Branch("nTracksVtx",&nTracksVtx);
  trackTree_->Branch("ptSumVtx",&ptSumVtx);

  // Tracks
  trackTree_->Branch("trkPt",&trkPt);
  trackTree_->Branch("trkPtError",&trkPtError);
  trackTree_->Branch("trkEta",&trkEta);
  trackTree_->Branch("trkPhi",&trkPhi);
  trackTree_->Branch("trkCharge",&trkCharge);
  trackTree_->Branch("trkPDFId",&trkPDGId);
  trackTree_->Branch("trkNHits",&trkNHits);
  trackTree_->Branch("trkNPixHits",&trkNPixHits);
  trackTree_->Branch("trkNLayers",&trkNLayers);
  trackTree_->Branch("highPurity",&highPurity);
}

// ------------ method called once each job just after ending the event loop  ------------
void
TrackAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackAnalyzer);
