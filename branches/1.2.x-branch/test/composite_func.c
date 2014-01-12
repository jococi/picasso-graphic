#include "stdio.h"

#include "../include/picasso.h"
#include "drawFunc.h"

static ps_matrix* pm;
static ps_path * pa;
static ps_image * pi;
static ps_pattern * pt;
static int op = 0;
static int step = 0;
void draw_test (int id, ps_context* gc)
{
	ps_color col = {0, 0, 1, 0.8};
	ps_color sol = {1, 0, 0, 0.8};
    ps_rect cr = {2.7 , 3.4, 272.4, 261.3};
	ps_rect gr = {50.2, 48.8, 250.1, 224.5};

	ps_set_composite_operator(gc, (ps_composite)3);	
	ps_set_line_width(gc, 3);
	ps_rectangle(gc, &cr);
	ps_set_source_color(gc, &col);
	ps_paint(gc);

	ps_set_composite_operator(gc, (ps_composite)op);	
	ps_set_source_color(gc, &sol);
	ps_ellipse(gc, &gr);
	ps_fill(gc);
}

void init_context (ps_context* gc, ps_canvas* cs)
{
	float version = (float)ps_version() / 10000;
	fprintf(stderr, "picasso version %.2f\n", version);

    pa = ps_path_create();
    pm = ps_matrix_create();

    ps_translate(gc, 33, 35);
    ps_rotate(gc, 0.32);
}

void dini_context (ps_context* gc)
{
	ps_image_unref(pi);
    ps_matrix_unref(pm);
	ps_pattern_unref(pt);
    ps_path_unref(pa);
}

void set_image_data(unsigned char* data, ps_color_format fmt, int w, int h, int p)
{
	pi = ps_image_create_with_data(data, fmt, w, h, p);
}

void set_pattern_data(unsigned char* data, ps_color_format fmt, int w, int h, int p)
{
	ps_image* pam = ps_image_create_with_data(data, fmt, w, h, p);
	pt = ps_pattern_create_image(pam, WRAP_TYPE_REPEAT, WRAP_TYPE_REPEAT, pm);
}

void timer_action(ps_context* gc)
{
	step ++;
	if (step > 5) {
		op++;
		step = 0;
	}

	if (op > 27) op = 0;
}
