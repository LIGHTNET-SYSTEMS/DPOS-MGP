/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

namespace ltnio {
   namespace internal_use_do_not_use {
      extern "C" {
         __attribute__((ltnio_wasm_import))
         uint64_t get_sender();
      }
   }
}

namespace ltnio {
   name get_sender() {
      return name( internal_use_do_not_use::get_sender() );
   }
}

class [[ltnio::contract]] get_sender_test : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void assertsender( ltnio::name expected_sender );
   using assertsender_action = ltnio::action_wrapper<"assertsender"_n, &get_sender_test::assertsender>;

   [[ltnio::action]]
   void sendinline( ltnio::name to, ltnio::name expected_sender );

   [[ltnio::action]]
   void notify( ltnio::name to, ltnio::name expected_sender, bool send_inline );

   // ltnio.cdt 1.6.1 has a problem with "*::notify" so hardcode to tester1 for now.
   // TODO: Change it back to "*::notify" when the bug is fixed in ltnio.cdt.
   [[ltnio::on_notify("tester1::notify")]]
   void on_notify( ltnio::name to, ltnio::name expected_sender, bool send_inline );

};
