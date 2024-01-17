# Howling Thunder C++

Howling Thunder (originally named Rolling Thunder) is an arcade game I made in 2017 for iOS.
Unfortunatelly, it got removed from the AppStore for not being updated for too long, and the UI breaks on newer devices,
so I didn't bother on just relaunching it as-it-is.

This is a C++ port I was working on for some time to achieve cross-platform compatibility, so I could run it on Android too.
It's built on top of the *Axmol* engine, which is a hard fork of the long unmaintained and forsaken *Cocos2d-x*.

> "R.I.P Cocos2d" -- *OG mobile game devs*

One day I might return and finish it, but now I have other priorities. I made the code public because pixel art never dies.

I made some tweaks to the engine itself (not uploaded here) changing the default texture graphics filtering of the GL renderer,
so that pixel art sprites are first-class citizens. Running this project without it will result in sprites blurried by bilinear filtering.

## Pixel Art Never Dies

As said, pixel art never dies.
