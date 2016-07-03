
#ifndef _NET_PROTOCOL_H_
#define _NET_PROTOCOL_H_

typedef enum {
	HSB_CMD_BOX_DISCOVER = 0x8801,
	HSB_CMD_BOX_DISCOVER_RESP = 0x8802,
	HSB_CMD_GET_DEVS = 0x8811,
	HSB_CMD_GET_DEVS_RESP = 0x8812,
	HSB_CMD_GET_INFO = 0x8813,
	HSB_CMD_GET_INFO_RESP = 0x8814,
	HSB_CMD_SET_CONFIG = 0x8815,
	HSB_CMD_GET_CONFIG = 0x8816,
	HSB_CMD_GET_CONFIG_RESP = 0x8817,
	HSB_CMD_DEV_ONLINE = 0x881A,
	HSB_CMD_GET_STATUS = 0x8821,
	HSB_CMD_GET_STATUS_RESP = 0x8822,
	HSB_CMD_SET_STATUS = 0x8823,
	HSB_CMD_SET_CHANNEL = 0x8824,
	HSB_CMD_DEL_CHANNEL = 0x8825,
	HSB_CMD_SWITCH_CHANNEL = 0x8826,
	HSB_CMD_GET_TIMER = 0x8831,
	HSB_CMD_GET_TIMER_RESP = 0x8832,
	HSB_CMD_SET_TIMER = 0x8833,
	HSB_CMD_DEL_TIMER = 0x8834,
	HSB_CMD_GET_DELAY = 0x8841,
	HSB_CMD_GET_DELAY_RESP = 0x8842,
	HSB_CMD_SET_DELAY = 0x8843,
	HSB_CMD_DEL_DELAY = 0x8844,
	HSB_CMD_GET_LINKAGE = 0x8851,
	HSB_CMD_GET_LINKAGE_RESP = 0x8852,
	HSB_CMD_SET_LINKAGE = 0x8853,
	HSB_CMD_DEL_LINKAGE = 0x8854,
	HSB_CMD_PROBE_DEV = 0x8861,
	HSB_CMD_ADD_DEV = 0x8862,
	HSB_CMD_EVENT = 0x8871,
	HSB_CMD_DO_ACTION = 0x8881,
	HSB_CMD_RESULT = 0x88A1,
	HSB_CMD_LAST,
} HSB_CMD_T;

#define HSB_CMD_VALID(x)	(x >= HSB_CMD_BOX_DISCOVER && x < HSB_CMD_LAST)

typedef enum {
	HSB_DEV_TYPE_PLUG = 0,
	HSB_DEV_TYPE_SENSOR,
	HSB_DEV_TYPE_REMOTE_CTL,
	HSB_DEV_TYPE_CC9201,
	HSB_DEV_TYPE_GREE_AC,
	HSB_DEV_TYPE_LAST,
} HSB_DEV_TYPE_T;

typedef enum {
	HSB_EVT_TYPE_STATUS_UPDATED = 0,
	HSB_EVT_TYPE_DEV_UPDATED,
	HSB_EVT_TYPE_SENSOR_TRIGGERED,
	HSB_EVT_TYPE_SENSOR_RECOVERED,
	HSB_EVT_TYPE_MODE_CHANGED,
	HSB_EVT_TYPE_IR_KEY,
} HSB_EVT_TYPE_T;

typedef enum {
	HSB_DEV_UPDATED_TYPE_OFFLINE = 0,
	HSB_DEV_UPDATED_TYPE_NEW_ADD,
	HSB_DEV_UPDATED_TYPE_ONLINE,
} HSB_DEV_UPDATED_TYPE_T;


typedef enum {
	HSB_DRV_ID_CJ_WIFI = 1,
	HSB_DRV_ID_CJ_ZIGBEE,
	HSB_DRV_ID_IR,
	HSB_DRV_ID_LAST,
} HSB_DRV_ID_T;

typedef enum {
	HSB_TV_STATUS_CHANNEL = 0,
	HSB_TV_STATUS_LAST,
} HSB_TV_STATUS_T;

typedef enum {
	HSB_TV_ACTION_ON_OFF = 0,
	HSB_TV_ACTION_ADD_VOL,
	HSB_TV_ACTION_DEC_VOL,
	HSB_TV_ACTION_OK,
	HSB_TV_ACTION_BACK,
	HSB_TV_ACTION_LEFT,
	HSB_TV_ACTION_RIGHT,
	HSB_TV_ACTION_UP,
	HSB_TV_ACTION_DOWN,
	HSB_TV_ACTION_MUTE,
	HSB_TV_ACTION_KEY_0,
	HSB_TV_ACTION_KEY_1,
	HSB_TV_ACTION_KEY_2,
	HSB_TV_ACTION_KEY_3,
	HSB_TV_ACTION_KEY_4,
	HSB_TV_ACTION_KEY_5,
	HSB_TV_ACTION_KEY_6,
	HSB_TV_ACTION_KEY_7,
	HSB_TV_ACTION_KEY_8,
	HSB_TV_ACTION_KEY_9,
	HSB_TV_ACTION_LAST,
} HSB_TV_ACTION_T;

typedef enum {
	HSB_ACT_TYPE_REMOTE_CONTROL = 0,
	HSB_ACT_TYPE_ALARM,
} HSB_ACTION_TYPE_T;

typedef enum {
	HSB_IR_PROTOCOL_TYPE_CC9201 = 0,
	HSB_IR_PROTOCOL_TYPE_NEC,
	HSB_IR_PROTOCOL_TYPE_GREE,
	HSB_IR_PROTOCOL_TYPE_LAST,
} HSB_IR_PROTOCOL_TYPE_T;

#endif
