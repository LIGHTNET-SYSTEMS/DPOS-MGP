/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */

#include <ltnio/chain/chain_id_type.hpp>
#include <ltnio/chain/exceptions.hpp>

namespace ltnio { namespace chain {

   void chain_id_type::reflector_init()const {
      LTN_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero" );
   }

} }  // namespace ltnio::chain

namespace fc {

   void to_variant(const ltnio::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, ltnio::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
