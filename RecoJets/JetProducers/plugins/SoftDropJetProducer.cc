#include "FWCore/Framework/interface/MakerMacros.h"
#include "RecoJets/JetProducers/plugins/SoftDropJetProducer.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "RecoJets/JetProducers/interface/JetSpecific.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/Common/interface/AssociationVector.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Common/interface/RefVector.h"

#include "fastjet/contrib/SoftDrop.hh"

#include <iostream>
#include <memory>
#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;
using namespace reco;
using namespace edm;
using namespace cms;

SoftDropJetProducer::SoftDropJetProducer(edm::ParameterSet const& iConfig):
  VirtualJetProducer( iConfig ),
  zCut_(-1.0),
  beta_(-1.0),
  R0_(-1.0),
  useOnlyCharged_(false)
{
  //get soft drop settings
  zCut_ = iConfig.getParameter<double>("zcut");
  beta_ = iConfig.getParameter<double>("beta");
  R0_ = iConfig.getParameter<double>("R0");
  useOnlyCharged_ = iConfig.getParameter<bool>("useOnlyCharged");

  input_candidateview_token_SD_ = consumes<reco::CandidateView>(src_);
  input_candidatefwdptr_token_SD_ = consumes<std::vector<edm::FwdPtr<reco::PFCandidate> > >(src_);
  input_packedcandidatefwdptr_token_SD_ = consumes<std::vector<edm::FwdPtr<pat::PackedCandidate> > >(src_);

  produces<edm::ValueMap<float> > ("sym");
  produces<edm::ValueMap<int> > ("droppedBranches");
  //produces<edm::ValueMap<std::vector<double>> > ("droppedSym");
  //produces<edm::AssociationVector<reco::JetRefBaseProd,std::vector<double>> > ("droppedSym");
  //produces<edm::AssociationVector<std::vector<double> > ("droppedSym");  
}

