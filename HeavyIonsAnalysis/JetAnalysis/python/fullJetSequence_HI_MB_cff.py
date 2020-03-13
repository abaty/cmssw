import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.JetAnalysis.rerecoGen_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoRho_HI_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoJets_HI_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoTracks_cff import *

# for legacy HI reco only!
from HeavyIonsAnalysis.JetAnalysis.modificationsForHIReco_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.akPu3CaloJetSequence_HIonPbPb_mb_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu3PFJetSequence_HIonPbPb_mb_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs3PFJetSequence_HIonPbPb_mb_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.akPu4CaloJetSequence_HIonPbPb_mb_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu4PFJetSequence_HIonPbPb_mb_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs4PFJetSequence_HIonPbPb_mb_cff import *

genSignalSequence = cms.Sequence(
    genParticlesForJets +

    hiSignalGenParticles +
    genParticlesForJetsSignal +

    ak3HiGenJets +
    ak4HiGenJets +

    signalPartons +

    ak3HiSignalGenJets +
    ak4HiSignalGenJets +

    ak3HiGenNjettiness +
    ak4HiGenNjettiness
)

genCleanedSequence = cms.Sequence(
    genParticlesForJets +

    ak3HiGenJets +
    ak4HiGenJets +

    myPartons +
    cleanedPartons +

    ak3HiCleanedGenJets +
    ak4HiCleanedGenJets
)

jetSequence = cms.Sequence(
    rhoSequence +

    highPurityTracks +
    offlinePrimaryVertices +

    akPu3CaloJets +
    akPu3PFJets +
    akCs3HIPFJets +

    akPu4CaloJets +
    akPu4PFJets +
    akCs4HIPFJets +

    akPu3CaloJetSequence +
    akPu3PFJetSequence +
    akCs3PFJetSequence +

    akPu4CaloJetSequence +
    akPu4PFJetSequence +
    akCs4PFJetSequence
)
