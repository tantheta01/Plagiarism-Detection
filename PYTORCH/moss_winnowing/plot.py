import numpy as np
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.manifold import TSNE

def get_reduced_components(data):
	"""!
	@brief Calculates the lower dimentional embedding of the input data
	@param data List of lists containing the frequency vector of each fingerprint
	@return Array of shape (n, 2) 
	"""
	# print(len(data))
	maxlen = max(len(frequency_vector) for frequency_vector in data)
	for i in range(len(data)):
		sc = StandardScaler()
		data[i] = np.pad(np.array(data[i]), (0, maxlen-len(data[i])), 'constant', constant_values=0)

	sc = StandardScaler()
	data = np.vstack(tuple(data))
	# print(data[0,:2], "hi")
	# print(data[2,:], "hi")
	
	# print(data.shape)
	# data = np.array(data)
	# print(data[0].size)

	if data.shape[0] < data.shape[1]:
		data = data[:, :data.shape[0]]
	# print(data[0,:2], "hi")
	# print(data[2,:], "hi")
	if data.shape[1] > 15:
		pca = PCA(n_components=30)
		data = pca.fir_transform(data)
	# print(data[0,:2], "hi")
	# print(data[2,:], "hi")
	data = sc.fit_transform(data)
	# print(data[0,:2], "hi")
	# print(data[2,:], "hi")

	data = TSNE().fit_transform(data)
	# print(data[0,:2], "hi")
	# print(data[2,:], "hi")
	return data