//______________________________________________________________________________
void SoftDropJetProducer::produce( edm::Event & iEvent, const edm::EventSetup & iSetup )
{
  // use the default production from one collection
  //VirtualJetProducer::produce( iEvent, iSetup );

  // If requested, set the fastjet random seed to a deterministic function
  // of the run/lumi/event.
  // NOTE!!! The fastjet random number sequence is a global singleton.
  // Thus, we have to create an object and get access to the global singleton
  // in order to change it.
  if ( useDeterministicSeed_ ) {
    fastjet::GhostedAreaSpec gas;
    std::vector<int> seeds(2);
    unsigned int runNum_uint = static_cast <unsigned int> (iEvent.id().run());
    unsigned int evNum_uint = static_cast <unsigned int> (iEvent.id().event());
    seeds[0] = std::max(runNum_uint,minSeed_ + 3) + 3 * evNum_uint;
    seeds[1] = std::max(runNum_uint,minSeed_ + 5) + 5 * evNum_uint;
    gas.set_random_status(seeds);
  }

  LogDebug("SoftDropJetProducer") << "Entered produce\n";
  //determine signal vertex2
  vertex_=reco::Jet::Point(0,0,0);
  if ( (makeCaloJet(jetTypeE) || makePFJet(jetTypeE)) &&doPVCorrection_) {
    LogDebug("SoftDropJetProducer") << "Adding PV info\n";
    edm::Handle<reco::VertexCollection> pvCollection;
    iEvent.getByToken(input_vertex_token_ , pvCollection);
    if (pvCollection->size()>0) vertex_=pvCollection->begin()->position();
  }

  // For Pileup subtraction using offset correction:
  // set up geometry map
  if ( doPUOffsetCorr_ ) {
     subtractor_->setupGeometryMap(iEvent, iSetup);
  }

  // clear data
  LogDebug("SoftDropJetProducer") << "Clear data\n";
  fjInputs_.clear();
  fjJets_.clear();
  inputs_.clear();

  // get inputs and convert them to the fastjet format (fastjet::PeudoJet)
  edm::Handle<reco::CandidateView> inputsHandle;

  edm::Handle< std::vector<edm::FwdPtr<reco::PFCandidate> > > pfinputsHandleAsFwdPtr;
  edm::Handle< std::vector<edm::FwdPtr<pat::PackedCandidate> > > packedinputsHandleAsFwdPtr;

  bool isView = iEvent.getByToken(input_candidateview_token_SD_, inputsHandle);
  if ( isView ) {
    if ( verbosity_ >= 1 ) {
      std::cout << "found inputs in event" << std::endl; }
    for (size_t i = 0; i < inputsHandle->size(); ++i) {
      inputs_.push_back(inputsHandle->ptrAt(i));
      // if ( verbosity_ >= 1 ) {
      //   std::cout << "input particle " << i << " pt = " << inputs_[i]->pt() << " phi: " << inputs_[i]->phi() << " eta: " << inputs_[i]->eta() << " " << std::endl;
      // }
    }
  } else {
    bool isPF = iEvent.getByToken(input_candidatefwdptr_token_SD_, pfinputsHandleAsFwdPtr);
    if ( isPF ) {
      for (size_t i = 0; i < pfinputsHandleAsFwdPtr->size(); ++i) {
        if ( (*pfinputsHandleAsFwdPtr)[i].ptr().isAvailable() ) {
          inputs_.push_back( (*pfinputsHandleAsFwdPtr)[i].ptr() );
        }
        else if ( (*pfinputsHandleAsFwdPtr)[i].backPtr().isAvailable() ) {
          inputs_.push_back( (*pfinputsHandleAsFwdPtr)[i].backPtr() );
        }
      }
    } else {
      iEvent.getByToken(input_packedcandidatefwdptr_token_SD_, packedinputsHandleAsFwdPtr);
      for (size_t i = 0; i < packedinputsHandleAsFwdPtr->size(); ++i) {
        if ( (*packedinputsHandleAsFwdPtr)[i].ptr().isAvailable() ) {
          inputs_.push_back( (*packedinputsHandleAsFwdPtr)[i].ptr() );
        }
        else if ( (*packedinputsHandleAsFwdPtr)[i].backPtr().isAvailable() ) {
          inputs_.push_back( (*packedinputsHandleAsFwdPtr)[i].backPtr() );
        }
      }
    }
  }
  LogDebug("SoftDropJetProducer") << "Got inputs\n";

  // Convert candidates to fastjet::PseudoJets.
  // Also correct to Primary Vertex. Will modify fjInputs_
  // and use inputs_
  fjInputs_.reserve(inputs_.size());
  inputTowers();
  LogDebug("VirtualJetProducer") << "Inputted towers\n";

  // Run algorithm. Will modify fjJets_ and allocate fjClusterSeq_.
  // This will use fjInputs_
  runAlgorithm( iEvent, iSetup );

  // Write the output jets.
  // This will (by default) call the member function template
  // "writeJets", but can be overridden.
  // this will use inputs_
  output( iEvent, iSetup );

  

  //use write function of this class
  //writeSoftDropJets<reco::PFJet>( iEvent, iSetup );

  
  //use runAlgorithm of this class
  //runAlgorithm(iEvent,iSetup);

  // fjClusterSeq_ retains quite a lot of memory - about 1 to 7Mb at 200 pileup
  // depending on the exact configuration; and there are 24 FastjetJetProducers in the
  // sequence so this adds up to about 60 Mb. It's allocated every time runAlgorithm
  // is called, so safe to delete here.
  fjClusterSeq_.reset();
  fjClusterSeqRecluster_.reset();

  // Clear the work vectors so that memory is free for other modules.
  // Use the trick of swapping with an empty vector so that the memory
  // is actually given back rather than silently kept.
  decltype(fjInputs_)().swap(fjInputs_);
  decltype(fjJets_)().swap(fjJets_);
  decltype(inputs_)().swap(inputs_);
}

//______________________________________________________________________________
void SoftDropJetProducer::output( edm::Event & iEvent, const edm::EventSetup & iSetup )
{
  //use write function of this class
  if ( writeCompound_ ) {
    // Write jets and subjets
    switch( jetTypeE ) {
    case JetType::CaloJet :
      writeSoftDropJets<reco::CaloJet>( iEvent, iSetup );
      break;
    case JetType::PFJet :
      writeSoftDropJets<reco::PFJet>( iEvent, iSetup );
      break;
    case JetType::GenJet :
      writeSoftDropJets<reco::GenJet>( iEvent, iSetup );
      break;
    case JetType::BasicJet :
      writeSoftDropJets<reco::BasicJet>( iEvent, iSetup );
      break;
    default:
      throw cms::Exception("InvalidInput") << "invalid jet type in SoftDropJetProducer\n";
      break;
    };
  }
  
  //  writeSoftDropJets<reco::PFJet>( iEvent, iSetup );

}

