// This file is generated by Simplicity Studio.  Please do not edit manually.
//
//

// This is a set of generated functions that parse the
// the incomming message, and call appropriate command handler.



#include PLATFORM_HEADER
#ifdef EZSP_HOST
// Includes needed for ember related functions for the EZSP host
#include "stack/include/error.h"
#include "stack/include/ember-types.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#include "app/util/ezsp/ezsp-utils.h"
#include "app/util/ezsp/serial-interface.h"
#else
// Includes needed for ember related functions for the EM250
#include "stack/include/ember.h"
#endif // EZSP_HOST

#include "app/framework/util/util.h"
#include "af-structs.h"
#include "call-command-handler.h"
#include "command-id.h"
#include "callback.h"

static EmberAfStatus status(bool wasHandled, bool clusterExists, bool mfgSpecific)
{
  if (wasHandled) {
    return EMBER_ZCL_STATUS_SUCCESS;
  } else if (clusterExists) {
    return EMBER_ZCL_STATUS_UNSUP_COMMAND;
  } else {
    return EMBER_ZCL_STATUS_UNSUPPORTED_CLUSTER;
  }
}

// Main command parsing controller.
EmberAfStatus emberAfClusterSpecificCommandParse(EmberAfClusterCommand *cmd)
{
  EmberAfStatus result = status(false, false, cmd->mfgSpecific);
  if (cmd->direction == (uint8_t)ZCL_DIRECTION_SERVER_TO_CLIENT
      && emberAfContainsClientWithMfgCode(cmd->apsFrame->destinationEndpoint,
                               cmd->apsFrame->clusterId,
                               cmd->mfgCode)) {
    switch (cmd->apsFrame->clusterId) {
    case 0x0000: // Multiple Manufacturer Clusters Present
      switch (cmd->mfgCode) {
      case 0x0000: // BASIC_CLUSTER Manufacturer: null
        result = status(false, true, cmd->mfgSpecific);
        break;

      default: 
        //Unrecognized mfg id, error status will apply
        break;
      }
    case ZCL_GREEN_POWER_CLUSTER_ID:
      result = emberAfGreenPowerClusterClientCommandParse(cmd);
      break;
    case ZCL_OPT_TUNNEL_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    default:
      // Unrecognized cluster ID, error status will apply.
      break;
    }
  } else if (cmd->direction == (uint8_t)ZCL_DIRECTION_CLIENT_TO_SERVER
             && emberAfContainsServerWithMfgCode(cmd->apsFrame->destinationEndpoint,
                                       cmd->apsFrame->clusterId,
                                       cmd->mfgCode)) {
    switch (cmd->apsFrame->clusterId) {
    case 0x0000: // Multiple Manufacturer Clusters Present
      switch (cmd->mfgCode) {
      case 0x0000: // BASIC_CLUSTER Manufacturer: null
        result = emberAfBasicClusterServerCommandParse(cmd);
        break;

      default: 
        //Unrecognized mfg id, error status will apply
        break;
      }
    case ZCL_IDENTIFY_CLUSTER_ID:
      result = emberAfIdentifyClusterServerCommandParse(cmd);
      break;
    case ZCL_ON_OFF_CLUSTER_ID:
      result = emberAfOnOffClusterServerCommandParse(cmd);
      break;
    case ZCL_THERMOSTAT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_FAN_CONTROL_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_ILLUM_MEASUREMENT_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_IAS_ZONE_CLUSTER_ID:
      result = emberAfIasZoneClusterServerCommandParse(cmd);
      break;
    case ZCL_DIAGNOSTICS_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    case ZCL_OPT_TUNNEL_CLUSTER_ID:
      result = status(false, true, cmd->mfgSpecific);
      break;
    default:
      // Unrecognized cluster ID, error status will apply.
      break;
    }
  }
  return result;
}

// Cluster: Basic, server
EmberAfStatus emberAfBasicClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_RESET_TO_FACTORY_DEFAULTS_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfBasicClusterResetToFactoryDefaultsCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: Identify, server
EmberAfStatus emberAfIdentifyClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_IDENTIFY_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint16_t identifyTime;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        identifyTime = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIdentifyClusterIdentifyCallback(identifyTime);
        break;
      }
    case ZCL_IDENTIFY_QUERY_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfIdentifyClusterIdentifyQueryCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: On/off, server
