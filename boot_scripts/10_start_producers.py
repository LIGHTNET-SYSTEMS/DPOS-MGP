import toml
from utils import startNode, firstProducer, numProducers, accounts
config = toml.load('./config.toml')

def startProducers(b, e):
    for i in range(b, e):
        startNode(i - b + 1, accounts[i])

if __name__ == '__main__':
    startProducers(firstProducer, firstProducer + numProducers)
    