//______________________________________________________________________________
void SoftDropJetProducer::runAlgorithm( edm::Event & iEvent, edm::EventSetup const& iSetup)
{

  //std::cout << "<SoftDropJetProducer::runAlgorithm (moduleLabel = " << moduleLabel_ << ")>:" << std::endl;
  
  if ( !doAreaFastjet_ && !doRhoFastjet_) {
    fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequence( fjInputs_, *fjJetDefinition_ ) );
  } else if (voronoiRfact_ <= 0) {
    fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequenceArea( fjInputs_, *fjJetDefinition_ , *fjAreaDefinition_ ) );
  } else {
    fjClusterSeq_ = ClusterSequencePtr( new fastjet::ClusterSequenceVoronoiArea( fjInputs_, *fjJetDefinition_ , fastjet::VoronoiAreaSpec(voronoiRfact_) ) );
  }
  
  std::vector<fastjet::PseudoJet> origJets = fastjet::sorted_by_pt(fjClusterSeq_->inclusive_jets(jetPtMin_));
  // fastjet::contrib::SoftDrop * sdr = new fastjet::contrib::SoftDrop(beta_, zCut_, R0_ );
  // sdr->set_verbose_structure(true);
  
  // for ( std::vector<fastjet::PseudoJet>::const_iterator ijet = origJets.begin(),
  //         ijetEnd = origJets.end(); ijet != ijetEnd; ++ijet ) {
  //   fastjet::PseudoJet transformedJet = *ijet;
  //   if ( transformedJet == 0 ) continue;
  //   transformedJet = (*sdr)(transformedJet);
  //   //fjJets_.push_back( transformedJet );

  //   double sym = transformedJet.structure_of<fastjet::contrib::SoftDrop>().symmetry();
  //   std::cout << "sym: " << sym << std::endl;
  //   int ndrop = transformedJet.structure_of<fastjet::contrib::SoftDrop>().dropped_count();
  //   std::cout << "#dropped branches: " << ndrop << std::endl;
  //   std::vector<double> dropped_symmetry = transformedJet.structure_of<fastjet::contrib::SoftDrop>().dropped_symmetry();
  //   std::cout << "dropped_symmetry.size() " << dropped_symmetry.size() << std::endl;
  //   for ( std::vector<double>::const_iterator dsym = dropped_symmetry.begin();
  //           dsym != dropped_symmetry.end(); ++dsym )
  //     std::cout << "dropped symmetry: " << (*dsym) << std::endl;
  // }

  //std::cout << "recluster manual" << std::endl;

  //select requested particle types and recluster with CA infinite radius
  //fjJetDefinitionRecluster_ = JetDefPtr(new fastjet::JetDefinition(fastjet::antikt_algorithm,rParam_));
  //fjJetDefinitionRecluster_ = JetDefPtr(new fastjet::JetDefinition(fastjet::cambridge_algorithm,999.));
      
  fjJets_.clear();
  clusterSequences.clear();
  jetDefinitions.clear();
  lSym.clear();
  lDroppedBranches.clear();
  lDroppedSym.clear();
  
  static const reco::PFCandidate dummySinceTranslateIsNotStatic;
  // clusterSequence_coll clusterSequences;
  // jetDefinition_coll jetDefinitions;
  for ( std::vector<fastjet::PseudoJet>::const_iterator ijet = origJets.begin(),
          ijetEnd = origJets.end(); ijet != ijetEnd; ++ijet ) {
    fjClusterSeqRecluster_.reset();
    std::vector<fastjet::PseudoJet> inputsRecluster;
    //    inputsRecluster.clear();
    std::vector<fastjet::PseudoJet> particles, ghosts;
    fastjet::SelectorIsPureGhost().sift(ijet->constituents(), ghosts, particles);
    //std::cout << "#particles in jet " << particles.size() << std::endl;
    for ( std::vector<fastjet::PseudoJet>::const_iterator ipart = particles.begin();
          ipart != particles.end(); ++ipart ) {
      auto orig = inputs_[(*ipart).user_index()];
      auto id = dummySinceTranslateIsNotStatic.translatePdgIdToType(orig->pdgId());
      
      bool passed  = false;
      if(useOnlyCharged_) {
        if(id==1) passed = true;
      } else
        passed = true;
      //if(passed) std::cout << "id: " << id << " pdfId: " << orig->pdgId() << std::endl;
      if(passed) inputsRecluster.push_back(*ipart);
    }
    //    std::cout << "inputsRecluster.size() " << inputsRecluster.size() << std::endl;

    //recluster with selected particles
    fjJetDefinitionRecluster_ = JetDefPtr(new fastjet::JetDefinition(fastjet::cambridge_algorithm,999.));
    //fjJetDefinitionRecluster_ = JetDefPtr(new fastjet::JetDefinition(fastjet::cambridge_algorithm,fastjet::JetDefinition::max_allowable_R));
    if ( !doAreaFastjet_ && !doRhoFastjet_) {
      fjClusterSeqRecluster_ = ClusterSequencePtr( new fastjet::ClusterSequence( inputsRecluster, *fjJetDefinitionRecluster_ ) );
    } else if (voronoiRfact_ <= 0) {
      fjClusterSeqRecluster_ = ClusterSequencePtr( new fastjet::ClusterSequenceArea( inputsRecluster, *fjJetDefinitionRecluster_ , *fjAreaDefinition_ ) );
    } else {
      fjClusterSeqRecluster_ = ClusterSequencePtr( new fastjet::ClusterSequenceVoronoiArea( inputsRecluster, *fjJetDefinitionRecluster_ , fastjet::VoronoiAreaSpec(voronoiRfact_) ) );
    }
    clusterSequences.push_back(fjClusterSeqRecluster_);
    jetDefinitions.push_back(fjJetDefinitionRecluster_);

    std::vector<fastjet::PseudoJet> tempJets = fastjet::sorted_by_pt(fjClusterSeqRecluster_->inclusive_jets(jetPtMin_));
    //std::vector<fastjet::PseudoJet> tempJets = fastjet::sorted_by_pt(clusterSequences[clusterSequences.size()]->inclusive_jets(jetPtMin_));
    if(tempJets.size()<1) continue;
    //std::cout << "got reclusted CA jet" << std::endl;
    //std::cout << "tempJets.size() " << tempJets.size() << std::endl;   
 
    fastjet::contrib::SoftDrop * sd = new fastjet::contrib::SoftDrop(beta_, zCut_, R0_ );
    sd->set_verbose_structure(true);

    fastjet::PseudoJet transformedJet = tempJets[0];
    if ( transformedJet == 0 ) {
      //fjClusterSeqRecluster_->delete_self_when_unused();
      if(sd) { delete sd; sd = 0;}
      continue;
    }
    // if(!transformedJet.has_valid_cluster_sequence()) {
    //   std::cout << "transformedJet does not have a valid cluster sequence" << std::endl;
    // }
    //std::cout << "orig jet pt: " << transformedJet.perp() << std::endl;
    transformedJet = (*sd)(transformedJet);
    fjJets_.push_back( transformedJet ); //put CA reclusterd jet after softDrop into vector which will be written to event

    double sym = transformedJet.structure_of<fastjet::contrib::SoftDrop>().symmetry();
    int ndrop = transformedJet.structure_of<fastjet::contrib::SoftDrop>().dropped_count();
    std::vector<double> dropped_symmetry = transformedJet.structure_of<fastjet::contrib::SoftDrop>().dropped_symmetry();
  
    // //DEBUGGING BEGIN 
    // std::cout << "SoftDropProducer: " << moduleLabel_ << std::endl; 
    // std::cout << "sym: " << sym << std::endl;
    // std::cout << "#dropped branches: " << ndrop << std::endl;
    // std::cout << "dropped_symmetry.size() " << dropped_symmetry.size() << std::endl;
    // for ( std::vector<double>::const_iterator dsym = dropped_symmetry.begin();
    //       dsym != dropped_symmetry.end(); ++dsym )
    //   std::cout << "dropped symmetry: " << (*dsym) << std::endl;
    
    // std::vector<fastjet::PseudoJet> constituents;
    // if ( transformedJet.has_pieces() )
    //   constituents = transformedJet.pieces();
    // std::vector<fastjet::PseudoJet>::const_iterator itSubJetBegin = constituents.begin(), itSubJet = itSubJetBegin, itSubJetEnd = constituents.end();
    // for (; itSubJet != itSubJetEnd; ++itSubJet ){
    //   fastjet::PseudoJet const & subjet = *itSubJet;
    //   std::cout << "subjet # " << (itSubJet - itSubJetBegin) << ": Pt = " << subjet.pt() << std::endl;
    // }
    // //DEBUGGING END

    lSym.push_back(sym);
    lDroppedBranches.push_back(ndrop);
    lDroppedSym.push_back(dropped_symmetry);
    
    if(sd) { delete sd; sd = 0;}
    //    fjClusterSeqRecluster_->delete_self_when_unused();
    
  }//anti-kt original jet loop
  
  //fjJets_ = fastjet::sorted_by_pt(fjClusterSeq_->inclusive_jets(jetPtMin_));
  
  // fastjet::RecursiveSymmetryCutBase rc(fastjet::SymmetryMeasure::scalar_z,  // the default SymmetryMeasure
  //                                      std::numeric_limits<double>::infinity(), // default is no mass drop
  //                                      fastjet::RecursionChoice::larger_pt, // the default RecursionChoice
  //                                      subtractor);
  // rc.set_grooming_mode();

  //  PseudoJet piece1, piece2;
  //  while (subjet.has_parents(piece1, piece2)) {
  //  double sym;
  //  double pt1 = piece1.pt();
  //  double pt2 = piece2.pt();
  //  make sure denominator is non-zero
  //  sym = pt1 + pt2;
  //  if (sym == 0) return PseudoJet(); 
  //  sym = std::min(pt1, pt2) / sym;
  // }

  //std::cout << "SoftDropProducer::runAlgorithm end" << std::endl;
  
}

