#!/bin/bash

# echo 1 | sudo tee /proc/sys/kernel/perf_event_paranoid
# wget https://github.com/brendangregg/FlameGraph/archive/refs/heads/master.zip

perf record -g --call-graph fp -o perf.data $@
perf script -i perf.data > perf.script

FlameGraph-master/stackcollapse-perf.pl perf.script > perf.folded
FlameGraph-master/flamegraph.pl ./perf.folded > flamegraph.svg

rm perf.data perf.script perf.folded
