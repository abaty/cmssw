import FWCore.ParameterSet.Config as cms

from HeavyIonsAnalysis.JetAnalysis.rerecoGen_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoRho_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoJets_cff import *
from HeavyIonsAnalysis.JetAnalysis.rerecoTracks_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.ak1CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak1PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu1CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu1PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs1PFJetSequence_pponPbPb_mc_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.ak2CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak2PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu2CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu2PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs2PFJetSequence_pponPbPb_mc_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.ak3CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak3PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu3CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu3PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs3PFJetSequence_pponPbPb_mc_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.ak4CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak4PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu4CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu4PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs4PFJetSequence_pponPbPb_mc_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.ak5CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak5PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu5CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu5PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs5PFJetSequence_pponPbPb_mc_cff import *

from HeavyIonsAnalysis.JetAnalysis.jets.ak6CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.ak6PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu6CaloJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akPu6PFJetSequence_pponPbPb_mc_cff import *
from HeavyIonsAnalysis.JetAnalysis.jets.akCs6PFJetSequence_pponPbPb_mc_cff import *

genSignalSequence = cms.Sequence(
    genParticlesForJets +

    hiSignalGenParticles +
    genParticlesForJetsSignal +

    ak1HiGenJets +
    ak2HiGenJets +
    ak3HiGenJets +
    ak4HiGenJets +
    ak5HiGenJets +
    ak6HiGenJets +

    signalPartons +

    ak1HiSignalGenJets +
    ak2HiSignalGenJets +
    ak3HiSignalGenJets +
    ak4HiSignalGenJets +
    ak5HiSignalGenJets +
    ak6HiSignalGenJets +

    ak1HiGenNjettiness +
    ak2HiGenNjettiness +
    ak3HiGenNjettiness +
    ak4HiGenNjettiness +
    ak5HiGenNjettiness +
    ak6HiGenNjettiness
)

genCleanedSequence = cms.Sequence(
    genParticlesForJets +

    ak1HiGenJets +
    ak2HiGenJets +
    ak3HiGenJets +
    ak4HiGenJets +
    ak5HiGenJets +
    ak6HiGenJets +

    myPartons +
    cleanedPartons +

    ak1HiCleanedGenJets +
    ak2HiCleanedGenJets +
    ak3HiCleanedGenJets +
    ak4HiCleanedGenJets +
    ak5HiCleanedGenJets +
    ak6HiCleanedGenJets
)

jetSequence = cms.Sequence(
    rhoSequence +

    highPurityTracks +

    ak1CaloJets +
    ak1PFJets +
    akPu1CaloJets +
    akPu1PFJets +
    akCs1PFJets +

    ak2CaloJets +
    ak2PFJets +
    akPu2CaloJets +
    akPu2PFJets +
    akCs2PFJets +

    ak3CaloJets +
    ak3PFJets +
    akPu3CaloJets +
    akPu3PFJets +
    akCs3PFJets +

    ak4CaloJets +
    ak4PFJets +
    akPu4CaloJets +
    akPu4PFJets +
    akCs4PFJets +

    ak5CaloJets +
    ak5PFJets +
    akPu5CaloJets +
    akPu5PFJets +
    akCs5PFJets +

    ak6CaloJets +
    ak6PFJets +
    akPu6CaloJets +
    akPu6PFJets +
    akCs6PFJets +

    ak1CaloJetSequence +
    ak1PFJetSequence +
    akPu1CaloJetSequence +
    akPu1PFJetSequence +
    akCs1PFJetSequence +

    ak2CaloJetSequence +
    ak2PFJetSequence +
    akPu2CaloJetSequence +
    akPu2PFJetSequence +
    akCs2PFJetSequence +

    ak3CaloJetSequence +
    ak3PFJetSequence +
    akPu3CaloJetSequence +
    akPu3PFJetSequence +
    akCs3PFJetSequence +

    ak4CaloJetSequence +
    ak4PFJetSequence +
    akPu4CaloJetSequence +
    akPu4PFJetSequence +
    akCs4PFJetSequence +

    ak5CaloJetSequence +
    ak5PFJetSequence +
    akPu5CaloJetSequence +
    akPu5PFJetSequence +
    akCs5PFJetSequence +

    ak6CaloJetSequence +
    ak6PFJetSequence +
    akPu6CaloJetSequence +
    akPu6PFJetSequence +
    akCs6PFJetSequence
)
