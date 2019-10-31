import toml
from utils import run, intToCurrency
config = toml.load('./config.toml')

def createTokens():
    run(config['cleos']['path'] + 'push action eosio.token create \'["eosio", "500000000.0000 %s"]\' -p eosio.token' % (config['general']['symbol']))
    run(config['cleos']['path'] + 'push action eosio.token issue \'["eosio", "%s", "Supply!"]\' -p eosio' % intToCurrency(2000000000000))

if __name__ == '__main__':
    createTokens()