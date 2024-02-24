#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-x11.h>

#include <boost/format.hpp>
#include <functional>
#include <iostream>
#include "modules/dwm_c.hpp"

/* key definitions */
#define MODKEY Mod4Mask

extern unsigned int numlockmask;
extern Display* dpy;
extern void (*external_handler)(XEvent*);
extern const Key keys[500];

xkb_context *ctx = NULL;
xkb_keymap *keymap = NULL;
xcb_connection_t *xcb_conn = NULL;
int32_t device_id;
xkb_state *state = NULL;

void x_events_listener(XEvent* e) {
    if (e->type == KeyRelease) {
        const XKeyEvent& ev = e->xkey;
    } else if (e->type == KeyPress) {
        const XKeyEvent& ev = e->xkey;

        const KeySym keysym = XLookupKeysym(&e->xkey, 0);
        KeySym keysym2 = XkbKeycodeToKeysym(dpy, e->xkey.keycode, 1, 1);
        int group, level;
        for (group = 0; group < 5; group++) {
            for (level = 0; level < 5; level++) {
                keysym2 = XkbKeycodeToKeysym(dpy, e->xkey.keycode, group, level);
                if (keysym2) break;
            }
            if (keysym2) break;
        }

        char keysym_name[300];
        xkb_keysym_get_name(keysym, keysym_name, sizeof(keysym_name));

        log_info((
            boost::format("KeyPress: keysym_name = %1%")
            % keysym_name
        ).str().c_str());

        log_info((
            boost::format("KeyPress: keycode=%1%, state=%2%")
            % e->xkey.keycode % e->xkey.state
        ).str().c_str());
        log_info((
            boost::format("KeyPress: keysym1=%1%, keysym2=%2% (%3%, %4%)")
            % keysym % keysym2 % group % level
        ).str().c_str());

        for (int i = 0; i < LENGTH(keys); i++) {
            if (!keys[i].func) {
                continue;
            }
            if (keys[i].keysym == keysym && CLEANMASK(keys[i].mod) == CLEANMASK(ev.state)) {
                keys[i].func(&(keys[i].arg));
            }
        }
    }
}

int init_xkb() {
    int xkb_major_version = XkbMajorVersion,
        xkb_minor_version = XkbMinorVersion;
    if (XkbLibraryVersion(&xkb_major_version, &xkb_minor_version)) {
        log_info(
            "The versions of the compile time and run time libraries of xkb "
            "are compatible.");
    } else {
        log_info(
            "WARNING: the versions of the compile time and run time libraries "
            "of xkb are not compatible!");
    }
    log_info("xkb server version is: %d, %d", xkb_major_version,
             xkb_minor_version);
    int opcode_rtrn, event_rtrn, error_rtrn, major_in_out, minor_in_out;
    if (!XkbQueryExtension(dpy, &opcode_rtrn, &event_rtrn, &error_rtrn,
                           &major_in_out, &minor_in_out)) {
        log_info(
            "ERROR: the versions of the compile time and run time libraries "
            "of xkb are not compatible!");
        return 1;
    }
    log_info("xkb server version is: %d, %d", major_in_out, minor_in_out);

    xcb_conn = xcb_connect(NULL, NULL);

    if (int err_val = xcb_connection_has_error(xcb_conn)) {
        log_info((boost::format(
            "xcb_connection_has_error: %1%") % err_val
        ).str().c_str());
        return 1;
    }

    if (!xkb_x11_setup_xkb_extension(
        xcb_conn,
        XKB_X11_MIN_MAJOR_XKB_VERSION,
        XKB_X11_MIN_MINOR_XKB_VERSION,
        XKB_X11_SETUP_XKB_EXTENSION_NO_FLAGS,
        NULL, NULL,
        NULL, NULL
    )) {
        log_info((
            boost::format("X server doesn't have the XKB extension, version %1%.%2% or newer ")
            % XKB_X11_MIN_MAJOR_XKB_VERSION % XKB_X11_MIN_MINOR_XKB_VERSION
        ).str().c_str());
        return 1;
    }

    device_id = xkb_x11_get_core_keyboard_device_id(xcb_conn);
    log_info((boost::format(
        "xkb_x11_get_core_keyboard_device_id: device_id is %1%") % device_id
    ).str().c_str());
    if (device_id == -1) {
        return 1;
    }

    ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (!ctx) {
        log_info("ERROR: can not create xkb context!");
        return 1;
    }

    keymap = xkb_x11_keymap_new_from_device(ctx, xcb_conn, device_id, XKB_KEYMAP_COMPILE_NO_FLAGS);

    state = xkb_x11_state_new_from_device(keymap, xcb_conn, device_id);
    if (!state) {
        log_info("ERROR: can not create xkb state!");
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    log_info("------ dwm-" VERSION " starting... args:");
    for (int i = 0; i < argc; i++) {
        log_info("\targv[%d] is '%s'", i, argv[i]);
    }
    if (argc == 2 && !strcmp("-v", argv[1]))
        die("dwm-" VERSION);
    else if (argc != 1)
        die("usage: dwm [-v]");
    if (!setlocale(LC_CTYPE, "") || !XSupportsLocale())
        fputs("warning: no locale support\n", stderr);
    if (!(dpy = XOpenDisplay(NULL))) die("dwm: cannot open display");

    if (init_xkb()) {
        die("dwm: cannot init xkb");
    }

    checkotherwm();
    log_info("dwm setup...");
    setup();

    log_info("... finished dwm setup");
#ifdef __OpenBSD__
    if (pledge("stdio rpath proc exec", NULL) == -1) die("pledge");
#endif /* __OpenBSD__ */
    scan();
    log_info("run...");
    external_handler = x_events_listener;

    runautostart();
    run();

    log_info("cleanup...");
    cleanup();

    xkb_state_unref(state);
    xkb_keymap_unref(keymap);
    xkb_context_unref(ctx);
    xcb_disconnect(xcb_conn);

    XCloseDisplay(dpy);
    log_info("success eixt.");
}
