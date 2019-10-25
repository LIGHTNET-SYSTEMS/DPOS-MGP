/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#include "noop.hpp"

using namespace ltnio;

void noop::anyaction( name                       from,
                      const ignore<std::string>& type,
                      const ignore<std::string>& data )
{
   require_auth( from );
}
