// TODO - Documentation

#ifndef __Color_hh
#define __Color_hh

#include <string>

namespace bt {

  // forward declarations
  class Display;
  class PenCache;

  /*
    The color object.  Colors are stored in rgb format (screen
    independent).  Screen dependent pixel values can be obtained using
    the pixel() function.
  */
  class Color {
  public:
    /*
      Frees unused colors on all screens.
     */
    static void clearCache(void);

    /*
      Returns the named color on the specified display and screen.  If
      the color couldn't be found, an invalid color is returned.
    */
    static Color namedColor(const Display &display, unsigned int screen,
                            const std::string &colorname);

    explicit inline Color(int r = -1, int g = -1, int b = -1)
      : _red(r), _green(g), _blue(b),
        _screen(~0u), _pixel(0ul)
    { }

    inline Color(const Color &c)
      : _red(c._red), _green(c._green), _blue(c._blue),
        _screen(~0u), _pixel(0ul)
    { }

    inline ~Color(void)
    { deallocate(); }


    /** ACCESSORS FOR PVT VARS */
    inline int   red(void) const { return _red; }

    inline int green(void) const { return _green; }

    inline int  blue(void) const { return _blue; }

    /** UTILITY FUNCS */
    inline void setRGB(int r, int g, int b) { deallocate(); _red = r; _green = g; _blue = b; }

    unsigned long pixel(unsigned int screen) const;

    inline bool valid(void) const { return _red != -1 && _green != -1 && _blue != -1; }

    // operator overrides
    // TODO - This should be moved to a utils class later on.
    // Should not be made specific to this class. (ColorUtils)
    inline Color &operator=(const Color &c) { setRGB(c._red, c._green, c._blue); return *this; }
    inline bool operator==(const Color &c) const { return _red == c._red && _green == c._green && _blue == c._blue; }
    inline bool operator!=(const Color &c) const { return !operator==(c); }

  private:

    /** Used for cleanup */
    void deallocate(void);

    /** Private variables */
    int _red, _green, _blue;

    /* Screen id we're using */
    mutable unsigned int _screen;

    /* Pixel id we're referencing */
    mutable unsigned long _pixel;

    /* Cache utils class. */
    friend class PenCache;
  };

} // namespace bt

#endif // __Color_hh