EmberAfStatus emberAfOnOffClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_OFF_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterOffCallback();
        break;
      }
    case ZCL_ON_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterOnCallback();
        break;
      }
    case ZCL_TOGGLE_COMMAND_ID:
      {
        // Command is fixed length: 0
        wasHandled = emberAfOnOffClusterToggleCallback();
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: Green Power, client
EmberAfStatus emberAfGreenPowerClusterClientCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_GP_NOTIFICATION_RESPONSE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t options;  // Ver.: since gp-1.0-09-5499-24
        uint32_t gpdSrcId;  // Ver.: since gp-1.0-09-5499-24
        uint8_t* gpdIeee;  // Ver.: since gp-1.0-09-5499-24
        uint8_t endpoint;  // Ver.: since gp-1.0-09-5499-24
        uint32_t gpdSecurityFrameCounter;  // Ver.: since gp-1.0-09-5499-24
        // Command is not a fixed length
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          options = 0xFF;
        } else {
          options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( !( (options & 0x0007) == 0x0000) || ( cmd->bufLen < payloadOffset + 4u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x0007) == 0x0000
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdSrcId = 0xFFFFFFFF;
        } else {
          gpdSrcId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 4u;
        }
        if ( !( (options & 0x0007) == 0x0002) || ( cmd->bufLen < payloadOffset + 8u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x0007) == 0x0002
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdIeee = NULL;
        } else {
          gpdIeee = cmd->buffer + payloadOffset;
          payloadOffset += 8u;
        }
        if ( !( (options & 0x0007) == 0x0002) || ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x0007) == 0x0002
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          endpoint = 0xFF;
        } else {
          endpoint = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 4u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdSecurityFrameCounter = 0xFFFFFFFF;
        } else {
          gpdSecurityFrameCounter = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfGreenPowerClusterGpNotificationResponseCallback(options,
                                                                            gpdSrcId,
                                                                            gpdIeee,
                                                                            endpoint,
                                                                            gpdSecurityFrameCounter);
        break;
      }
    case ZCL_GP_PAIRING_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint32_t options;  // Ver.: since gp-1.0-09-5499-24
        uint32_t gpdSrcId;  // Ver.: since gp-1.0-09-5499-24
        uint8_t* gpdIeee;  // Ver.: since gp-1.0-09-5499-24
        uint8_t endpoint;  // Ver.: since gp-1.0-09-5499-24
        uint8_t* sinkIeeeAddress;  // Ver.: since gp-1.0-09-5499-24
        uint16_t sinkNwkAddress;  // Ver.: since gp-1.0-09-5499-24
        uint16_t sinkGroupId;  // Ver.: since gp-1.0-09-5499-24
        uint8_t deviceId;  // Ver.: since gp-1.0-09-5499-24
        uint32_t gpdSecurityFrameCounter;  // Ver.: since gp-1.0-09-5499-24
        uint8_t* gpdKey;  // Ver.: since gp-1.0-09-5499-24
        uint16_t assignedAlias;  // Ver.: since gp-1.0-09-5499-24
        uint8_t groupcastRadius;  // Ver.: since gp-1.0-09-5499-24
        // Command is not a fixed length
        if ( ( cmd->bufLen < payloadOffset + 3u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          options = 0xFFFFFFFF;
        } else {
          options = emberAfGetInt24u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 3u;
        }
        if ( !( (options & 0x000007) == 0x000000) || ( cmd->bufLen < payloadOffset + 4u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000007) == 0x000000
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdSrcId = 0xFFFFFFFF;
        } else {
          gpdSrcId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 4u;
        }
        if ( !( (options & 0x000007) == 0x000002) || ( cmd->bufLen < payloadOffset + 8u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000007) == 0x000002
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdIeee = NULL;
        } else {
          gpdIeee = cmd->buffer + payloadOffset;
          payloadOffset += 8u;
        }
        if ( !( (options & 0x000007) == 0x000002) || ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000007) == 0x000002
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          endpoint = 0xFF;
        } else {
          endpoint = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( !( (options & 0x000010) == 0x000000 && ((options & 0x000060) == 0x000000 || (options & 0x000060) == 0x000060)) || ( cmd->bufLen < payloadOffset + 8u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000010) == 0x000000 && ((options & 0x000060) == 0x000000 || (options & 0x000060) == 0x000060)
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          sinkIeeeAddress = NULL;
        } else {
          sinkIeeeAddress = cmd->buffer + payloadOffset;
          payloadOffset += 8u;
        }
        if ( !( (options & 0x000010) == 0x000000 && ((options & 0x000060) == 0x000000 || (options & 0x000060) == 0x000060)) || ( cmd->bufLen < payloadOffset + 2u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000010) == 0x000000 && ((options & 0x000060) == 0x000000 || (options & 0x000060) == 0x000060)
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          sinkNwkAddress = 0xFFFF;
        } else {
          sinkNwkAddress = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 2u;
        }
        if ( !( (options & 0x000010) == 0x000000 && ((options & 0x000060) == 0x000020 || (options & 0x000060) == 0x000040)) || ( cmd->bufLen < payloadOffset + 2u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000010) == 0x000000 && ((options & 0x000060) == 0x000020 || (options & 0x000060) == 0x000040)
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          sinkGroupId = 0xFFFF;
        } else {
          sinkGroupId = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 2u;
        }
        if ( !( (options & 0x000008) == 0x000008 && (options & 0x000010) != 0x000010) || ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x000008) == 0x000008 && (options & 0x000010) != 0x000010
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          deviceId = 0xFF;
        } else {
          deviceId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( !( (options & 0x004000) == 0x004000) || ( cmd->bufLen < payloadOffset + 4u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x004000) == 0x004000
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdSecurityFrameCounter = 0xFFFFFFFF;
        } else {
          gpdSecurityFrameCounter = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 4u;
        }
        if ( !( (options & 0x008000) == 0x008000) || ( cmd->bufLen < payloadOffset + 16u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x008000) == 0x008000
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdKey = NULL;
        } else {
          gpdKey = cmd->buffer + payloadOffset;
          payloadOffset += 16u;
        }
        if ( !( (options & 0x010000) == 0x010000) || ( cmd->bufLen < payloadOffset + 2u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x010000) == 0x010000
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          assignedAlias = 0xFFFF;
        } else {
          assignedAlias = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 2u;
        }
        if ( !( (options & 0x020000) == 0x020000) || ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x020000) == 0x020000
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          groupcastRadius = 0xFF;
        } else {
          groupcastRadius = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfGreenPowerClusterGpPairingCallback(options,
                                                               gpdSrcId,
                                                               gpdIeee,
                                                               endpoint,
                                                               sinkIeeeAddress,
                                                               sinkNwkAddress,
                                                               sinkGroupId,
                                                               deviceId,
                                                               gpdSecurityFrameCounter,
                                                               gpdKey,
                                                               assignedAlias,
                                                               groupcastRadius);
        break;
      }
    case ZCL_GP_PROXY_COMMISSIONING_MODE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t options;  // Ver.: since gp-1.0-09-5499-24
        uint16_t commissioningWindow;  // Ver.: since gp-1.0-15-02014-011
        uint8_t channel;  // Ver.: since gp-1.0-09-5499-24
        // Command is not a fixed length
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          options = 0xFF;
        } else {
          options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( !( (options & 0x02) == 0x02) || ( cmd->bufLen < payloadOffset + 2u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x02) == 0x02
          // - it is present only in versions higher than: gp-1.0-15-02014-011
          commissioningWindow = 0xFFFF;
        } else {
          commissioningWindow = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 2u;
        }
        if ( !( (options & 0x10) == 0x10) || ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x10) == 0x10
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          channel = 0xFF;
        } else {
          channel = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfGreenPowerClusterGpProxyCommissioningModeCallback(options,
                                                                              commissioningWindow,
                                                                              channel);
        break;
      }
    case ZCL_GP_RESPONSE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t options;  // Ver.: since gp-1.0-09-5499-24
        uint16_t tempMasterShortAddress;  // Ver.: since gp-1.0-09-5499-24
        uint8_t tempMasterTxChannel;  // Ver.: since gp-1.0-09-5499-24
        uint32_t gpdSrcId;  // Ver.: since gp-1.0-09-5499-24
        uint8_t* gpdIeee;  // Ver.: since gp-1.0-09-5499-24
        uint8_t endpoint;  // Ver.: always
        uint8_t gpdCommandId;  // Ver.: since gp-1.0-09-5499-24
        uint8_t* gpdCommandPayload;  // Ver.: always
        // Command is not a fixed length
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          options = 0xFF;
        } else {
          options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 2u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          tempMasterShortAddress = 0xFFFF;
        } else {
          tempMasterShortAddress = emberAfGetInt16u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 2u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          tempMasterTxChannel = 0xFF;
        } else {
          tempMasterTxChannel = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( !( (options & 0x07) == 0x00) || ( cmd->bufLen < payloadOffset + 4u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x07) == 0x00
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdSrcId = 0xFFFFFFFF;
        } else {
          gpdSrcId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 4u;
        }
        if ( !( (options & 0x07) == 0x02) || ( cmd->bufLen < payloadOffset + 8u)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x07) == 0x02
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdIeee = NULL;
        } else {
          gpdIeee = cmd->buffer + payloadOffset;
          payloadOffset += 8u;
        }
        if ( !( (options & 0x07) == 0x02)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x07) == 0x02
          endpoint = 0xFF;
        } else {
          endpoint = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( ( cmd->bufLen < payloadOffset + 1u)) {
          // Argument is not always present:
          // - it is present only in versions higher than: gp-1.0-09-5499-24
          gpdCommandId = 0xFF;
        } else {
          gpdCommandId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if (cmd->bufLen < payloadOffset + emberAfStringLength(cmd->buffer + payloadOffset) + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        gpdCommandPayload = emberAfGetString(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfGreenPowerClusterGpResponseCallback(options,
                                                                tempMasterShortAddress,
                                                                tempMasterTxChannel,
                                                                gpdSrcId,
                                                                gpdIeee,
                                                                endpoint,
                                                                gpdCommandId,
                                                                gpdCommandPayload);
        break;
      }
    case ZCL_GP_SINK_TABLE_RESPONSE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t status;  // Ver.: always
        uint8_t totalNumberofNonEmptySinkTableEntries;  // Ver.: always
        uint8_t startIndex;  // Ver.: always
        uint8_t sinkTableEntriesCount;  // Ver.: always
        uint8_t* sinkTableEntries;  // Ver.: always
        // Command is fixed length: 4
        if (cmd->bufLen < payloadOffset + 4u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        status = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        totalNumberofNonEmptySinkTableEntries = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        startIndex = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        sinkTableEntriesCount = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        sinkTableEntries = cmd->buffer + payloadOffset;
        wasHandled = emberAfGreenPowerClusterGpSinkTableResponseCallback(status,
                                                                         totalNumberofNonEmptySinkTableEntries,
                                                                         startIndex,
                                                                         sinkTableEntriesCount,
                                                                         sinkTableEntries);
        break;
      }
    case ZCL_GP_PROXY_TABLE_REQUEST_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t options;  // Ver.: always
        uint32_t gpdSrcId;  // Ver.: always
        uint8_t* gpdIeee;  // Ver.: always
        uint8_t endpoint;  // Ver.: always
        uint8_t index;  // Ver.: always
        // Command is not a fixed length
        if (cmd->bufLen < payloadOffset + 1u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        options = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        if ( !( ((options & 0x18) == 0x00) && ((options & 0x07) == 0x00))) {
          // Argument is not always present:
          // - it is conditionally present based on expression: ((options & 0x18) == 0x00) && ((options & 0x07) == 0x00)
          gpdSrcId = 0xFFFFFFFF;
        } else {
          gpdSrcId = emberAfGetInt32u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 4u;
        }
        if ( !( ((options & 0x18) == 0x00) && ((options & 0x07) == 0x02))) {
          // Argument is not always present:
          // - it is conditionally present based on expression: ((options & 0x18) == 0x00) && ((options & 0x07) == 0x02)
          gpdIeee = NULL;
        } else {
          gpdIeee = cmd->buffer + payloadOffset;
          payloadOffset += 8u;
        }
        if ( !( (options & 0x07) == 0x02)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x07) == 0x02
          endpoint = 0xFF;
        } else {
          endpoint = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
          payloadOffset += 1u;
        }
        if ( !( (options & 0x18) == 0x08)) {
          // Argument is not always present:
          // - it is conditionally present based on expression: (options & 0x18) == 0x08
          index = 0xFF;
        } else {
          index = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        }
        wasHandled = emberAfGreenPowerClusterGpProxyTableRequestCallback(options,
                                                                         gpdSrcId,
                                                                         gpdIeee,
                                                                         endpoint,
                                                                         index);
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}

// Cluster: IAS Zone, server
EmberAfStatus emberAfIasZoneClusterServerCommandParse(EmberAfClusterCommand *cmd)
{
  bool wasHandled = false;
  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
    case ZCL_ZONE_ENROLL_RESPONSE_COMMAND_ID:
      {
        uint16_t payloadOffset = cmd->payloadStartIndex;
        uint8_t enrollResponseCode;  // Ver.: always
        uint8_t zoneId;  // Ver.: always
        // Command is fixed length: 2
        if (cmd->bufLen < payloadOffset + 2u) { return EMBER_ZCL_STATUS_MALFORMED_COMMAND; }
        enrollResponseCode = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        payloadOffset += 1u;
        zoneId = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);
        wasHandled = emberAfIasZoneClusterZoneEnrollResponseCallback(enrollResponseCode,
                                                                     zoneId);
        break;
      }
    default:
      {
        // Unrecognized command ID, error status will apply.
        break;
      }
    }
  }
  return status(wasHandled, true, cmd->mfgSpecific);
}
