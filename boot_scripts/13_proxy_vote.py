import toml
import random
from utils import retry, firstProducer, numProducers, accounts, listProducers, sleep, vote

config = toml.load('./config.toml')

def proxyVote(b, e):
    vote(firstProducer, firstProducer + 1)
    proxy = accounts[firstProducer]['name']
    retry(config['cleos']['path'] + 'system regproxy ' + proxy)
    sleep(1.0)
    for i in range(b, e):
        voter = accounts[i]['name']
        retry(config['cleos']['path'] + 'system voteproducer proxy ' + voter + ' ' + proxy)

if __name__ == '__main__':
    proxyVote(0, 0 + config['general']['num_voters'])
    sleep(1)
    listProducers()
    