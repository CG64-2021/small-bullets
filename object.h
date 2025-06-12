#ifndef __OBJECT_H__
#define __OBJECT_H__

typedef enum
{
	OBJ_NONE=0,
	OBJ_SPAWNER,
	OBJ_BULLET,
	OBJ_NUMTYPES
} obj_type_t;

typedef struct object_s
{
	obj_type_t type;
	float x, y, speed;
	uint16_t w, h, angle;
	uint8_t r, g, b;
	struct object_s* next;
	struct object_s* prev;
} object_t;

object_t* OBJ_GetFirstObj();
object_t* OBJ_GetLastObj();
object_t* OBJ_Create(uint8_t type, float x, float y, uint16_t angle);
void OBJ_Remove(object_t** obj);
void OBJ_ClearList();
void OBJ_Update();

#endif