#!/usr/bin/bash

# can't complete simulation because:
#warn: instruction 'movntdq_Mo_Vo' unimplemented 
# and then:
#panic: Tried to read unmapped address 0x4bc68.
#PC: 0x449493, Instr:   ADD_R_M : ld   t1, DS:[rdx + 0x8]
#Memory Usage: 16891216 KBytes
#Program aborted at tick 31476236000
#--- BEGIN LIBC BACKTRACE ---
#/home/tongxian/Projects/umd-memsys.gem5-modified/build/X86/gem5.opt(_Z15print_backtracev+0x15)[0x7378a5]
#/home/tongxian/Projects/umd-memsys.gem5-modified/build/X86/gem5.opt(_Z12abortHandleri+0x36)[0x7416d6]

cd ../spec2006v1.1/ || exit
source ./shrc
cd - || exit

BENCH=450.soplex
BENCH_NAME=soplex
BEN_suffix=run/run_base_test_amd64-m64-gcc43-nn.0000
BEN_workingdir=$SPEC/benchspec/CPU2006/$BENCH/$BEN_suffix
EXEfile=${BENCH_NAME}_base.amd64-m64-gcc43-nn

GEM5root=/home/tongxian/Projects/umd-memsys.gem5-modified
OUT_dir_root=$GEM5root/gem5cpu2006result

DRAMSIM3_ini_dir=long-tREFI-configs/ddr3

#DRAMSIM3_ini_file=DDR4_8Gb_x8_1866.ini
for DRAMSIM3_ini_file in ${DRAMSIM3_ini_dir}/*.ini
do
	DRAMSIM3_ini_file=$(basename ${DRAMSIM3_ini_file} .ini)
	
	OUTdir=$OUT_dir_root/$BENCH_NAME/${DRAMSIM3_ini_file}-$(date +%FT%H%M%S)

	if [ ! -d "$OUTdir" ]; then
		echo "per-ini ${OUTdir} "
		echo "output directory dones't exitst, creating it."
		mkdir -p "$OUTdir"
	fi

	#screen -d -m \
	$GEM5root/build/X86/gem5.opt \
	--outdir="$OUTdir" \
	$GEM5root/configs/example/se.py \
	-c "$BEN_workingdir/$EXEfile" \
	-o "-m10000 ${BEN_workingdir}/test.mps" \
	--cpu-type=TimingSimpleCPU \
	--mem-type=DRAMsim3 \
	--dramsim3-ini=$DRAMSIM3_ini_dir/${DRAMSIM3_ini_file}.ini
	
	#--debug-flags=MemoryAccess \
	#-i "$SPEC/$BENCH/$BEN_suffix/inp.in" \
	#--debug-file=$BENCH.debugfile \
done