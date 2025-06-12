#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "m_utils.h"
#include "object.h"

static uint32_t num_objs = 0;
static object_t* head = NULL;
static object_t* tail = NULL;

object_t* OBJ_GetFirstObj()
{
	return head;
}

object_t* OBJ_GetLastObj()
{
	return tail ? tail : head;
}

static void OBJ_PutInTheList(object_t* obj)
{
	if (!head)
	{
		obj->next = NULL;
		obj->prev = NULL;
		head = obj;
		tail = obj;
		num_objs++;
		return;
	}
	
	tail->next = obj;
	obj->prev = tail;
	obj->next = NULL;
	tail = obj;
	num_objs++;
}

object_t* OBJ_Create(uint8_t type, float x, float y, uint16_t angle)
{
	object_t* obj = (object_t*)malloc(sizeof(object_t));
	if (!obj) return NULL;
	memset(obj, 0, sizeof(object_t));
	
	obj->type = type;
	obj->x = x;
	obj->y = y;
	obj->speed = 0;
	obj->w = 8;
	obj->h = 8;
	obj->r = 0;
	obj->g = 0;
	obj->b = 0;
	obj->angle = angle;
	
	OBJ_PutInTheList(obj);
	
	return obj;
}

static void OBJ_RemoveFromList(object_t* obj)
{
	if (!obj) return;
	object_t* prev = obj->prev;
	object_t* next = obj->next;
	
	if (prev) prev->next = next;
	if (next) next->prev = prev;
}

void OBJ_Remove(object_t** obj)
{
	if (!obj || !*obj) return;
	
	if (*obj == head)
	{
		head = head->next;
		if (head) head->prev = NULL;
	}
	else if (*obj == tail)
	{
		tail = tail->prev;
		if (tail) tail->next = NULL;
	}
	else
	{
		OBJ_RemoveFromList(*obj);
	}
	
	free(*obj);
	*obj = NULL;
	num_objs--;
}

void OBJ_ClearList()
{
	object_t* aux;
	while(head)
	{
		aux = head;
		head = head->next;
		aux->prev = NULL;
		aux->next = NULL;
		free(aux);
	}
	head = NULL;
	tail = NULL;
	num_objs = 0;
}

void OBJ_Update()
{
	object_t* aux = head;
	while(aux)
	{
		//if the object is out of bounds, remove it
		if (aux->x < 0 || aux->x > SCREENWIDTH || aux->y < 0 || aux->y > SCREENHEIGHT)
		{
			aux->speed = 0;
			object_t* aux2 = aux;
			aux = aux->next;
			OBJ_Remove(&aux2);
			continue;
		}
		
		//Update X, Y positions
		aux->x += COS(aux->angle)*aux->speed;
		aux->y += SIN(aux->angle)*aux->speed;
		
		aux = aux->next;
	}
}