import FWCore.ParameterSet.Config as cms

from RecoJets.JetProducers.PFJetParameters_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

akFilter4PFJets = cms.EDProducer(
    "FastjetJetProducer",
    PFJetParameters,
    AnomalousCellParameters,
    jetAlgorithm        = cms.string("AntiKt"),
    rParam              = cms.double(0.4),
    useFiltering        = cms.bool(True),
    nFilt               = cms.int32(4),
    rFilt               = cms.double(0.15),
    useExplicitGhosts   = cms.bool(True),
    writeCompound       = cms.bool(True),
    jetCollInstanceName = cms.string("SubJets")
)

akSoftDrop4PFJets = cms.EDProducer(
    "FastjetJetProducer",
    PFJetParameters,
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

akSoftDrop4HIPFJets = cms.EDProducer(
    "SoftDropJetProducer",
    PFJetParameters,
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

akCsSoftDrop4PFJets = akSoftDrop4PFJets.clone(
    src = cms.InputTag("akCs4PFJets", "pfParticlesCs"))

akCsSoftDropZ05B154PFJets = akCsSoftDrop4PFJets.clone(
    zcut = cms.double(0.5), beta = cms.double(1.5))

akCsSoftDrop4HIPFJets = akSoftDrop4HIPFJets.clone(
    src = cms.InputTag("akCs4PFJets", "pfParticlesCs"))

akCsSoftDropZ05B154HIPFJets = akCsSoftDrop4HIPFJets.clone(
    zcut = cms.double(0.5), beta = cms.double(1.5))

akSoftDrop1PFJets = akSoftDrop4PFJets.clone(rParam = 0.1)
akSoftDrop2PFJets = akSoftDrop4PFJets.clone(rParam = 0.2)
akSoftDrop3PFJets = akSoftDrop4PFJets.clone(rParam = 0.3)
akSoftDrop5PFJets = akSoftDrop4PFJets.clone(rParam = 0.5)
akSoftDrop6PFJets = akSoftDrop4PFJets.clone(rParam = 0.6)

akCsSoftDrop1PFJets = akCsSoftDrop4PFJets.clone(rParam = 0.1)
akCsSoftDrop2PFJets = akCsSoftDrop4PFJets.clone(rParam = 0.2)
akCsSoftDrop3PFJets = akCsSoftDrop4PFJets.clone(rParam = 0.3)
akCsSoftDrop5PFJets = akCsSoftDrop4PFJets.clone(rParam = 0.5)
akCsSoftDrop6PFJets = akCsSoftDrop4PFJets.clone(rParam = 0.6)

akCsSoftDropZ05B151PFJets = akCsSoftDropZ05B154PFJets.clone(rParam = 0.1)
akCsSoftDropZ05B152PFJets = akCsSoftDropZ05B154PFJets.clone(rParam = 0.2)
akCsSoftDropZ05B153PFJets = akCsSoftDropZ05B154PFJets.clone(rParam = 0.3)
akCsSoftDropZ05B155PFJets = akCsSoftDropZ05B154PFJets.clone(rParam = 0.5)
akCsSoftDropZ05B156PFJets = akCsSoftDropZ05B154PFJets.clone(rParam = 0.6)

akCsSoftDrop1HIPFJets = akCsSoftDrop4HIPFJets.clone(rParam = 0.1)
akCsSoftDrop2HIPFJets = akCsSoftDrop4HIPFJets.clone(rParam = 0.2)
akCsSoftDrop3HIPFJets = akCsSoftDrop4HIPFJets.clone(rParam = 0.3)
akCsSoftDrop5HIPFJets = akCsSoftDrop4HIPFJets.clone(rParam = 0.5)
akCsSoftDrop6HIPFJets = akCsSoftDrop4HIPFJets.clone(rParam = 0.6)

akCsSoftDropZ05B151HIPFJets = akCsSoftDropZ05B154HIPFJets.clone(rParam = 0.1)
akCsSoftDropZ05B152HIPFJets = akCsSoftDropZ05B154HIPFJets.clone(rParam = 0.2)
akCsSoftDropZ05B153HIPFJets = akCsSoftDropZ05B154HIPFJets.clone(rParam = 0.3)
akCsSoftDropZ05B155HIPFJets = akCsSoftDropZ05B154HIPFJets.clone(rParam = 0.5)
akCsSoftDropZ05B156HIPFJets = akCsSoftDropZ05B154HIPFJets.clone(rParam = 0.6)
