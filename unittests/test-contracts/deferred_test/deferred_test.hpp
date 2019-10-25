/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>
#include <vector>

class [[ltnio::contract]] deferred_test : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void defercall( ltnio::name payer, uint64_t sender_id, ltnio::name contract, uint64_t payload );

   [[ltnio::action]]
   void delayedcall( ltnio::name payer, uint64_t sender_id, ltnio::name contract,
                     uint64_t payload, uint32_t delay_sec, bool replace_existing );

   [[ltnio::action]]
   void deferfunc( uint64_t payload );
   using deferfunc_action = ltnio::action_wrapper<"deferfunc"_n, &deferred_test::deferfunc>;

   [[ltnio::action]]
   void inlinecall( ltnio::name contract, ltnio::name authorizer, uint64_t payload );

   [[ltnio::action]]
   void fail();

   [[ltnio::on_notify("ltnio::onerror")]]
   void on_error( uint128_t sender_id, ltnio::ignore<std::vector<char>> sent_trx );
};
