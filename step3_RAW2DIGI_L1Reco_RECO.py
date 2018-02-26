# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --eventcontent AODSIM --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1_HI --datatier AODSIM --conditions 75X_mcRun2_HeavyIon_v13 --step RAW2DIGI,L1Reco,RECO --scenario HeavyIons --data --era Run2_HI --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO2',eras.Run2_HI)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(50)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/afs/cern.ch/user/a/abaty/work/private/BaselineFollowerStudies/CMSSW_7_5_8/src/RecoLocalTracker/SiStripZeroSuppression/test/inputVR.root',
    #'/store/hidata/HIRun2015/HITrackerVirginRaw/RAW/v1/000/263/400/00000/40322926-4AA3-E511-95F7-02163E0146A8.root',
    #'file:/afs/cern.ch/work/a/abaty/public/HIPhoton40AndZ/82DD08B3-CD98-E511-8871-02163E0127B4.root'),
#    'file:hireco_RAW2DIGI_L1Reco_RECO_run262768_ls0203_280TevHF.root'),
    )
    #secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    fileName = cms.untracked.string('step3_nominal.root'),
    outputCommands = process.AODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v13', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)


#process.siStripZeroSuppression.Algorithms.CommonModeNoiseSubtractionMode = cms.string("Median")
#process.siStripZeroSuppression.Algorithms.DeltaCMThreshold = 5
#process.siStripZeroSuppression.Algorithms.CommonModeNoiseSubtractionMode = cms.string("Percentile")
#process.siStripZeroSuppression.Algorithms.Percentile = cms.double(33)
#process.siStripZeroSuppression.Algorithms.CommonModeNoiseSubtractionMode = cms.string("Median")
#process.siStripZeroSuppression.Algorithms.ForceNoRestore = True
#process.siStripZeroSuppression.Algorithms.PedestalSubtractionFedMode = cms.bool(True)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.AODSIMoutput_step)

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1_HI 

#call to customisation function customisePostLS1_HI imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1_HI(process)

# End of customisation functions
