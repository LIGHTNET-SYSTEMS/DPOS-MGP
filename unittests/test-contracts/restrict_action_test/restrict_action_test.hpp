/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] restrict_action_test : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void noop( );

   [[ltnio::action]]
   void sendinline( ltnio::name authorizer );

   [[ltnio::action]]
   void senddefer( ltnio::name authorizer, uint32_t senderid );


   [[ltnio::action]]
   void notifyinline( ltnio::name acctonotify, ltnio::name authorizer );

   [[ltnio::action]]
   void notifydefer( ltnio::name acctonotify, ltnio::name authorizer, uint32_t senderid );

   [[ltnio::on_notify("testacc::notifyinline")]]
   void on_notify_inline( ltnio::name acctonotify, ltnio::name authorizer );

   [[ltnio::on_notify("testacc::notifydefer")]]
   void on_notify_defer( ltnio::name acctonotify, ltnio::name authorizer, uint32_t senderid );
};
