```bash
curl -O https://vision.in.tum.de/rgbd/dataset/freiburg1/rgbd_dataset_freiburg1_desk-groundtruth.txt
curl -O https://svncvpr.in.tum.de/cvpr-ros-pkg/trunk/rgbd_benchmark/rgbd_benchmark_tools/src/rgbd_benchmark_tools/associate.py
```
<br>

Since `associate.py` is written in Python2, if you use Python3, you should modify the following code in `associate.py`.
```bash
# first_keys.remove(a)
# second_keys.remove(b)
list(first_keys).remove(a)
list(second_keys).remove(b)
```
<br>

generate `pose_rgb.txt`
```bash
python associate.py rgbd_dataset_freiburg1_desk-groundtruth.txt rgb.txt > pose_rgb.txt
```