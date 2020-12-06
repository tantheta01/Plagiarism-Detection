import numpy as np
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.manifold import TSNE

def get_reduced_components(data):
	# print(len(data))
	maxlen = max(len(frequency_vector) for frequency_vector in data)
	for i in range(len(data)):
		sc = StandardScaler()
		data[i] = np.pad(np.array(data[i]), (0, maxlen-len(data[i])), 'constant', constant_values=0)

	sc = StandardScaler()
	data = sc.fit_transform(np.vstack(tuple(data)))
	# print(data.shape)
	# data = np.array(data)
	# print(data[0].size)

	if data.shape[0] < data.shape[1]:
		data = data[:, :data.shape[0]]

	if data.shape[1] > 30:
		pca = PCA(n_components=30)
		data = pca.fir_transform(data)

	return TSNE().fit_transform(data)

