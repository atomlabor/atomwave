#include <pebble.h>
#include <stdlib.h> 

static Window *s_main_window;
static Layer *s_canvas_layer;
static Layer *s_air_layer;
static Layer *s_water_layer;

static char s_time_buffer[10];
static char s_date_buffer[32];
static char s_batt_buffer[20];

static GFont s_custom_font_time = NULL;
static GFont s_use_font_date, s_use_font_batt;

static GBitmap *s_sub_bitmap = NULL;
static int s_sub_x = -200; 
static AppTimer *s_sub_timer = NULL;

static int s_water_level_y = 0;

#define NUM_STARS 60
typedef struct { int16_t x, y; uint8_t size; } Star;
static Star s_stars[NUM_STARS];

static bool s_has_shooting_star = false; 
static int s_shooting_star_progress = 0; 
static int s_shooting_star_start_y = 0;  

#define NUM_PARTICLES 10
typedef struct { int16_t x, y, speed, radius; } Particle;
static Particle s_particles[NUM_PARTICLES];

static GPath *s_wave_path = NULL;
#define NUM_WAVE_POINTS 15 
static GPoint s_wave_points[NUM_WAVE_POINTS + 2]; 
static GPathInfo WAVE_PATH_INFO = { .num_points = NUM_WAVE_POINTS + 2, .points = s_wave_points };

static AppTimer *s_anim_timer = NULL;
static int s_animation_frame = 0;
static bool s_is_animating = false;
static BatteryChargeState s_battery_state;

static int random_range(int min, int max) { return (rand() % (max - min + 1)) + min; }

static void get_german_date(struct tm *t, char *buffer, size_t buffer_size) {
  const char* sys_locale = i18n_get_system_locale();
  if (strncmp(sys_locale, "de", 2) == 0) {
    const char* tage[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
    snprintf(buffer, buffer_size, "%s %02d.%02d.", tage[t->tm_wday], t->tm_mday, t->tm_mon + 1);
  } else {
    strftime(buffer, buffer_size, "%a %m/%d", t);
  }
}

static void update_time_data() {
  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);

  if (clock_is_24h_style()) {
    strftime(s_time_buffer, sizeof(s_time_buffer), "%H:%M", t);
  } else {
    int hour = t->tm_hour % 12;
    if (hour == 0) hour = 12;
    snprintf(s_time_buffer, sizeof(s_time_buffer), "%d:%02d", hour, t->tm_min);
  }

  get_german_date(t, s_date_buffer, sizeof(s_date_buffer));
  snprintf(s_batt_buffer, sizeof(s_batt_buffer), "%d%% PWR", s_battery_state.charge_percent);
  
  if (s_main_window) {
    GRect bounds = layer_get_bounds(window_get_root_layer(s_main_window));
    s_water_level_y = bounds.size.h - (t->tm_min * bounds.size.h / 60);
    layer_mark_dirty(window_get_root_layer(s_main_window));
  }
}

static void sub_timer_callback(void *data) {
  if (s_sub_x > -150) {
    s_sub_x -= 3; 
    layer_mark_dirty(s_water_layer);
    s_sub_timer = app_timer_register(33, sub_timer_callback, NULL);
  } else {
    s_sub_x = -200;
    s_sub_timer = NULL;
  }
}

static void anim_timer_callback(void *data) {
  if (s_animation_frame < 100) { 
    s_animation_frame++;
    
    if (s_has_shooting_star) {
      s_shooting_star_progress += 8;
    }

    GRect bounds = layer_get_bounds(s_canvas_layer);
    for(int i = 0; i < NUM_PARTICLES; i++) {
      s_particles[i].y -= s_particles[i].speed; 
      if(s_particles[i].y < 0) { 
        s_particles[i].y = bounds.size.h; 
        s_particles[i].x = random_range(0, bounds.size.w); 
      }
    }
    layer_mark_dirty(window_get_root_layer(s_main_window));
    s_anim_timer = app_timer_register(50, anim_timer_callback, NULL);
  } else {
    s_is_animating = false; 
    s_animation_frame = 0; 
    s_has_shooting_star = false;
    s_anim_timer = NULL;
    layer_mark_dirty(window_get_root_layer(s_main_window)); 
  }
}

static void trigger_animation() {
  if (!s_is_animating) {
    s_is_animating = true; 
    s_animation_frame = 0;
    
    if ((rand() % 10) < 3) {
      s_has_shooting_star = true;
      s_shooting_star_progress = 0;
      s_shooting_star_start_y = random_range(10, 60); 
    } else {
      s_has_shooting_star = false;
    }

    if(s_anim_timer) app_timer_cancel(s_anim_timer);
    s_anim_timer = app_timer_register(50, anim_timer_callback, NULL);
  }
}

static void battery_callback(BatteryChargeState state) { s_battery_state = state; update_time_data(); }

