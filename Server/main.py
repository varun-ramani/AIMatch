from sys import argv
from flask import Flask, app, request
from flask.wrappers import Response
import vectors
from threading import Thread
import time

app = Flask(__name__)

vectors.setup('data-file.txt')

def parse_result(result):
    print(result)
    if result[1] > 0.5:
        return result[0]
    else:
        return "FAIL"

@app.route('/nearest')
def nearest():
    word = request.args.get('word', None)

    if word == None:
        return "Error: no word supplied."

    return parse_result(vectors.n_nearest_word(word, 1)[0])

@app.route('/subtract')
def subtract():
    first = request.args.get('first', None)
    second = request.args.get('second', None)

    if first == None or second == None:
        return "Error: Need to supply two words"

    return parse_result(vectors.subtract(first, second, 1)[0])


@app.route('/add')
def add():
    first = request.args.get('first', None)
    second = request.args.get('second', None)

    if first == None or second == None:
        return "Error: Need to supply two words"

    return parse_result(vectors.add(first, second, 1)[0])

@app.route('/analogy')
def analogy():
    first = request.args.get('first', None)
    second = request.args.get('second', None)
    third = request.args.get('third', None)

    if first == None or second == None or third == None:
        return "Error: Need to supply three words"

    return parse_result(vectors.analogy(first, second, third, 1)[0])

if __name__ == "__main__":
    app.run()