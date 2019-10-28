import toml
from utils import run, systemAccounts
config = toml.load('./config.toml')

def createSystemAccounts():
    for a in systemAccounts:
        run(config['cleos']['path'] + 'create account eosio ' + a + ' ' + config['keosd']['public_key'])

if __name__ == '__main__':
    createSystemAccounts()