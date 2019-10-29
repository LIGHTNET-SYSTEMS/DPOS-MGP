import toml
import random
from utils import run, intToCurrency

config = toml.load('./config.toml')

def unstakeFunds(account, receiver, net_amount, cpu_amount):
    run(config['cleos']['path'] + 'system undelegatebw %s %s "%s" "%s" -p %s' % (account, receiver, intToCurrency(net_amount), intToCurrency(cpu_amount), account))

if __name__ == '__main__':
    unstakeFunds("eosio.team", 'eosio.team', 2_000_000_0000, 2_000_000_0000)
