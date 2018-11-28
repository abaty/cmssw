import FWCore.ParameterSet.Config as cms

from RecoHI.HiJetAlgos.HiCaloJetParameters_cff import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

ak4CaloJets = cms.EDProducer(
    "FastjetJetProducer",
    HiCaloJetParameters,
    AnomalousCellParameters,
    MultipleAlgoIteratorBlock,
    jetAlgorithm = cms.string("AntiKt"),
    rParam       = cms.double(0.4)
)
ak4CaloJets.doPUOffsetCorr = False
ak4CaloJets.jetPtMin = 1.0

akPu4CaloJets = cms.EDProducer(
    "FastjetJetProducer",
    HiCaloJetParameters,
    AnomalousCellParameters,
    MultipleAlgoIteratorBlock,
    jetAlgorithm = cms.string("AntiKt"),
    rParam       = cms.double(0.4)
)
akPu4CaloJets.jetPtMin = 1.0
akPu4CaloJets.puPtMin = 8.0

# jets for deriving jec
ak4CaloJECJets = ak4CaloJets.clone(
    doSubEvent = cms.bool(True))

akPu4CaloJECJets = akPu4CaloJets.clone(
    doSubEvent = cms.bool(True))

# cloning jets for other radii
ak1CaloJets = ak4CaloJets.clone(rParam = 0.1)
ak2CaloJets = ak4CaloJets.clone(rParam = 0.2)
ak3CaloJets = ak4CaloJets.clone(rParam = 0.3)
ak5CaloJets = ak4CaloJets.clone(rParam = 0.5)
ak6CaloJets = ak4CaloJets.clone(rParam = 0.6)

akPu1CaloJets = akPu4CaloJets.clone(rParam = 0.1, puPtMin = 4.0)
akPu2CaloJets = akPu4CaloJets.clone(rParam = 0.2, puPtMin = 4.0)
akPu3CaloJets = akPu4CaloJets.clone(rParam = 0.3, puPtMin = 6.0)
akPu5CaloJets = akPu4CaloJets.clone(rParam = 0.5, puPtMin = 10.0)
akPu6CaloJets = akPu4CaloJets.clone(rParam = 0.6, puPtMin = 12.0)

ak1CaloJECJets = ak1CaloJets.clone(doSubEvent = cms.bool(True))
ak2CaloJECJets = ak2CaloJets.clone(doSubEvent = cms.bool(True))
ak3CaloJECJets = ak3CaloJets.clone(doSubEvent = cms.bool(True))
ak5CaloJECJets = ak5CaloJets.clone(doSubEvent = cms.bool(True))
ak6CaloJECJets = ak6CaloJets.clone(doSubEvent = cms.bool(True))

akPu1CaloJECJets = akPu1CaloJets.clone(doSubEvent = cms.bool(True))
akPu2CaloJECJets = akPu2CaloJets.clone(doSubEvent = cms.bool(True))
akPu3CaloJECJets = akPu3CaloJets.clone(doSubEvent = cms.bool(True))
akPu5CaloJECJets = akPu5CaloJets.clone(doSubEvent = cms.bool(True))
akPu6CaloJECJets = akPu6CaloJets.clone(doSubEvent = cms.bool(True))
