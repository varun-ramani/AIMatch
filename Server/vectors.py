import numpy as np

W_norm = None
vocab = None
ivocab = None

def setup(data_file_path: str):
    global W_norm, vocab, ivocab

    vectors = {}

    print("Opening vectors file... ", end="")
    # yield "Opening vectors file... "

    with open(data_file_path, 'r') as data_file:
        print("done")
        # yield "done\n"

        print("Loading file into vectors mapping... ", end="")
        # yield "Loading file into vectors mapping... "

        for line in data_file:
            line_tokens = line.split(' ')
            vectors[line_tokens[0]] = [float(value) for value in line_tokens[1:]]

        print("done")
        # yield "done\n"

    print("Generating vocabulary from vectors mapping... ", end="")
    # yield "Generating vocabulary from vectors mapping... "

    words = vectors.keys()
    vocab = {w: idx for idx, w in enumerate(words)}
    ivocab = {idx: w for idx, w in enumerate(words)}

    print("done")
    # yield "done\n"

    print("Normalizing vectors... ", end="")
    # yield "Normalizing vectors... "

    vector_dim = len(vectors[ivocab[0]])
    W = np.zeros((len(words), vector_dim))
    for word, v in vectors.items():
        if word == '<unk>':
            continue
        W[vocab[word], :] = v

    # normalize each word vector to unit variance
    W_norm = np.zeros(W.shape)
    d = (np.sum(W ** 2, 1) ** (0.5))
    W_norm = (W.T / d).T

    print("done")
    # yield "done\n"

def n_nearest_word(word: str, n_results: int):
    global W_norm, vocab, ivocab

    vecs = {}
    if word not in vocab:
        return None

    index = vocab[word]

    return n_nearest_vector(W_norm[index, :], n_results)

def n_nearest_vector(input_vector, n_results: int):
    global W_norm, vocab, ivocab

    vec_norm = np.zeros(input_vector.shape)
    d = (np.sum(input_vector ** 2,) ** (0.5))
    vec_norm = (input_vector.T / d).T

    dist = np.dot(W_norm, vec_norm.T)

    a = np.argsort(-dist)[1:n_results + 1]

    return [ivocab[word_index] for word_index in a]

def subtract(first: str, second: str, n_results: int):
    global W_norm, vocab, ivocab
    
    first_vector = W_norm[vocab[first], :]
    second_vector = W_norm[vocab[second], :]

    result_vector = first_vector - second_vector

    return n_nearest_vector(result_vector, n_results)

def add(first: str, second: str, n_results: int):
    global W_norm, vocab, ivocab
    
    first_vector = W_norm[vocab[first], :]
    second_vector = W_norm[vocab[second], :]

    result_vector = first_vector + second_vector

    return n_nearest_vector(result_vector, n_results)