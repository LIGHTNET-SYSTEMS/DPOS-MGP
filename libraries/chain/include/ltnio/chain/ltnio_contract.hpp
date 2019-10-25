/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/chain/types.hpp>
#include <ltnio/chain/contract_types.hpp>

namespace ltnio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_ltnio_newaccount(apply_context&);
   void apply_ltnio_updateauth(apply_context&);
   void apply_ltnio_deleteauth(apply_context&);
   void apply_ltnio_linkauth(apply_context&);
   void apply_ltnio_unlinkauth(apply_context&);

   /*
   void apply_ltnio_postrecovery(apply_context&);
   void apply_ltnio_passrecovery(apply_context&);
   void apply_ltnio_vetorecovery(apply_context&);
   */

   void apply_ltnio_setcode(apply_context&);
   void apply_ltnio_setabi(apply_context&);

   void apply_ltnio_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace ltnio::chain
