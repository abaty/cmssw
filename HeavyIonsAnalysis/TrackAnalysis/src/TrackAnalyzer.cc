#include "HeavyIonsAnalysis/TrackAnalysis/interface/TrackAnalyzer.h"
#include <iostream>
#include <iomanip>
//#include "FWCore/Framework/interface/Event.h"

TrackAnalyzer::TrackAnalyzer(const edm::ParameterSet& iConfig)
{
  doTrack_ = iConfig.getUntrackedParameter<bool>("doTrack",true);

  trackPtMin_ = iConfig.getUntrackedParameter<double>("trackPtMin",0.01);

  vertexSrcLabel_ = iConfig.getParameter<edm::InputTag>("vertexSrc");
  vertexSrc_ = consumes<reco::VertexCollection>(vertexSrcLabel_);

  packedCandLabel_ = iConfig.getParameter<edm::InputTag>("packedCandSrc");
  packedCandSrc_ = consumes<edm::View<pat::PackedCandidate>>(packedCandLabel_);
  
  lostTracksLabel_ = iConfig.getParameter<edm::InputTag>("lostTracksSrc");
  lostTracksSrc_ = consumes<edm::View<pat::PackedCandidate>>(lostTracksLabel_);
  
  beamSpotProducer_ = consumes<reco::BeamSpot>(iConfig.getUntrackedParameter<edm::InputTag>("beamSpotSrc",edm::InputTag("offlineBeamSpot")));

  //jets1Token_      = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets1"));
  jets2Token_      = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets2"));
  //jets3Token_      = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets3"));
  //jets4Token_      = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets4"));
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

  //fillJets1(iEvent);
  fillJets2(iEvent);
  //fillJets3(iEvent);
  //fillJets4(iEvent);

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
    //chi2Vtx.push_back( recoVertices->at(i).chi2() );
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
void TrackAnalyzer::fillJets2(const edm::Event& iEvent) {
  edm::Handle<pat::JetCollection> jets2;
  iEvent.getByToken(jets2Token_, jets2);

  const reco::VertexCollection* recoVertices;
  edm::Handle<reco::VertexCollection> vertexCollection;
  iEvent.getByToken(vertexSrc_,vertexCollection);
  recoVertices = vertexCollection.product();

  edm::Handle<edm::View<pat::PackedCandidate>> cands;
  iEvent.getByToken(packedCandSrc_,cands);

    int passer = 0;
    // Let's compute the fraction of charged pt from particles with dz < 0.1 cm
    for (const pat::Jet &j :  *jets2) {
        if (j.pt() < 100 || fabs(j.eta()) > 2.4) continue;

	jetPt.push_back(j.pt());
        jetEta.push_back(j.eta());
	jetPhi.push_back(j.phi());
        jetTheta.push_back(j.theta());
        jetMass.push_back(j.mass());
        jetNumDaughters.push_back(j.numberOfDaughters());
	chargedMultiplicity.push_back(j.chargedMultiplicity());
	muonMultiplicity.push_back(j.muonMultiplicity());

	std::vector<int>		vcharge;
	std::vector<int>	        vpid;
        std::vector<unsigned int>	vVertRef;
	std::vector<float>		vpt;
        std::vector<float>		veta;
        std::vector<float>		vphi;
        std::vector<float>              vtheta;
        std::vector<float>		vdauVZ;
        std::vector<float>		vdauVY;
        std::vector<float>		vdauVX;
        std::vector<float>		vdauVrefZ;
        std::vector<float>		vdauVrefY;
        std::vector<float>		vdauVrefX;
        std::vector<float>		vp_difZ;
        std::vector<float>		vp_difY;
        std::vector<float>		vp_difX;

	float Ndau_pt_sum = 0;

        for( unsigned int dID=0; dID < j.numberOfDaughters();  dID++){
		const pat::PackedCandidate &dau = dynamic_cast<const pat::PackedCandidate &>(*j.daughter(dID));
		
		vcharge.push_back(	dau.charge());
		vpid.push_back(		dau.pdgId());
		vpt.push_back(		dau.pt());
		veta.push_back(		dau.eta());
		vphi.push_back(		dau.phi());
                vtheta.push_back(       dau.theta());

		Ndau_pt_sum = Ndau_pt_sum + dau.pt();

		float dauVZ    = dau.vertex().z();
		float dauVrefZ = recoVertices->at(dau.vertexRef().key()).position().z();
		float dauVY    = dau.vertex().y();
		float dauVrefY = recoVertices->at(dau.vertexRef().key()).position().y();
		float dauVX    = dau.vertex().x();
		float dauVrefX = recoVertices->at(dau.vertexRef().key()).position().x();
		float V_percent_difZ = 100 * fabs(fabs(dauVrefZ/dauVZ) - 1);
                float V_percent_difY = 100 * fabs(fabs(dauVrefY/dauVY) - 1);
                float V_percent_difX = 100 * fabs(fabs(dauVrefX/dauVX) - 1);
		vVertRef.push_back(  	dau.vertexRef().key());
		vdauVZ.push_back(	dauVZ);
                vdauVY.push_back(       dauVY);
                vdauVX.push_back(       dauVX);
                vdauVrefZ.push_back(    dauVrefZ);
                vdauVrefZ.push_back(    dauVrefY);
                vdauVrefZ.push_back(    dauVrefX);
                vp_difZ.push_back(    	V_percent_difZ);
                vp_difY.push_back(      V_percent_difY);
                vp_difX.push_back(      V_percent_difX);
	}
        dau_pt_sum.push_back(   Ndau_pt_sum);

	dau_chg.push_back(	vcharge);
	dau_pid.push_back(      vpid);
	dau_vref.push_back(     vVertRef);
	dau_pt.push_back(       vpt);
	dau_eta.push_back(      veta);
	dau_phi.push_back(      vphi);
	dau_theta.push_back(    vtheta);
	dau_vz.push_back(       vdauVZ);
        dau_vy.push_back(       vdauVY);
        dau_vx.push_back(       vdauVX);
	dau_vrefz.push_back(    vdauVrefZ);
        dau_vrefy.push_back(    vdauVrefY);
        dau_vrefx.push_back(    vdauVrefX);
	dau_vp_difZ.push_back(  vp_difZ);
        dau_vp_difY.push_back(  vp_difY);
        dau_vp_difX.push_back(  vp_difX);

	passer = passer +1;
		//if(dau.charge()  ==0 ) continue;
        	//const edm::Ref<std::vector<reco::Vertex> > JetVRef = dau.vertexRef().key();
        	//int JetVRef_int = dau.vertexRef().key();
		//int fromPV = dau.fromPV(dau.vertexRef().key() );
		//std::cout << j.pt() <<"  "<<  JetVRef_int << "  " << fromPV << std::endl;

		//float dauVRef = recoVertices->at(dau.vertexRef().key()).position().z();
		//float dauV    = dau.vertex().z();
		//std::cout << std::setprecision(4)<< std::endl;
		//std::cout << j.pt() << " " << Ndau_pt_sum << std::endl;

    }
    jetN = passer;


}

//--------------------------------------------------------------------------------------------------
void TrackAnalyzer::fillTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
  edm::Handle<edm::View<pat::PackedCandidate>> cands;
 // edm::Handle<edm::ValueMap<float>> chi2Map;
  
  //loop over packed cands, then loop over lost tracks
  for(int i = 0; i<2; i++){

    if(i==0){
      iEvent.getByToken(packedCandSrc_,cands);
   //   iEvent.getByToken(chi2Map_,chi2Map);
    }
    if(i==1){
      iEvent.getByToken(lostTracksSrc_,cands);
     // iEvent.getByToken(chi2MapLost_,chi2Map);
    }

    for(unsigned it = 0; it<cands->size(); ++it){
      const pat::PackedCandidate & c = (*cands)[it];

      if(!c.hasTrackDetails()) continue;

      reco::Track const& t = c.pseudoTrack();

      if(t.pt() < trackPtMin_) continue;

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
     // trkNormChi2.push_back( (*chi2Map)[cands->ptrAt(it)] );

      //DCA info for associated vtx
      trkAssociatedVtxIndx.push_back( c.vertexRef().key() );
      trkAssociatedVtxQuality.push_back( c.fromPV(c.vertexRef().key() ));
      trkDzAssociatedVtx.push_back( c.dz( c.vertexRef()->position() ) );
      trkDzErrAssociatedVtx.push_back( sqrt( c.dzError()*c.dzError() + c.vertexRef()->zError() * c.vertexRef()->zError() ) );
      trkDxyAssociatedVtx.push_back( c.dxy( c.vertexRef()->position() ) );
      trkDxyErrAssociatedVtx.push_back( sqrt( c.dxyError()*c.dxyError() + c.vertexRef()->xError() * c.vertexRef()->yError() ) );
   
      //DCA info for first (highest pt) vtx
      if( !xVtx.empty() ){
        math::XYZPoint v(xVtx.at(0),yVtx.at(0), zVtx.at(0));   
        trkFirstVtxQuality.push_back( c.fromPV( 0 ));
        trkDzFirstVtx.push_back( c.dz( v ) );
        trkDzErrFirstVtx.push_back( sqrt( c.dzError()*c.dzError() + zErrVtx.at(0) * zErrVtx.at(0) ) );
        trkDxyFirstVtx.push_back( c.dxy( v ) );
        trkDxyErrFirstVtx.push_back( sqrt( c.dxyError()*c.dxyError() + xErrVtx.at(0) * yErrVtx.at(0) ) );
      }
    }
  }
}


