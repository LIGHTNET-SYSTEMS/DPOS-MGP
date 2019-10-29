import toml
import random
from utils import run, accounts, jsonArg, intToCurrency, firstProducer, numProducers

config = toml.load('./config.toml')

def msigPropose(proposer, proposalName, proposition):
    requestedPermissions = []
    for i in range(firstProducer, firstProducer + numProducers):
        requestedPermissions.append({'actor': accounts[i]['name'], 'permission': 'active'})
    trxPermissions = [{'actor': 'eosio.market', 'permission': 'active'}]
    run(config['cleos']['path'] + 'multisig propose ' + proposalName + jsonArg(requestedPermissions) + 
        jsonArg(trxPermissions) + 'eosio.token transfer' + jsonArg(proposition) + ' -p ' + proposer)

if __name__ == '__main__':
    proposition = {"from":"eosio.market", 
        "to": accounts[0]['name'], 
        "quantity": intToCurrency(250000), 
        "memo":"Pay market insentives"}
    msigPropose(accounts[firstProducer]['name'], 'transfer', proposition)
