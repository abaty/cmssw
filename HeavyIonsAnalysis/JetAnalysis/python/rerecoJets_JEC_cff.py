import FWCore.ParameterSet.Config as cms

# import and alias calo jet producers for JEC
from HeavyIonsAnalysis.JetAnalysis.akCaloJets_cfi import (
    ak1CaloJECJets, akPu1CaloJECJets,
    ak2CaloJECJets, akPu2CaloJECJets,
    ak3CaloJECJets, akPu3CaloJECJets,
    ak4CaloJECJets, akPu4CaloJECJets,
    ak5CaloJECJets, akPu5CaloJECJets,
    ak6CaloJECJets, akPu6CaloJECJets)

ak1CaloJets = cms.EDAlias(ak1CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
ak2CaloJets = cms.EDAlias(ak2CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
ak3CaloJets = cms.EDAlias(ak3CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
ak4CaloJets = cms.EDAlias(ak4CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
ak5CaloJets = cms.EDAlias(ak5CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
ak6CaloJets = cms.EDAlias(ak6CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))

akPu1CaloJets = cms.EDAlias(akPu1CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
akPu2CaloJets = cms.EDAlias(akPu2CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
akPu3CaloJets = cms.EDAlias(akPu3CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
akPu4CaloJets = cms.EDAlias(akPu4CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
akPu5CaloJets = cms.EDAlias(akPu5CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))
akPu6CaloJets = cms.EDAlias(akPu6CaloJECJets = cms.VPSet(cms.PSet(type = cms.string('recoCaloJets'))))

# import and alias particle flow jet producers for JEC
from HeavyIonsAnalysis.JetAnalysis.akPFJets_cfi import (
    ak1PFJECJets, akPu1PFJECJets, akCs1PFJECJets,
    ak2PFJECJets, akPu2PFJECJets, akCs2PFJECJets,
    ak3PFJECJets, akPu3PFJECJets, akCs3PFJECJets,
    ak4PFJECJets, akPu4PFJECJets, akCs4PFJECJets,
    ak5PFJECJets, akPu5PFJECJets, akCs5PFJECJets,
    ak6PFJECJets, akPu6PFJECJets, akCs6PFJECJets)

ak1PFJets = cms.EDAlias(ak1PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak2PFJets = cms.EDAlias(ak2PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak3PFJets = cms.EDAlias(ak3PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak4PFJets = cms.EDAlias(ak4PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak5PFJets = cms.EDAlias(ak5PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
ak6PFJets = cms.EDAlias(ak6PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))

akPu1PFJets = cms.EDAlias(akPu1PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akPu2PFJets = cms.EDAlias(akPu2PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akPu3PFJets = cms.EDAlias(akPu3PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akPu4PFJets = cms.EDAlias(akPu4PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akPu5PFJets = cms.EDAlias(akPu5PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akPu6PFJets = cms.EDAlias(akPu6PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))

akCs1PFJets = cms.EDAlias(akCs1PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akCs2PFJets = cms.EDAlias(akCs2PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akCs3PFJets = cms.EDAlias(akCs3PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akCs4PFJets = cms.EDAlias(akCs4PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akCs5PFJets = cms.EDAlias(akCs5PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
akCs6PFJets = cms.EDAlias(akCs6PFJECJets = cms.VPSet(cms.PSet(type = cms.string('recoPFJets'))))
