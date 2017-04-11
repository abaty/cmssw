#!/bin/bash
#README documentation
#This script uses the sed command to alter files, it is recommended you back up your files before using
#If you do not let this script run to completion, it might screw up your files, as it only 'undoes' all the changes it makes to your files at the very end
#This script runs the track reconstruction multiple times, and slowly adds on additional tracking iterations each time.
#It then evaluates the trackign efficiency for each iteration.
#The code expects to be run from RecoHI/HiTracking/config_tmp
#The code expects a Tracking efficiency repository similar to the one here: https://github.com/cmsHiTracking/TrackingCode/tree/master/HIRun2015Ana which outputs a file: trk.root
#This should be placed in the CMSSW /src/ directory, so that the code can find a config file at *CMSSW*/src/TrackingCode/HIRun2015Ana/test/*.py
#After this code is run, you can run a plotting macro like 'effByIterationPlot.C' to get plots from the multiple root files it produces. That plotting macro expects a /plots/ directory to dump the plots into
#
#the 'if false' and 'fi' can be commented in order to skip the reconstruction step and just run the efficiency step (if you want different cuts, etc.)
#one can speed up the code a bit by commenting out everything but hte trackign step in the HI_Reconstruction file in RecoHI/configuration
#End README

#part that runs reconstruction
if false; then #comment if you want to run reconstruction step
cmsRun step3_hi.py
cat ../python/HiTracking_cff.py\
| sed "s@\*hiLowPtQuadStep@#\*hiLowPtQuadStep@g"\
| sed "s@\*hiHighPtTripletStep@#\*hiHighPtTripletStep@g"\
| sed "s@\*hiDetachedQuadStep@#\*hiDetachedQuadStep@g"\
| sed "s@\*hiDetachedTripletStep@#\*hiDetachedTripletStep@g"\
| sed "s@\*hiLowPtTripletStep@#\*hiLowPtTripletStep@g"\
| sed "s@\*hiPixelPairStep@#\*hiPixelPairStep@g"\
 > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3.root@step3_0.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
cmsRun step3_hi.py

cat ../python/HiTracking_cff.py | sed "s@#\*hiLowPtQuadStep@\*hiLowPtQuadStep@g" > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3_0.root@step3_1.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
cmsRun step3_hi.py

cat ../python/HiTracking_cff.py | sed "s@#\*hiHighPtTripletStep@\*hiHighPtTripletStep@g" > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3_1.root@step3_2.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
cmsRun step3_hi.py

cat ../python/HiTracking_cff.py | sed "s@#\*hiDetachedQuadStep@\*hiDetachedQuadStep@g" > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3_2.root@step3_3.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
cmsRun step3_hi.py

cat ../python/HiTracking_cff.py | sed "s@#\*hiDetachedTripletStep@\*hiDetachedTripletStep@g" > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3_3.root@step3_4.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
cmsRun step3_hi.py

cat ../python/HiTracking_cff.py | sed "s@#\*hiLowPtTripletStep@\*hiLowPtTripletStep@g" > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3_4.root@step3_5.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
cmsRun step3_hi.py

cat ../python/HiTracking_cff.py | sed "s@#\*hiPixelPairStep@\*hiPixelPairStep@g" > ../python/tempTrk.py
mv ../python/tempTrk.py ../python/HiTracking_cff.py
cat step3_hi.py | sed "s@step3_5.root@step3.root@g" > tempStep3.py
mv tempStep3.py step3_hi.py
fi #comment if you want to run reconstruction step

#part that runs efficiency code
dir=../../../TrackingCode/HIRun2015Ana/test
cmsRun $dir/run_PbPb_cfg.py
cat $dir/run_PbPb_cfg.py | sed "s@step3.root@step3_0.root@g" | sed "s@trk.root@trk_0.root@g" > $dir/temp.py
mv $dir/temp.py $dir/run_PbPb_cfg.py

for i in `seq 0 4`;
do
cmsRun $dir/run_PbPb_cfg.py
cat $dir/run_PbPb_cfg.py | sed "s@step3_$i.root@step3_$(( $i+1 )).root@g" | sed "s@trk_$i.root@trk_$(( $i+1 )).root@g" > $dir/temp.py
mv $dir/temp.py $dir/run_PbPb_cfg.py
done

cmsRun $dir/run_PbPb_cfg.py
cat $dir/run_PbPb_cfg.py | sed "s@step3_5.root@step3.root@g" | sed "s@trk_5.root@trk.root@g" > $dir/temp.py
mv $dir/temp.py $dir/run_PbPb_cfg.py

mkdir plots
root -b -q effByIterationPlot.C 
