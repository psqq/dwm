
Original: [https://dwm.suckless.org/](https://dwm.suckless.org/)

This project based on dwm 6.4

See also: [https://github.com/psqq/dwm-scripts](https://github.com/psqq/dwm-scripts)

# build and install

```bash
cd ~
git clone https://github.com/psqq/dwm
cd dwm
make build
make install
```

# configuration

Install [https://github.com/psqq/dwm-scripts](https://github.com/psqq/dwm-scripts).

Copy `src/config.example.h` to `src/config.h` and change `DWM_SCRIPTS_DIR`.

Add to `.xinitrc`:

```bash
exec ~/dwm-scripts/startdwm
```

Example script that will run when `dwm` starts in `~/.dwm/autostart.sh` (patch: [https://dwm.suckless.org/patches/autostart/](https://dwm.suckless.org/patches/autostart/)):

```bash
~/dwm-scripts/dwm-logs.sh
picom &
copyq &
flameshot &
if [ -x /usr/bin/nm-applet ] ; then
  nm-applet --sm-disable &
fi
python ~/dwm-scripts/kb_layout.py set us &
~/dwm-scripts/set-random-wallpapers.sh ~/Wallpapers/WideWall &
python ~/dwm-scripts/status_bar.py loop $DISPLAY &

```

# Testing with Xephyr

You can use `Xephyr` for test runs:

```sh
DWM_PATH=/abs/path/to/dwm/build/dwm startx -- /usr/bin/Xephyr -br -ac -noreset -screen 800x600 :1
```

`.xinitrc`:

```sh
if ! [ -z ${DWM_PATH+x} ]; then
  exec $DWM_PATH
  exit
fi;

exec ~/dwm-scripts/startdwm
```

# Running with restart and logs support

`~/dwm-scripts/startdwm`:

```bash
#!/bin/bash

ssh-agent dwm 1>>~/.dwm.log 2>>~/.dwm.error.log
```

`.xinitrc`:

```bash
exec ~/dwm-scripts/startdwm
```

# lsp

`clangd` used for lsp.

# todo

- [ ] Справка и способ получения справки по горячей клавише
- [ ] перенести весь код на C++

# bugs

- [ ] когда открыто модальное/плавающее окно не перемещать фокус на движение мыши (copyq)
  - [ ] добавить также хоткей, который обратно перемещает фокус на горячую клавишу
- [ ] окно в фулскрине не перемещается на другой монитор
