# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --conditions auto:phase1_2017_realistic -s RAW2DIGI,L1Reco,RECO,VALIDATION,DQM -n 2 --era Run2_2017 --eventcontent RECOSIM,MINIAODSIM,DQM --runUnscheduled --scenario HeavyIons --datatier GEN-SIM-RECO,MINIAODSIM,DQMIO --filein file:step2.root --fileout file:step3.root
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2017)


# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
#process.load('Configuration.StandardSequences.L1Reco_cff')
#process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.TFileService = cms.Service("TFileService", fileName = cms.string("histo.root") )

#process.Timing = cms.Service("Timing",
#  summaryOnly = cms.untracked.bool(False),
#  useJobReport = cms.untracked.bool(True)
#)
process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
    ignoreTotal = cms.untracked.int32(1)
)

#
# Input source
process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring('file:step2_17.root'),
    fileNames = cms.untracked.vstring(
#VR file
     'root://cms-xrd-global.cern.ch////store/hidata/HIRun2015/HITrackerVirginRaw/RAW/v1/000/262/495/00000/14634975-5493-E511-AC10-02163E0138B3.root',
#    MC below here
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_1.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_2.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_3.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_4.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_5.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_6.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_7.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_8.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_9.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_10.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_11.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_12.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_13.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_14.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_15.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_16.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_17.root',
#    'root://cms-xrd-global.cern.ch///store/user/abaty/TrackingPhase1_MC/Hydjet_10_0_X_v2_DIGI/Hydjet_5TeV/Hydjet_5TeV_CMSSW_10_0_X_v2_DIGI/171221_174146/0000/step2_18.root',
),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:2'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:step3_withChanges.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)


# Additional output definition

# Other statements
#comment from VR, not MB #MC
#process.mix.playback = True
#process.mix.digitizers = cms.PSet()
#for a in process.aliases: delattr(process, a)
#process.RandomNumberGeneratorService.restoreStateLabel=cms.untracked.string("randomEngineStateProducer")


from Configuration.AlCa.GlobalTag import GlobalTag
#for MC
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')
#for VR MB
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v13', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
#process.L1Reco_step = cms.Path(process.L1Reco)
#process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
#process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.RECOSIMoutput_step)
process.schedule = cms.Schedule(process.raw2digi_step)
#from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
#associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from SimGeneral.MixingModule.fullMixCustomize_cff
#from SimGeneral.MixingModule.fullMixCustomize_cff import setCrossingFrameOn 

#call to customisation function setCrossingFrameOn imported from SimGeneral.MixingModule.fullMixCustomize_cff
#process = setCrossingFrameOn(process)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
#from FWCore.ParameterSet.Utilities import convertToUnscheduled
#process=convertToUnscheduled(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
#from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
#process = customiseEarlyDelete(process)
# End adding early deletion
