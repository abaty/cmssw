import FWCore.ParameterSet.Config as cms

from RecoHI.HiJetAlgos.HiRecoPFJets_cff import PFTowers

HIPFTowers = PFTowers.clone(
    src = cms.InputTag('particleFlowTmp'))

# kt jets for rho estimators
from RecoJets.JetProducers.kt4PFJets_cfi import kt4PFJets
from RecoHI.HiJetAlgos.HiRecoPFJets_cff import kt4PFJetsForRho

kt4PFJets.doAreaFastjet = True
kt4PFJets.jetPtMin      = cms.double(0.0)
kt4PFJets.GhostArea     = cms.double(0.005)

kt4HIPFJets = kt4PFJets.clone(
    src = cms.InputTag('particleFlowTmp'))

kt4HIPFJetsForRho = kt4PFJetsForRho.clone(
    src = cms.InputTag('particleFlowTmp'))
