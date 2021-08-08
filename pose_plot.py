# https://qiita.com/moizumi99/items/b0a2c84896ce5e0deb8a
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

def load_problem(path):
	global points
	points = []
	with open(path) as f:
		0 = tuple(map(lambda z: int(z), f.readline().strip().split()))
		for i in range(2):
			skip = f.readline()

		for i in range(11):
			vals = tuple(map(lambda z: float(z), f.readline().strip().split()))
			point = vals[-3:]
			points.append(point)
		points = np.array(points).T


if __name__ == '__main__':
	# load_problem("tf_stamp.txt")
	load_problem("SfM_quality_evaluation/p11_tf.txt")
	print(points)
	fig = plt.figure()
	ax = Axes3D(fig)
	ax.scatter3D(points[0], points[1], points[2])
	# show()
	fig.savefig("pose.png")