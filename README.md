# Projection of Bunny point clouds on image plane

<img src="https://user-images.githubusercontent.com/51239551/128713397-7efe6fd8-e29f-4f47-8294-96db4d9ad69e.png" width=350>
<img src="https://user-images.githubusercontent.com/51239551/128713326-49941311-d701-451f-bc8d-7d6a560cf7f3.png" width=500>

## Dataset
* camera pose(Rwc, tcw, P): [fountain-P11](https://documents.epfl.ch/groups/c/cv/cvlab-unit/www/data/multiview/denseMVS.html)
<br>

I generated `SfM_quality_evaluation/p11_tf.txt` using `SfM_quality_evaluation/gen_txt.py`.
<br>

* 3D point cloud: [Stanford Bunny](http://graphics.stanford.edu/data/3Dscanrep/)
<br>

I generated `bunny/data/bun000.xyz`, which contains only xyz coordinate.

## Usage
```bash
docker run --rm -it --runtime=nvidia --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" -v $HOME/coding/:/opt -e CUDA_DEBUGGER_SOFTWARE_PREEMPTION=1 rin/cuda:10.1-cudnn7-ubuntu18.04-opencv3.4.11-CC5.0-gdb
```
<br>

run cpp
```bash
docker run --rm -it -v $HOME/coding/:/opt/coding/ -w /opt/coding/ codesignal/opencv:v9.4.0
```
<br>


build, then execute program
```bash
./run.sh
./build/main
```
<br>

## plot projection point on image plane
plot uv.txt with `plot.cpp`
```bash
g++ plot.cpp
./a.out uv.txt
```
<br>

plot on terminal
```bash
gnuplot
gnuplot > set terminal png
gnuplot > set output "graph.png"
gnuplot > plot "./uv.txt" with dots
# plot "./uv.txt" with point ps 1
```
<br>

https://sci-tech.ksc.kwansei.ac.jp/~osaki/students/gnu/save_png.html

python plot of pose
```bash
docker run --rm -it -v $HOME/coding/:/opt/coding/ -w /opt/coding/ rin/python:opencv
```
