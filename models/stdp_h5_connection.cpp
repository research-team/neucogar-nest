/* Based on stdp_dopa_connection */

#include "stdp_h5_connection.h"
// Includes from nestkernel:
#include "common_synapse_properties.h"
#include "connector_model.h"
#include "event.h"
#include "kernel_manager.h"

// Includes from sli:
#include "dictdatum.h"

namespace nest
{
//
// Implementation of class STDPH5CommonProperties.
//

STDPH5CommonProperties::STDPH5CommonProperties()
  : CommonSynapseProperties()
  , vt_( 0 )
  , A_plus_( 1.5 )
  , A_minus_( 1.8 )
  , tau_plus_( 10.0 )
  , tau_c_( 2000.0 )
  , tau_n_( 1000.0 )
  , b_( 0.4 )
  , Wmin_( 0.0 )
  , Wmax_( 200.0 )
{
}

void
STDPH5CommonProperties::get_status( DictionaryDatum& d ) const
{
  CommonSynapseProperties::get_status( d );

  if ( vt_ != 0 )
    def< long >( d, "vt", vt_->get_gid() );
  else
    def< long >( d, "vt", -1 );

  def< double >( d, "A_plus", A_plus_ );
  def< double >( d, "A_minus", A_minus_ );
  def< double >( d, "tau_plus", tau_plus_ );
  def< double >( d, "tau_c", tau_c_ );
  def< double >( d, "tau_n", tau_n_ );
  def< double >( d, "b", b_ );
  def< double >( d, "Wmin", Wmin_ );
  def< double >( d, "Wmax", Wmax_ );
}

void
STDPH5CommonProperties::set_status( const DictionaryDatum& d, ConnectorModel& cm )
{
  CommonSynapseProperties::set_status( d, cm );

  long vtgid;
  if ( updateValue< long >( d, "vt", vtgid ) )
  {
     vt_ = dynamic_cast< volume_transmitter* >( kernel().node_manager.get_node(
      vtgid, kernel().vp_manager.get_thread_id() ) );

    if ( vt_ == 0 )
      throw BadProperty( "Serotonine source must be volume transmitter" );
  }

  updateValue< double >( d, "A_plus", A_plus_ );
  updateValue< double >( d, "A_minus", A_minus_ );
  updateValue< double >( d, "tau_plus", tau_plus_ );
  updateValue< double >( d, "tau_c", tau_c_ );
  updateValue< double >( d, "tau_n", tau_n_ );
  updateValue< double >( d, "b", b_ );
  updateValue< double >( d, "Wmin", Wmin_ );
  updateValue< double >( d, "Wmax", Wmax_ );
}

Node*
STDPH5CommonProperties::get_node()
{
  if ( vt_ == 0 )
    throw BadProperty( "No volume transmitter has been assigned to the serotonin synapse." );
  else
    return vt_;
}

} // of namespace nest