// ------------ method called once each job just before starting event loop  ------------
void TrackAnalyzer::beginJob()
{
  trackTree_ = fs->make<TTree>("trackTree","v1");
  //jetTree_ = fs->make<TTree>("jetTree","v1");

  // event
  trackTree_->Branch("nRun",&nRun,"nRun/I");
  trackTree_->Branch("nEv",&nEv,"nRun/I");
  trackTree_->Branch("nLumi",&nLumi,"nLumi/I");

  // vertex
  trackTree_->Branch("xVtx",&xVtx);
  trackTree_->Branch("nTracksVtx",&nTracksVtx);
  trackTree_->Branch("ptSumVtx",&ptSumVtx);

  // Tracks
  trackTree_->Branch("trkPt",&trkPt);
  trackTree_->Branch("trkEta",&trkEta);
  trackTree_->Branch("trkPhi",&trkPhi);
  trackTree_->Branch("trkCharge",&trkCharge);
  trackTree_->Branch("trkPDFId",&trkPDGId);
  trackTree_->Branch("trkNHits",&trkNHits);
  trackTree_->Branch("highPurity",&highPurity);
  trackTree_->Branch("trkAssociatedVtxIndx",&trkAssociatedVtxIndx);
  
  // Jets
  trackTree_->Branch("jetNumDaughters",&jetNumDaughters);
  trackTree_->Branch("jetEta",&jetEta);
  trackTree_->Branch("jetPt",&jetPt);
  trackTree_->Branch("jetPhi",&jetPhi);
  trackTree_->Branch("jetTheta",&jetTheta);
  trackTree_->Branch("jetMass",&jetMass);
  trackTree_->Branch("muonMultiplicity",&muonMultiplicity);
  trackTree_->Branch("chargedMultiplicity",&chargedMultiplicity);
  trackTree_->Branch("jetN",&jetN);


  trackTree_->Branch("dau_pt_sum",      &dau_pt_sum);
  trackTree_->Branch("dau_chg",		&dau_chg); 
  trackTree_->Branch("dau_pid",		&dau_pid);	 
  trackTree_->Branch("dau_vref",	&dau_vref);
  trackTree_->Branch("dau_pt",		&dau_pt);
  trackTree_->Branch("dau_eta",		&dau_eta);	 
  trackTree_->Branch("dau_phi",		&dau_phi );
  trackTree_->Branch("dau_theta",	&dau_theta);
  trackTree_->Branch("dau_vz",		&dau_vz	 );
  trackTree_->Branch("dau_vy",		&dau_vy	 );
  trackTree_->Branch("dau_vx",		&dau_vx	 );
  trackTree_->Branch("dau_vrefz",	&dau_vrefz);
  trackTree_->Branch("dau_vrefy",	&dau_vrefy);
  trackTree_->Branch("dau_vrefx",	&dau_vrefx);
  trackTree_->Branch("dau_vp_difZ",	&dau_vp_difZ);
  trackTree_->Branch("dau_vp_difY",	&dau_vp_difY);
  trackTree_->Branch("dau_vp_difX",	&dau_vp_difX);


}

// ------------ method called once each job just after ending the event loop  ------------
void
TrackAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TrackAnalyzer);
