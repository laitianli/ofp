export ODP_PLATFORM_PARAMS="-v -a 0000:02:06.0 --file-prefix ofp"
./tcpperf -i 0 -p 5001 -f ./ofp.cli
