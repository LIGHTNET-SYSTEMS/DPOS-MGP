/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once
#include <ltnio/chain/transaction.hpp>
#include <ltnio/chain/types.hpp>
#include <boost/asio/io_context.hpp>
#include <future>

namespace boost { namespace asio {
   class thread_pool;
}}

namespace ltnio { namespace chain {

class transaction_metadata;
using transaction_metadata_ptr = std::shared_ptr<transaction_metadata>;
using signing_keys_future_value_type = std::tuple<chain_id_type, fc::microseconds, flat_set<public_key_type>>;
using signing_keys_future_type = std::shared_future<signing_keys_future_value_type>;
using recovery_keys_type = std::pair<fc::microseconds, const flat_set<public_key_type>&>;

/**
 *  This data structure should store context-free cached data about a transaction such as
 *  packed/unpacked/compressed and recovered keys
 */
class transaction_metadata {
   public:
      transaction_id_type                                        id;
      transaction_id_type                                        signed_id;
      packed_transaction_ptr                                     packed_trx;
      signing_keys_future_type                                   signing_keys_future;
      bool                                                       accepted = false;
      bool                                                       implicit = false;
      bool                                                       scheduled = false;

      transaction_metadata() = delete;
      transaction_metadata(const transaction_metadata&) = delete;
      transaction_metadata(transaction_metadata&&) = delete;
      transaction_metadata operator=(transaction_metadata&) = delete;
      transaction_metadata operator=(transaction_metadata&&) = delete;

      explicit transaction_metadata( const signed_transaction& t, packed_transaction::compression_type c = packed_transaction::none )
      :id(t.id()), packed_trx(std::make_shared<packed_transaction>(t, c)) {
         //raw_packed = fc::raw::pack( static_cast<const transaction&>(trx) );
         signed_id = digest_type::hash(*packed_trx);
      }

      explicit transaction_metadata( const packed_transaction_ptr& ptrx )
      :id(ptrx->id()), packed_trx(ptrx) {
         //raw_packed = fc::raw::pack( static_cast<const transaction&>(trx) );
         signed_id = digest_type::hash(*packed_trx);
      }

      // must be called from main application thread
      static signing_keys_future_type
      start_recover_keys( const transaction_metadata_ptr& mtrx, boost::asio::io_context& thread_pool,
                          const chain_id_type& chain_id, fc::microseconds time_limit );

      // start_recover_keys must be called first
      recovery_keys_type recover_keys( const chain_id_type& chain_id );
};

} } // ltnio::chain
