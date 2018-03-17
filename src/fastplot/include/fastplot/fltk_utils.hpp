/* 
 * fltk_utils.hpp
 * 
 * Created on: Mar 16, 2018 16:51
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef FLTK_UTILS_HPP
#define FLTK_UTILS_HPP

#include <functional>

#include <FL/x.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>

#include <cairo.h>
#ifdef WIN32
#include <cairo-win32.h>
#elif defined(__APPLE__)
#include <cairo-quartz.h>
#else
#include <cairo-xlib.h>
#endif

namespace librav
{
class FltkCanvas : public Fl_Box
{
public:
  FltkCanvas(int x, int y, int w, int h);

  using CallBackFunc_t = std::function<void(cairo_t *cr, double, double, double, double)>;

public:
  virtual void graphic(cairo_t *cr, double, double, double, double);
  void SaveToPNG(const char *filename, int, int);
  void SaveToSVG(const char *filename, int, int);
  void SaveToEPS(const char *filename, int, int);
  void SaveToPDF(const char *filename, int, int);

  void star(cairo_t *cr, double radius);
  void SetDrawCallback(CallBackFunc_t func);

private:
  // callback function for cario plotting
  std::function<void(cairo_t *cr, double, double, double, double)> cairo_callback_;

  // draw function for box
  void draw(void);
  // this function creates a surface for current platform (win/linux/mac)
  cairo_surface_t *cairo_gui_surface_create(int wo, int ho);
};

class FltkWindow
{
public:
  FltkWindow() = default;
  ~FltkWindow() = default;

  void SetupWindow();

  const int w = 700;
  const int h = 600;
  const int sp = 5;
  const int bw = 75;
  const int bh = 25;

  const int wpts = 175; // width in points
  const int hpts = 175; // height in points
  const int wpix = 175; // width in pixels
  const int hpix = 175; // height in pixels

  Fl_Group *buttons;
  Fl_Button *quit;
  Fl_Button *png;
  Fl_Button *svg;
  Fl_Button *eps;
  Fl_Button *pdf;
  Fl_Box *spacer;
  FltkCanvas *canvas;
  Fl_Double_Window *win;

  void cb_Quit(Fl_Button *, void *);
  void cb_to_png(Fl_Button *, void *);
  void cb_to_svg(Fl_Button *, void *);
  void cb_to_eps(Fl_Button *, void *);
  void cb_to_pdf(Fl_Button *, void *);

  void run();
};
}

#endif /* FLTK_UTILS_HPP */