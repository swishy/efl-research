#ifndef CANVAS_H_
#define CANVAS_H_

void ekeko_canvas_renderable_add(Ekeko_Canvas *c, Ekeko_Renderable *r);
void ekeko_canvas_damage_add_internal(Ekeko_Canvas *c, Eina_Rectangle *r);

//void ekeko_canvas_change(Ekeko_Canvas *c);
//void ekeko_canvas_input_add(Ekeko_Canvas *c, Ekeko_Input *i);
//Ekeko_Renderable * ekeko_canvas_object_get_at_coordinate(Ekeko_Canvas *c, unsigned int x, unsigned int y);

#endif