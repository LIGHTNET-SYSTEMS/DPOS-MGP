import toml
import random
from utils import retry, firstProducer, accounts

config = toml.load('./config.toml')

def msigExecTransfer(proposer, proposalName):
    retry(config['cleos']['path'] + 'multisig exec ' + proposer + ' ' + proposalName + ' -p ' + proposer)

if __name__ == '__main__':
    msigExecTransfer(accounts[firstProducer]['name'], 'transfer')
