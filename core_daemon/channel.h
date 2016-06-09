
#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <glib.h>
#include <stdint.h>
#include "hsb_config.h"

typedef struct {
	char		name[HSB_CHANNEL_MAX_NAME_LEN];
	uint32_t	id;
} HSB_CHANNEL_T;

typedef struct {
	GQueue	queue;
	GMutex	mutex;
} HSB_CHANNEL_DB_T;

int init_channel(HSB_CHANNEL_DB_T *db);
int set_channel(HSB_CHANNEL_DB_T *db, char *name, uint32_t cid);
int del_channel(HSB_CHANNEL_DB_T *db, char *name);
int get_channel(HSB_CHANNEL_DB_T *db, char *name, uint32_t *cid);


#endif /* _CHANNEL_H_ */
