#!/usr/bin/env python3

from testUtils import Utils
from Cluster import Cluster
from WalletMgr import WalletMgr
from TestHelper import TestHelper

import random

Print=Utils.Print
errorExit=Utils.errorExit

args=TestHelper.parse_args({"-p","-n","-d","-s","--nodes-file","--seed"
                           ,"--dump-error-details","-v","--leave-running","--clean-run","--keep-logs"})

pnodes=args.p
topo=args.s
delay=args.d
total_nodes = pnodes if args.n < pnodes else args.n
debug=args.v
nodesFile=args.nodes_file
dontLaunch=nodesFile is not None
seed=args.seed
dontKill=args.leave_running
dumpErrorDetails=args.dump_error_details
killAll=args.clean_run
keepLogs=args.keep_logs

killWallet=not dontKill
killLtnInstances=not dontKill
if nodesFile is not None:
    killLtnInstances=False

Utils.Debug=debug
testSuccessful=False

random.seed(seed) # Use a fixed seed for repeatability.
cluster=Cluster(walletd=True)
walletMgr=WalletMgr(True)

try:
    cluster.setWalletMgr(walletMgr)

    if dontLaunch: # run test against remote cluster
        jsonStr=None
        with open(nodesFile, "r") as f:
            jsonStr=f.read()
        if not cluster.initializeNodesFromJson(jsonStr):
            errorExit("Failed to initilize nodes from Json string.")
        total_nodes=len(cluster.getNodes())

        walletMgr.killall(allInstances=killAll)
        walletMgr.cleanup()
        print("Stand up walletd")
        if walletMgr.launch() is False:
            errorExit("Failed to stand up kltnd.")
    else:
        cluster.killall(allInstances=killAll)
        cluster.cleanup()

        Print ("producing nodes: %s, non-producing nodes: %d, topology: %s, delay between nodes launch(seconds): %d" %
               (pnodes, total_nodes-pnodes, topo, delay))

        Print("Stand up cluster")
        if cluster.launch(pnodes=pnodes, totalNodes=total_nodes, topo=topo, delay=delay) is False:
            errorExit("Failed to stand up ltn cluster.")

        Print ("Wait for Cluster stabilization")
        # wait for cluster to start producing blocks
        if not cluster.waitOnClusterBlockNumSync(3):
            errorExit("Cluster never stabilized")

    accountsCount=total_nodes
    walletName="MyWallet-%d" % (random.randrange(10000))
    Print("Creating wallet %s if one doesn't already exist." % walletName)
    walletAccounts=[cluster.defproduceraAccount,cluster.defproducerbAccount]
    if not dontLaunch:
        walletAccounts.append(cluster.ltnioAccount)
    wallet=walletMgr.create(walletName, walletAccounts)
    if wallet is None:
        errorExit("Failed to create wallet %s" % (walletName))

    Print ("Populate wallet with %d accounts." % (accountsCount))
    if not cluster.populateWallet(accountsCount, wallet):
        errorExit("Wallet initialization failed.")

    defproduceraAccount=cluster.defproduceraAccount
    defproducerbAccount=cluster.defproducerbAccount
    ltnioAccount=cluster.ltnioAccount

    Print("Create accounts.")
    if not cluster.createAccounts(ltnioAccount):
        errorExit("Accounts creation failed.")

    Print("Spread funds and validate")
    if not cluster.spreadFundsAndValidate(10):
        errorExit("Failed to spread and validate funds.")

    print("Funds spread validated")

    if not dontKill:
        cluster.killall(allInstances=killAll)
    else:
        print("NOTE: Skip killing nodes, block log verification will be limited")

    cluster.compareBlockLogs()

    testSuccessful=True
finally:
    TestHelper.shutdown(cluster, walletMgr, testSuccessful, killLtnInstances, killWallet, keepLogs, killAll, dumpErrorDetails)

exit(0)
