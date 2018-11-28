import FWCore.ParameterSet.Config as cms

from RecoJets.Configuration.GenJetParticles_cff import genParticlesForJets
from RecoHI.HiJetAlgos.HiSignalParticleProducer_cfi import hiSignalGenParticles
genParticlesForJetsSignal = genParticlesForJets.clone(
    src = cms.InputTag("hiSignalGenParticles"))

myPartons = cms.EDProducer("PartonSelector",
    withLeptons = cms.bool(False),
    src = cms.InputTag("genParticles")
)

signalPartons = myPartons.clone(src = 'hiSignalGenParticles')

from RecoHI.HiJetAlgos.HiGenCleaner_cff import hiPartons
cleanedPartons = hiPartons.clone(src = 'myPartons')

# import gen jet producers
from HeavyIonsAnalysis.JetAnalysis.akGenJets_cfi import (
    ak1GenJets, ak1HiGenJets,
    ak2GenJets, ak2HiGenJets,
    ak3GenJets, ak3HiGenJets,
    ak4GenJets, ak4HiGenJets,
    ak5GenJets, ak5HiGenJets,
    ak6GenJets, ak6HiGenJets)

from RecoHI.HiJetAlgos.HiGenCleaner_cff import heavyIonCleanedGenJets
ak1HiCleanedGenJets = heavyIonCleanedGenJets.clone(src = "ak1HiGenJets")
ak2HiCleanedGenJets = heavyIonCleanedGenJets.clone(src = "ak2HiGenJets")
ak3HiCleanedGenJets = heavyIonCleanedGenJets.clone(src = "ak3HiGenJets")
ak4HiCleanedGenJets = heavyIonCleanedGenJets.clone(src = "ak4HiGenJets")
ak5HiCleanedGenJets = heavyIonCleanedGenJets.clone(src = "ak5HiGenJets")
ak6HiCleanedGenJets = heavyIonCleanedGenJets.clone(src = "ak6HiGenJets")

from RecoHI.HiJetAlgos.HiSignalGenJetProducer_cfi import hiSignalGenJets
ak1HiSignalGenJets = hiSignalGenJets.clone(src = "ak1HiGenJets")
ak2HiSignalGenJets = hiSignalGenJets.clone(src = "ak2HiGenJets")
ak3HiSignalGenJets = hiSignalGenJets.clone(src = "ak3HiGenJets")
ak4HiSignalGenJets = hiSignalGenJets.clone(src = "ak4HiGenJets")
ak5HiSignalGenJets = hiSignalGenJets.clone(src = "ak5HiGenJets")
ak6HiSignalGenJets = hiSignalGenJets.clone(src = "ak6HiGenJets")

from RecoJets.JetProducers.nJettinessAdder_cfi import Njettiness
ak1GenNjettiness = Njettiness.clone(src = "ak1GenJets", R0 = 0.1)
ak2GenNjettiness = Njettiness.clone(src = "ak2GenJets", R0 = 0.2)
ak3GenNjettiness = Njettiness.clone(src = "ak3GenJets", R0 = 0.3)
ak4GenNjettiness = Njettiness.clone(src = "ak4GenJets", R0 = 0.4)
ak5GenNjettiness = Njettiness.clone(src = "ak5GenJets", R0 = 0.5)
ak6GenNjettiness = Njettiness.clone(src = "ak6GenJets", R0 = 0.6)

ak1HiGenNjettiness = Njettiness.clone(src = "ak1HiSignalGenJets", R0 = 0.1)
ak2HiGenNjettiness = Njettiness.clone(src = "ak2HiSignalGenJets", R0 = 0.2)
ak3HiGenNjettiness = Njettiness.clone(src = "ak3HiSignalGenJets", R0 = 0.3)
ak4HiGenNjettiness = Njettiness.clone(src = "ak4HiSignalGenJets", R0 = 0.4)
ak5HiGenNjettiness = Njettiness.clone(src = "ak5HiSignalGenJets", R0 = 0.5)
ak6HiGenNjettiness = Njettiness.clone(src = "ak6HiSignalGenJets", R0 = 0.6)