static void tap_handler(AccelAxisType axis, int32_t direction) { 
  trigger_animation(); 

  if (s_sub_timer == NULL) {
      if (s_sub_bitmap) {
         GRect bounds = layer_get_bounds(window_get_root_layer(s_main_window));
         GRect sub_bounds = gbitmap_get_bounds(s_sub_bitmap);
         
         int sub_top_y = bounds.size.h - sub_bounds.size.h - 15;
         
         if (s_water_level_y < (sub_top_y - 5)) {
            s_sub_x = bounds.size.w;
            sub_timer_callback(NULL);
         }
      }
  }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) { 
  update_time_data(); 
  
  if (tick_time->tm_min % 15 == 0) {
    trigger_animation();
  }

  if (s_sub_timer == NULL && (rand() % 60 == 0)) {
    if (s_sub_bitmap) {
       GRect bounds = layer_get_bounds(window_get_root_layer(s_main_window));
       GRect sub_bounds = gbitmap_get_bounds(s_sub_bitmap);
       
       int sub_top_y = bounds.size.h - sub_bounds.size.h - 15;
       
       if (s_water_level_y < (sub_top_y - 5)) {
          s_sub_x = bounds.size.w;
          sub_timer_callback(NULL);
       }
    }
  }
}

static void draw_text_common(GContext *ctx, Layer *layer, GColor color) {
  GRect bounds = layer_get_bounds(window_get_root_layer(s_main_window));
  GRect layer_frame = layer_get_frame(layer);
  graphics_context_set_text_color(ctx, color);
  
  int time_h = 50; 
  int date_h = 30; 
  int batt_h = 24; 
  int quote_h = 20; 
  int spacing = 2;
  
  int total_content_height = time_h + date_h + batt_h + (spacing * 2);
  int start_y = (bounds.size.h - total_content_height) / 2;
  int offset_y = layer_frame.origin.y;

  GFont font_time = s_custom_font_time ? s_custom_font_time : fonts_get_system_font(FONT_KEY_LECO_32_BOLD_NUMBERS);
  GRect time_rect = GRect(-10, start_y - offset_y, bounds.size.w + 20, time_h);
  graphics_draw_text(ctx, s_time_buffer, font_time, time_rect, GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  
  graphics_draw_text(ctx, s_date_buffer, s_use_font_date, GRect(0, start_y + time_h + spacing - offset_y, bounds.size.w, date_h), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  
  graphics_draw_text(ctx, s_batt_buffer, s_use_font_batt, GRect(0, start_y + time_h + date_h + (spacing * 2) - offset_y, bounds.size.w, batt_h), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);

  time_t temp = time(NULL);
  struct tm *t = localtime(&temp);
  
  if (t->tm_min == 0) {
    GFont quote_font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
    GRect quote_rect = GRect(0, start_y + time_h + date_h + batt_h + (spacing * 3) - offset_y, bounds.size.w, quote_h);
    graphics_draw_text(ctx, "we all live in a ...", quote_font, quote_rect, GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);
  }
}

static void air_update_proc(Layer *layer, GContext *ctx) { 
  graphics_context_set_fill_color(ctx, COLOR_FALLBACK(GColorIcterine, GColorWhite)); 
  int safe_sky_limit = s_water_level_y - 10;

  for (int i = 0; i < NUM_STARS; i++) {
    if (s_stars[i].y < safe_sky_limit) {
      if (s_stars[i].size == 1) {
         graphics_draw_pixel(ctx, GPoint(s_stars[i].x, s_stars[i].y));
      } else {
         graphics_fill_circle(ctx, GPoint(s_stars[i].x, s_stars[i].y), 1);
      }
    }
  }

  if (s_has_shooting_star) {
    int start_x = -20 + s_shooting_star_progress;
    int start_y = s_shooting_star_start_y + (s_shooting_star_progress / 3); 
    int tail_len = 25; 
    graphics_context_set_stroke_color(ctx, GColorWhite);
    graphics_context_set_stroke_width(ctx, 2);
    graphics_draw_line(ctx, GPoint(start_x, start_y), GPoint(start_x - tail_len, start_y - (tail_len / 3)));
  }

  draw_text_common(ctx, layer, GColorWhite); 
}

static void water_update_proc(Layer *layer, GContext *ctx) { 
  GRect layer_frame = layer_get_frame(layer);
  GRect root_bounds = layer_get_bounds(window_get_root_layer(s_main_window));
  int offset_y = layer_frame.origin.y;
  
  if (s_sub_bitmap && s_sub_x > -150) {
    GRect sub_bounds = gbitmap_get_bounds(s_sub_bitmap);
    
    int fixed_y_pos = root_bounds.size.h - sub_bounds.size.h - 15;
    
    if (s_water_level_y < fixed_y_pos) {
        graphics_context_set_compositing_mode(ctx, GCompOpSet);
        graphics_draw_bitmap_in_rect(ctx, s_sub_bitmap, GRect(s_sub_x, fixed_y_pos - offset_y, sub_bounds.size.w, sub_bounds.size.h));
        graphics_context_set_compositing_mode(ctx, GCompOpAssign); 
    }
  }

  if (s_is_animating) { 
    graphics_context_set_fill_color(ctx, GColorWhite);
    for (int i = 0; i < NUM_PARTICLES; i++) {
      graphics_fill_circle(ctx, GPoint(s_particles[i].x, s_particles[i].y - offset_y), s_particles[i].radius);
    }
  }
  
  draw_text_common(ctx, layer, GColorBlack); 
}

static void canvas_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  int base_y = s_water_level_y; 
  int amp = s_is_animating ? 12 : 0;
  int phase = s_animation_frame * 1000;

  s_wave_points[0] = GPoint(bounds.size.w, bounds.size.h);
  s_wave_points[1] = GPoint(0, bounds.size.h);
  for (int i = 0; i < NUM_WAVE_POINTS; i++) {
    int x = (bounds.size.w * i) / (NUM_WAVE_POINTS - 1);
    int y_wave = base_y + (s_is_animating ? (sin_lookup((x * 400) + phase) * amp / TRIG_MAX_RATIO) : 0);
    s_wave_points[i + 2] = GPoint(x, y_wave);
  }

  GColor water_color = (s_battery_state.charge_percent > 50) ? COLOR_FALLBACK(GColorElectricUltramarine, GColorDarkGray) :
                       (s_battery_state.charge_percent > 20) ? COLOR_FALLBACK(GColorChromeYellow, GColorDarkGray) :
                                                              COLOR_FALLBACK(GColorShockingPink, GColorLightGray);
  
  graphics_context_set_fill_color(ctx, water_color);
  gpath_draw_filled(ctx, s_wave_path);

  layer_set_frame(s_air_layer, GRect(0, 0, bounds.size.w, base_y + amp)); 
  layer_set_frame(s_water_layer, GRect(0, base_y - amp, bounds.size.w, bounds.size.h - (base_y - amp)));

  graphics_context_set_stroke_color(ctx, GColorWhite);
#if defined(PBL_COLOR)
  graphics_context_set_stroke_width(ctx, 2);
#endif
  for (int i = 2; i < NUM_WAVE_POINTS + 1; i++) {
    graphics_draw_line(ctx, s_wave_points[i], s_wave_points[i+1]);
  }
}

static void main_window_load(Window *window) {
  Layer *root = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(root);
  srand(time(NULL));

  for (int i = 0; i < NUM_STARS; i++) {
    s_stars[i].x = random_range(0, bounds.size.w);
    s_stars[i].y = random_range(0, bounds.size.h); 
    s_stars[i].size = (rand() % 10) > 7 ? 2 : 1;   
  }

  for (int i = 0; i < NUM_PARTICLES; i++) {
    s_particles[i].x = random_range(0, bounds.size.w);
    s_particles[i].y = random_range(bounds.size.h, bounds.size.h + 100);
    s_particles[i].speed = random_range(2, 5);
    s_particles[i].radius = random_range(1, 3);
  }

  s_wave_path = gpath_create(&WAVE_PATH_INFO);
  s_canvas_layer = layer_create(bounds); layer_set_update_proc(s_canvas_layer, canvas_update_proc); layer_add_child(root, s_canvas_layer);
  s_air_layer = layer_create(bounds); layer_set_update_proc(s_air_layer, air_update_proc); layer_add_child(root, s_air_layer);
  s_water_layer = layer_create(bounds); layer_set_update_proc(s_water_layer, water_update_proc); layer_add_child(root, s_water_layer);

  s_custom_font_time = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_CUSTOM_FONT_42));
  s_use_font_date = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_use_font_batt = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_sub_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SUBMARINE);

  s_battery_state = battery_state_service_peek();
  update_time_data();
}

static void main_window_unload(Window *window) {
  if (s_anim_timer) app_timer_cancel(s_anim_timer);
  if (s_sub_timer) app_timer_cancel(s_sub_timer);
  if (s_custom_font_time) fonts_unload_custom_font(s_custom_font_time);
  if (s_sub_bitmap) gbitmap_destroy(s_sub_bitmap);
  gpath_destroy(s_wave_path); layer_destroy(s_canvas_layer); layer_destroy(s_air_layer); layer_destroy(s_water_layer);
}

static void init() {
  s_main_window = window_create();
  window_set_background_color(s_main_window, GColorBlack);
  window_set_window_handlers(s_main_window, (WindowHandlers) { .load = main_window_load, .unload = main_window_unload });
  window_stack_push(s_main_window, true);
  
  battery_state_service_subscribe(battery_callback);
  accel_tap_service_subscribe(tap_handler);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() { window_destroy(s_main_window); }

int main() { init(); app_event_loop(); deinit(); }