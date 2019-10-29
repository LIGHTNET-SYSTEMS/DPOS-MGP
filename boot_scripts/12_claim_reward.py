import toml
import random
from utils import getJsonOutput 
config = toml.load('./config.toml')

def claimReawards():
    table = getJsonOutput(config['cleos']['path'] + 'get table eosio eosio producers -l 100')
    times = []
    for row in table['rows']:
        if row['unpaid_blocks'] and not row['last_claim_time']:
            times.append(getJsonOutput(config['cleos']['path'] + 'system claimrewards -j ' + row['owner'])['processed']['elapsed'])
    print('Elapsed time for claimrewards:', times)


if __name__ == '__main__':
    claimReawards()