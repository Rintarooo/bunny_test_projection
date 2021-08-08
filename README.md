# DTAM implementation

```bash
docker run --rm -it --runtime=nvidia --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -v $HOME/coding/:/opt -e CUDA_DEBUGGER_SOFTWARE_PREEMPTION=1 rin/cuda:10.1-cudnn7-ubuntu18.04-opencv3.4.11-CC5.0-gdb
```
<br>

```bash
docker run --rm -it -v $HOME/coding/:/opt/coding/ -w /opt/coding/ codesignal/opencv:v9.4.0
docker run --rm -it -v $HOME/coding/:/opt/coding/ -w /opt/coding/ rin/python:opencv
```

```bash
gnuplot
```
<br>

```bash
gnuplot > 
set terminal png
set output "graph.png"
plot "./uv.txt" with dots
# plot "./uv.txt" with point ps 1
```
<br>

https://sci-tech.ksc.kwansei.ac.jp/~osaki/students/gnu/save_png.html

