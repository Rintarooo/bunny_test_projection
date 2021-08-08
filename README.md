# DTAM implementation

```bash
docker run --rm -it --runtime=nvidia --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -v $HOME/coding/:/opt -e CUDA_DEBUGGER_SOFTWARE_PREEMPTION=1 rin/cuda:10.1-cudnn7-ubuntu18.04-opencv3.4.11-CC5.0-gdb
```
<br>

```bash
docker run --rm -it -v $HOME/coding/:/opt/coding/ -w /opt/coding/ codesignal/opencv:v9.4.0
docker run --rm -it -v $HOME/coding/:/opt/coding/ -w /opt/coding/ rin/python:opencv
```

memory checker
```bash
cuda-memcheck ./build/main tf_stamp.txt
```
<br>


run `cuda-gdb`
```bash
cuda-gdb ./build/main
```
<br>

```bash
(cuda-gdb) b updateCostVolume
```
<br>

start program
```bash
(cuda-gdb) r tf_stamp.txt
```
<br>


if the error, `fatal:  All CUDA devices are used for display and cannot be used while debugging. (error code = CUDBG_ERROR_ALL_DEVICES_WATCHDOGGED(0x18)
` happens during debugging, set the following environment command
```bash
export CUDA_DEBUGGER_SOFTWARE_PREEMPTION=1
```
