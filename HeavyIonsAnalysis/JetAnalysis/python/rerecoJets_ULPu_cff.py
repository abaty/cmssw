import FWCore.ParameterSet.Config as cms

# import and alias calo jet producers
from HeavyIonsAnalysis.JetAnalysis.akCaloJets_cfi import (
    ak1CaloJets, akPu1CaloJets,
    ak2CaloJets, akPu2CaloJets,
    ak3CaloJets, akPu3CaloJets,
    ak4CaloJets, akPu4CaloJets,
    ak5CaloJets, akPu5CaloJets,
    ak6CaloJets, akPu6CaloJets)

# import and alias unlimited pu subtracted particle flow jet producers
from HeavyIonsAnalysis.JetAnalysis.akPFJets_cfi import (
    ak1PFJets, akULPu1PFJets, akCs1PFJets,
    ak2PFJets, akULPu2PFJets, akCs2PFJets,
    ak3PFJets, akULPu3PFJets, akCs3PFJets,
    ak4PFJets, akULPu4PFJets, akCs4PFJets,
    ak5PFJets, akULPu5PFJets, akCs5PFJets,
    ak6PFJets, akULPu6PFJets, akCs6PFJets)

akPu1PFJets = cms.EDAlias(akULPu1PFJets = cms.VPSet(cms.PSet(type = cms.string('recoBasicJets'))))
akPu2PFJets = cms.EDAlias(akULPu2PFJets = cms.VPSet(cms.PSet(type = cms.string('recoBasicJets'))))
akPu3PFJets = cms.EDAlias(akULPu3PFJets = cms.VPSet(cms.PSet(type = cms.string('recoBasicJets'))))
akPu4PFJets = cms.EDAlias(akULPu4PFJets = cms.VPSet(cms.PSet(type = cms.string('recoBasicJets'))))
akPu5PFJets = cms.EDAlias(akULPu5PFJets = cms.VPSet(cms.PSet(type = cms.string('recoBasicJets'))))
akPu6PFJets = cms.EDAlias(akULPu6PFJets = cms.VPSet(cms.PSet(type = cms.string('recoBasicJets'))))
