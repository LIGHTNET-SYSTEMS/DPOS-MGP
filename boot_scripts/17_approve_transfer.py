import toml
import random
from utils import run, accounts, jsonArg, firstProducer, numProducers

config = toml.load('./config.toml')

def msigApprovePropose(proposer, proposalName):
    for i in range(firstProducer, firstProducer + numProducers):
        run(config['cleos']['path'] + 'multisig approve ' + proposer + ' ' + proposalName +
            jsonArg({'actor': accounts[i]['name'], 'permission': 'active'}) +
            '-p ' + accounts[i]['name'])

if __name__ == '__main__':
    msigApprovePropose(accounts[firstProducer]['name'], 'transfer')
