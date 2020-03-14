import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets

from RecoHI.HiJetAlgos.HiGenJets_cff import (
    ak1HiGenJets, ak2HiGenJets, ak3HiGenJets,
    ak4HiGenJets, ak5HiGenJets, ak6HiGenJets)

from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

akSoftDrop4GenJets = cms.EDProducer(
    "FastjetJetProducer",
    GenJetParameters,
    AnomalousCellParameters,
    jetAlgorithm        = cms.string("AntiKt"),
    rParam              = cms.double(0.4),
    useSoftDrop         = cms.bool(True),
    zcut                = cms.double(0.1),
    beta                = cms.double(0.0),
    R0                  = cms.double(0.4),
    useExplicitGhosts   = cms.bool(True),
    writeCompound       = cms.bool(True),
    jetCollInstanceName = cms.string("SubJets")
)

akSoftDrop4HIGenJets = cms.EDProducer(
    "SoftDropJetProducer",
    GenJetParameters,
    AnomalousCellParameters,
    jetAlgorithm        = cms.string("AntiKt"),
    rParam              = cms.double(0.4),
    zcut                = cms.double(0.1),
    beta                = cms.double(0.0),
    R0                  = cms.double(0.4),
    useOnlyCharged      = cms.bool(False),
    useExplicitGhosts   = cms.bool(True),
    writeCompound       = cms.bool(True),
    jetCollInstanceName = cms.string("SubJets")
)

akSoftDropZ05B154GenJets = akSoftDrop4GenJets.clone(
    zcut = cms.double(0.5), beta = cms.double(1.5))

akSoftDropZ05B154HIGenJets = akSoftDrop4HIGenJets.clone(
    zcut = cms.double(0.5), beta = cms.double(1.5))

# cloning jets for other radii
ak1GenJets = ak4GenJets.clone(rParam = 0.1)
ak2GenJets = ak4GenJets.clone(rParam = 0.2)
ak3GenJets = ak4GenJets.clone(rParam = 0.3)
ak5GenJets = ak4GenJets.clone(rParam = 0.5)
ak6GenJets = ak4GenJets.clone(rParam = 0.6)