/// function template to write out the outputs
template< class T>
void SoftDropJetProducer::writeSoftDropJets(  edm::Event & iEvent, edm::EventSetup const& iSetup)
{
  if ( verbosity_ >= 1 ) {
    std::cout << "<SoftDropJetProducer::writeSoftDropJets (moduleLabel = " << moduleLabel_ << ")>:" << std::endl;
  }

  // get a list of output jets
  auto jetCollection = std::make_unique<reco::BasicJetCollection>();
  // get a list of output subjets
  auto subjetCollection = std::make_unique<std::vector<T>>();

  // This will store the handle for the subjets after we write them
  edm::OrphanHandle< std::vector<T> > subjetHandleAfterPut;
  // this is the mapping of subjet to hard jet
  std::vector< std::vector<int> > indices;
  // this is the list of hardjet 4-momenta
  std::vector<math::XYZTLorentzVector> p4_hardJets;
  // this is the hardjet areas
  std::vector<double> area_hardJets;

  // Loop over the hard jets
  indices.resize( fjJets_.size() );
  for (auto it = fjJets_.begin(); it != fjJets_.end(); ++it) {
    fastjet::PseudoJet const & localJet = *it;
    unsigned int jetIndex = it - fjJets_.begin();
    // Get the 4-vector for the hard jet
    p4_hardJets.emplace_back(localJet.px(), localJet.py(), localJet.pz(), localJet.e());
    double localJetArea = 0.0;
    if ( doAreaFastjet_ && localJet.has_area() ) {
      localJetArea = localJet.area();
    }
    area_hardJets.push_back( localJetArea );

    // create the subjet/constituent list
    std::vector<fastjet::PseudoJet> constituents,ghosts;
    if ( it->has_pieces() ) {
      constituents = it->pieces();
    } else if ( it->has_constituents() ) {
      fastjet::SelectorIsPureGhost().sift(it->constituents(), ghosts, constituents); //filter out ghosts
    }

    //loop over constituents of jet (can be subjets or normal constituents)
    //std::cout << "N subjets: " << constituents.size() << std::endl;
    for (auto itSubJet = constituents.begin(); itSubJet != constituents.end(); ++itSubJet ){

      fastjet::PseudoJet const & subjet = *itSubJet;
      if ( verbosity_ >= 1 ) {
        std::cout << "subjet #" << (itSubJet - constituents.begin()) << ": Pt = " << subjet.pt() << ", eta = " << subjet.eta() << ", phi = " << subjet.phi() << ", mass = " << subjet.m()
                  << " (#constituents = " << subjet.constituents().size() << ")" << std::endl;
        std::vector<fastjet::PseudoJet> subjet_constituents = subjet.constituents();
        int idx_constituent = 0;
        for ( std::vector<fastjet::PseudoJet>::const_iterator constituent = subjet_constituents.begin();
              constituent != subjet_constituents.end(); ++constituent ) {
          //if ( constituent->pt() < 1.e-3 ) continue; // CV: skip ghosts
          std::cout << "  constituent #" << idx_constituent << ": Pt = " << constituent->pt() << ", eta = " << constituent->eta() << ", phi = " << constituent->phi() << ","
                    << " mass = " << constituent->m() << std::endl;
          ++idx_constituent;
        }
      }

      math::XYZTLorentzVector p4Subjet(subjet.px(), subjet.py(), subjet.pz(), subjet.e() ); //4-vector of subjet/constituent
      reco::Particle::Point point(0,0,0);

      // This will hold ptr's to the subjets/constituents -> MV: not used?
      std::vector<reco::CandidatePtr> subjetConstituents;

      // Get the transient subjet constituents from fastjet
      std::vector<reco::CandidatePtr> constituentsOfSubjet;
      if(subjet.has_constituents()) {
        std::vector<fastjet::PseudoJet> subjetFastjetConstituents = subjet.constituents();
        constituentsOfSubjet = getConstituents(subjetFastjetConstituents );
      }
      indices[jetIndex].push_back( subjetCollection->size() );

      // Add the concrete subjet type to the subjet list to write to event record
      T jet;
      reco::writeSpecific( jet, p4Subjet, point, constituentsOfSubjet, iSetup);
      double subjetArea = 0.0;
      if ( doAreaFastjet_ && itSubJet->has_area() ){
        subjetArea = itSubJet->area();
      }
      jet.setJetArea( subjetArea );
      subjetCollection->push_back( jet );
    }
  }
  // put subjets into event record
  subjetHandleAfterPut = iEvent.put( std::move(subjetCollection), jetCollInstanceName_ );
  
  // Now create the hard jets with ptr's to the subjets as constituents
  for ( auto ip4 = p4_hardJets.begin(); ip4 != p4_hardJets.end(); ++ip4 ) {
    int p4_index = ip4 - p4_hardJets.begin();
    std::vector<int> & ind = indices[p4_index];
    std::vector<reco::CandidatePtr> i_hardJetConstituents;
    // Add the subjets to the hard jet
    for( std::vector<int>::const_iterator isub = ind.begin();
         isub != ind.end(); ++isub ) {
      reco::CandidatePtr candPtr( subjetHandleAfterPut, *isub, false );
      i_hardJetConstituents.push_back( candPtr );
    }
    reco::Particle::Point point(0,0,0);
    reco::BasicJet toput( *ip4, point, i_hardJetConstituents);
    toput.setJetArea( area_hardJets[p4_index] );
    jetCollection->push_back( toput );
  }

  // put hard jets into event record
  edm::OrphanHandle<std::vector<reco::BasicJet> > jetHandleAfterPut = iEvent.put(std::move(jetCollection));

  //Fill it into the event
  auto lSymOut = std::make_unique<edm::ValueMap<float> >();
  edm::ValueMap<float>::Filler  lSymFiller(*lSymOut);
  lSymFiller.insert(jetHandleAfterPut,lSym.begin(),lSym.end());
  lSymFiller.fill();
  iEvent.put(std::move(lSymOut),"sym");

  auto lDroppedBranchesOut = std::make_unique<edm::ValueMap<int> >();
  edm::ValueMap<int>::Filler  lDroppedBranchesFiller(*lDroppedBranchesOut);
  lDroppedBranchesFiller.insert(jetHandleAfterPut,lDroppedBranches.begin(),lDroppedBranches.end());
  lDroppedBranchesFiller.fill();
  iEvent.put(std::move(lDroppedBranchesOut),"droppedBranches");
}

void SoftDropJetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription descSoftDropJetProducer;
  fillDescriptionsFromSoftDropJetProducer(descSoftDropJetProducer);
  VirtualJetProducer::fillDescriptionsFromVirtualJetProducer(descSoftDropJetProducer);
  descSoftDropJetProducer.add<string>("jetCollInstanceName", "");
  descSoftDropJetProducer.add<bool>("sumRecHits", false);

  descriptions.add("SoftDropJetProducer", descSoftDropJetProducer);
}

void SoftDropJetProducer::fillDescriptionsFromSoftDropJetProducer(edm::ParameterSetDescription& desc) {
  desc.add<double>("zcut", -1.0);
  desc.add<double>("beta", -1.0);
  desc.add<double>("R0", -1.0);
  desc.add<bool>("useOnlyCharged", false);
}

////////////////////////////////////////////////////////////////////////////////
// define as cmssw plugin
////////////////////////////////////////////////////////////////////////////////

DEFINE_FWK_MODULE(SoftDropJetProducer);
