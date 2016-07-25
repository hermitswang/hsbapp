
#include <glib.h>
#include <stdint.h>
#include <stdbool.h>
#include "scene.h"
#include "hsb_error.h"

static GQueue scene_q;

int init_scene(void)
{
	g_queue_init(&scene_q);

	return HSB_E_OK;
}

static HSB_SCENE_T *find_scene(char *name)
{
	int id;
	GQueue *queue = &scene_q;
	int len = g_queue_get_length(queue);
	HSB_SCENE_T *scene = NULL;

	for (id = 0; id < len; id++) {
		scene = (HSB_SCENE_T *)g_queue_peek_nth(queue, id);
		if (0 == strcmp(scene->name, name))
			return scene;
	}

	return NULL;
}

HSB_SCENE_T *alloc_scene(void)
{
	HSB_SCENE_T *pscene = g_slice_new0(HSB_SCENE_T);

	return pscene;
}

static int free_scene(HSB_SCENE_T *scene)
{
	g_slice_free(HSB_SCENE_T, scene);

	return HSB_E_OK;
}

int add_scene(HSB_SCENE_T *scene)
{
	GQueue *queue = &scene_q;
	HSB_SCENE_T *pscene = find_scene(scene->name);
	if (pscene) {
		del_scene(scene->name);
	}

	g_queue_push_tail(queue, scene);

	return HSB_E_OK;
}

int del_scene(char *name)
{
	GQueue *queue = &scene_q;
	HSB_SCENE_T *scene = find_scene(name);
	if (!scene)
		return HSB_E_BAD_PARAM;

	g_queue_remove(queue, scene);

	free_scene(scene);

	return HSB_E_OK;
}

int enter_scene(char *name)
{
	// TODO
}

int get_scene_num(uint32_t *num)
{
	GQueue *queue = &scene_q;

	return g_queue_get_length(queue);
}

int get_scene(int id, HSB_SCENE_T **scene)
{
	GQueue *queue = &scene_q;
	int len = g_queue_get_length(queue);

	if (id >= len)
		return HSB_E_BAD_PARAM;

	HSB_SCENE_T *pscene = g_queue_peek_nth(queue, id);

	*scene = pscene;

	return HSB_E_OK;
}


