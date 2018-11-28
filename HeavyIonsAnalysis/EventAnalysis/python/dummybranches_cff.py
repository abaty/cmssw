import FWCore.ParameterSet.Config as cms

def addDummyBranchesForHLT(process):
    process.hltanalysis.dummyBranches.extend([])
