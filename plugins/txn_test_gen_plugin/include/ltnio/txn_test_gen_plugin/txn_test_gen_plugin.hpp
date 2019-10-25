/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once
#include <appbase/application.hpp>
#include <ltnio/http_plugin/http_plugin.hpp>
#include <ltnio/chain_plugin/chain_plugin.hpp>

namespace ltnio {

using namespace appbase;

class txn_test_gen_plugin : public appbase::plugin<txn_test_gen_plugin> {
public:
   txn_test_gen_plugin();
   ~txn_test_gen_plugin();

   APPBASE_PLUGIN_REQUIRES((http_plugin)(chain_plugin))
   virtual void set_program_options(options_description&, options_description& cfg) override;
 
   void plugin_initialize(const variables_map& options);
   void plugin_startup();
   void plugin_shutdown();

private:
   std::unique_ptr<struct txn_test_gen_plugin_impl> my;
};

}
