

#include <string.h>
#include <glib.h>
#include <pthread.h>
#include <errno.h>
#include "device.h"
#include "network_utils.h"
#include "debug.h"
#include "thread_utils.h"
#include "device.h"
#include "hsb_error.h"
#include "hsb_config.h"
#include "channel.h"

static HSB_DEV_DRV_T ir_drv;
static HSB_DEV_OP_T cc9201_op;
static HSB_DEV_DRV_OP_T ir_drv_op;

typedef struct {
	// TODO: channel mapping
} CC9201_DATA_T;

static uint8_t cc9201_key_map[HSB_TV_ACTION_LAST] = {
	0x1,	// TODO
	0x1,	// TODO
	0x2,
	0x43,
	0x42,
	0x1,	// TODO
	0x1,
	0x1,
	0x1,
	0x1,
	0x30,
	0x31,
	0x32,
	0x33,
	0x34,
	0x35,
	0x36,
	0x37,
	0x38,
	0x39,
};

static int cc9201_key_press(HSB_DEV_T *ir_dev, HSB_TV_ACTION_T action)
{
	if (!ir_dev || action >= HSB_TV_ACTION_LAST)
		return HSB_E_BAD_PARAM;

	HSB_ACTION_T act = { 0 };

	act.devid = ir_dev->id;
	act.id = HSB_ACT_TYPE_REMOTE_CONTROL;
	act.param1 = HSB_IR_PROTOCOL_TYPE_CC9201;
	act.param2 = cc9201_key_map[action];

	return set_action(ir_dev, &act);
}


static int cc9201_init(void **priv)
{
	HSB_CHANNEL_DB_T *pdb = g_slice_new0(HSB_CHANNEL_DB_T);
	if (!pdb)
		return HSB_E_NO_MEMORY;
	
	init_channel(pdb);

	*priv = pdb;

	return HSB_E_OK;
}

static int cc9201_release(void *priv)
{
	g_slice_free(HSB_CHANNEL_DB_T, priv);

	return HSB_E_OK;
}

static int cc9201_set_status(const HSB_STATUS_T *status)
{
	HSB_DEV_T *pdev = find_dev(status->devid);

	if (!pdev)
		return HSB_E_OTHERS;

	HSB_DEV_T *irdev = pdev->ir_dev;
	if (!irdev)
		return HSB_E_OTHERS;

	
	switch (status->id[0]) {
		case HSB_TV_STATUS_CHANNEL:
		{
			uint32_t channel = status->val[0];
			int id;

			id = (channel / 100) % 10;
			cc9201_key_press(irdev, HSB_TV_ACTION_KEY_0 + id);
			usleep(200000);

			id = (channel / 10) % 10;
			cc9201_key_press(irdev, HSB_TV_ACTION_KEY_0 + id);
			usleep(200000);

			id = channel % 10;
			cc9201_key_press(irdev, HSB_TV_ACTION_KEY_0 + id);

			pdev->status[HSB_TV_STATUS_CHANNEL] = channel;
			break;
		}
		default:
			break;
	}

	return HSB_E_OK;
}

static int cc9201_get_status(HSB_STATUS_T *status)
{
	HSB_DEV_T *pdev = find_dev(status->devid);

	if (!pdev)
		return HSB_E_OTHERS;

	uint32_t id = status->id[0];
	if (id >= HSB_TV_STATUS_LAST)
		return HSB_E_OTHERS;

	status->val[0] = pdev->status[id];
	status->num = 1;

	return HSB_E_OK;
}

static int cc9201_set_action(const HSB_ACTION_T *act)
{
	HSB_DEV_T *pdev = find_dev(act->devid);

	if (!pdev)
		return HSB_E_OTHERS;

	HSB_DEV_T *irdev = pdev->ir_dev;
	if (!irdev)
		return HSB_E_OTHERS;

	return cc9201_key_press(irdev, act->param1);
}

static int cc9201_get_channel_db(HSB_DEV_T *pdev, HSB_CHANNEL_DB_T **pdb)
{
	*pdb = (HSB_CHANNEL_DB_T *)pdev->priv_data;

	return HSB_E_OK;
}

static int ir_add_dev(HSB_DEV_TYPE_T ir_type)
{
	uint32_t devid;
	HSB_DEV_INFO_T dev_info = { 0 };
	dev_info.interface = HSB_INTERFACE_IR;
	dev_info.dev_type = ir_type;

	HSB_DEV_OP_T *op = NULL;
	// ir_type to dev op
	switch (ir_type) {
		case HSB_DEV_TYPE_CC9201:
			dev_info.cls = HSB_DEV_CLASS_STB;
			op = &cc9201_op;
			break;
		default:
			break;
	}

	if (!op)
		return HSB_E_NOT_SUPPORTED;

	void *priv = NULL;
	int ret;
	if (op->init) {
		ret = op->init(&priv);
		if (ret != HSB_E_OK)
			return ret;
	}

	ret = dev_online(ir_drv.id, &dev_info, &devid, op, priv);
	if (HSB_E_OK != ret)
		return ret;

	return HSB_E_OK;
}

static HSB_DEV_OP_T cc9201_op = {
	cc9201_get_status,
	cc9201_set_status,
	cc9201_set_action,
	cc9201_init,
	cc9201_release,
	cc9201_get_channel_db,
};

static HSB_DEV_DRV_OP_T ir_drv_op = {
	NULL,
	ir_add_dev,
};

static HSB_DEV_DRV_T ir_drv = {
	"cg ir",
	HSB_DRV_ID_IR,
	&ir_drv_op,
};

int init_ir_drv(void)
{
	return register_dev_drv(&ir_drv);
}



